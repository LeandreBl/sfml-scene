#include <sstream>

#include "GameObject.hpp"
#include "WScene.hpp"

namespace sfs {
static uint64_t id = 0;
GameObject::GameObject(const sf::Vector2f &position, const std::string &name) noexcept
	: sf::Transformable()
	, _name(name)
	, _parent(nullptr)
	, _tag(0)
	, _subscribedEvents()
	, _childs()
	, _components()
	, _layer(GameObject::defaultLayer)
	, _id(id++)
	, _toDestroy(false)
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

void GameObject::startPendingComponents(Scene &scene) noexcept
{
	while (!_componentsToAdd.empty()) {
		auto &c = _componentsToAdd.front();
		c->start(scene, *this);
		_components.push_back(std::move(c));
		_componentsToAdd.pop();
	}
}

void GameObject::errorLog(const std::string &str) noexcept
{
	std::cerr << "Error: " << asString() << ": " << str << std::endl;
}
} // namespace sfs