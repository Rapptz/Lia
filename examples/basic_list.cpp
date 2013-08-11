#include <Lia/list/basics.hpp>
#include <Lia/prettyprint.hpp>
#include <vector>
#include <iostream>

using namespace lia::operators;

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    std::cout << "First element: " << lia::head(v);
    std::cout << "\nLast element: " << lia::last(v);
    std::cout << "\nEvery element but the first: " << lia::tail(v);
    std::cout << "\nEvery element but the last: " << lia::init(v);
    std::cout << "\nCheck if the list is empty.. ";
    if(lia::null(v)) {
        std::cout << "It's empty\n";
    }
    std::cout << "And of course the size is: " << lia::length(v);
}