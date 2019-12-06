#pragma once

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "IComponent.hpp"

template <typename T> T &operator<<(T &os, const sf::Vector2f &v)
{
	os << '(' << v.x << ", " << v.y << ')';
	return os;
}

template <typename T> T &operator<<(T &os, const sf::Vector3f &v) noexcept
{
	os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	return os;
}

template <typename T, typename B> T &operator<<(T &os, const sf::Rect<B> &rect) noexcept
{
	os << "[(" << rect.top << ", " << rect.left << "), (" << rect.width << ", " << rect.height
	   << ")]";
	return os;
}

namespace sfs {
class GameObject : public sf::Transformable {
      public:
	const uint32_t defaultLayer = 5;

	GameObject(const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
		   const std::string &name = "") noexcept;
	GameObject(const GameObject &) noexcept = default;
	GameObject &operator=(GameObject &) noexcept = default;

	void errorLog(const std::string &str) noexcept;

	virtual ~GameObject() = default;
	virtual void start(Scene &) noexcept {};
	virtual void update(Scene &) noexcept {};
	virtual void onEvent(Scene &, const sf::Event &) noexcept {};
	virtual void onDestroy() noexcept {};

	void destroy() noexcept;

	template <typename T, typename... Args> T &addChild(Scene &scene, Args &&... args) noexcept
	{
		auto &go = scene.addGameObject<T>(args...);
		go.parent(this);
		_childs.push_back(&go);
		return go;
	}

	template <typename T> std::vector<T *> getChilds() noexcept
	{
		std::vector<T *> v;

		for (auto &&i : _childs) {
			auto *p = dynamic_cast<T *>(i);
			if (p != nullptr)
				v.push_back(p);
		}
		return v;
	}
	std::vector<GameObject *> getChilds() noexcept;

	template <typename T, typename... Args> T &addComponent(Args &&... args) noexcept
	{
		std::unique_ptr<T> c = std::make_unique<T>(args...);
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
				v.push_back(p);
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

	std::vector<sf::Event::EventType> &getSubscribedEvents() noexcept;

	bool toDestroy() const noexcept;

	std::string asString() const noexcept;
	uint64_t getId() const noexcept;

      protected:
	void addChild(Scene &scene, std::unique_ptr<GameObject> &object) noexcept;
	std::string _name;
	GameObject *_parent;
	int _tag;
	std::vector<sf::Event::EventType> _subscribedEvents;
	std::vector<GameObject *> _childs;
	std::vector<std::unique_ptr<IComponent>> _components;
	uint32_t _layer;
	const uint64_t _id;
	bool _toDestroy;
};
} // namespace sfs
