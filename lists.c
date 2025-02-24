#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};
typedef struct node node_t;

node_t *newNode(int data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    return node;
}

void printList(node_t *head)
{
    node_t *cur = head;
    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void addLast(node_t **head, int data)
{
    node_t *new = newNode(data);
    if (*head == NULL) 
    {
        *head = new;
        return;
    }

    node_t *cur = *head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new;
}

int main()
{
    // // node_t *node1 = newNode(1);
    // // node_t *node2 = newNode(2);
    // // node_t *node3 = newNode(3);
    // node1->next = node2;
    // node2->next = node3;

    node_t *head = NULL;
    int n;
    while (1)
    {
        printf("\nВведите число:");
        scanf("%d", &n);
        if (n==0){
            break;
        }
        addLast(&head, n);
    }

    printList(head);

    return 0;
}
