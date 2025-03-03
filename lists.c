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
    if (element)
        printf("%d\n", element->data);
    else
        printf("Элемент не найден!\n");
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
        if (*head != NULL)
        {
            (*head)->second_next = *S;
        }
        return;
    }
    
    node_t *cur_second = *S;
    while (cur_second->next != NULL)
    {   
        cur_second = cur_second->next;
    }
    cur_second->next = new;
    
    node_t *cur_first = *head;
    while (cur_first !=NULL && cur_first->second_next)
    {
        cur_first = cur_first->next;
    }
    cur_first->second_next = new;
}

int main()
{
    node_t *head = NULL;
    int n;
    
    printf("Введите числа для первого списка (0 для завершения):\n");
    while (1)
    {
        scanf("%d", &n);
        if (n == 0)
            break;
        addLast(&head, n);
    }

    node_t *S = NULL;
    printf("\nПервый список:\n");
    printList(head);

    printf("\nВведите числа для второго списка (0 для завершения):\n");
    while (1)
    {
        scanf("%d", &n);
        if (n == 0)
            break;
        addSecond(&head, n, &S);
    }

    printf("\nВторой список:\n");
    printList(S);

    node_t *current = head;
    char con;
    
    printf("\nУправление: \nW - Печать текущего элемента списка\nD - Печать следующего элемента списка\nS - Печать нижнего элемента\nA - Печать начального элемента текущего списка\n");
    
    while (1)
    {
        scanf(" %c", &con);
        switch (con)
        {
            case 'W':
                printElement(current);
                break;
            case 'D':
                if (current && current->next)
                    current = current->next;
                printElement(current);
                break;
            case 'S':
                if (current && current->second_next)
                    current = current->second_next;
                printElement(current);
                break;
            case 'A':
                current = head;
                printElement(current);
                break;
            default:
                printf("Неизвестная команда!\n");
                break;
        }
    }
    return 0;
}
