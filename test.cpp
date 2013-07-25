#include "Lia/list/basic.hpp"
#include <vector>
#include <iostream>

void basic_test() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10,11};
    std::cout << "Head: " << lia::head(v) << " Last: " << lia::last(v);
    std::cout << "\nEmpty? " << std::boolalpha << lia::null(v);
    std::cout << " Length: " << lia::length(v);
    auto g = lia::tail(v);
    auto appended = lia::append(v, g);
    std::cout << "\nTail: ";
    for(auto&& i : g)
        std::cout << i << ' ';
    std::cout << "\nRegular: ";
    for(auto&& i : v)
        std::cout << i << ' ';
    std::cout << "\nAppended: ";
    for(auto&& i : appended)
        std::cout << i << ' ';
}

int main() {
    basic_test();
}