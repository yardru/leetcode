#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

// 1697. Checking Existence of Edge Length Limited Paths
class Solution1697 {
public:
    void run(void) {
        struct {
        } tests[] = {
            {}
        };
        for (auto & test : tests)
            std::cout << "!!!\n";
    }

    struct node {
        std::unordered_map<int, int> neighbors;
        int worts_distance = 0;
    };

    std::vector<bool> distanceLimitedPathsExist(int n, std::vector<std::vector<int>> & edgeList, std::vector<std::vector<int>> & queries) {
        std::vector<bool> res;
        std::vector<node> nodes(n);
        auto add_edge = [&nodes](int v1, int v2, int distance) {
            if (nodes[v1].neighbors.count(v2))
                distance = std::min(distance, nodes[v1].neighbors[v2]);
            nodes[v1].neighbors[v2] = distance;
            nodes[v2].neighbors[v1] = distance;
        };
        for (auto & e : edgeList)
            add_edge(e[0], e[1], e[2]);

        for (auto & q : queries) {
            res.push_back(false);
            int start = q[0], finish = q[1], limit = q[2];
            std::deque<int> search_queue({start});
            nodes[start].worts_distance = 1;
            while (!search_queue.empty()) {
                int cur = search_queue.front();
                search_queue.pop_front();
                if (nodes[cur].neighbors.count(finish) && nodes[cur].neighbors[finish] < limit) {
                    res.back() = true;
                    break;
                }
                for (auto & n : nodes[cur].neighbors)
                    if (nodes[n.first].worts_distance == 0 && n.second < limit) {
                        nodes[n.first].worts_distance = std::max(nodes[cur].worts_distance, n.second);
                        search_queue.push_back(n.first);
                        add_edge(start, n.first, nodes[n.first].worts_distance);
                    }
            }
            for (auto & n : nodes)
                n.worts_distance = 0;
        }
        return res;
    }
};
