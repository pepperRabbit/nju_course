#include <iostream>
#include <vector>
using namespace std;

/*
题目：[算法设计与分析作业] 所有逆序对

题目描述：

题目描述
请大家在做oj题之前，仔细阅读关于抄袭的说明http://www.bigoh.net/JudgeOnline/ (http://www.bigoh.net/JudgeOnline/).
给出一个字符串数组，如果（按照字典序）一个大的字符串在比它小的字符串前面我们称这两个字符串组成一个“逆序对”。你需要找到所
有的逆序对的个数。


输入
第一行是数组大小，第二行是以空格分隔的字符串数组.
注：预先知道每个字符串的长度都是 10.


输出
所有的逆序对个数. 这次需要大家先输出一个字符串，它是“我已阅读关于抄袭的说明”的汉语拼音.输出此行的提交我们将认为已经完全
阅读并了解了“关于抄袭的说明”公告.
注意：结果比较大，请用 long 类型保存.

样例输入
3
aaaaaaaaaa cccccccccc bbbbbbbbbb
 

样例输出
wo yi yue du guan yu chao xi de shuo ming
1
---
5
aaa ccc ddd eee bbb
*/

void merge_count(vector<string> &v, int l, int m, int r, long long &res)
{
    //cout << "start " << l << " " << m << " " << r << endl;
    vector<string> tmp(m - l + 1);
    for (int i = l; i <= m; i++)
    {
        tmp[i - l] = v[i];
    }
    int p1 = 0, p2 = m + 1;
    for (int i = l; i <= r; i++)
    {
        //cout << p1 << " " << p2 << endl;
        if (p1 > m - l)
        {
            while (p2 <= r)
            {
                v[i++] = v[p2++];
            }
        }
        else if (p2 > r)
        {
            while (p1 <= m - l)
            {
                v[i++] = tmp[p1++];
            }
        }
        else if (tmp[p1] <= v[p2])
        {
            v[i] = tmp[p1];
            p1++;
        }
        else
        {
            //cout<<"inversion"<<endl;
            v[i] = v[p2];
            p2++;
            res += m - l - p1 + 1;
        }
    }
}

void merge_sort(vector<string> &v, int l, int r, long long &res)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        merge_sort(v, l, mid, res);
        merge_sort(v, mid + 1, r, res);
        merge_count(v, l, mid, r, res);
    }
}

int main()
{
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    int n;
    long long res = 0;
    cin >> n;
    string s;
    vector<string> v;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        v.push_back(s);
    }
    merge_sort(v, 0, n - 1, res);
    cout << res << endl;
    system("pause");
    return 0;
}