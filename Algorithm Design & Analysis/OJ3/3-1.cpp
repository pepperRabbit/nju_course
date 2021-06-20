#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;

/*题目：[算法设计与分析]问题 A: 动态中位数问题

题目描述：

题目描述

输入一组整数a , a , …, a ，每输入一个整数，输出到此时为止的中位数。
中位数定义：如果数串的大小是偶数 2j，中位数是从小到大排列的第 j 个数；如果数串的大小是奇数 2j+1，中位数是从小到大排列的 第 j+1 个数。

输入

一组整数，数字和数字之间以空格隔开。

输出

一组整数，数字和数字之间以空格隔开。最后一个数后面也有空格。
第 i 个输出的整数，是前 i 个输入的中位数。
*/

int main()
{
    int n, cnt = 0, median;
    priority_queue<int, vector<int>, less<int>> left;
    priority_queue<int, vector<int>, greater<int>> right;
    while (cin >> n)
    {
        if (cnt == 0)
        {
            left.push(n);
            median = n;
            cnt++;
            printf("%d ", median);
            continue;
        }
        else if (n >= median)
        {
            right.push(n);
        }
        else
        {
            left.push(n);
        }
        if (left.size() - right.size() == 2)
        {
            right.push(left.top());
            left.pop();
        }
        else if (right.size() - left.size() == 2)
        {
            left.push(right.top());
            right.pop();
        }
        cnt++;
        if (cnt % 2)
        {
            if (left.size() == cnt / 2)
                median = right.top();
            else
                median = left.top();
        }
        else
            median = left.top();
        printf("%d ", median);
    }
    return 0;
}
