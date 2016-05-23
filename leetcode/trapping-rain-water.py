# Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it # is able to trap after raining.
# For example, 
# Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

class Solution(object):
    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        left_max = 0
        left_bar = []
        for i in range(len(height)):
            if height[i] > left_max:
                left_max = height[i]
            left_bar.append(left_max)
        sum = 0
        right_max = 0
        for i in reversed(range(len(height))):
            if height[i] > right_max:
                right_max = height[i]
            sum += min(left_bar[i], right_max) - height[i]
        return sum
