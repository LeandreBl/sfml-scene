#include <sstream>

#include "GameObject.hpp"
#include "WScene.hpp"

namespace sfs {
static uint64_t id = 0;
GameObject::GameObject(Scene &scene, const std::string &name, const sf::Vector2f &position,
		       uint32_t layer, int tag) noexcept
	: sf::Transformable()
	, _scene(scene)
	, _name(name)
	, _parent(nullptr)
	, _tag(tag)
	, _subscribedEvents()
	, _childs()
	, _componentsToAdd()
	, _components()
	, _layer(layer)
	, _id(id++)
	, _toDestroy(false)
	, _isActive(true)
{
	setPosition(position);
}

std::vector<GameObject *> GameObject::getChilds() noexcept
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

std::vector<sf::Event::EventType> &GameObject::getSubscribedEvents() noexcept
{
	return _subscribedEvents;
}

bool GameObject::toDestroy() const noexcept
{
	return _toDestroy;
}

std::string GameObject::asString() const noexcept
{
	std::ostringstream os;

	os << "{ \"" << _name << "\" " << getPosition() << " }";
	return os.str();
}

uint64_t GameObject::getId() const noexcept
{
	return _id;
}

void GameObject::subscribe(const sf::Event::EventType &type) noexcept
{
	scene().subscribe(*this, type);
}

void GameObject::unsubscribe(const sf::Event::EventType &type) noexcept
{
	scene().unsubscribe(*this, type);
}

void GameObject::setActive(bool state) noexcept
{
	_isActive = state;
}

bool GameObject::isActive() const noexcept
{
	return _isActive;
}

void GameObject::destroy() noexcept
{
	if (_toDestroy == true)
		return;
	_toDestroy = true;
	onDestroy();
	if (parent() != nullptr) {
		_parent->_childs.erase(
			std::remove(_parent->_childs.begin(), _parent->_childs.end(), this));
		parent(nullptr);
	}
	while (!_childs.empty()) {
		auto &p = _childs.front();
		p->destroy();
	}
}

void GameObject::startPendingComponents() noexcept
{
	while (!_componentsToAdd.empty()) {
		auto &c = _componentsToAdd.front();
		c->start(*this);
		_components.push_back(std::move(c));
		_componentsToAdd.pop();
	}
}

Scene &GameObject::scene() noexcept
{
	return _scene;
}

void GameObject::errorLog(const std::string &str) noexcept
{
	std::cerr << "Error: " << asString() << ": " << str << std::endl;
}
} // namespace sfs