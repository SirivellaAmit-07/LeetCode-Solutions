// Time:  O(nlogn)
// Space: O(1)

// math, binary search
class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        const auto& check = [&](int x, int64_t t) {
            int64_t cnt = 0;
            for (int i = 0; i < size(nums); ++i) {
                if (nums[i] <= x) {
                    cnt += cost[i];
                }
            }
            return cnt >= t;
        };

        const int64_t total = accumulate(cbegin(cost), cend(cost), 0ll);
        int left = *min_element(cbegin(nums), cend(nums));
        int right = *max_element(cbegin(nums), cend(nums));
        const int64_t median = (total + 1) / 2;
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (check(mid, median)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        int64_t result = 0;
        for (int i = 0; i < size(nums); ++i) {
            result += static_cast<int64_t>(abs(nums[i] - left)) * cost[i];
        }
        return result;
    }
};

// Time:  O(nlogn)
// Space: O(n)
// prefix sum
class Solution2 {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        vector<int> idxs(size(nums));
        iota(begin(idxs), end(idxs), 0);
        sort(begin(idxs), end(idxs), [&](const auto& a, const auto& b) {
            return nums[a] < nums[b];
        });
        vector<int64_t> prefix(size(cost) + 1);
        int64_t left = 0;
        for (int i = 0; i < size(cost); ++i) {
            if (i - 1 >= 0) {
                left += prefix[i] * (nums[idxs[i]] - nums[idxs[i - 1]]);
            }
            prefix[i + 1] = prefix[i] + cost[idxs[i]];
        }
        int64_t result = numeric_limits<int64_t>::max();
        int64_t suffix = 0, right = 0;
        for (int i = size(cost) - 1; i >= 0; --i) {
            if (i + 1 < size(idxs)) {
                right += suffix * (nums[idxs[i + 1]] - nums[idxs[i]]);
            }
            result = min(result, left + right);
            if (i - 1 >= 0) {
                left -= prefix[i] * (nums[idxs[i]] - nums[idxs[i - 1]]);
            }
            suffix += cost[idxs[i]];
        }
        return result;
    }
};
