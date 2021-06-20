#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
题目：割点与桥

题目描述：

题目描述
给出一个无向连通图，找到所有的割点和桥
输入
第一行：点的个数，如果点个数是n，他们的编号为0 ~ n-1

余下的行：每行代表一条边，如“0 2”代表顶点0和顶点2有一条边 (一条边只出现一次，如出现“0 2”则不会出现“2 0”)

 

输出
所有的割点和所有的桥，先输出割点再输出桥

割点按编号升序排列，桥按边的升序排列，如“0 2”小于“0 3”，“1 5”小于“2 3”（边的输出和排列总是把小顶点放前面，所以输出总是“0 2”而非“2 0”）
5
1 2
1 3
2 4
0 1
0 2

1
2
1 3
2 4*/

int mytime = 0;

void articulation_point_dfs(vector<int> *g, int v, pair<int, int> *time_table, vector<int> &res, int &tree, int father)
{
    //cout << "dfs" << v << endl;
    mytime++;
    time_table[v].first = mytime * -1;
    time_table[v].second = mytime;
    for (auto i = g[v].begin(); i != g[v].end(); i++)
    {
        if (time_table[*i].first == 0)
        {
            if (v == 0)
                tree++;
            articulation_point_dfs(g, *i, time_table, res, tree, v);
            if (time_table[*i].second >= abs(time_table[v].first) && v != 0)
            {
                //cout << "p" << v << endl;
                res.push_back(v);
            }
            time_table[v].second = min(time_table[v].second, time_table[*i].second);
        }
        else
        {
            if (time_table[*i].first < 0 && *i != father)
            {
                time_table[v].second = min(time_table[v].second, abs(time_table[*i].first));
            }
        }
    }
    time_table[v].first = abs(time_table[v].first);
}

void bridge_dfs(vector<int> *g, int v, pair<int, int> *time_table, vector<pair<int, int>> &res, int father)
{
    mytime++;
    time_table[v].first = mytime * -1;
    time_table[v].second = mytime;
    for (auto i = g[v].begin(); i != g[v].end(); i++)
    {
        if (time_table[*i].first == 0)
        {
            bridge_dfs(g, *i, time_table, res, v);
            time_table[v].second = min(time_table[v].second, time_table[*i].second);
            //cout<<v<<" "<<*i<<" "<<time_table[v].second<<endl;
            if (time_table[*i].second > abs(time_table[v].first))
            {
                if (v > *i)
                {
                    res.push_back(pair<int, int>(*i, v));
                }
                else
                    res.push_back(pair<int, int>(v, *i));
            }
        }
        else
        {
            if (time_table[*i].first < 0 && *i != father)
            {
                time_table[v].second = min(time_table[v].second, abs(time_table[*i].first));
            }
        }
    }
    time_table[v].first = abs(time_table[v].first);
}

int main()
{
    int n, a, b;
    cin >> n;
    vector<int> *g = new vector<int>[n];
    while (cin >> a)
    {
        cin >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    pair<int, int> *time_table = new pair<int, int>[n]; // discover_time, back
    int tree = 0;
    vector<int> point;
    articulation_point_dfs(g, 0, time_table, point, tree, -1);
    /*for(int i=0;i<n;i++){
        cout<<time_table[i].first<<" "<<time_table[i].second<<endl;
    }*/
    if (tree > 1)
        point.push_back(0);
    //cout << point.size() << endl;
    sort(point.begin(), point.end());
    for (auto i = point.begin(); i != point.end(); i++)
    {
        cout << *i << endl;
    }
    mytime = 0;
    delete[] time_table;
    time_table = new pair<int, int>[n];
    vector<pair<int, int>> bridge;
    bridge_dfs(g, 0, time_table, bridge, -1);
    /*for(int i=0;i<n;i++){
        cout<<time_table[i].first<<" "<<time_table[i].second<<endl;
    }*/
    sort(bridge.begin(), bridge.end());
    for (int i = 0; i < bridge.size(); i++)
    {
        cout << bridge[i].first << " " << bridge[i].second << endl;
    }
    system("pause");
    return 0;
}