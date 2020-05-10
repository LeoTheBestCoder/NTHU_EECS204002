/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107061218
 * 3. OJ ID: leo
 * 4. OJ SID: 2223878
 * 5. OJ Score: 10
 */
#include <iostream>
#include <queue>
using namespace std;
string level_order_after_tree = "";
class TreeNode
{
public:
    char data;
    TreeNode *leftChild = 0;
    TreeNode *rightChild = 0;
    TreeNode(char ch = 'A')
    {
        data = ch;
    }
};

TreeNode *build_tree(string level_order, string in_order)
{
    int root_idx;
    char root_data;
    TreeNode *root;
    string left_subtree = "", right_subtree = "";
    string new_left_level_order = "", new_right_level_order = "";
    root_data = level_order[0];
    root = new TreeNode(root_data);

    for (int i = 0; i < in_order.length(); i++)
    {
        // find the index of root
        if (in_order[i] == root_data)
        {
            root_idx = i;
            break;
        }
    }

    for (int i = 0; i < root_idx; i++)
    {
        left_subtree += in_order[i];
    }
    for (int i = root_idx + 1; i < in_order.length(); i++)
    {
        right_subtree += in_order[i];
    }

    if (left_subtree.length() == 1)
    {
        // cout << "add a left node directly: " << left_subtree[0] << "\n";
        root->leftChild = new TreeNode(left_subtree[0]);
    }
    else if (left_subtree.length() > 1)
    {
        // root->leftChild = new TreeNode(left_subtree[0]);
        for (int i = 0; i < level_order.length(); i++)
        {
            for (int j = 0; j < left_subtree.length(); j++)
            {
                if (level_order[i] == left_subtree[j])
                {
                    new_left_level_order += level_order[i];
                }
            }
        }
        // cout << "new_left_level_order = " << new_left_level_order << " left_subtree = " << left_subtree << "\n";
        root->leftChild = build_tree(new_left_level_order, left_subtree);
    }

    if (right_subtree.length() == 1)
    {
        // cout << "add a right node directly: " << right_subtree[0] << "\n";
        root->rightChild = new TreeNode(right_subtree[0]);
    }
    else if (right_subtree.length() > 1)
    {
        // root->rightChild = new TreeNode(right_subtree[0]);
        for (int i = 0; i < in_order.length(); i++)
        {
            for (int j = 0; j < right_subtree.length(); j++)
            {
                if (level_order[i] == right_subtree[j])
                {
                    new_right_level_order += level_order[i];
                }
            }
        }
        // cout << "fuck";
        // cout << "new_right_level_order = " << new_right_level_order << " right_subtree = " << right_subtree << "\n";
        root->rightChild = build_tree(new_right_level_order, right_subtree);
    }
    return root;
}

void visit(TreeNode *p)
{
    level_order_after_tree += p->data;
    // cout << p->data;
}

void in_order_traversal(TreeNode *p)
{
    if (p == nullptr)
        return;
    in_order_traversal(p->leftChild);
    visit(p);
    in_order_traversal(p->rightChild);
}

void level_order_traversal(TreeNode *p)
{
    queue<TreeNode *> q;
    TreeNode *currentNode = p;
    while (currentNode)
    {
        visit(currentNode);
        if (currentNode->leftChild)
        {
            q.push(currentNode->leftChild);
        }
        if (currentNode->rightChild)
        {
            q.push(currentNode->rightChild);
        }
        if (q.empty())
            return;
        currentNode = q.front();
        q.pop();
    }
}

int main()
{
    int pairs;
    string level_order, in_order;
    TreeNode *root_of_tree;
    cin >> pairs;
    cout << pairs << "\n";
    for (int i = 0; i < pairs; i++)
    {
        cin >> level_order;
        cin >> in_order;
        root_of_tree = build_tree(level_order, in_order);
        level_order_traversal(root_of_tree);
        // cout << "level_after_tree = " << level_order_after_tree << "\n";
        cout << level_order << "\n"
             << in_order << " ";
        for (int i = 0; i < level_order.length(); i++)
        {
            for (int j = 0; j < in_order.length(); j++)
            {
                if (level_order[i] == in_order[j] && i == 0)
                    cout << j;
                else if (level_order[i] == in_order[j] && i != 0)
                    cout << "-" << j;
            }
        }
        cout << " ";
        if (level_order == level_order_after_tree)
            cout << "Yes\n";
        else
            cout << "No\n";
        level_order_after_tree = "";
        // cout << "in order: ";
        // in_order_traversal(root_of_tree);
        // cout << "\nlevel order: ";

        // level_order_traversal(root_of_tree);
        // cout << "\n"
        //      << root_of_tree->data;
        // cout << root_of_tree->rightChild->data << root_of_tree->rightChild->leftChild->data << root_of_tree->rightChild->rightChild->data;
        // cout << root_of_tree->rightChild->rightChild->leftChild->data << root_of_tree->rightChild->rightChild->rightChild->data << "\n";
        // cout << root_of_tree->leftChild->data;
        // if (root_of_tree->rightChild->leftChild->leftChild == nullptr)
        //     cout << "FK";
        // if (root_of_tree->rightChild->leftChild->rightChild == nullptr)
        //     cout << "FK2";
    }
    return 0;
}