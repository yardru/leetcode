#include <vector>

// 4. Median of Two Sorted Arrays
class Solution4 {
public:
    double findMedianSortedArrays(std::vector<int> & nums1, std::vector<int> & nums2) {
        int i = bi_search_median_index(nums1, nums2);
        if (i < 0)
            return findMedianSortedArrays(nums2, nums1);

        if ((nums1.size() + nums2.size()) % 2 != 0)
            return nums1[i];

        int k = (nums1.size() + nums2.size() - 1) / 2 - i;
        return (nums1[i] + (i < nums1.size() - 1 ? (k < nums2.size() && k >= 0 ? std::min(nums2[k], nums1[i + 1]) : nums1[i + 1]) : nums2[k])) / 2.0;
    }
private:
    int bi_search_median_index(std::vector<int> & primary, std::vector<int> & secondary) {
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
