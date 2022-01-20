#include "sudoku.hpp"

int main()
{
    auto s = sudoku();
    std::cin >> s;
    s.solve();
    s.print();
}