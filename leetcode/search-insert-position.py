# Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
# You may assume no duplicates in the array.
# Here are few examples.
# [1,3,5,6], 5 → 2
# [1,3,5,6], 2 → 1
# [1,3,5,6], 7 → 4
# [1,3,5,6], 0 → 0

class Solution(object):
    def searchInsert(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        return self.insert_helper(nums, target, 0)
        
    def insert_helper(self, nums, target, pos):
        if nums is None:
            return 0
        if pos >= len(nums):
            return pos
        if target <= nums[pos]:
            return pos
        return self.insert_helper(nums, target, pos + 1)
