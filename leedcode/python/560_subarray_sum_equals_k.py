class Solution(object):
    def subarraySum(self, nums, k) -> int:
        """
        nums = [1, -1, 2, 3, -3, 1], k = 0

        prefix_sums = [1, 0, 2, 5, 2, 3] -> O(n)
        prefix_sums[3] - prefix_sums[1] = nums[2] + nums[3]
        prefix_sums[i] - prefix_sums[j] = k,
        prefix_sums[j] = prefix_sums[i] - k
        """

        prefix_sums = [0 for _ in range(0, len(nums))]
        sums = 0
        ans = 0

        for i, num in enumerate(nums):
            sums += num
            prefix_sums[i] += sums

        hash_sums = {}  # key: sum, value: sum 값이 나온 횟수
        hash_sums[0] = 1  # {}은 반드시 한 개 이상 존재

        for prefix_sum in prefix_sums:
            find = prefix_sum - k

            if find in hash_sums:
                ans += hash_sums[find]
            hash_sums[prefix_sum] = hash_sums.get(prefix_sum, 0) + 1

        return ans
