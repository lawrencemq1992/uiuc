# Given two arrays, write a function to compute their intersection.
# Example:
# Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].
# Note:
# Each element in the result should appear as many times as it shows in both arrays.
# The result can be in any order.

class Solution(object):
    def intersect(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        if len(nums1) == 0 or len(nums2) == 0:
            return []
        num_dict = {}
        for i in nums1:
            if i not in num_dict:
                num_dict[i] = 1
            else:
                num_dict[i] += 1
        return_set = []
        for i in nums2:
            if i in num_dict and num_dict[i] > 0:
                return_set.append(i)
                num_dict[i] -= 1
        return return_set
