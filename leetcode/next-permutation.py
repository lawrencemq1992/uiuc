# Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
# If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
# The replacement must be in-place, do not allocate extra memory.
# Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
# 1,2,3 → 1,3,2
# 3,2,1 → 1,2,3
# 1,1,5 → 1,5,1

# Qing's Solution:
# Example: "163842"
# 1. find the last index which has a larger number in index + 1
# 	3 < 8, index_1 at position 2
# 1.1 if there is no such index(Example: "54321"): reverse the list("12345") and return
# 2. find the last index2 > index which has a larger number
# 	4 > 3, index_2 at position 4
# 2.1 index_2 must be exist since in #1 we have a larger number in index + 1
# 3. switch value between index_1 and index_2:
# 	163842->164832
# 4. reverse the part of the list after index_1:
#	164832->164238
# DONE!

class Solution(object):
    def nextPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """
        if len(nums) <= 1: return
        switch_1 = -1
        for i in range(len(nums) - 1):
            if nums[i] < nums[i + 1]:
                switch_1 = i
        if switch_1 == -1:
            nums.reverse()
            return
        switch_2 = i + 1
        for i in range(switch_1 + 1, len(nums)):
            if nums[switch_1] < nums[i]:
                switch_2 = i
        nums[switch_1], nums[switch_2] = nums[switch_2], nums[switch_1]
        nums[switch_1 + 1: len(nums)] = nums[len(nums) - 1:switch_1:-1]
        return
