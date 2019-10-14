#pragma once

#include <IComponent.hpp>

namespace sfs
{
class Offset : public sfs::IComponent
{
      public:
	Offset(const sf::Vector2f &Parentpos, sf::Vector2f offset) noexcept
	    : _parentPos(Parentpos), _offset(offset){};
	void update(sfs::Scene &, GameObject &go) noexcept
	{
		sf::Vector2f newPos;
		newPos.x = _parentPos.x + _offset.x;
		newPos.y = _parentPos.y + _offset.y;
		go.setPosition(newPos);
	}

      protected:
	const sf::Vector2f &_parentPos;
	sf::Vector2f _offset;
};
} // namespace sfs