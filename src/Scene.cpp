#include "Scene.hpp"
#include "GameObject.hpp"

namespace sfs
{
Scene::Scene(const std::string &name, uint32_t fps) noexcept
    : _name(name), _clock(fps), _objects(), _layeredObjects(), _toAdd(),
      _fonts(), _images(), _textures(), _soundBuffers(), _running(false)
{
	_objects.reserve(64);
	_layeredObjects.reserve(10);
}

static void eraseObject(std::vector<GameObject *> &v, GameObject *key)
{
	auto rm = std::remove(v.begin(), v.end(), key);
	auto go = *rm;

	if (go == nullptr)
		return;
	auto parent = go->parent();
	if (parent != nullptr) {
		for (auto it = parent->getChilds().begin();
		     it != parent->getChilds().end(); ++it) {
			if ((*it)->toDestroy() == true) {
				(*it)->parent(nullptr);
				it = parent->getChilds().erase(it);
				--it;
			}
		}
	}
	v.erase(rm);
}

void Scene::insertToAddObjects() noexcept
{
	while (_toAdd.size() > 0) {
		auto &i = _toAdd.front();
		if (_layeredObjects.size() < i->layer() + 1)
			_layeredObjects.resize(i->layer() + 1);
		_layeredObjects[i->layer()].push_back(i.get());
		if (i->parent())
			i->parent()->getChilds().push_back(i.get());
		i->start(*this);
		for (auto &&c: i->getComponents())
			c->start(*this, *i);
		_objects.push_back(std::move(i));
		_toAdd.pop_front();
	}
}

void Scene::deleteToRemoveObjects() noexcept
{
	for (auto it = _objects.begin(); it != _objects.end(); ++it) {
		auto *go = it->get();
		if (go->toDestroy()) {
			eraseObject(_layeredObjects[it->get()->layer()], go);
			it = _objects.erase(it);
			--it;
		}
	}
}

void Scene::run() noexcept
{
	_running = true;
	_clock.reset();
	while (_running) {
		insertToAddObjects();
		deleteToRemoveObjects();
		for (auto &&it = _layeredObjects.rbegin();
		     it != _layeredObjects.rend(); ++it) {
			for (auto &&object : *it) {
				for (auto &&c : object->getComponents())
					c->update(*this, *object);
				object->update(*this);
			}
		}
		_clock.refreshDeltaTime();
	}
}

void Scene::close() noexcept
{
	_running = false;
}

std::vector<GameObject *> Scene::getGameObjects(const std::string &name) const
	noexcept
{
	std::vector<GameObject *> v;

	for (auto &&i : _objects)
		if (i->name() == name)
			v.push_back(i.get());
	for (auto &&i : _toAdd)
		if (i->name() == name)
			v.push_back(i.get());
	return v;
}

std::vector<GameObject *> Scene::getGameObjects(int tag) const noexcept
{
	std::vector<GameObject *> v;

	for (auto &&i : _objects)
		if (i->tag() == tag)
			v.push_back(i.get());
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

template <typename T>
const T *getAsset(const std::string &name,
		  std::unordered_map<std::string, T> &map)
{
	const auto &asset = map.find(name);

	if (name.empty())
		return map.empty() ? nullptr : &map.begin()->second;
	if (asset == map.end()) {
		T item;
		if (item.loadFromFile(name) == false)
			return NULL;
		auto p = map.insert(map.begin(),
				    std::pair<std::string, T>(name, item));
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

const sf::SoundBuffer *
Scene::getAssetSoundBuffer(const std::string &name) noexcept
{
	return getAsset<sf::SoundBuffer>(name, _soundBuffers);
}

sf::RenderWindow *Scene::getVideoHandle() noexcept
{
	return nullptr;
}

void Scene::subscribe(const GameObject &object, const sf::Event::EventType &type) noexcept
{
	// no window -> no events
	(void)object;
	(void)type;
}

void Scene::unsubscribe(const GameObject &object,
			const sf::Event::EventType &type) noexcept
{
	// no window -> no events
	(void)object;
	(void)type;
}

} // namespace sfs
