#include <Lia/list/folds.hpp>
#include <Lia/prettyprint.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace lia::operators;

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    std::cout << "10! == " << lia::product(v) << '\n';
    std::cout << "Sum is: " << lia::sum(v) << '\n';
    std::cout << "Folding: " << lia::foldl(v, [](int x, int y) { return x * y + 11; }, 10);
    std::cout << "\n\nConcatenation: \n";
    std::vector<std::string> list = {"hello", " world!"};
    std::cout << "Before: " << list << '\n';
    std::cout << "After: " << lia::concat(list);
}