#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int **edges;
//int *vis, *matched;
int vis[100001], matched[100001];
int x, y;

bool dfs(int k)
{
    //printf("dfs %d\n", k);
    for (int i = 1; i <= edges[k][0]; i++)
    {
        int j = edges[k][i];
        //printf("j:%d ", j);
        //printf("visj val %d\n", vis[j]);
        if (vis[j] != 1)
        { //不在交替路
            vis[j] = 1;
            if (matched[j] <= 0 || dfs(matched[j]))
            { //增广，交换
                matched[j] = k;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    int res = 0;
    memset(matched, 0, sizeof(matched));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= x; i++)
    {
        if (dfs(i))
        {
            res++;
            memset(vis, 0, sizeof(vis));
            //vis = new int[y+1];
        }
    }
    return res;
}

int main()
{
    cin >> x >> y;
    //edges = (int **)malloc(sizeof(int *) * (x + 1));
    edges = new int *[x + 1];
    for (int i = 1; i <= x; i++)
    {
        int num, tmp;
        cin >> num;
        edges[i] = new int[num + 1];
        edges[i][0] = num;
        for (int j = 1; j <= num; j++)
        {
            cin >> tmp;
            edges[i][j] = tmp;
        }
    }
    //vis = (int *)malloc(sizeof(int) * (x + 1));
    //matched = (int *)malloc(sizeof(int) * (x + 1));
    cout << hungary() << endl;
    system("pause");
    return 0;
}