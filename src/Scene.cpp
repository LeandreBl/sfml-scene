#include <chrono>

#include "Scene.hpp"
#include "GameObject.hpp"

namespace sfs {
Scene::Scene(const std::string &name, uint32_t fps) noexcept
	: _name(name)
	, _clock(fps)
	, _layeredObjects()
	, _toAdd()
	, _fonts()
	, _images()
	, _textures()
	, _soundBuffers()
	, _running(false)
{
	_layeredObjects.resize(10);
	for (auto &v : _layeredObjects)
		v.reserve(64);
}

void Scene::clearAssets() noexcept
{
	_fonts.clear();
	_images.clear();
	_textures.clear();
	_soundBuffers.clear();
}

void Scene::clear() noexcept
{
	if (_running) {
		for (auto &&v : _layeredObjects)
			for (auto &&go : v)
				go->destroy();
		for (auto &&go : _toAdd)
			go->destroy();
	}
	else {
		_layeredObjects.clear();
		_toAdd.clear();
	}
}

void Scene::insertToAddObjects() noexcept
{
	while (_toAdd.size() > 0) {
		auto &i = _toAdd.front();
		auto *go = i.get();
		if (_layeredObjects.size() < i->layer() + 1)
			_layeredObjects.resize(i->layer() + 1);
		_layeredObjects[i->layer()].push_back(std::move(i));
		if (go->parent())
			go->parent()->getChilds().push_back(go);
		go->start(*this);
		for (auto &&c : go->getComponents())
			c->start(*this, *go);
		_toAdd.pop_front();
	}
}

static void eraseParentChilds(GameObject &go)
{
	auto parent = go.parent();

	if (parent != nullptr) {
		auto childs = parent->getChilds();
		for (auto it = childs.begin(); it != childs.end(); ++it) {
			if ((*it)->toDestroy() == true)
				(*it)->parent(nullptr);
			it = childs.erase(it);
			if (it-- == childs.end())
				break;
		}
	}
}

void Scene::deleteUpdate(std::vector<std::unique_ptr<GameObject>> &v) noexcept
{
	for (auto it = v.begin(); it != v.end(); ++it) {
		auto &go = *it->get();
		if (go.toDestroy()) {
			eraseParentChilds(go);
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
		}
	}
}

void Scene::run() noexcept
{
	_running = true;
	_clock.reset();
	while (_running) {
		auto t1 = _clock.getNative();
		insertToAddObjects();
		for (auto rit = _layeredObjects.rbegin(); rit != _layeredObjects.rend(); ++rit) {
			deleteUpdate(*rit);
		}
		_clock.refreshDeltaTime();
		auto t2 = _clock.getNative();
		sf::sleep(sf::microseconds(1000000 / _clock.framerate()) - (t2 - t1));
	}
}

void Scene::close() noexcept
{
	_running = false;
}

std::vector<GameObject *> Scene::getGameObjects(const std::string &name) const noexcept
{
	std::vector<GameObject *> v;

	for (auto &&i : _layeredObjects)
		for (auto &&go : i)
			if (go->name() == name)
				v.push_back(go.get());

	for (auto &&i : _toAdd)
		if (i->name() == name)
			v.push_back(i.get());
	return v;
}

GameObject *Scene::getGameObject(uint64_t id) const noexcept
{
	for (auto &&i : _layeredObjects)
		for (auto &&go : i)
			if (go->getId() == id)
				return go.get();

	for (auto &&go : _toAdd)
		if (go->getId() == id)
			return go.get();
	return nullptr;
}

std::vector<GameObject *> Scene::getGameObjects(int tag) const noexcept
{
	std::vector<GameObject *> v;

	for (auto &&i : _layeredObjects)
		for (auto &&go : i)
			if (go->tag() == tag)
				v.push_back(go.get());

	for (auto &&i : _toAdd)
		if (i->tag() == tag)
			v.push_back(i.get());
	return v;
}
float Scene::deltaTime() noexcept
{
	return _clock.getDeltaTime();
}

float Scene::time() noexcept
{
	return _clock.getTime();
}

float Scene::realTime() noexcept
{
	return _clock.getRealTime();
}

void Scene::timeScale(float timescale) noexcept
{
	_clock.timeScale(timescale);
}

float Scene::timeScale() const noexcept
{
	return _clock.timeScale();
}

void Scene::framerate(uint32_t framerate) noexcept
{
	_clock.framerate(framerate);
}

uint32_t Scene::framerate() const noexcept
{
	return _clock.framerate();
}

uint32_t Scene::getRealFramerate() const noexcept
{
	return 1.f / _clock.getDeltaTime();
}

template <typename T>
const T *getAsset(const std::string &name, std::unordered_map<std::string, T> &map)
{
	const auto &asset = map.find(name);

	if (name.empty())
		return map.empty() ? nullptr : &map.begin()->second;
	if (asset == map.end()) {
		T item;
		if (item.loadFromFile(name) == false)
			return NULL;
		auto p = map.insert(map.begin(), std::pair<std::string, T>(name, item));
		return &p->second;
	}
	return &asset->second;
}

const sf::Font *Scene::getAssetFont(const std::string &name) noexcept
{
	return getAsset<sf::Font>(name, _fonts);
}

const sf::Texture *Scene::getAssetTexture(const std::string &name) noexcept
{
	return getAsset<sf::Texture>(name, _textures);
}

const sf::Image *Scene::getAssetImage(const std::string &name) noexcept
{
	return getAsset<sf::Image>(name, _images);
}

const sf::SoundBuffer *Scene::getAssetSoundBuffer(const std::string &name) noexcept
{
	return getAsset<sf::SoundBuffer>(name, _soundBuffers);
}

sf::RenderWindow *Scene::getVideoHandle() noexcept
{
	return nullptr;
}

void Scene::subscribe(GameObject &, const sf::Event::EventType &) noexcept
{
	// no window -> no events
}

void Scene::unsubscribe(GameObject &, const sf::Event::EventType &) noexcept
{
	// no window -> no events
}

} // namespace sfs
