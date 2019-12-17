#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

namespace sfs {
class UI : public GameObject {
      public:
	const uint32_t defaultLayer = 0;

	UI(const std::string &name, const sf::Vector2f &position = sf::Vector2f(0.f, 0.f)) noexcept;
};
} // namespace sfs