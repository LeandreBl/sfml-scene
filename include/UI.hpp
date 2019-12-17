#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.hpp"

namespace sfs {
class UI : public GameObject {
      public:
	UI(Scene &scene, const std::string &name,
	   const sf::Vector2f &position = sf::Vector2f(0.f, 0.f), uint32_t layer = 2)
	noexcept;
};
} // namespace sfs