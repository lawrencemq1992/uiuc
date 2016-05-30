# Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
#     For example, given array S = {-1 2 1 -4}, and target = 1.
#     The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

class Solution(object):
    def threeSumClosest(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        snums =  sorted(nums)
        min_diff = sys.maxint
        return_sum = 0
        for i in range(len(snums)):
            l = i + 1
            r = len(snums) - 1
            while l < r:
                sum = snums[i] + snums[l] + snums[r]
                if abs(sum - target) < min_diff:
                    min_diff = abs(sum - target)
                    return_sum = sum
                if sum == target:
                    return sum
                elif sum < target:
                    l += 1
                else:
                    r -= 1
        return return_sum
