#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 4. Median of Two Sorted Arrays
    double findMedianSortedArrays(vector<int> & nums1, vector<int> & nums2) {
        int i = bi_search_median_index(nums1, nums2);
        if (i < 0)
            return findMedianSortedArrays(nums2, nums1);

        if ((nums1.size() + nums2.size()) % 2 != 0)
            return nums1[i];

        int k = (nums1.size() + nums2.size() - 1) / 2 - i;
        return (nums1[i] + (i < nums1.size() - 1 ? (k < nums2.size() && k >= 0 ? min(nums2[k], nums1[i + 1]) : nums1[i + 1]) : nums2[k])) / 2.0;
    }
    // 71. Simplify Path
    string simplifyPath(string path) {
        vector<int> slashs = {0};
        int n = 1;
        for (int i = 1; i < path.size(); i++) {
            if (path[i] == '/') {
                if (path[i - 1] == '/')
                    continue;
                slashs.push_back(n);
            }
            if (path[i] == '.') {
                if (path[i - 1] == '.' && path[i - 2] == '/' && (i + 1 == path.size() || path[i + 1] == '/')) {
                    if (slashs.size() > 1)
                        slashs.pop_back();
                    n = slashs.back() + 1;
                    i++;
                    continue;
                }
                else if (path[i - 1] == '/' && (i + 1 == path.size() || path[i + 1] == '/')) {
                    n = slashs.back() + 1;
                    i++;
                    continue;
                }
            }

            path[n++] = path[i];
        }
        if (path[n - 1] == '/' && n > 1)
            n--;
        path.resize(n);
        return path;
    }
    struct ListNode {
        int val;
        ListNode * next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode * next) : val(x), next(next) {}
    };
    // 23. Merge k Sorted Lists
    ListNode * mergeKLists(vector<ListNode *> & lists) {
        int left = 0, right = lists.size() - 1;
        while (left < right) {
            while (left < right && lists[left] != nullptr)
                left++;
            while (left < right && lists[right] == nullptr)
                right--;
            if (lists[left] == nullptr && lists[right] != nullptr)
                swap(lists[left], lists[right]);
        }
        if (right < 0 || lists[0] == nullptr)
            return nullptr;
        int n = left;
        if (lists[n] != nullptr)
            n++;
        for (int i = n / 2; i >= 0; i--)
            heapify_down(lists, i, n);
        ListNode * res = lists[0];
        ListNode * tail = lists[0];
        ListNode * tmp_next;
        while (n > 0) {
            tmp_next = lists[0]->next;
            tail->next = lists[0];
            tail = tail->next;
            tail->next = nullptr;
            lists[0] = tmp_next;
            if (lists[0] == nullptr)
                swap(lists[0], lists[--n]);
            heapify_down(lists, 0, n);
        }
        return res;
    }
    // 10. Regular Expression Matching
    bool isMatch(string s, string p) {
        return isMatchR(s, p);
    }
    bool isMatchR(const string & s, const string & p, int s_begin = 0, int p_begin = 0) {
        int i = s_begin, j = p_begin, new_j, new_i;
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
    int find_substr(const string & str, const string & pattern, int s_begin = 0, int s_end = -1, int p_begin = 0, int p_end = -1) {
        if (s_end == -1)
            s_end = str.size();
        if (p_end == -1)
            p_end = pattern.size();
        int p_size = p_end - p_begin;

        if (s_begin + p_size > s_end)
            return -1;

        int64_t h = 0, ph = 0, p = 1'000'000'007, x = 263, xi = 1, xprev = 0;
        unordered_map<int, int64_t> dots;
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

    void heapify_down(vector<ListNode *> & lists, int i, int n) {
        int left = 2 * i + 1, right = 2 * i + 2, path = i;
        if (right < n && lists[right]->val < lists[i]->val)
            path = right;
        if (left < n && lists[left]->val < lists[path]->val)
            path = left;
        if (path == i)
            return;
        swap(lists[i], lists[path]);
        heapify_down(lists, path, n);
    }
    int bi_search_median_index(vector<int> & primary, vector<int> & secondary) {
        int median = (primary.size() + secondary.size() - 1) / 2;
        int l = 0, r = primary.size() - 1, m, k;

        if (primary.size() == 0)
            return -1;

        if (secondary.size() == 0)
            return (r + l) / 2;

        while (l < r) {
            m = (r + l) / 2;
            k = median - m;
            if (k >= 0 && k <= secondary.size() && (k == secondary.size() || primary[m] <= secondary[k]) && (k == 0 || primary[m] >= secondary[k - 1]))
                return m;

            if (k < 0) {
                r = m;
                continue;
            }
            if (k >= secondary.size()) {
                l = m + 1;
                continue;
            }
            if (primary[m] > secondary[k])
                r = m;
            else if (k > 0 && primary[m] < secondary[k - 1])
                l = m + 1;
            else
                return m;
        }

        m = (r + l) / 2;
        k = median - m;
        if (k >= 0 && k <= secondary.size() && (k == secondary.size() || primary[m] <= secondary[k]) && (k == 0 || primary[m] >= secondary[k - 1]))
            return m;

        return -1;
    }
};

int main(void) {
    struct {
        string s, p;
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

    for (auto & test : tests)
        if (Solution().isMatch(test.s, test.p) != test.answer)
            cout << "AAA!!! '" << test.s << (test.answer ? "' doesn't match '" : "' matches '") << test.p << "'\n";

    return 0;
}
