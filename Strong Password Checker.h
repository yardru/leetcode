#pragma once

#include <vector>
#include <string>

// 420. Strong Password Checker
class Solution {
public:
    /* TESTS:
    struct {
        string password;
        int res;
    } tests[] = {
        {"baaaaaaaaaaaaaaaacccccc", 8},
        {"bbaaaaaaaaaaaaaaacccccc", 8},
        {"ABABABABABABABABABAB1", 2},
        {"aaaB1", 1},
        {"a", 5},
        {"aA1", 3},
        {"1337C0d3", 0},
        {"1337C0d31337C0d31337C0d3", 4},
        {"", 6}
    };
    */

    int strongPasswordChecker(const std::string & password, int offset = 0, int len = -1) {
        if (len == -1)
            len = password.size();
        std::vector<int> reps;
        bool has_upper = false;
        bool has_lower = false;
        bool has_digit = false;
        for (int i = 0; i < len; i++) {
            if (password[i] >= 'A' && password[i] <= 'Z')
                has_upper = true;
            if (password[i] >= 'a' && password[i] <= 'z')
                has_lower = true;
            if (password[i] >= '0' && password[i] <= '9')
                has_digit = true;
            if (i < len - 2 && password[i] == password[i + 1] && password[++i] == password[i + 1]) {
                char r = password[i++];
                reps.push_back(3);
                while (i + 1 < len && password[i + 1] == r)
                    reps.back()++, i++;
            }
        }
        int to_del = std::max(0, len - 20), deleted = 0;
        int to_change = 0;
        for (auto & rep : reps)
            to_change += rep / 3;

        for (auto & rep : reps) {
            if (to_del - deleted <= 0 || to_change <= 0)
                break;
            if (rep % 3 == 0)
                rep--, to_change--, deleted++;
        }

        for (auto & rep : reps) {
            if (to_del - deleted <= 1 || to_change <= 0)
                break;
            if (rep % 3 == 1)
                rep -= 2, to_change--, deleted += 2;
        }

        for (auto & rep : reps) {
            if (to_del - deleted <= 2 || to_change <= 0)
                break;
            int change_opt = std::min((to_del - deleted) / 3, rep / 3);
            to_change -= change_opt;
            deleted += change_opt * 3;
        }

        to_change = std::max(to_change, 6 - len);
        to_change = std::max(to_change, !has_upper + !has_lower + !has_digit);

        return to_change + to_del;
    }
};
