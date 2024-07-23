#include <iostream>

struct Node_t {
    int data;
    Node_t* next;

    Node_t(int val) : data(val), next(nullptr) {}
};

void append(Node_t* &head, int val) {
    Node_t* newNode = new Node_t(val);
    if (!head) {
        head = newNode;
        return;
    }
    Node_t* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void remove(Node_t* &head, int val)
{
    if (!head)
        return;

    Node_t* temp = head;

    if (temp->data == val)
    {
        head = temp->next;
        delete temp;
        return;
    }

    while (temp->next) {
        Node_t* next = temp->next;

        if (next->data == val) {
            temp->next = next->next;
            delete next;
            break;
        }
        temp = next;
    }
}

void display(Node_t* head) {
    if (!head) {
        std::cout << "List is empty." << std::endl;
        return;
    }
    Node_t* temp = head;
    while (temp) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "nullptr" << std::endl;
}

void deleteList(Node_t*& head) {
    Node_t* temp = head;
    while (temp) {
        Node_t* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}

int main() {
    Node_t* head = nullptr;

    append(head, 10);
    append(head, 20);
    append(head, 30);
    append(head, 40);

    display(head);

    remove(head, 10);
    remove(head, 40);
    remove(head, 70);

    display(head);

    remove(head, 20);
    remove(head, 30);

    display(head);
    deleteList(head);

    return 0;
}
