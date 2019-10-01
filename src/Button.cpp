#include "Scene.hpp"
#include "Button.hpp"

namespace sfs
{
Button::Button(const sf::Vector2f &position, const sf::Texture &texture,
	       const std::function<void()> &onClick, const sf::Font &font,
	       const std::string &text, const sf::Color &color,
	       uint32_t charSize) noexcept
    : UI(position, "Button"), _sprite(addComponent<Sprite>(texture)),
      _text(addComponent<Text>(font, text, color, charSize)),
      _onClick(std::move(onClick)), _clickPos(0, 0), _movePos(0, 0),
      _moved(false), _pressed(false)
{
}

sf::FloatRect Button::getGlobalBounds() const noexcept
{
  return _sprite.getGlobalBounds();
}
  
void Button::setText(const std::string &buttonText) noexcept
{
	_text.setString(buttonText);
}

void Button::setTexture(const sf::Texture &texture, bool resetRect) noexcept
{
	_sprite.setTexture(texture, resetRect);
}

void Button::setTexture(const sf::Texture &texture,
			const sf::IntRect &rectangle) noexcept
{
	_sprite.setTexture(texture);
	_sprite.setTextureRect(rectangle);
}

void Button::setOnClick(const std::function<void()> &onClick) noexcept
{
	_onClick = onClick;
}

void Button::setFont(const sf::Font &font) noexcept
{
	_text.setFont(font);
}

void Button::setTextSize(uint32_t size) noexcept
{
	_text.setCharacterSize(size);
}

void Button::setTextColor(const sf::Color &color) noexcept
{
	_text.setFillColor(color);
}

void Button::setScale(const sf::Vector2f &scale) noexcept
{
  _sprite.setScale(scale);
}
  
void Button::start(Scene &scene) noexcept
{
	scene.subscribe(*this, sf::Event::MouseButtonPressed);
	scene.subscribe(*this, sf::Event::MouseButtonReleased);
	scene.subscribe(*this, sf::Event::MouseMoved);
}

void Button::update(Scene &) noexcept
{
	if (_pressed) {
		_pressed = _sprite.getGlobalBounds().contains(_clickPos);
		if (_pressed) {
			_sprite.setColor(sf::Color(110, 110, 110));
			_onClick();
		} else {
			_moved = false;
		}
	} else if (_moved) {
		_moved = _sprite.getGlobalBounds().contains(_movePos);
		if (_moved)
			_sprite.setColor(sf::Color(170, 170, 170));
	} else {
		_sprite.setColor(sf::Color::White);
	}
	auto rect = _sprite.getGlobalBounds();
	auto textRect = _text.getGlobalBounds();
	auto textLRect = _text.getLocalBounds();
	_text.setPosition(rect.left + (rect.width - textRect.width) / 2.f
				  - textLRect.left,
			  rect.top + (rect.height - textRect.height) / 2.f
				  - textLRect.top);
}

void Button::onEvent(Scene &, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::MouseMoved) {
		_moved = true;
		_movePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
	} else if (event.type == sf::Event::MouseButtonReleased) {
		_pressed = false;
		_clickPos =
			sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	} else if (event.type == sf::Event::MouseButtonPressed) {
		_pressed = true;
		_clickPos =
			sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
	}
}
} // namespace sfs
