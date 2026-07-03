class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        curr_group = dummy

        while True:
            kth = self.getKth(curr_group, k)
            if not kth:
                break
            next_group = kth.next

            # Reverse the current group
            prev, curr = next_group, curr_group.next
            while curr != next_group:
                tmp = curr.next
                curr.next = prev
                prev = curr
                curr = tmp

            # Update pointers to connect the reversed group
            tmp = curr_group.next
            curr_group.next = kth  # kth is the new head after reversal
            curr_group = tmp  # Move to the end of the current reversed group

        return dummy.next

    def getKth(self, node, k):
        while node and k > 0:
            node = node.next
            k -= 1
        return node