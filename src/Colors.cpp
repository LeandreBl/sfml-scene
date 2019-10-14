#include "Colors.hpp"

namespace sfs
{
std::ostream &operator<<(std::ostream &os, const sf::Color &color)
{
	os << "(" << static_cast<unsigned int>(color.r) << ", "
	   << static_cast<unsigned int>(color.g) << ", "
	   << static_cast<unsigned int>(color.b);
	if (color.a != 0)
		os << ", " << static_cast<unsigned int>(color.a);
	os << ")";
	return os;
}
} // namespace sfs