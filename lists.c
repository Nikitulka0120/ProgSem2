#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
    struct node *second_next;
};
typedef struct node node_t;

node_t *newNode(int data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    node->second_next = NULL;
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

void printElement(node_t *element)
{
    node_t *cur = element;
    printf("%d ", cur->data);
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

void addSecond(node_t **head, int data, node_t **S)
{
    node_t *new = newNode(data);
    if (*S == NULL) 
    {
        *S = new;
        return;
    }

    node_t *cur_first = *head;
    node_t *cur_second = *S;

    while (cur_second->next != NULL)
    {   
        cur_second = cur_second->next;
        cur_first = cur_first->second_next;
    }
    cur_second->next = new;
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

    node_t *S = NULL;
    printf("\nПервый список\n");
    printList(head);
    while (1)
    {
        printf("\nВведите число второго списка:");
        scanf("%d", &n);
        if (n==0){
            break;
        }
        addSecond(&head, n, &S);
    }
    printList(S);
    char con;
    printf("Управление: \nW-Печать текущего элемента списка\nD-Печать следующего элемента списка\nS-Печать нижнего элемента\nA-Печать начального элемента текущего списка");
    scanf("%c", &con);
    node_t *current=head;
    if (con == "W"){
        printElement(&current);
    }
        elif (con == "W"){
        printElement(&current);
    }

    return 0;
}
