#include <iostream>
#include <vector>

class sudoku{
public:
    sudoku();
    friend std::istream &operator>>(std::istream&,sudoku&);
    bool check(std::size_t,std::size_t,std::size_t);
    void solve();
    void print();
private:
    std::size_t map(std::size_t,std::size_t) const;
    std::vector<std::size_t> matrix;
};