tuples [![travis](https://travis-ci.org/LB--/tuples.svg?branch=tuples)](https://travis-ci.org/LB--/tuples)
======

Tuples are useful for acting as arrays of types in template metaprogramming, often called type vectors. This library has boilerplate code for dealing with tuples at compile-time and also some utility functions.

**Some support for C++1z is required.**

## Usage
### CMake
From the `cmake` directory, copy the `FindLB` directory to a place in your `CMAKE_MODULE_PATH`.
Then, add `find_package(LB/tuples REQUIRED)` to your CMake script.
You may need to set the CMake variable `LB/tuples_ROOT` if you installed to a nonstandard location.
Finally, link to the `LB::tuples` imported target with `target_link_libraries()`.

### C++
`#include <LB/tuples/tuples.hpp>`

Note that alongside `std::tuple` there is also `LB::tuples::tuple` - the latter does not hold any data whereas the former does.
`std::tuple` does not support `void` or abstract types, whereas `LB::tuples::tuple` does - the latter should be your default.

#### `tuple_template_forward`
Takes the types stored in an `LB::tuples::tuple` or a `std::tuple` and uses them as template parameters to the given template.
Due to limitations in the C++ language, you cannot forward types to a template that has value template arguments even if they are defaulted - instead, you should create a proxy template in that situation.

For [example](https://github.com/LB--/tuples/blob/tuples/test/tuple_template_forward.cpp), you could use it to convert between `LB::tuples::tuple` and `std::tuple`:
```cpp
//convert LB::tuples::tuple to std::tuple
using t1 = LB::tuples::tuple<int, int, float>;
using t2 = LB::tuples::tuple_template_forward_t<std::tuple, t1>;
static_assert(std::is_same<t2, std::tuple<int, int, float>>{}, "t1 != t2");

//convert std::tuple to LB::tuples::tuple
using t3 = std::tuple<float, int, double>;
using t4 = LB::tuples::tuple_template_forward_t<LB::tuples::tuple, t3>;
static_assert(std::is_same<t4, LB::tuples::tuple<float, int, double>>{}, "t3 != t4");
```

#### `tuple_forward`
Takes the values in a `std::tuple` and calls a function with them.
See [`std::apply`](http://en.cppreference.com/w/cpp/utility/apply) - `tuple_forward` is an implementation for cases when `std::apply` is not available.
If you have access to `std::apply` and/or `std::invoke`, please use them instead as they are more robust.
When C++17 is finalized and major compilers and standard library implementations have support for `std::apply`, this function will be deprecated.
For obvious reasons, `LB::tuples::tuple` is not supported.

[Example](https://github.com/LB--/tuples/blob/tuples/test/tuple_forward.cpp):
```cpp
static constexpr auto t1 = std::make_tuple(1, 1);
static constexpr auto t2 = std::make_tuple(1, 2);
static_assert(LB::tuples::tuple_forward(std::equal_to<int>{}, t1), "t1 doesn't contain the same value twice");
static_assert(!LB::tuples::tuple_forward(std::equal_to<int>{}, t2), "t2 contains the same value twice");
```

#### `tuple_type_cat`
Concatenates the types in zero or more `LB::tuples::tuple`s in left-to-right order.
`std::tuple` is not supported.

[Example](https://github.com/LB--/tuples/blob/tuples/test/tuple_type_cat.cpp):
```cpp
using t1 = LB::tuples::tuple<int>;
using t2 = LB::tuples::tuple<float>;
using t3 = typename LB::tuples::tuple_type_cat_t<t1, t2>;
static_assert(std::is_same<t3, LB::tuples::tuple<int, float>>{}, "t1 + t2 != t3");
```

#### `tuple_contains`
Checks if an `LB::tuples::tuple` contains the given type.
`std::tuple` is not supported.

[Example](https://github.com/LB--/tuples/blob/tuples/test/tuple_contains.cpp):
```cpp
using t1 = LB::tuples::tuple<int, int>;
using t2 = LB::tuples::tuple<int, float>;
static_assert(!LB::tuples::tuple_contains<t1, float>{}, "t1 contains float");
static_assert(LB::tuples::tuple_contains_v<t2, float>, "t2 doesn't contain float");
```

#### `tuple_prune`
Takes an `LB::tuples::tuple` and removes duplicate types without rearranging the order of the types.
`std::tuple` is not supported.

[Example](https://github.com/LB--/tuples/blob/tuples/test/tuple_prune.cpp):
```cpp
using pruned_t = LB::tuples::tuple_prune_t
<
	LB::tuples::tuple<void, void, int, void, int, short, void, short, int, short>
>;
static_assert(std::is_same<pruned_t, LB::tuples::tuple<void, int, short>>{}, "tuple_prune is broken");
```

#### `multi_assert`
Given a template that takes zero or more template arguments and yields a `value` member, takes all the given `LB::tuples::tuple`s and/or `std::tuple`s and forwards their contents to the given template individually.
The resulting `value` is all the intermediate `value`s combined with `&&`.
In other words, asserts that multiple tuples satisfy a requirement.

[Example](https://github.com/LB--/tuples/blob/tuples/test/multi_assert.cpp):
```cpp
using t1 = LB::tuples::tuple<int, int>;
using t2 = LB::tuples::tuple<float, float>;
using t3 = LB::tuples::tuple<int, float>;

static_assert(LB::tuples::multi_assert<std::is_same, t1, t2>{}, "t1 or t2 isn't homogeneous");
static_assert(!LB::tuples::multi_assert_v<std::is_same, t1, t2, t3>, "t1, t2 and t3 are homogeneous");
```
