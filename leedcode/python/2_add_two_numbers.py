# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        """
        1. create new linked list for return
        2. 짧은 노드 기준으로 루프 돌면서 +
        """
        start_node = ListNode()
        current_node = start_node
        carry = 0

        while l1 and l2:
            sum_value = l1.val + l2.val
            rest = (sum_value + carry) % 10
            current_node.next = ListNode(val=rest)

            carry = int((sum_value + carry) / 10)
            l1 = l1.next
            l2 = l2.next
            current_node = current_node.next

        while l1:
            rest = (l1.val + carry) % 10
            current_node.next = ListNode(val=rest)

            carry = int((l1.val + carry) / 10)
            l1 = l1.next
            current_node = current_node.next

        while l2:
            rest = (l2.val + carry) % 10
            current_node.next = ListNode(val=rest)

            carry = int((l2.val + carry) / 10)
            l2 = l2.next
            current_node = current_node.next

        if carry == 1:
            current_node.next = ListNode(val=1)

        return start_node.next