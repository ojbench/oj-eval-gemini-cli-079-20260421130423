#include <iostream>
#include <cstdio>

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

struct LinkedList {
    Node* head;
    int size;

    LinkedList() : head(nullptr), size(0) {}

    void initialize() {
        int n;
        if (scanf("%d", &n) != 1) return;
        Node* tail = nullptr;
        for (int i = 0; i < n; i++) {
            int val;
            if (scanf("%d", &val) != 1) break;
            Node* newNode = new Node(val);
            if (!head) {
                head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
            size++;
        }
    }

    void insert(int i, int x) {
        if (i < 0 || i > size) return;
        Node* newNode = new Node(x);
        if (i == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* curr = head;
            for (int k = 1; k < i; k++) {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
        size++;
    }

    void erase(int i) {
        if (i < 1 || i > size) return;
        if (i == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node* curr = head;
            for (int k = 1; k < i - 1; k++) {
                curr = curr->next;
            }
            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
        size--;
    }

    void swap() {
        if (!head || !head->next) return;
        
        Node dummy(0);
        dummy.next = head;
        Node* prev = &dummy;
        Node* curr = head;
        
        while (curr && curr->next) {
            Node* first = curr;
            Node* second = curr->next;
            Node* nextPair = second->next;
            
            prev->next = second;
            second->next = first;
            first->next = nextPair;
            
            prev = first;
            curr = nextPair;
        }
        head = dummy.next;
    }

    void moveback(int i, int x) {
        if (i <= 0 || x <= 0 || i + x > size) return;
        
        Node* node_i = head;
        for (int k = 1; k < i; k++) node_i = node_i->next;
        
        Node* node_ix = node_i;
        for (int k = 0; k < x; k++) node_ix = node_ix->next;
        
        Node* first_start = head;
        Node* first_end = node_i;
        Node* second_start = node_i->next;
        Node* second_end = node_ix;
        Node* third_start = node_ix->next;
        
        head = second_start;
        second_end->next = first_start;
        first_end->next = third_start;
    }

    int query(int i) {
        if (i < 1 || i > size) return -1;
        Node* curr = head;
        for (int k = 1; k < i; k++) curr = curr->next;
        return curr->data;
    }

    void printAll() {
        Node* curr = head;
        while (curr) {
            printf("%d%c", curr->data, curr->next ? ' ' : '\n');
            curr = curr->next;
        }
        if (!head) printf("\n");
    }

    void ClearMemory() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        size = 0;
    }
};

int main() {
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    if (scanf("%d", &m) != 1) return 0;
    while(m--) {
        if (scanf("%d", &op) != 1) break;
        if(op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if(op == 2) {
            scanf("%d", &i);
            List.erase(i);
        }
        else if(op == 3) {
            List.swap();
        }
        else if(op == 4) {
            scanf("%d%d",&i, &x);
            List.moveback(i, x);
        }
        else if(op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        }
        else if(op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}
