#include "InputBox.hpp"
#include "Colors.hpp"

namespace sfs {
InputBox::InputBox(Scene &scene, const sf::Font &font, const sf::Vector2f &position,
		   const std::string &placeholder, const sf::Color &color,
		   uint32_t characterSize) noexcept
	: UI(scene, "InputBox", position)
	, _color(color)
	, _charSize(characterSize)
	, _placeholder(placeholder)
	, _content("")
	, _font(font)
	, _text(addComponent<Text>(font, placeholder, color, characterSize))
	, _prevTime(0)
	, _blink(true)
	, _selected(false)
	, _clicked(false)
{
}

void InputBox::start() noexcept
{
	_prevTime = scene().realTime();
	subscribe(sf::Event::MouseButtonPressed);
	subscribe(sf::Event::MouseButtonReleased);
	subscribe(sf::Event::TextEntered);
}

void InputBox::update() noexcept
{
	float t = scene().realTime();

	_text.setPosition(getPosition());
	if (t - _prevTime >= 1.f) {
		_blink = !_blink;
		_prevTime = t;
	}
	if (_content.isEmpty() && !_selected) {
		_text.setString(_placeholder);
		_text.setFillColor(_color / 2);
	}
	else {
		_text.setFillColor(_color);
		if (_blink && _selected)
			_content += '|';
		_text.setString(_content);
		if (_blink && _selected) {
			_content.erase(_content.getSize() - 1, _content.getSize());
		}
	}
}

void InputBox::onEvent(const sf::Event &event) noexcept
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			_clicked = true;
		}
		else {
			_clicked = false;
			_selected = false;
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased
		 && _text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)
		 && _clicked == true) {
		_selected = true;
	}
	if (_selected == true) {
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b') {
				if (_content.getSize())
					_content.erase(_content.getSize() - 1, _content.getSize());
			}
			else if (event.text.unicode == '\r') {
				_selected = false;
				_clicked = false;
			}
			else {
				_content += event.text.unicode;
			}
		}
	}
}

void InputBox::onDestroy() noexcept
{
}

std::string InputBox::string() const noexcept
{
	return _content.toAnsiString();
}

void InputBox::string(const std::string &string) noexcept
{
	_content = string;
}

sf::FloatRect InputBox::getGlobalBounds() const noexcept
{
	return _text.getGlobalBounds();
}

void InputBox::toggle(bool _switch) noexcept
{
	_selected = _switch;
}

bool InputBox::getSelected() const noexcept
{
	return _selected;
}

////////////////////////////////////////////////////////////////////////////////

CustomBox::CustomBox(Scene &scene, const sf::Font &font, const sf::Vector2f &position,
		     const std::string &placeholder, const sf::Color &color, uint32_t characterSize,
		     const std::string &char_accepted) noexcept
	: InputBox(scene, font, position, placeholder, color, characterSize)
	, _chars(char_accepted)
{
}

void CustomBox::onEvent(const sf::Event &event) noexcept
{
	InputBox::onEvent(event);
	if (event.type == sf::Event::TextEntered && _selected) {
		if (event.text.unicode != '\b') {
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
}

} // namespace sfs
