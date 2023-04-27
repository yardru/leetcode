#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <set>

// 2612. Minimum Reverse Operations
class Solution2612 {
public:
    void run(void) {
        struct {
            int n, p;
            std::vector<int> banned;
            int k;
            std::vector<int> res;
        } tests[] = {
            {100000, 0, {}, 21719, {}},
            {6, 1, {}, 4, {3, 0, 1, 2, 1, 2}},
            {5, 0, {}, 2, {0, 1, 2, 3, 4}},
            {5, 4, {}, 2, {4, 3, 2, 1, 0}},
            {5, 2, {}, 2, {2, 1, 0, 1, 2}},
            {4, 2, {}, 4, {-1, 1, 0, -1}},
            {3, 0, {2}, 2, {0, 1, -1}},
            {3, 1, {}, 3, {-1, 0, -1}},
            {4, 2, {0, 1, 3}, 1, {-1, -1, 0, -1}},
            {5, 0, {2, 4}, 3, {0, -1, -1, -1, -1}},
            {4, 0, {1, 2}, 4, {0, -1, -1, 1}}
        };
        for (auto & test : tests) {
            for (int v : minReverseOperations(test.n, test.p, test.banned, test.k))
                std::cout << v << " ";
            std::cout << "\n";
        }
    }
    std::vector<int> minReverseOperations(int n, int p, std::vector<int> & banned, int k) {
        std::vector<int> res(n, n);
        for (int i : banned)
            res[i] = -1;
        res[p] = 0;

        /* Widght search */
        std::set<int> to_find;
        for (int i = 0; i < n; i++)
            if (i != p && res[i] != -1)
                to_find.insert(i);

        std::queue<int> q;
        q.push(p);
        while (!q.empty() && !to_find.empty()) {
            int i = q.front();
            q.pop();
            int left = std::max(i - k + 1, 0), right = std::min(i + k - 1, n - 1);
            for (auto jt = to_find.lower_bound(left); jt != to_find.end() && *jt <= right;) {
            //for (int l = left, r = left + k - 1; r <= right; l++, r++) {
                int j = *jt;
                auto cur = jt++;
                if ((i + j + k) % 2 == 0 || (j + i - k + 1) / 2 < left || (j + i + k - 1) / 2 > right)
                    continue;
                //int j = l + k - (i - l) - 1; // 2 * l + k - i - 1
                if (res[j] != -1 && res[j] > res[i] + 1) {
                    res[j] = res[i] + 1;
                    q.push(j);
                    to_find.erase(cur);
                }
            }
        }
        /**/
        for (auto & r : res)
            if (r == n)
                r = -1;
        return res;
    }
};
