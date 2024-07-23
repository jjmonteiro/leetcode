#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t {
    int data;
    struct Node_t* next;
} Node_t;

typedef enum {
    SUCCESS_EXIT,
    ALLOCATION_FAIL,
    INVALID_REFERENCE,
    NODE_NOT_FOUND
} Code_t;

Code_t addNode(Node_t** head, int val) {
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if (newNode == NULL) {
        return ALLOCATION_FAIL;
    }
    newNode->data = val;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return SUCCESS_EXIT;
    }
    Node_t* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Code_t delNode(Node_t** head, int val) {
    if (*head == NULL)
        return INVALID_REFERENCE;

    Node_t* temp = *head;

    if (temp->data == val) {
        *head = temp->next;
        free(temp);
        return SUCCESS_EXIT;
    }

    while (temp->next) {
        Node_t* next = temp->next;
        if (next->data == val) {
            temp->next = next->next;
            free(next);
            return SUCCESS_EXIT;
        }
        temp = next;
    }
    return NODE_NOT_FOUND;
}

Code_t printNodes(Node_t* head) {
    if (head == NULL) {
        return NODE_NOT_FOUND;
    }
    Node_t* temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    return SUCCESS_EXIT;
}

Code_t deleteAll(Node_t** head) {
    if (*head == NULL)
        return INVALID_REFERENCE;

    Node_t* temp = *head;
    while (temp) {
        Node_t* next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    return SUCCESS_EXIT;
}

int main() {
    Node_t* head = NULL;

    addNode(&head, 10);
    addNode(&head, 20);
    addNode(&head, 30);
    addNode(&head, 40);

    printNodes(head);

    delNode(&head, 10);
    delNode(&head, 40);
    delNode(&head, 70);
    addNode(&head, 50);

    printNodes(head);

    delNode(&head, 20);
    delNode(&head, 30);

    printNodes(head);

    deleteAll(&head);

    return 0;
}
