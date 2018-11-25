#include "node.h"


DataNode * findPrevMatching(int x, int y)
{
    DataNode *next = head->next;

    while (!(next->data->x == x && next->data->y == y))
    {
        head = head->next;
        next = head->next;
    }

    return head;
}
