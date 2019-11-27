#include "WScene.hpp"
#include "GameObject.hpp"

namespace sfs {
WScene::WScene(const std::string &name, uint32_t fps) noexcept
	: Scene(name, fps)
	, _window()
	, _subscribedEvents()
{
	auto &v = sf::VideoMode::getFullscreenModes();

	_window.create(v[0], _name, sf::Style::Close | sf::Style::Fullscreen);
	_window.setFramerateLimit(fps);
}

void WScene::callSubscribedEvents() noexcept
{
	sf::Event event;

	while (_window.pollEvent(event))
		for (auto &i : _subscribedEvents[event.type])
			i->onEvent(*this, event);
}

void WScene::deleteGameObjectEvents(GameObject *object) noexcept
{
	auto &v = object->getSubscribedEvents();

	for (auto &&i : v) {
		auto &sv = _subscribedEvents[i];
		sv.erase(std::remove(sv.begin(), sv.end(), object));
	}
	v.clear();
}

void WScene::deleteUpdate(std::vector<std::unique_ptr<GameObject>> &v) noexcept
{
	for (auto it = v.begin(); it != v.end(); ++it) {
		auto &go = *it->get();
		if (go.toDestroy()) {
			deleteGameObjectEvents(it->get());
			it = v.erase(it);
			if (it-- == v.end())
				return;
			continue;
		}
		auto &components = go.getComponents();
		go.update(*this);
		for (auto cit = components.begin(); cit != components.end(); ++cit) {
			auto &c = *cit->get();
			if (c.toDestroy()) {
				cit = components.erase(cit);
				if (cit-- == components.end())
					break;
				continue;
			}
			c.update(*this, go);
			c.display(_window);
		}
	}
}

void WScene::run() noexcept
{
	_running = true;
	_clock.reset();
	while (_running) {
		_window.clear();
		callSubscribedEvents();
		insertToAddObjects();
		for (auto rit = _layeredObjects.rbegin(); rit != _layeredObjects.rend(); ++rit) {
			deleteUpdate(*rit);
		}
		_clock.refreshDeltaTime();
		_window.display();
	}
	_window.close();
}

sf::RenderWindow *WScene::getWindow() noexcept
{
	return &_window;
}

void WScene::framerate(uint32_t framerate) noexcept
{
	Scene::framerate(framerate);
	_window.setFramerateLimit(framerate);
}

void WScene::subscribe(GameObject &object, const sf::Event::EventType &type) noexcept
{
	for (auto &&i : _subscribedEvents[type])
		if (i == &object)
			return;
	_subscribedEvents[type].push_back(&object);
	object.getSubscribedEvents().push_back(type);
}

void WScene::unsubscribe(GameObject &object, const sf::Event::EventType &type) noexcept
{
	for (auto it = _subscribedEvents[type].begin(); it != _subscribedEvents[type].end(); ++it) {
		if (*it == &object) {
			_subscribedEvents[type].erase(it);
			auto &sv = object.getSubscribedEvents();
			sv.erase(std::remove(sv.begin(), sv.end(), type));
			return;
		}
	}
}
} // namespace sfs
