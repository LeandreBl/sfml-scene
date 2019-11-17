#include "Overloads.hpp"

namespace sfs {
std::ostream &operator<<(std::ostream &os, const sfs::GameObject &object) noexcept
{
	os << "{ \"" << object.name() << "\" " << object.getPosition() << " }";
	return os;
}
}