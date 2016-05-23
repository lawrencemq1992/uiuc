# You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of # their nodes contain a single digit. Add the two numbers and return it as a linked list.
# Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
# Output: 7 -> 0 -> 8

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        if l1 is None or l2 is None:
            return None
        head = ListNode((l1.val + l2.val) % 10)
        ten = int((l1.val + l2.val)/10)
        node1 = l1.next
        node2 = l2.next
        temp = head
        while node1 is not None or node2 is not None or ten != 0:
            if (node1 is not None and node2 is not None):
                temp.next = ListNode((node1.val + node2.val + ten) % 10)
                ten = int((node1.val + node2.val + ten)/10)
                node1 = node1.next
                node2 = node2.next
                temp = temp.next
            elif node1 is None and node2 is not None:
                temp.next = ListNode((node2.val + ten) % 10)
                ten = int((node2.val + ten) / 10)
                node2 = node2.next
                temp = temp.next
            elif node2 is None and node1 is not None:
                temp.next = ListNode((node1.val + ten) % 10)
                ten = int((node1.val + ten) / 10)
                node1 = node1.next
                temp = temp.next
            else:
                temp.next = ListNode(ten)
                ten = 0
                temp = temp.next
        return head
        
