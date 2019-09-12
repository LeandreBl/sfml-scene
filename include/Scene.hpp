#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <deque>

#include "Clock.hpp"

namespace sfs
{
class GameObject;

class Scene
{
      public:
	Scene(const std::string &name, uint32_t fps) noexcept;
	virtual ~Scene();

	void run() noexcept;
	void close() noexcept;

	void addGameObject(GameObject *object) noexcept;
	void removeGameObject(GameObject *object) noexcept;

	std::vector<GameObject *> getGameObjects(const std::string &name) const
		noexcept;
	std::vector<GameObject *> getGameObjects(int tag) const noexcept;
	template <typename T>
	std::vector<T *> getGameObjects() const noexcept {
		std::vector<T *> v;

		for (auto &&i : _objects) {
			T *p = dynamic_cast<T *>(i);
			if (p != nullptr)
				v.push_back(p);
		}
		for (auto &&i : _toAdd) {
			T *p = dynamic_cast<T *>(i);
			if (p != nullptr)
				v.push_back(p);
		}
		return v;
	}

	float deltaTime() noexcept;
	float time() noexcept;
	float realTime() noexcept;
	void timeScale(float timescale) noexcept;
	float timescale() const noexcept;

	void framerate(uint32_t framerate) noexcept;
	uint32_t framerate() const noexcept;

	const sf::Font *getAssetFont(const std::string &name) noexcept;
	const sf::Texture *getAssetTexture(const std::string &name) noexcept;
	const sf::Image *getAssetImage(const std::string &name) noexcept;
	const sf::SoundBuffer *
	getAssetSoundBuffer(const std::string &name) noexcept;

	virtual sf::RenderWindow *getWindow() noexcept;
	virtual void subscribe(const GameObject *object,
			       const sf::Event::EventType &type) noexcept;
	virtual void unsubscribe(const GameObject *object,
				 const sf::Event::EventType &type) noexcept;

      protected:
	void insertToAddObjects() noexcept;
	void deleteToRemoveObjects() noexcept;
	std::string _name;
	Clock _clock;
	std::vector<GameObject *> _objects;
	std::vector<std::vector<GameObject *>> _layeredObjects;
	std::deque<GameObject *> _toAdd;
	std::deque<GameObject *> _toRemove;
	std::unordered_map<std::string, sf::Font> _fonts;
	std::unordered_map<std::string, sf::Image> _images;
	std::unordered_map<std::string, sf::Texture> _textures;
	std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
	bool _running;
};
} // namespace sfs