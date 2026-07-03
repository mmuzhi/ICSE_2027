class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        prev_group = dummy
        
        while True:
            kth = self.getKth(prev_group, k)
            if not kth:
                break
            next_group_start = kth.next
            
            start = prev_group.next
            prev = None
            curr = start
            for _ in range(k):
                next_node = curr.next
                curr.next = prev
                prev = curr
                curr = next_node
            
            prev_group.next = prev
            prev_group = next_group_start
        
        return dummy.next

    def getKth(self, node, k):
        while node and k > 0:
            node = node.next
            k -= 1
        return node