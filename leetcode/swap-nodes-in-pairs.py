# Given a linked list, swap every two adjacent nodes and return its head.
# For example,
# Given 1->2->3->4, you should return the list as 2->1->4->3.
# Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def swapPairs(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        if head == None or head.next == None:
            return head
        new_head = ListNode(0)
        new_curr = new_head
        temp = head
        while temp != None: # in the odd position of the list
            if temp.next == None:
                new_curr.next = temp
                break
            else:
                temp_temp = temp.next.next
                new_curr.next = temp.next
                new_curr.next.next = temp
                temp.next = temp_temp
                new_curr = new_curr.next.next
                temp = temp.next
        return new_head.next
