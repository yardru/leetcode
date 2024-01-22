#pragma once

#include <vector>
#include <iostream>

class Solution42 {
public:
    void run(void) {
        struct {
            std::vector<int> height;
        } tests[] = {
            {{0,1,0,2,1,0,1,3,2,1,2,1}}
        };
        for (auto & test : tests)
            std::cout << trap(test.height) << "!!!\n";
    }

    int trap(std::vector<int> & height) {
        int s = 0;
        int l = 0, r = height.size() - 1;
        int lh = height[l], rh = height[r];
        while (l < r) {
            if (lh <= rh) {
                if (height[++l] > lh)
                    lh = height[l];
                else
                    s += lh - height[l];
            }
            else {
                if (height[--r] > rh)
                    rh = height[r];
                else
                    s += rh - height[r];
            }
        }
        return s;
    }
};