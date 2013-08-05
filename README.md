## Lia

Lia is a functional programming library that includes list comprehensions using Haskell-like syntax and semantics. Every function returns a new list; that is to say that the old list is not modified in any shape or form. With move semantics, temporaries created will be moved so no copies will be made for multiple chained function calls.

### Example

```cpp
#include <iostream>
#include <vector>
#include <Lia/list.hpp>
#include <Lia/functional/objects.hpp>

int main() {
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    auto evens = lia::filter(vec, lia::even()); // Contains: [2, 4, 6, 8, 10]
    auto times_five = lia::map(evens, lia::curry(lia::multiplies(), 5)); // Contains: [10, 20, 30, 40, 50]
    // They can even be in a chained call
    auto single = lia::map(lia::filter(vec, lia::even()), lia::curry(lia::multiplies(), 5));
    // single == times_five
    auto products = lia::product(vec); // 1*2*3*4*5*6... == 10! == 3628800
}
```

