#pragma once

#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "Text.hpp"

namespace sfs
{
class InputBox : public UI
{
      public:
	InputBox(const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
		 const std::string &fontName = "",
		 const std::string &placeholder = "...",
		 uint32_t characterSize = 32,
		 const sf::Color &color = sf::Color::White) noexcept;
	void start(Scene &scene) noexcept;
	void update(Scene &scene) noexcept;
	const std::string &string() noexcept;
	void string(const std::string &string) noexcept;
      protected:
	Text *text;
};
} // namespace sfs