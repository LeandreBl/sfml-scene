#include "UI.hpp"

namespace sfs {
UI::UI(const std::string &name, const sf::Vector2f &position) noexcept
	: GameObject(name, position)
{
	_layer = UI::defaultLayer;
}
} // namespace sfs