# There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        total = len(nums1) + len(nums2)
        if total == 0:
            return None
        if total % 2 == 1:
            return self.get_kth_smallest(nums1, nums2, total / 2 + 1)
        else:
            return (self.get_kth_smallest(nums1, nums2, total / 2) + self.get_kth_smallest(nums1, nums2, total / 2 + 1)) * 0.5
    
    def get_kth_smallest(self, nums1, nums2, k):
        if len(nums1) > len(nums2):
            return self.get_kth_smallest(nums2, nums1, k)
        if len(nums1) == 0:
            return nums2[k - 1]
        if k == 1:
            return min(nums1[0], nums2[0])
        len1 = min(k / 2, len(nums1))
        if nums1[len1 - 1] <= nums2[k / 2 - 1]:
            return self.get_kth_smallest(nums1[len1: ], nums2, k - len1)
        else:
            return self.get_kth_smallest(nums1, nums2[(k / 2): ], k - k / 2)
