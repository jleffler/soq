/* SO 4568-6957 */
/* Create a binary tree with nodes presented in BFS order */

#include <cassert>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

struct node
{
    int data;
    node *left;
    node *right;
    node(int n) : data(n), left(0), right(0) { }
};

void print_bt(const node *root)
{
    if (root != nullptr)
    {
        print_bt(root->left);
        cout << root->data << '\n';
        print_bt(root->right);
    }
}

int main()
{
    vector<node *> v;
    int n;

    while (cin >> n && n >= 0)
        v.push_back(new node(n));

    for (size_t i = 0; i < v.size()/2; i++)
    {
        assert(2*i+1 < v.size());
        v[i]->left = v[2*i+1];
        if (2*i+2 < v.size())
            v[i]->right = v[2*i+2];
    }

    print_bt(v[0]);

    for (size_t i = 0; i < v.size(); i++)
        delete(v[i]);

    return 0;
}
