#include "GameObject.hpp"
#include "Text.hpp"

namespace sfs
{
Text::Text(const sf::Font &font, const std::string &text,
	   const sf::Color &color, uint32_t characterSize) noexcept
    : sf::Text(text, font, characterSize)
{
	setFillColor(color);
}

void Text::display(sf::RenderWindow &window) noexcept
{
	window.draw(*this);
}

void Text::start(Scene &, GameObject &go) noexcept
{
	setPosition(go.getPosition());
}

} // namespace sfs