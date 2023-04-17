export module Merge_k_Sorted_Lists;

import std.core;

// 23. Merge k Sorted Lists
export class Solution23 {
public:
    struct ListNode {
        int val;
        ListNode * next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode * next) : val(x), next(next) {}
    };
    ListNode * mergeKLists(std::vector<ListNode *> & lists) {
        int left = 0, right = lists.size() - 1;
        while (left < right) {
            while (left < right && lists[left] != nullptr)
                left++;
            while (left < right && lists[right] == nullptr)
                right--;
            if (lists[left] == nullptr && lists[right] != nullptr)
                std::swap(lists[left], lists[right]);
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
                std::swap(lists[0], lists[--n]);
            heapify_down(lists, 0, n);
        }
        return res;
    }
private:
    void heapify_down(std::vector<ListNode *> & lists, int i, int n) {
        int left = 2 * i + 1, right = 2 * i + 2, path = i;
        if (right < n && lists[right]->val < lists[i]->val)
            path = right;
        if (left < n && lists[left]->val < lists[path]->val)
            path = left;
        if (path == i)
            return;
        std::swap(lists[i], lists[path]);
        heapify_down(lists, path, n);
    }
};