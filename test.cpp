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
    assert((lia::scanl(std::vector<int>{1,2,3}, [](int x, int y) { return x + y; }, 10) == std::vector<int>{10,11,13,16}) && "scanl");
    assert((lia::scanl1(std::vector<int>{1,2,3}, [](int x, int y) { return x + y; }) == std::vector<int>{1,3,6}) && "scanl1");
}

void sublist_test() {
    std::string str("Hello World!");
    assert(lia::take(str, 5) == "Hello" && "take(str)");
    assert((lia::take(std::vector<int>{1,2,3,4,5}, 3) == std::vector<int>{1,2,3}) && "take(1)");
    assert((lia::take(std::vector<int>{1,2}, 3) == std::vector<int>{1,2}) && "take(2)");
    assert((lia::take(std::vector<int>{}, 3).empty()) && "take(empty)");
    assert((lia::drop(str, 6) == "World!") && "drop(str)");
    assert((lia::split_at(str, 6) == std::make_pair(lia::take(str, 6), lia::drop(str, 6))) && "split_at");
    std::vector<int> v = {1,2,3,4,1,2,3,4};
    std::vector<int> w = {1,2,3};
    assert((lia::take_while(v, [](int x) { return x < 3; }) == std::vector<int>{1,2}) && "take_while");
    assert((lia::take_while(w, [](int x) { return x < 9; }) == w) && "take_while(2)");
    assert((lia::drop_while(v, [](int x) { return x < 3; }) == std::vector<int>{3,4,1,2,3,4}) && "drop_while");
    assert((lia::drop_while(w, [](int x) { return x < 9; }).empty()) && "drop_while(2)");   
}

void search_test() {
    std::vector<int> v = {1,2,3,4,5};
    assert(lia::elem(v, 5) && "elem(true)");
    assert(!lia::elem(v, 6) && "elem(false)");
    assert(lia::not_elem(v, 7) && "not_elem");
    assert((*lia::find(v, [](int x) { return x % 2 == 0; }) == 2) && "find(1)");
    assert((lia::find(v, [](int x) { return x == 6; }) == v.end()) && "find(2)");
    assert((lia::filter(v, [](int x) { return x % 2 == 0; }) == std::vector<int>{2,4}) && "filter");
    assert((lia::elem_index(v, 2) == 1) && "elem_index");
    assert((lia::elem_index(v, 6) == lia::npos) && "elem_index(npos)");
    assert((lia::elem_indices(v, 5) == std::vector<size_t>{4}) && "elem_indices");
    assert((lia::find_index(v, [](int x) { return x % 2 == 0; }) == 1) && "find_index");
    assert((lia::find_index(v, [](int x) { return x == 7; }) == lia::npos) && "find_index(npos)");
    assert((lia::find_indices(v, [](int x) { return x % 2 == 0; }) == std::vector<size_t>{1,3}) && "find_indices");
}

int main() {
    basic_test();
    transform_test();
    fold_test();
    sublist_test();
    search_test();
}