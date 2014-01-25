/* SO 21348173 BFS implementation not working properly */
#include <cassert>
#include <iostream>
#include <queue>

class node {
public:
    node(int x1 = 0, int y1 = 0, int l1 = 0) : x(x1), y(y1), l(l1) { }
    int x, y, l;
};

void push_if_valid(const int map[4][4], std::queue<node> &q, const node &n)
{
    if (n.x < 0 || n.x >= 4)
        return;
    if (n.y < 0 || n.y >= 4)
        return;
    if (map[n.x][n.y] == 1) 
        return;
    q.push(n);
}

int bfs(int bx, int by, int ex, int ey)
{
    node start;
    int result = 0;
    start.x = bx;
    start.y = by;
    start.l = 1;
    std::queue<node> search_queue;
    std::queue<node> path;
    bool visited[4][4];
    int map[4][4] =
    {
        {0, 1, 0, 1},
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 0}
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            visited[i][j] = false;
        }
    }

    search_queue.push(start);
    while (!search_queue.empty())
    {
        node top = search_queue.front();
        search_queue.pop();

        assert(top.x >= 0 && top.x < 4);
        assert(top.y >= 0 && top.y < 4);
        assert(map[top.x][top.y] == 0);
        if (visited[top.x][top.y])
            continue;

        path.push(top);
        visited[top.x][top.y] = true;
        std::cout << "visit: [" << top.x << "][" << top.y << "] = " << top.l << "\n";

        result = top.l;
        if (top.x == ex && top.y == ey)
            break;

        push_if_valid(map, search_queue, node(top.x + 1, top.y + 0, top.l + 1));
        push_if_valid(map, search_queue, node(top.x - 1, top.y + 0, top.l + 1));
        push_if_valid(map, search_queue, node(top.x + 0, top.y + 1, top.l + 1));
        push_if_valid(map, search_queue, node(top.x - 0, top.y - 1, top.l + 1));
    }

    //result = path.size();
    char const *pad = "path:";
    while (!path.empty())
    {
        node p = path.front();
        path.pop();
        std::cout << pad << " [" << p.x << "][" << p.y << "]";
        pad = " -->";
    }
    std::cout << std::endl;

    return result;
}

int main()
{
    std::cout << bfs(0, 0, 3, 3) << std::endl;
}

