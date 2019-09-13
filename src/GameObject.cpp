#include "GameObject.hpp"
#include "WScene.hpp"

namespace sfs
{
GameObject::GameObject(const sf::Vector2f &position,
		       const std::string &name) noexcept
    : sf::Transformable(), _name(name), _parent(nullptr), _tag(0), _childs(),
      _components(), _layer(GameObject::defaultLayer), _toDestroy(false)
{
	setPosition(position);
}

GameObject::~GameObject()
{
	for (auto &&i : _childs)
		i->destroy();
}

void GameObject::start(Scene &scene) noexcept
{
	(void)scene;
}

void GameObject::update(Scene &scene) noexcept
{
	(void)scene;
}

std::vector<GameObject *> &GameObject::getChilds() noexcept
{
	return _childs;
}

std::vector<std::unique_ptr<IComponent>> &GameObject::getComponents() noexcept
{
	return _components;
}

GameObject *GameObject::parent() noexcept
{
	return _parent;
}

void GameObject::parent(GameObject *parent) noexcept
{
	_parent = parent;
}

const std::string &GameObject::name() const noexcept
{
	return _name;
}

void GameObject::name(const std::string &name) noexcept
{
	_name = name;
}

int GameObject::tag() const noexcept
{
	return _tag;
}

void GameObject::tag(int tag) noexcept
{
	_tag = tag;
}

uint32_t GameObject::layer() const noexcept
{
	return _layer;
}

void GameObject::layer(uint32_t layer) noexcept
{
	_layer = layer;
}

bool GameObject::toDestroy() const noexcept
{
	return _toDestroy;
}

void GameObject::destroy() noexcept
{
	_toDestroy = true;
}

} // namespace sfs