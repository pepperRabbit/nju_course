#include <iostream>
using namespace std;

/*
题目：[算法设计与分析]问题 B: 非完美二叉树的高度与直径

题目描述：

题目描述
记T为一棵二叉树，树中共有n个节点。
定义根节点的深度为0，其余节点的深度为其父节点的深度加1。T的高度定义为其叶节点深度的最大值。
定义树中任意两点a和b之间的距离为其间最短简单路径的长度。T的直径定义为T中所有点对间距离的最大值。
输入一棵二叉树T，请计算它的高度和直径。
 
输入
输入共三行。
第一行为节点数n
第二行为树的前序遍历表示，每个节点之间用空格隔开。
第三行为树的中序遍历表示，每个节点之间也用空格隔开。
 
输出
输出共两行。
第一行输出树的高度。
第二行输出树的直径。
8
1 2 4 7 3 5 6 8
4 7 2 1 3 5 8 6
*/

struct node
{
    int val;
    node *left;
    node *right;
};

node *create(int *pre, int *in, int n)
{
    if (n <= 0)
        return NULL;
    int val = pre[0];
    int pos;
    for (int i = 0; i < n; i++)
    {
        if (in[i] == val)
        {
            pos = i;
            break;
        }
    }
    //if(pos==n) printf("error\n");
    node *root = (node *)malloc(sizeof(node));
    root->val = val;
    root->left = create(pre + 1, in, pos);
    root->right = create(pre + 1 + pos, in + 1 + pos, n - 1 - pos);
    return root;
}

int height(node *root)
{
    if (root == NULL)
        return -1;
    else
    {
        //printf("%d ", root->val);
        int left = height(root->left);
        int right = height(root->right);
        return max(left, right) + 1;
    }
}

int diameter(node *root)
{
    if (root == NULL)
        return 0;
    if (root->left && root->right)
        return height(root->left) + height(root->right) + 2;
    else if (root->left)
        return max(height(root), diameter(root->left));
    else
        return max(height(root), diameter(root->right));
}

int main()
{
    int n;
    cin >> n;
    int *pre = new int[n];
    int *in = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> pre[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> in[i];
    }
    node *root = create(pre, in, n);
    cout << height(root) << endl;
    cout << diameter(root) << endl;
    system("pause");
    return 0;
}