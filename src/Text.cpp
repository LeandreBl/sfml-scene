#include "GameObject.hpp"
#include "Text.hpp"

namespace sfs
{
Text::Text(const std::string &text, const sf::Font &font,
	   uint32_t characterSize,
	   const sf::Color &color) noexcept
    : sf::Text(text, font, characterSize)
{
	setFillColor(color);
}

void Text::display(sf::RenderWindow &window) noexcept
{
	window.draw(*this);
}

void Text::update(Scene &scene, GameObject &go) noexcept
{
	(void)scene;
	setPosition(go.getPosition());
}
} // namespace sfs