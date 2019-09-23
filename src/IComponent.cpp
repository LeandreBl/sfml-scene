#include "IComponent.hpp"

namespace sfs
{
	void IComponent::destroy() noexcept
	{
		_toDestroy = true;
	}

	bool IComponent::toDestroy() const noexcept
	{
		return _toDestroy;
	}
}