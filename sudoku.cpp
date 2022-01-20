#include "sudoku.hpp"
#include <stack>
#include <algorithm>

sudoku::sudoku()
{
    matrix.resize(81,0);
}

std::size_t sudoku::map(std::size_t u, std::size_t v) const
{
    return 9 * v + u;
}

std::istream &operator>>(std::istream &is, sudoku &s)
{
    int i;
    while (is >> i)
    {
        s.matrix.push_back(i);
    }
    return is;
}

void sudoku::print()
{
    for (std::size_t i; i < 9; i++){
        for (std::size_t j; j < 9; j++)
            std::cout << this->matrix[map(i, j)] << " ";
        std::cout << "\n";
    }
}

bool sudoku::check(std::size_t row, std::size_t col, std::size_t n)
{
    for (std::size_t i = 0; i < 9; ++i)
        if (matrix[map(row,i)]== n || matrix[map(i,col)] == n)
            return false;

    if (row < 3){
        if (col < 3){
            for (std::size_t i = 0; i < 3; ++i)
                for (std::size_t j = 0; j < 3; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
        else if (2 < col && col < 6){
            for (std::size_t i = 0; i < 3; ++i)
                for (std::size_t j = 3; j < 6; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
        else{
            for (std::size_t i = 0; i < 3; ++i)
                for (std::size_t j = 6; j < 9; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
    }

    else if (2 < row && row < 6){
        if (col < 3){
            for (std::size_t i = 3; i < 6; ++i)
                for (std::size_t j = 0; j < 3; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
        else if (2 < col && col < 6){
            for (std::size_t i = 3; i < 6; ++i)
                for (std::size_t j = 3; j < 6; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
        else{
            for (std::size_t i = 3; i < 6; ++i)
                for (std::size_t j = 6; j < 9; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
    }
    else{
        if (col < 3){
            for (std::size_t i = 6; i < 9; ++i)
                for (std::size_t j = 0; j < 3; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
        else if (2 < col && col < 6){
            for (std::size_t i = 6; i < 9; ++i)
                for (std::size_t j = 3; j < 6; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
        else{
            for (std::size_t i = 6; i < 9; ++i)
                for (std::size_t j = 6; j < 9; ++j)
                    if (matrix[map(i,j)] == n)
                        return false;
        }
    }
    return true;
}

void sudoku::solve()
{
    std::stack<std::pair<std::size_t, std::size_t>> gap;
    std::stack<std::pair<std::size_t, std::size_t>> store_sol;

    for (std::size_t i = 0; i < 9; ++i)
        for (std::size_t j = 0; j < 9; ++j)
            if (matrix[map(i, j)] == 0)
                gap.push({i, j});

    while (!gap.empty()){
        bool solution = false;
        for (std::size_t k = matrix[map(gap.top().first, gap.top().second)] + 1; !solution && k <= 9; ++k){
            if (check(gap.top().first, gap.top().second, k)){
                matrix[map(gap.top().first, gap.top().second)] = k;
                solution = true;
            }
        }

        if (!solution){
            gap.push(store_sol.top());
            store_sol.pop();
            matrix[map(gap.top().first, gap.top().second)] = 0;
        }
        else{
            store_sol.push(gap.top());
            gap.pop();
        }
    }
}