#include "IComponent.hpp"

namespace sfs {
static uint64_t id = 0;
IComponent::IComponent() noexcept
	: _id(id++)
	, _toDestroy(false)
	, _isActive(true)
{
}

uint64_t IComponent::getId() const noexcept
{
	return _id;
}

void IComponent::destroy() noexcept
{
	_toDestroy = true;
	onDestroy();
}

bool IComponent::toDestroy() const noexcept
{
	return _toDestroy;
}

bool IComponent::isActive() const noexcept
{
	return _isActive;
}

void IComponent::setActive(bool state) noexcept
{
	_isActive = state;
}

} // namespace sfs