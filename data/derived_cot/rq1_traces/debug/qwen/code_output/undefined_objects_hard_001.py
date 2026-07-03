class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        currGroup = dummy
        
        while True:
            kth = self.getKth(currGroup, k)
            if not kth:
                break
            nextGroup = kth.next
            
            prev_node = None
            curr = currGroup.next
            for _ in range(k):
                next_node = curr.next
                curr.next = prev_node
                prev_node = curr
                curr = next_node
            
            currGroup.next = prev_node
            currGroup = nextGroup
        
        return dummy.next

    def getKth(self, node, k):
        while node and k:
            node = node.next
            k -= 1
        return node