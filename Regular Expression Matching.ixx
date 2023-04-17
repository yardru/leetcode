export module Regular_Expression_Matching;

import std.core;

// 10. Regular Expression Matching
export class Solution10 {
public:
    static void test(void) {
        struct {
            std::string s, p;
            bool answer;
        } tests[] = {
            {"a", "a*", true},
            {"ab", ".*..", true},
            {"a", "ab*", true},
            {"a", "ab*c*", true},
            {"aaa", "ab*ac*a", true},
            {"ab", "c*a*b", true},
            {"aab", "c*a*b", true},
            {"aaaaaabaaa", "a*a.a.a", true},
            {"aaba", "a*a.a", true},
            {"aabaaa", "a*a.a.a", true},
            {"aaaaba", "a*a.a.a", true},
            {"aaaaaaaaba", "a*a.a.a", true},
            {"aaabaa", "a*a.a.a", false},
            {"aaaaaaabaa", "a*a.a.a", false},
            {"aaaba", "a*a.a.a", true},
            {"aaa", "a*.*", true},
            {"aa", "a*.*", true},
            {"ab", "a*.*", true},
            {"abc", "a*.*", true},
            {"aabc", "a*.*", true},
            {"aabc", "a*a.*", true},
            {"a", "a*.*", true},
            {"aaa", "a*a", true},
            {"aa", "a*a", true},
            {"aa", "a*aa", true},
            {"aa", "a*a*", true},
            {"aaaaaaa", "a*aa*aa.a", true},
            {"aaaaaaaaaaaa", "a*aa*aa.a", true},
            {"aaaaaaaaaaba", "a*aa*aa.a", true},
            {"aaaaaaaaabaa", "a*aa*aa.a", false},
            {"aaaaaa", "a*aa*aa.a", true},
            {"aaabbb", "aaa.bb", true},
            {"aaabb", "aaa.bb", false}
        };
        std::cout << "???\n";
        for (auto & t : tests)
            if (Solution10().isMatch(t.s, t.p) != t.answer)
                std::cout << "AAA!!! '" << t.s << (t.answer ? "' doesn't match '" : "' matches '") << t.p << "'\n";
    }

    bool isMatch(std::string s, std::string p) {
        return isMatchR(s, p);
    }
    bool isMatchR(const std::string & s, const std::string & p, int s_begin = 0, int p_begin = 0) {
        size_t i = s_begin, j = p_begin, new_j, new_i;
        auto check_skip = [&](int end_i) {
            if (p[j - 1] != '.')
                while (i < end_i)
                    if (s[i++] != p[j - 1])
                        return false;
            i = end_i;
            return true;
        };

        for (; j < p.size(); j++) {
            if (p[j] == '*') {
                new_j = j + 1;
                if (new_j == p.size()) { // end of pattern
                    if (!check_skip(s.size()))
                        return false;
                    return true;
                }
                while (new_j < p.size() && p[new_j] != '*')
                    new_j++;

                while ((new_i = find_substr(s, p, i, s.size(), j + 1, new_j - 1)) != -1) {
                    if (!check_skip(new_i))
                        return false;
                    if (isMatchR(s, p, new_i + (new_j - j - 2), new_j - 1))
                        return true;
                    if (!check_skip(new_i + 1))
                        return false;
                }
                return false;
            }
            else {
                if ((j + 1 == p.size() || p[j + 1] != '*') &&
                    (i >= s.size() || (s[i++] != p[j] && p[j] != '.')))
                    return false;
            }
        }

        return i == s.size();
    }

private:
    int find_substr(const std::string & str, const std::string & pattern, int s_begin = 0, int s_end = -1, int p_begin = 0, int p_end = -1) {
        if (s_end == -1)
            s_end = str.size();
        if (p_end == -1)
            p_end = pattern.size();
        int p_size = p_end - p_begin;

        if (s_begin + p_size > s_end)
            return -1;

        int64_t h = 0, ph = 0, p = 1'000'000'007, x = 263, xi = 1, xprev = 0;
        std::unordered_map<int, int64_t> dots;
        for (int i = p_size - 1; i >= 0; i--) {
            h = (h + xi * str[s_begin + i]) % p;
            if (pattern[p_begin + i] != '.')
                ph = (ph + xi * pattern[p_begin + i]) % p;
            else
                dots[i] = xi;
            xprev = xi;
            xi = (xi * x) % p;
        }
        auto ph_f = [&](int str_i) {
            int64_t res = ph;
            for (auto & d : dots)
                res = (res + d.second * str[str_i + d.first]) % p;
            return res;
        };

        for (int i = s_begin; i <= s_end - p_size; i++) {
            if (h == ph_f(i)) {
                bool is_substr = true;
                for (int j = 0; j < p_size; j++)
                    if (str[i + j] != pattern[p_begin + j] && pattern[p_begin + j] != '.')
                        is_substr = false;
                if (is_substr)
                    return i;
            }
            h = (((p * str[i] + h - str[i] * xprev) % p) * x + str[i + p_size]) % p;
        }
        return -1;
    }
};