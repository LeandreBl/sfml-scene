#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace sfs
{

class Scene;

class GameObject : public sf::Sprite
{
      public:
	GameObject(const std::string &name = "") noexcept;
	GameObject(const GameObject &object) noexcept = default;
	GameObject &operator=(GameObject &object) noexcept = default;
	virtual ~GameObject();
	virtual void start(Scene &scene) noexcept;
	virtual void update(Scene &scene) noexcept;
	virtual void display(Scene &scene) noexcept;
	virtual void onEvent(Scene &scene, const sf::Event &event) noexcept;

	void addChild(Scene &scene, GameObject *object) noexcept;
	std::vector<GameObject *> &getChilds() noexcept;

	GameObject *parent() noexcept;
	void parent(GameObject *parent) noexcept;

	const std::string &name() const noexcept;
	void name(const std::string &name) noexcept;

	int tag() const noexcept;
	void tag(int tag) noexcept;

	uint32_t layer() const noexcept;
	void layer(uint32_t layer) noexcept;

      private:
	std::string _name;
	GameObject *_parent;
	int _tag;
	// int _type;
	std::vector<GameObject *> _childs;
	uint32_t _layer;
};
} // namespace sfs