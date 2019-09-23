#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "IComponent.hpp"

namespace sfs
{
class GameObject : public sf::Transformable
{
      public:
	const uint32_t defaultLayer = 5;

	GameObject(const sf::Vector2f &position = sf::Vector2f(0.f, 0.f), const std::string &name = "") noexcept;
	GameObject(const GameObject &) noexcept = default;
	GameObject &operator=(GameObject &) noexcept = default;

	void errorLog(const std::string &str) noexcept;

	virtual ~GameObject();
	virtual void start(Scene &) noexcept {};
	virtual void update(Scene &) noexcept {};
	virtual void onEvent(Scene &, const sf::Event &) {};

	void destroy() noexcept;

	template <typename T, typename... Args>
	T &addChild(Scene &scene, const Args &... args) noexcept
	{
		auto &go = scene.addGameObject<T>(args...);
		go.parent(this);
		return go;
	}

	template <typename T> std::vector<T *> getChilds() noexcept;
	std::vector<GameObject *> &getChilds() noexcept;

	template <typename T, typename... Args>
	T &addComponent(const Args &... args) noexcept
	{
		std::unique_ptr<T> c =
			std::make_unique<T>(args...);
		auto &p = *c.get();

		_components.push_back(std::move(c));
		return p;
	}

	template <typename T> std::vector<T *> getComponents() noexcept
	{
		std::vector<T *> v;

		for (auto &&i : _components) {
			auto *p = dynamic_cast<T *>(i.get());
			if (p != nullptr)
				v.push_back(i.get());
		}
		return v;
	}
	std::vector<std::unique_ptr<IComponent>> &getComponents() noexcept;

	GameObject *parent() noexcept;
	void parent(GameObject *parent) noexcept;

	const std::string &name() const noexcept;
	void name(const std::string &name) noexcept;

	int tag() const noexcept;
	void tag(int tag) noexcept;

	uint32_t layer() const noexcept;
	void layer(uint32_t layer) noexcept;

	bool toDestroy() const noexcept;

      protected:
	void addChild(Scene &scene,
		      std::unique_ptr<GameObject> &object) noexcept;
	std::string _name;
	GameObject *_parent;
	int _tag;
	std::vector<GameObject *> _childs;
	std::vector<std::unique_ptr<IComponent>> _components;
	uint32_t _layer;
	bool _toDestroy;
};
std::ostream &operator<<(std::ostream &os, const GameObject &object) noexcept;
} // namespace sfs