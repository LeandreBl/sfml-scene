#include "Scene.hpp"
#include "GameObject.hpp"

namespace sfs
{
Scene::Scene(const std::string &name, uint32_t fps) noexcept
    : _name(name), _clock(fps), _objects(), _layeredObjects(), _toAdd(),
      _toRemove(), _fonts(), _images(), _textures(), _soundBuffers(),
      _running(false)
{
	_objects.reserve(64);
	_layeredObjects.reserve(10);
}

Scene::~Scene()
{
	for (auto &&i : _objects)
		delete i;
}

template <typename T> static void eraseObject(std::vector<T> &v, T &key)
{
	v.erase(std::remove(v.begin(), v.end(), key));
}

void Scene::insertToAddObjects() noexcept
{
	while (_toAdd.size() > 0) {
		auto i = _toAdd.front();
		_toAdd.pop_front();
		_objects.push_back(i);
		if (_layeredObjects.size() < i->layer() + 1)
			_layeredObjects.resize(i->layer() + 1);
		_layeredObjects[i->layer()].push_back(i);
		if (i->parent())
			i->parent()->getChilds().push_back(i);
		i->start(*this);
	}
}

void Scene::deleteToRemoveObjects() noexcept
{
	while (_toRemove.size() > 0) {
		auto &i = _toRemove.front();
		_toRemove.pop_front();
		eraseObject(_layeredObjects[i->layer()], i);
		delete i;
	}
}

void Scene::run() noexcept
{
	_running = true;
	_clock.reset();
	while (_running) {
		insertToAddObjects();
		deleteToRemoveObjects();
		for (auto &&v : _layeredObjects)
			for (auto &&object : v)
				object->update(*this);
		_clock.refresh();
	}
}

void Scene::close() noexcept
{
	_running = false;
}

void Scene::addGameObject(GameObject *object) noexcept
{
	_toAdd.push_back(object);
}

void Scene::removeGameObject(GameObject *object) noexcept
{
	_toRemove.push_back(object);
}

std::vector<GameObject *> Scene::getGameObjects(const std::string &name) const
	noexcept
{
	std::vector<GameObject *> v;

	for (auto &&i : _objects)
		if (i->name() == name)
			v.push_back(i);
	for (auto &&i : _toAdd)
		if (i->name() == name)
			v.push_back(i);
	return v;
}

std::vector<GameObject *> Scene::getGameObjects(int tag) const noexcept
{
	std::vector<GameObject *> v;

	for (auto &&i : _objects)
		if (i->tag() == tag)
			v.push_back(i);
	for (auto &&i : _toAdd)
		if (i->tag() == tag)
			v.push_back(i);
	return v;
}
// std::vector<GameObject *> getGameObjects(int type) noexcept;

float Scene::deltaTime() noexcept
{
	return _clock.deltaTime();
}

float Scene::time() noexcept
{
	return _clock.time();
}

float Scene::realTime() noexcept
{
	return _clock.refresh();
}

void Scene::timeScale(float timescale) noexcept
{
	_clock.timeScale(timescale);
}

float Scene::timescale() const noexcept
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

sf::RenderWindow *Scene::getWindow() noexcept
{
	return nullptr;
}

void Scene::subscribe(const GameObject *object,
		      const sf::Event::EventType &type) noexcept
{
	// no window -> no events
	(void)object;
	(void)type;}

void Scene::unsubscribe(const GameObject *object,
			const sf::Event::EventType &type) noexcept
{
	// no window -> no events
	(void)object;
	(void)type;
}

} // namespace sfs
