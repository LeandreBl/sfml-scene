#pragma once

#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "BasicShape.hpp"

namespace sfs {
class InputBox : public UI {
      public:
	InputBox(Scene &scene, const sf::Font &font,
		 const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
		 const std::string &placeholder = "...", const sf::Color &color = sf::Color::White,
		 uint32_t characterSize = 32) noexcept;
	InputBox(const InputBox &) noexcept = default;
	InputBox &operator=(InputBox &) noexcept = default;
	void start() noexcept;
	void update() noexcept;
	void onEvent(const sf::Event &event) noexcept;
	void onDestroy() noexcept;
	std::string string() const noexcept;
	void string(const std::string &string) noexcept;
	sf::FloatRect getGlobalBounds() const noexcept;
	void toggle(bool _switch) noexcept;
	bool getSelected() const noexcept;

      protected:
	sf::Color _color;
	uint32_t _charSize;
	std::string _placeholder;
	sf::String _content;
	const sf::Font &_font;
	Text &_text;
	float _prevTime;
	bool _blink;
	bool _selected;
	bool _clicked;
};

class CustomBox : public InputBox {
      public:
	CustomBox(Scene &scene, const sf::Font &font,
		  const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
		  const std::string &placeholder = "...", const sf::Color &color = sf::Color::White,
		  uint32_t characterSize = 32, const std::string &char_accepted = "") noexcept;
	void onEvent(const sf::Event &event) noexcept;

      protected:
	std::string _chars;
};
} // namespace sfs
