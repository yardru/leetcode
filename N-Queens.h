#pragma once

#include <iostream>
#include <vector>
#include <string>

//51. N-Queens
class Solution51 {
public:
    void run(void) {
        struct {
            int n;
        } tests[] = {
            {10},
            {4},
            {2},
            {1}
        };
        for (auto & test : tests)
            std::cout << solveNQueens(test.n).size() << "!!!\n";
    }

    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::string> board(n, std::string(n, '.'));
        solveNQueensRec(board);
        return std::move(res);
    }
private:
    std::vector<std::vector<std::string>> res;
    struct queen_t {
        int i, j;
    };
    std::vector<queen_t> queens;

    void solveNQueensRec(std::vector<std::string> & board, int row = 0) {
        for (int j = 0; j < board.size(); j++) {
            bool good_place = true;
            for (auto & q : queens)
                if (q.j == j || row - q.i == abs(j - q.j)) {
                    good_place = false;
                    break;
                }
            if (good_place) {
                board[row][j] = 'Q';
                queens.push_back({row, j});
                if (row == board.size() - 1)
                    res.push_back(board);
                else
                    solveNQueensRec(board, row + 1);
                queens.pop_back();
                board[row][j] = '.';
            }
        }
    }
};
