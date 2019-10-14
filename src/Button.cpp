#include "Scene.hpp"
#include "Button.hpp"

namespace sfs
{
Button::Button(const sf::Texture &texture, const sf::Font &font,
	       const sf::Vector2f &position,
	       const std::function<void()> &onClick, const std::string &text,
	       const sf::Color &color, uint32_t charSize) noexcept
    : UI(position, "Button"), _sprite(addComponent<Sprite>(texture)),
      _text(addComponent<Text>(font, text, color, charSize)),
      _onClick(std::move(onClick)), _pressed(false)
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

void Button::setRotate(const float &angle) noexcept
{
	_sprite.setRotation(angle);
}

void Button::start(Scene &scene) noexcept
{
	scene.subscribe(*this, sf::Event::MouseButtonPressed);
	scene.subscribe(*this, sf::Event::MouseButtonReleased);
	scene.subscribe(*this, sf::Event::MouseMoved);
}

void Button::update(Scene &) noexcept
{
	auto rect = _sprite.getGlobalBounds();
	auto textRect = _text.getGlobalBounds();
	auto textLRect = _text.getLocalBounds();
	_text.setOffset(sf::Vector2f(
		(rect.width - textRect.width) / 2.f - textLRect.left,
		(rect.height - textRect.height) / 2.f - textLRect.top));
}

static void setColor(sf::Sprite &sprite, float x, float y) noexcept
{
	if (sprite.getGlobalBounds().contains(x, y)) {
		sprite.setColor(sf::Color(170, 170, 170));
	} else {
		sprite.setColor(sf::Color::White);
	}
}

void Button::onEvent(Scene &, const sf::Event &event) noexcept
{
	if (event.type == sf::Event::MouseButtonPressed
	    && _sprite.getGlobalBounds().contains(event.mouseButton.x,
						  event.mouseButton.y)) {
		if (_pressed == false) {
			_pressed = true;
			_sprite.setColor(sf::Color(110, 110, 110));
			_onClick();
		} else {
		}
	} else if (event.type == sf::Event::MouseMoved) {
		setColor(_sprite, event.mouseMove.x, event.mouseMove.y);
	} else if (event.type == sf::Event::MouseButtonReleased) {
		_pressed = false;
		setColor(_sprite, event.mouseButton.x, event.mouseButton.y);
	}
}
} // namespace sfs
