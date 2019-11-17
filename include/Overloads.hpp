#pragma once

#include "GameObject.hpp"

namespace sfs {

std::ostream &operator<<(std::ostream &os, const sfs::GameObject &object) noexcept;

template <typename T> std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &v)
{
	os << '(' << v.x << ", " << v.y << ')';
	return os;
}

template <typename T> std::ostream &operator<<(std::ostream &os, const sf::Vector3<T> &v) noexcept
{
	os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	return os;
}

template <typename T> std::ostream &operator<<(std::ostream &os, const sf::Rect<T> &rect) noexcept
{
	os << "[(" << rect.top << ", " << rect.left << "), (" << rect.width << ", " << rect.height
	   << ")]";
	return os;
}
}