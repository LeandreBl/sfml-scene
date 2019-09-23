#pragma once

#include "IComponent.hpp"


namespace sfs
{
class Text : public IComponent, public sf::Text
{
      public:
	Text(const sf::Font &font, const std::string &text = "",
	     const sf::Color &color = sf::Color::White,
	     uint32_t characterSize = 32) noexcept;
	void start(Scene &, GameObject &) noexcept;
	void display(sf::RenderWindow &) noexcept;
};
} // namespace sfs