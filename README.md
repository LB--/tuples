tuples [![Build Status](https://webapi.biicode.com/v1/badges/LB/LB/tuples/master)](https://www.biicode.com/LB/tuples)
======

Tuples are useful for acting as arrays of types in template metaprogramming, often called type vectors. This library has boilerplate code for dealing with tuples at compile-time and also some utility functions.

*This library requires that your compiler support C++1z (the C++ standard _after_ C++14)*

## Usage
Instead of using `std::tuple`, you should use `LB::tuples::tuple` because it does not try to hold data. `std::tuple` was used originally until it was found that there are issues with using `void` and abstract classes.

### `tuple_unpack`
TODO

### `tuple_template_forward`
Takes the types stored in an `LB::tuples::tuple` or a `std::tuple` and uses them as template parameters to the given template.

For example, you could use it to convert between `LB::tuples::tuple` and `std::tuple`:
```cpp
//convert LB::tuples::tuple to std::tuple
using t1 = tuples::tuple<int, int, float>;
using t2 = tuples::tuple_template_forward<std::tuple, t1>::type;
static_assert(std::is_same<t2, std::tuple<int, int, float>>::value, "t1 != t2");

//convert std::tuple to LB::tuples::tuple
using t3 = std::tuple<float, int, double>;
using t4 = tuples::tuple_template_forward<tuples::tuple, t3>::type;
static_assert(std::is_same<t4, tuples::tuple<float, int, double>>::value, "t3 != t4");
```

### `tuple_type_cat`
Concatenates the types in two or more tuples in left-to-right order.

Example:
```cpp
using t1 = LB::tuples::tuple<int>;
using t2 = LB::tuples::tuple<float>;
using t3 = typename LB::tuples::tuple_type_cat<t1, t2>::type;
static_assert(std::is_same<t3, LB::tuples::tuple<int, float>>::value, "t1 + t2 != t3");
```

### `tuple_contains`
Checks if a tuple contains the given type.

Example:
```cpp
using t1 = LB::tuples::tuple<int, int>;
using t2 = LB::tuples::tuple<int, float>;
static_assert(!LB::tuples::tuple_contains<t1, float>::value, "t1 contains float");
static_assert(LB::tuples::tuple_contains<t2, float>::value, "t2 doesn't contain float");
```

### `tuple_prune`
Takes an `LB::tuples::tuple` and removes duplicate types without rearranging the order of the types.

Example:
```cpp
using pruned_t = typename LB::tuples::tuple_prune
<
	LB::tuples::tuple<void, void, int, void, int, short, void, short, int, short>
>::type;
static_assert(std::is_same<pruned_t, LB::tuples::tuple<void, int, short>>::value, "tuple_prune is broken");
```

### `multi_assert`
TODO
