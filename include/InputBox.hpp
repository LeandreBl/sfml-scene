#pragma once

#include <SFML/Graphics.hpp>

#include "UI.hpp"
#include "BasicShape.hpp"

namespace sfs
{
class InputBox : public UI
{
    public:
		InputBox(const sf::Font &font,
		 const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
		 const std::string &placeholder = "...",
		 const sf::Color &color = sf::Color::White,
		 uint32_t characterSize = 32) noexcept;
		InputBox(const InputBox &) noexcept = default;
		InputBox &operator=(InputBox &) noexcept = default;
		void start(Scene &scene) noexcept;
		void update(Scene &scene) noexcept;
		void onEvent(Scene &scene, const sf::Event &event) noexcept;
		std::string string() const noexcept;
		void string(const std::string &string) noexcept;
    	sf::FloatRect getGlobalBounds() const noexcept;
		void toggle(bool _switch) noexcept {_selected = _switch;};
		bool getSelected() const noexcept {return _selected;};

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

class CustomBox : public InputBox
{
	public:
		CustomBox(const sf::Font &font,
			 const sf::Vector2f &position = sf::Vector2f(0.f, 0.f),
		 	const std::string &placeholder = "...",
		 	const sf::Color &color = sf::Color::White,
		 	uint32_t characterSize = 32, const std::string &char_accepted = "") noexcept
				: InputBox(font, position, placeholder, color, characterSize), _chars(char_accepted)
				{};
			void onEvent(Scene &scene, const sf::Event &event) noexcept
			{
				InputBox::onEvent(scene, event);
				if (event.type == sf::Event::TextEntered && _selected) {
					auto found = _chars.find(event.text.unicode);
					if (found == std::string::npos) {
						auto content = _content.toWideString();
						if (content.size()) {
							content.pop_back();
							_content = content;
						}
					}
				}
			}
	protected:
		std::string _chars;
};
} // namespace sfs
