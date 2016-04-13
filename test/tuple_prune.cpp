#include "tuple_prune.hpp"

#include <type_traits>

int main() noexcept
{
	using namespace LB::tuples;

	static_assert(std::is_same
	<
		tuple<void, int, short>,
		tuple_prune_t<tuple<void, void, int, void, int, short, void, short, int, short>>
	>{}, "tuple_prune is broken");
}
