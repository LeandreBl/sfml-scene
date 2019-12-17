#include "UI.hpp"

namespace sfs {
UI::UI(Scene &scene, const std::string &name, const sf::Vector2f &position, uint32_t layer) noexcept
	: GameObject(scene, name, position, layer)
{
}
} // namespace sfs