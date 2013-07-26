#include "Lia/list/basics.hpp"
#include "Lia/list/folds.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

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

void fold_test() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    auto b = lia::concat(std::vector<std::vector<int>>{{1,2,3},{4,5,6,7,8,9,10}});
    assert(lia::foldl(v, [](int x, int y) { return x + y; }, 0) == lia::sum(v) && "foldl or foldl1");
    assert(lia::foldr(v, [](int x, int y) { return x * y; }, 1) == lia::product(v) && "foldr or foldl1");
    assert(lia::foldr1(std::vector<int>{4,5,6,7,8,9,10}, [](int x, int y) { return x * y; }) == 604800 && "foldr1");
    assert(lia::all(std::vector<bool>{1,1,1,1,1,1,1,1}) && "all(bool)");
    assert(lia::all(std::vector<int>{6,7,8,9,10,11}, [](int x) { return x > 5; }) && "all(pred)");
    assert(lia::any(std::vector<bool>{0,0,0,1,0,1,0,0}) && "any(bool)");
    assert(lia::any(std::vector<int>{4,5,11,9,8}, [](int x) { return x == 5; }) && "any(pred)");
    assert(lia::minimum(std::vector<int>{99,11,11,10}) == 10 && "minimum");
    assert(lia::maximum(std::vector<int>{99,11,11,10}) == 99 && "maximum");
    assert(lia::concat(std::vector<std::string>{"Hello", "World"}) == "HelloWorld" && "concat(str)");
    assert(b == v && "concat");
}

int main() {
    basic_test();
    transform_test();
    fold_test();
}