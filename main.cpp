#include <iostream>
#include <vector>

using namespace std;

// 37. Sudoku Solver
class Solution {
public:
    Solution() : n(81), heap(n) {
        for (int i = 0, k = 0; i < 9; i++)
            for (int j = 0; j < 9; j++, k++) {
                cells[i][j].i = i;
                cells[i][j].j = j;
                cells[i][j].pos_in_heap = k;
                heap[k] = &cells[i][j];
            }
    }

    void solveSudoku(vector<vector<char>> & board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++)
                if (board[i][j] != '.') {
                    int d = board[i][j] - '1';
                    for (int k = 0; k < 9; k++)
                        if (k != d)
                            cells[i][j].digits[k] = false;
                    cells[i][j].dn = 0;
                    heapify_up(cells[i][j].pos_in_heap);
                    put_digit(d);
                }
        }
        solveSudokuMainLoop(board);
    }
    bool solveSudokuMainLoop(vector<vector<char>> & board) {
        while (n > 0) {
            if (heap[0]->dn < 1)
                return false;
            if (heap[0]->dn > 1) {
                for (int k = 0; k < 9; k++)
                    if (heap[0]->digits[k]) {
                        auto recurent_solution = Solution(*this); // :_(
                        for (int i = 0; i < n; i++)
                            recurent_solution.heap[i] = &recurent_solution.cells[heap[i]->i][heap[i]->j];
                        for (int rk = 0; rk < 9; rk++)
                            if (rk != k)
                                recurent_solution.heap[0]->digits[rk] = false;
                        recurent_solution.heap[0]->dn = 1;
                        if (recurent_solution.solveSudokuMainLoop(board))
                            return true;
                    }
                return false;
            }
            int d;
            for (int k = 0; k < 9; k++)
                if (heap[0]->digits[k])
                    d = k;
            board[heap[0]->i][heap[0]->j] = '1' + d;
            put_digit(d);
        }
        return true;
    }
private:
    struct cell_t {
        int i, j;
        bool digits[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        int dn = 9;
        int pos_in_heap;
    } cells[9][9];
    int n;
    vector<cell_t *> heap;

    void put_digit(int d) {
        swap(heap[0], heap[--n]);
        swap(heap[0]->pos_in_heap, heap[n]->pos_in_heap);
        heapify_down(0);
        int di = heap[n]->i, dj = heap[n]->j;
        for (int i = 0; i < 9; i++)
            if (di != i && cells[i][dj].digits[d]) {
                cells[i][dj].digits[d] = false;
                cells[i][dj].dn--;
                heapify_up(cells[i][dj].pos_in_heap);
            }
        for (int j = 0; j < 9; j++)
            if (dj != j && cells[di][j].digits[d]) {
                cells[di][j].digits[d] = false;
                cells[di][j].dn--;
                heapify_up(cells[di][j].pos_in_heap);
            }
        for (int i = (di / 3) * 3; i < (di / 3 + 1) * 3; i++)
            for (int j = (dj / 3) * 3; j < (dj / 3 + 1) * 3; j++)
                if ((i != di || dj != j) && cells[i][j].digits[d]) {
                    cells[i][j].digits[d] = false;
                    cells[i][j].dn--;
                    heapify_up(cells[i][j].pos_in_heap);
                }
    }
    void heapify_up(int i) {
        int p = (i - 1) / 2;
        if (i == 0 || heap[p]->dn <= heap[i]->dn)
            return;
        swap(heap[p], heap[i]);
        swap(heap[p]->pos_in_heap, heap[i]->pos_in_heap);
        heapify_up(p);
    }
    void heapify_down(int i) {
        int l = 2 * i + 1, r = 2 * i + 2, next = i;
        if (r < n && heap[r]->dn < heap[next]->dn)
            next = r;
        if (l < n && heap[l]->dn < heap[next]->dn)
            next = l;
        if (i == next)
            return;
        swap(heap[next], heap[i]);
        swap(heap[next]->pos_in_heap, heap[i]->pos_in_heap);
        heapify_down(next);
    }
};

int main(void) {
    vector<vector<char>> boards[] = {{
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    }, {
        {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
        {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
        {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
        {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
        {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
        {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
        {'.', '.', '.', '2', '7', '5', '9', '.', '.'}}
    };

    Solution().solveSudoku(boards[1]);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            cout << boards[1][i][j];
        cout << "\n";
    }
    return 0;
}
