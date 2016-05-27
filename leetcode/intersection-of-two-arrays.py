# Given two arrays, write a function to compute their intersection.
# Example:
# Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].
# Note:
# Each element in the result must be unique.
# The result can be in any order.

class Solution(object):
    def intersection(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        return_set = []
        for i in nums1:
            if i in nums2 and i not in return_set:
                return_set.append(i)
        return return_set
                
