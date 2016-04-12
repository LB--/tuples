#include "tuples.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	using t1 = tuple<int>;
	using t2 = tuple<float>;
	using t3 = tuple_type_cat_t<t1, t2>;
	static_assert(std::is_same<t3, tuple<int, float>>{}, "t1 + t2 != t3");
}
