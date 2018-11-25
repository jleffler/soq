#include "node.h"


DataNode * findPrevMatching(int x, int y)
{
    DataNode *next = head->next;
    Data *data = next->data;

    while (!(data->x == x && data->y == y))
    {
        head = head->next;
        next = head->next;
        data = next->data;
    }

    return head;
}
