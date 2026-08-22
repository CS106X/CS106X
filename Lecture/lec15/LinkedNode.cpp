struct ListNode {
    int val;            // Data stored in the node
    ListNode *next;     // Pointer to the next node in the list

    // Default constructor
    ListNode() : val(0), next(nullptr) {}

    // Constructor with value initialization
    ListNode(int x) : val(x), next(nullptr) {}

    // Constructor with value and next pointer initialization
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


int size(ListNode* first) {
    ListNode* tmp = first;
    int cap = 0;
    while (tmp != nullptr) {
        cap++;
        tmp = tmp->next;
    }
    return cap;
}

int get(ListNode* first, int index) {
    ListNode* tmp = first;
    for (int i = 0; i <index; ++i) {
        tmp = tmp->next;
    }
    return tmp->val;
}

void print(ListNode *head) {

        ListNode* curr = head;
        while(curr) {
            cout << curr->val << endl;
            curr = curr->next;
        }

}

// &是为了+first
void add(ListNode *& head, int value)  { // 指的是末尾
    // 错误：ListNode new_node = ListNode(value); 分派stack
    ListNode *newNode = new ListNode(value);
    if (!head) {
        head = newNode;
    } else {
            ListNode *tmp = head;
            while(tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = newNode;
    }

} 

void addFirst(ListNode *&head, int value) {
    head = new ListNode(value, head);

        

}


void removeFirst(ListNode *& head) {
    if (!head ) return;
    ListNode *trash = head;
    head = head -> next;
    delete trash;  // delete is to delete what the pointer points at , not the pointer itself
}

void remove(ListNode *& head, int index) {
    if (!head) return;
    ListNode *tmp = head;
    
    if (index == 0) {
        ListNode *trash = head;
        head = head->next; 
        delete trash;
        return;
    }

    for (int i = 0; i < index-1; i++) // 这里ide开始给的size_t i可是无符号整数害惨了我
    {
        tmp = tmp->next;
    }
    ListNode *trash = tmp->next;
    tmp->next = tmp->next->next;
    delete trash;
}

