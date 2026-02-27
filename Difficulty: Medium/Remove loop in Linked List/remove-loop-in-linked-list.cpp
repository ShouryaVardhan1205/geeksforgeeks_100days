class Solution {
public:
    void removeLoop(Node* head) {
        if (head == NULL || head->next == NULL)
            return;

        Node *slow = head, *fast = head;

        // Detect loop using Floyd’s Cycle Detection
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                // Loop detected

                slow = head;

                // If loop starts at head
                if (slow == fast) {
                    while (fast->next != slow)
                        fast = fast->next;
                }
                else {
                    while (slow->next != fast->next) {
                        slow = slow->next;
                        fast = fast->next;
                    }
                }

                // Break the loop
                fast->next = NULL;
                return;
            }
        }
    }
};