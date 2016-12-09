#include "node.h"

DataNode * findPrevMatching(int x, int y)
{
    // Chained arrow operators in a loop
    while (!(head->next->data->x == x && head->next->data->y == y))  
        head = head->next;

    return head;
}

