/* SO 21348173 BFS implementation not working properly */
#include <iostream>
#include <queue>

class node { public: int x, y, l; };

int bfs(int bx, int by, int ex, int ey)
{
    node start;
    int result = 0;
    start.x = bx;
    start.y = by;
    start.l = 1;
    std::queue<node> search_queue;
    //std::queue<node> path;
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

        if (top.x < 0 || top.x >= 4)
            continue;
        if (top.y < 0 || top.y >= 4)
            continue;
        if (visited[top.x][top.y])
            continue;
        if (map[top.x][top.y] == 1)
            continue;

        //path.push(top);
        visited[top.x][top.y] = true;
        std::cout << "visit: [" << top.x << "][" << top.y << "] = " << top.l << "\n";

        result = top.l;
        if (top.x == ex && top.y == ey)
            break;

        node temp;

        temp.l = top.l + 1;

        temp.x = top.x + 1;
        temp.y = top.y;
        search_queue.push(temp);

        temp.x = top.x - 1;
        temp.y = top.y;
        search_queue.push(temp);

        temp.x = top.x;
        temp.y = top.y + 1;
        search_queue.push(temp);

        temp.x = top.x;
        temp.y = top.y - 1;
        search_queue.push(temp);
    }

    //std::cout << "path:";
    //while (!path.empty())
    //{
    //    node p = path.front();
    //    path.pop();
    //    std::cout << " --> [" << p.x << "][" << p.y << "]";
    //}
    //std::cout << std::endl;

    return result;
}

int main()
{
    std::cout << bfs(0, 0, 3, 3) << std::endl;
}

