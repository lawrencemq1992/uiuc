# Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
# push(x) -- Push element x onto stack.
# pop() -- Removes the element on top of the stack.
# top() -- Get the top element.
# getMin() -- Retrieve the minimum element in the stack.
# Example:
# MinStack minStack = new MinStack();
# minStack.push(-2);
# minStack.push(0);
# minStack.push(-3);
# minStack.getMin();   --> Returns -3.
# minStack.pop();
# minStack.top();      --> Returns 0.
# minStack.getMin();   --> Returns -2.

class MinStack(object):

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.length = 0
        self.values = []
        self.min = []

    def push(self, x):
        """
        :type x: int
        :rtype: void
        """
        self.values.append(x)
        if self.length == 0:
            self.min.append(x)
        else:
            self.min.append(min(self.min[self.length - 1], x))
        self.length += 1

    def pop(self):
        """
        :rtype: void
        """
        if self.length == 0:
            return
        self.values = self.values[:-1]
        self.min = self.min[:-1]
        self.length -= 1

    def top(self):
        """
        :rtype: int
        """
        if self.length == 0:
            return None
        return self.values[self.length - 1]

    def getMin(self):
        """
        :rtype: int
        """
        if self.length == 0:
            return None
        return self.min[self.length - 1]


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(x)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()
