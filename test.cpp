#include "Lia/list.hpp"
#include <vector>
#include <string>
#include <cassert>

void basic_test() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10,11};
    assert(lia::head(v) == 1 && "head");
    assert(lia::last(v) == 11 && "last");
    assert(lia::null(v) == false && "null");
    assert(lia::length(v) == 11 && "length");
    assert((lia::tail(std::vector<int>{1,2,3,4}) == std::vector<int>{2,3,4}) && "tail");
    assert((v == std::vector<int>{1,2,3,4,5,6,7,8,9,10,11}) && "const-correctness");
    assert((lia::append(std::vector<int>{1,2,3},{4,5,6}) == std::vector<int>{1,2,3,4,5,6}) && "append");
    assert((lia::append(std::string("one"), std::string("two")) == "onetwo") && "append(str)");
}

void transform_test() {
    std::vector<int> v = {1,2,3,4,5};
    assert((lia::map(v, [](int x) { return x > 4;}) == std::vector<bool>{false,false,false,false,true}) && "map");
    assert((lia::reverse(v) == std::vector<int>{5,4,3,2,1}) && "reverse");
    assert((lia::intersperse(v, 0) == std::vector<int>{1,0,2,0,3,0,4,0,5}) && "intersperse");
    assert((lia::subsequences(std::vector<int>{1,2,3,4}).size() == 16) && "subsequences");
    assert((lia::permutations(std::vector<int>{1,2,3,4}).size() == 24) && "permutations");
    assert((v == std::vector<int>{1,2,3,4,5}) && "const-correctness");
}

void fold_test() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    auto a = std::vector<std::vector<int>>{{1,2,3},{4,5,6,7,8,9,10}};
    auto b = lia::concat(a);
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
    auto c = lia::map(a, [](const std::vector<int>& i) { return lia::append(i, std::vector<int>{1,2,3}); });
    auto w = lia::concat(c);
    assert(lia::concat_map(a, [](const std::vector<int>& i) { return lia::append(i, std::vector<int>{1,2,3});}) == w && "concat_map");
    assert((lia::intercalate(std::vector<std::vector<int>>{{0,1},{4,5}}, {2,3}) == std::vector<int>{0,1,2,3,4,5}) && "intercalate");
}

void sublist_test() {
    std::string str("Hello World!");
    assert(lia::take(str, 5) == "Hello" && "take(str)");
    assert((lia::take(std::vector<int>{1,2,3,4,5}, 3) == std::vector<int>{1,2,3}) && "take(1)");
    assert((lia::take(std::vector<int>{1,2}, 3) == std::vector<int>{1,2}) && "take(2)");
    assert((lia::take(std::vector<int>{}, 3) == std::vector<int>{}) && "take(empty)");
    assert((lia::drop(str, 6) == "World!") && "drop(str)");
}

int main() {
    basic_test();
    transform_test();
    fold_test();
}