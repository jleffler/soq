typedef struct Data 
{
    int x;
    int y;
} Data;

typedef struct DataNode 
{
    struct DataNode *next;
    struct Data *data;
} DataNode;

extern DataNode *head;

extern DataNode *findPrevMatching(int x, int y);

