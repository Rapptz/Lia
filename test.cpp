#include "Lia/list/basics.hpp"
#include "Lia/list/transforms.hpp"
#include <vector>
#include <iostream>

template<class Elem, class Traits, class Cont>
std::basic_ostream<Elem,Traits>& operator<<(std::basic_ostream<Elem,Traits>& out, const Cont& cont) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    if(first == last) {
        out << "[]";
        return out;
    }
    else {
        out << '[' << *first++;
    }
    while(first != last) {
        out << ',' << *first++;
    }
    out << ']';
    return out;
}


void basic_test() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10,11};
    std::cout << "Head: " << lia::head(v) << " Last: " << lia::last(v);
    std::cout << "\nEmpty? " << std::boolalpha << lia::null(v);
    std::cout << " Length: " << lia::length(v);
    auto g = lia::tail(v);
    auto appended = lia::append(v, g);
    std::cout << "\nTail: " << g;
    std::cout << "\nRegular: " << v;
    std::cout << "\nAppended: " << appended << '\n';
}

void transform_test() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10,11};
    std::cout << "Map: " << lia::map(v, [](int v) { return v > 4; });
    std::cout << "\nReverse: " << lia::reverse(v);
    std::cout << "\nIntersperse: " << lia::intersperse(v, 0);
    std::cout << "\nSubsequences: " << lia::subsequences(std::vector<int>{1,2,3,4});
    std::cout << "\nPermutations: " << lia::permutations(std::vector<int>{1,2,3,4});
}

int main() {
    basic_test();
    transform_test();
}