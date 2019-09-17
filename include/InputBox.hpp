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
	void onEvent(Scene &scene, const sf::Event &event) noexcept;
	std::string string() const noexcept;
	void string(const std::string &string) noexcept;

      protected:
	sf::Color _color;
	uint32_t _charSize;
	std::string _placeholder;
	sf::String _content;
	std::string _fontName;
	const sf::Font *_font;
	Text *_text;
	float _prevTime;
	bool _blink;
	bool _selected;
	bool _clicked;
};
} // namespace sfs