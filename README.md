## Welcome

Lia is a functional programming library that includes list comprehensions using Haskell-like syntax and semantics. Every function returns a new list; that is to say that the old list is not modified in any shape or form. With move semantics, temporaries created will be moved so no copies will be made for multiple chained function calls.

## List Comprehensions

List comprehensions are a way to create lists based on existing lists. It builds on the notion of [set-builder notation][sbn]. While C++ doesn't have the syntactic construct to generate these on the fly, we can emulate the approach by using functions similar to the way other languages do such as Haskell and C# with LINQ. Most of the list comprehension functions are container agnostic. However there is no effort to support non-associative containers which includes:

- `std::map`
- `std::multimap`
- `std::set`
- `std::multiset`
- `std::unordered_map`
- `std::unordered_multimap`
- `std::unordered_set`
- `std::unordered_multiset`

Support for `std::string` where typically not possible is given through uses of SFINAE, this also applies to efficient usage of operations of `std::list` which doesn't use the [erase-remove idiom][eri] and has its own member functions instead.

[sbn]: https://en.wikipedia.org/wiki/Set-builder_notation
[eri]: https://en.wikipedia.org/wiki/Erase-remove_idiom

### Example

```cpp
#include <iostream>
#include <vector>
#include <Lia/list.hpp>
#include <Lia/functional/objects.hpp>

int main() {
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    auto evens = lia::filter(vec, lia::even()); // Contains: [2, 4, 6, 8, 10]
    // times_five contains: [10, 20, 30, 40, 50]
    auto times_five = lia::map(evens, lia::curry(lia::multiplies(), 5)); 
    // They can even be in a chained call
    auto single = lia::map(lia::filter(vec, lia::even()), lia::curry(lia::multiplies(), 5));
    // single == times_five
    auto products = lia::product(vec); // 1*2*3*4*5*6... == 10! == 3628800
}
```
