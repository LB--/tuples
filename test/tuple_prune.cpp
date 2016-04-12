#include "tuples.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	static_assert(std::is_same
	<
		tuple<void, int, short>,
		typename tuple_prune<tuple<void, void, int, void, int, short, void, short, int, short>
	>::type>::value, "tuple_prune is broken");
}
