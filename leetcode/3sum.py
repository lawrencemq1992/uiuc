# Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
# Note:
# Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
# The solution set must not contain duplicate triplets.
#     For example, given array S = {-1 0 1 2 -1 -4},
#     A solution set is:
#     (-1, 0, 1)
#     (-1, -1, 2)

class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        snums = sorted(nums)
        return_set = []
        for i in range(len(snums)):
            if i == 0 or snums[i] > snums[i - 1]:
                l = i + 1
                r = len(snums) - 1
                while l < r:
                    if snums[i] + snums[l] + snums[r] == 0:
                        return_set.append([snums[i], snums[l], snums[r]])
                        l += 1
                        r -= 1
                        while l < r and snums[l] == snums[l - 1]:
                            l +=1
                        while l < r and snums[r] == snums[r + 1]:
                            r -= 1
                    elif snums[i] + snums[l] + snums[r] < 0:
                        l += 1
                        while l < r and snums[l] == snums[l - 1]:
                            l +=1
                    else:
                        r -= 1
                        while l < r and snums[r] == snums[r + 1]:
                            r -= 1
        return return_set
            
