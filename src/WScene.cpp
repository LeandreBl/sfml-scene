#include "WScene.hpp"
#include "GameObject.hpp"

namespace sfs
{
WScene::WScene(const std::string &name, uint32_t fps) noexcept
    : Scene(name, fps), _window(), _subscribedEvents()
{
	auto &v = sf::VideoMode::getFullscreenModes();

	_window.create(v[0], _name, sf::Style::Close | sf::Style::Fullscreen);
	_window.setFramerateLimit(fps);
}

void WScene::callSubscribedEvents() noexcept
{
	sf::Event event;

	while (_window.pollEvent(event))
		for (auto &&i : _subscribedEvents[event.type])
			i.second->onEvent(*this, event, *i.first);
}

void WScene::run() noexcept
{
	_running = true;
	_clock.reset();
	while (_running) {
		_window.clear();
		callSubscribedEvents();
		insertToAddObjects();
		deleteToRemoveObjects();
		for (auto &&it = _layeredObjects.rbegin();
		     it != _layeredObjects.rend(); ++it) {
			for (auto &&object : *it) {
				for (auto &&c : object->getComponents()) {
					c->update(*this, *object);
					c->display(_window);
				}
				object->update(*this);
			}
		}
		_window.display();
		_clock.refresh();
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

void WScene::subscribe(const GameObject &object, const IComponent &component,
		       const sf::Event::EventType &type) noexcept
{
	for (auto &&i : _subscribedEvents[type])
		if (i.second == &component)
			return;
	_subscribedEvents[type].emplace_back(
		const_cast<GameObject *>(&object),
		const_cast<IComponent *>(&component));
}

void WScene::unsubscribe(const IComponent &component,
			 const sf::Event::EventType &type) noexcept
{
	for (auto it = _subscribedEvents[type].begin();
	     it != _subscribedEvents[type].end(); ++it) {
		if (it->second == &component) {
			_subscribedEvents[type].erase(it);
			return;
		}
	}
}
} // namespace sfs