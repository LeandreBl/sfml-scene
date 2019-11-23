#include "IComponent.hpp"

namespace sfs {
static uint64_t id = 0;
IComponent::IComponent() noexcept
	: _id(id++)
{
}

uint64_t IComponent::getId() const noexcept
{
	return _id;
}

void IComponent::destroy() noexcept
{
	_toDestroy = true;
}

bool IComponent::toDestroy() const noexcept
{
	return _toDestroy;
}

} // namespace sfs