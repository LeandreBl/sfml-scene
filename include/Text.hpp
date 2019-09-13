#pragma once

#include "IComponent.hpp"


namespace sfs
{
class Text : public IComponent, public sf::Text
{
      public:
	Text(const std::string &text, const sf::Font &font,
	     uint32_t characterSize = 32,
	     const sf::Color &color = sf::Color::White) noexcept;
	void display(sf::RenderWindow &) noexcept;
	void update(Scene &, GameObject &) noexcept;

	void start(Scene &, GameObject &) noexcept {};
	void onEvent(Scene &, const sf::Event &, GameObject &) noexcept {};
      protected:
};
} // namespace sfs