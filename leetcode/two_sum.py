# Given an array of integers, return indices of the two numbers such that they add up to a specific target.
# You may assume that each input would have exactly one solution.
# Example:
# Given nums = [2, 7, 11, 15], target = 9,
# Because nums[0] + nums[1] = 2 + 7 = 9,
# return [0, 1].
# UPDATE (2016/2/13):
# The return format had been changed to zero-based indices. Please read the above updated description carefully.

class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        sorted_nums = sorted(nums)
        start = 0
        end = len(sorted_nums) - 1
        if end <= 1:
            return []
        while start < end:
            sum = sorted_nums[start] + sorted_nums[end]
            if sum == target:
                break
            elif sum < target:
                start += 1
            else:
                end -= 1
        if start >= end:
            return []
        for i in range(0, len(nums)):
            if sorted_nums[start] == nums[i]:
                start = i
                break
        for i in range(0, len(nums)):
            if start != i and sorted_nums[end] == nums[i]:
                end = i
                break
        if start > end:
            start, end = end, start
        return [start, end]
