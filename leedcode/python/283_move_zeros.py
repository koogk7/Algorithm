class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        0 1 0 3 12
        1 0 0 3 12, cursor 1, find_nonzero 1
        1 3 12 0 0, cursor 3, find_nonzero 3
        """
        find_nonzero = 0
        cursor = 0
        nums_size = len(nums)

        while cursor < nums_size:
            if nums[cursor] == 0:
                while find_nonzero < nums_size and nums[find_nonzero] == 0:
                    find_nonzero += 1
                if find_nonzero >= nums_size:
                    return
                nums[cursor] = nums[find_nonzero]
                nums[find_nonzero] = 0

            cursor += 1
            find_nonzero += 1