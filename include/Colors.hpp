#pragma once

#include <SFML/Graphics.hpp>

namespace sfs
{
template <typename T>
sf::Color operator/(const sf::Color &color, const T &div)
{
	return sf::Color(color.r / div, color.g / div, color.b / div);
}

template <typename T>
sf::Color &operator/=(sf::Color &color, const T &div)
{
	color.r /= div;
	color.g /= div;
	color.b /= div;
	return color;
}

template <typename T>
sf::Color operator*(const sf::Color &color, const T &mul)
{
	return sf::Color(color.r * mul, color.g * mul, color.b * mul);
}

template <typename T>
sf::Color &operator*=(sf::Color &color, const T &mul)
{
	color.r *= mul;
	color.g *= mul;
	color.b *= mul;
	return color;
}
} // namespace sfs