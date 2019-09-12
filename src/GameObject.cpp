#include "GameObject.hpp"
#include "WScene.hpp"

namespace sfs
{
GameObject::GameObject(const std::string &name) noexcept
    : sf::Sprite(), _name(name), _parent(nullptr), _tag(0), _childs(), _layer(0)
{
}

GameObject::~GameObject()
{
	if (_parent)
		_parent->_childs.erase(std::remove(_parent->_childs.begin(),
						   _parent->_childs.end(),
						   this));
	for (auto &&i : _childs)
		i->_parent = nullptr;
}

void GameObject::start(Scene &scene) noexcept
{
	(void)scene;
}

void GameObject::update(Scene &scene) noexcept
{
	(void)scene;
}

void GameObject::display(Scene &scene) noexcept
{
	scene.getWindow()->draw(*this);
}

void GameObject::onEvent(Scene &scene, const sf::Event &event) noexcept
{
	(void)scene;
	(void)event;
}

void GameObject::addChild(Scene &scene, GameObject *object) noexcept
{
	scene.addGameObject(object);
	object->_parent = this;
}

std::vector<GameObject *> &GameObject::getChilds() noexcept
{
	return _childs;
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
} // namespace sfs