#include "node.h"


DataNode * findPrevMatching(int x, int y)
{
    DataNode *next = head->next;
    Data *data = next->data;
    int thisX = data->x;
    int thisY = data->y;

    while (!(thisX == x && thisY == y))
    {
        // Assign head->next to head
        head = head->next;

        // Assign each local variable, using the new head
        next = head->next;
        data = next->data;
        thisX = data->x;
        thisY = data->y;
    }

    return head;
}
