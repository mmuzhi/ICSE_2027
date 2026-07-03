class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        currGroup = dummy

        while True:
            kth = self.getKth(currGroup, k)
            if not kth:
                break
            nextGroup = kth.next

            node = currGroup.next
            prev = None
            curr = node
            count = k

            while count > 0:
                next_node = curr.next
                curr.next = prev
                prev = curr
                curr = next_node
                count -= 1

            node.next = nextGroup
            currGroup.next = prev
            currGroup = nextGroup

        return dummy.next

    def getKth(self, node, k):
        while node and k:
            node = node.next
            k -= 1
        return node