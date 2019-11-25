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

namespace sfs {
class GameObject;
class IComponent;

class Scene {
      public:
	Scene(const std::string &name, uint32_t fps) noexcept;
	virtual ~Scene() = default;

	void run() noexcept;
	void close() noexcept;
	void clear() noexcept;
	void clearAssets() noexcept;

	template <typename T, typename... Args> T &addGameObject(Args &&... args) noexcept
	{
		std::unique_ptr<T> go = std::make_unique<T>(args...);
		auto &i = *go.get();

		_toAdd.push_back(std::move(go));
		return i;
	}

	std::vector<GameObject *> getGameObjects(const std::string &name) const noexcept;
	std::vector<GameObject *> getGameObjects(int tag) const noexcept;
	GameObject *getGameObject(uint64_t id) const noexcept;
	template <typename T> std::vector<T *> getGameObjects() const noexcept
	{
		std::vector<T *> v;

		for (auto &&i : _layeredObjects) {
			for (auto &&go : i) {
				T *p = dynamic_cast<T *>(go.get());
				if (p != nullptr)
					v.push_back(p);
			}
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

	virtual void framerate(uint32_t framerate) noexcept;
	uint32_t framerate() const noexcept;
	uint32_t getRealFramerate() const noexcept;

	const sf::Font *getAssetFont(const std::string &name) noexcept;
	const sf::Texture *getAssetTexture(const std::string &name) noexcept;
	const sf::Image *getAssetImage(const std::string &name) noexcept;
	const sf::SoundBuffer *getAssetSoundBuffer(const std::string &name) noexcept;

	virtual void subscribe(GameObject &object, const sf::Event::EventType &type) noexcept;
	virtual void unsubscribe(GameObject &object, const sf::Event::EventType &type) noexcept;

	virtual sf::RenderWindow *getVideoHandle() noexcept;

      protected:
	void forceClear() noexcept;
	void insertToAddObjects() noexcept;
	void deleteUpdate(std::vector<std::unique_ptr<GameObject>> &v) noexcept;
	std::string _name;
	Clock _clock;
	std::vector<std::vector<std::unique_ptr<GameObject>>> _layeredObjects;
	std::deque<std::unique_ptr<GameObject>> _toAdd;
	std::unordered_map<std::string, sf::Font> _fonts;
	std::unordered_map<std::string, sf::Image> _images;
	std::unordered_map<std::string, sf::Texture> _textures;
	std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
	bool _running;
};
} // namespace sfs