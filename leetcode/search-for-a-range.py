# Given a sorted array of integers, find the starting and ending position of a given target value.
# Your algorithm's runtime complexity must be in the order of O(log n).
# If the target is not found in the array, return [-1, -1].
# For example,
# Given [5, 7, 7, 8, 8, 10] and target value 8,
# return [3, 4].

class Solution(object):
    def searchRange(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        left = 0
        right = len(nums) - 1
        while left <= right:
            mid = (left + right) / 2
            if nums[mid] > target:
                right = mid - 1
            elif nums[mid] < target:
                left = mid + 1
            else:
                list = [0, 0]
                if nums[left] == target:
                    list[0] = left
                if nums[right] == target:
                    list[1] = right
                for i in range(mid, right + 1):
                    if nums[i] != target:
                        list[1] = i - 1
                        break
                for i in range(mid, left - 1, -1):
                    if nums[i] != target:
                        list[0] = i + 1
                        break
                return list
        return [-1, -1]
