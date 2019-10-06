#include "InputBox.hpp"
#include "Colors.hpp"

namespace sfs
{
InputBox::InputBox(const sf::Font &font, const sf::Vector2f &position,
		   const std::string &placeholder, const sf::Color &color,
		   uint32_t characterSize) noexcept
    : UI(position, "InputBox"), _color(color), _charSize(characterSize),
      _placeholder(placeholder), _content(""), _font(font),
      _text(addComponent<Text>(font, placeholder, color, characterSize)),
      _prevTime(0), _blink(true), _selected(false), _clicked(false)
{
}

void InputBox::start(Scene &scene) noexcept
{
	_prevTime = scene.realTime();
	scene.subscribe(*this, sf::Event::MouseButtonPressed);
	scene.subscribe(*this, sf::Event::MouseButtonReleased);
	scene.subscribe(*this, sf::Event::TextEntered);
}

void InputBox::update(Scene &scene) noexcept
{
	float t = scene.realTime();

	_text.setPosition(getPosition());
	if (t - _prevTime >= 1.f) {
		_blink = !_blink;
		_prevTime = t;
	}
	if (_content.isEmpty() && !_selected) {
		_text.setString(_placeholder);
		_text.setFillColor(_color / 2);
	} else {
		_text.setFillColor(_color);
		if (_blink && _selected)
			_content += '|';
		_text.setString(_content);
		if (_blink && _selected) {
			_content.erase(_content.getSize() - 1,
				       _content.getSize());
		}
	}
}

void InputBox::onEvent(Scene &, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (_text.getGlobalBounds().contains(event.mouseButton.x,
						     event.mouseButton.y)) {
			_clicked = true;
		} else {
			_clicked = false;
			_selected = false;
		}
	} else if (event.type == sf::Event::MouseButtonReleased
		   && _text.getGlobalBounds().contains(event.mouseButton.x,
						       event.mouseButton.y)
		   && _clicked == true) {
		_selected = true;
	}
	if (_selected == true) {
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b') {
				if (_content.getSize())
					_content.erase(_content.getSize() - 1,
						       _content.getSize());
			} else if (event.text.unicode == '\r') {
				_selected = false;
				_clicked = false;
			} else {
				_content += event.text.unicode;
			}
		}
	}
} // namespace sfs

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
} // namespace sfs
