#include "UI.hpp"

namespace sfs
{
UI::UI(const sf::Vector2f &position, const std::string &name) noexcept
    : GameObject(position, name), sf::Sprite()
{
	_layer = UI::defaultLayer;
}
} // namespace sfs