#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <deque>

#include "Clock.hpp"

namespace sfs
{
class GameObject;
class IComponent;

class Scene
{
      public:
	Scene(const std::string &name, uint32_t fps) noexcept;
	virtual ~Scene() = default;

	void run() noexcept;
	void close() noexcept;

	template <typename T, typename... Args>
	T &addGameObject(const Args &... args) noexcept
	{
		std::unique_ptr<T> go = std::make_unique<T>(args...);
		auto &i = *go.get();

		_toAdd.push_back(std::move(go));
		return i;
	}

	std::vector<GameObject *> getGameObjects(const std::string &name) const
		noexcept;
	std::vector<GameObject *> getGameObjects(int tag) const noexcept;
	template <typename T> std::vector<T *> getGameObjects() const noexcept
	{
		std::vector<T *> v;

		for (auto &&i : _objects) {
			T *p = dynamic_cast<T *>(i.get());
			if (p != nullptr)
				v.push_back(p);
		}
		for (auto &&i : _toAdd) {
			T *p = dynamic_cast<T *>(i.get());
			if (p != nullptr)
				v.push_back(p);
		}
		return v;
	}

	float deltaTime() noexcept;
	float time() noexcept;
	float realTime() noexcept;
	void timeScale(float timescale) noexcept;
	float timeScale() const noexcept;

	void framerate(uint32_t framerate) noexcept;
	uint32_t framerate() const noexcept;

	const sf::Font *getAssetFont(const std::string &name) noexcept;
	const sf::Texture *getAssetTexture(const std::string &name) noexcept;
	const sf::Image *getAssetImage(const std::string &name) noexcept;
	const sf::SoundBuffer *
	getAssetSoundBuffer(const std::string &name) noexcept;

	virtual void subscribe(const GameObject &object,
			       const sf::Event::EventType &type) noexcept;
	virtual void unsubscribe(const GameObject &object,
				 const sf::Event::EventType &type) noexcept;

	virtual sf::RenderWindow *getVideoHandle() noexcept;

      protected:
	void insertToAddObjects() noexcept;
	void deleteToRemoveObjects() noexcept;
	std::string _name;
	Clock _clock;
	sf::Mutex _runMutex;
	std::vector<std::unique_ptr<GameObject>> _objects;
	std::vector<std::vector<GameObject *>> _layeredObjects;
	std::deque<std::unique_ptr<GameObject>> _toAdd;
	std::unordered_map<std::string, sf::Font> _fonts;
	std::unordered_map<std::string, sf::Image> _images;
	std::unordered_map<std::string, sf::Texture> _textures;
	std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
	bool _running;
};
} // namespace sfs