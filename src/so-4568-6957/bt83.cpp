/* SO 4568-6957 */
/* Create a binary tree with nodes presented in BFS order */

#include <cassert>
#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;
using std::cout;
using std::cin;
using std::ostream;
using std::setw;

struct node
{
    int data;
    node *left;
    node *right;
    node(int n) : data(n), left(0), right(0) { }
};

void print_bt(const node *root);

int main()
{
    vector<node> v;
    int n;

    // Read data to EOF or a negative value
    while (cin >> n && n >= 0)
        v.push_back(node(n));

    // Create binary tree
    for (size_t i = 0; i < v.size()/2; i++)
    {
        assert(2*i+1 < v.size());
        v[i].left = &v[2*i+1];
        if (2*i+2 < v.size())
            v[i].right = &v[2*i+2];
    }

    // Print binary tree
    print_bt(&v[0]);

    return 0;
}

// print_bt() presents the data so that if you mentally rotate the
// output through 90º clockwise (so the root is at the top), then the
// left child appears on the left and the right on the right.  Reversing
// the order of left/right leaves that as somewhat confusing.
void print_bt(const node *root)
{
    static int level = 0;
    if (root != nullptr)
    {
        level++;
        print_bt(root->right);
        cout << setw(4*level) << root->data << '\n';
        print_bt(root->left);
        level--;
    }
}
