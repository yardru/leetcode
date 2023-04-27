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

        std::set<int> to_find[2];
        for (int i = 0; i < n; i++)
            if (i != p && res[i] != -1)
                to_find[i % 2].insert(i);

        std::queue<int> q;
        q.push(p);
        while (!q.empty() && (!to_find[0].empty() || !to_find[1].empty())) {
            int i = q.front();
            q.pop();
            int left = std::max(i - k + 1, 0), right = std::min(i + k - 1, n - 1);
            auto & tf = to_find[(i + k + 1) % 2];
            for (auto jt = tf.lower_bound(2 * left - i + k - 1); jt != tf.end() && *jt <= 2 * right - i - k + 1;) {
                int j = *jt;
                auto cur = jt++;
                if (res[j] != -1 && res[j] > res[i] + 1) {
                    res[j] = res[i] + 1;
                    q.push(j);
                    tf.erase(cur);
                }
            }
        }

        for (auto & r : res)
            if (r == n)
                r = -1;
        return res;
    }
};
