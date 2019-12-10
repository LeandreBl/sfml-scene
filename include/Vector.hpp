#pragma once

#include <math.h>

#include <SFML/System.hpp>

namespace sfs
{
template <typename T, typename T2>
double distance(const sf::Vector2<T> &a, const sf::Vector2<T2> &b) noexcept
{
	return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

template <typename T, typename T2>
double angle(const sf::Vector2<T> &a, const sf::Vector2<T2> &b) noexcept
{
	return atan2(b.y - a.y, b.x - a.x);
}

} // namespace sfs