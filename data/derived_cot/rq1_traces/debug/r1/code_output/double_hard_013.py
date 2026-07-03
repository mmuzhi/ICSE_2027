class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        curr_group = dummy  # Tracks the end of the previous reversed group

        while True:
            kth = self.getKth(curr_group, k)
            if not kth:
                break
            next_group = kth.next

            # Reverse the current group
            prev, curr = next_group, curr_group.next
            while curr != next_group:
                temp = curr.next
                curr.next = prev
                prev = curr
                curr = temp

            # Connect the previous group to the reversed group and move to the next
            tmp = curr_group.next
            curr_group.next = kth  # kth is now the head of the reversed group
            curr_group = tmp  # Move to the end of the current reversed group

        return dummy.next

    def getKth(self, node: ListNode, k: int) -> Optional[ListNode]:
        while node and k > 0:
            node = node.next
            k -= 1
        return node if k == 0 else None