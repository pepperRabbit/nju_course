#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
题目：三数之和

题目描述：

题目描述

一个没有重复元素的整数数组，给定某个整数，找到所有triple之和等于该整数的个数，其中triple是数组中的不同的3个数。

 

输入

数组长度，以及要求的三数之和；
没有重复元素的数组。

 

输出

所有triple的个数。

 

样例输入

6 3

8 0 -5 -2 6 -1

 

样例输出

2

6 3
8 0 -5 -2 6 -1
2
8 0 -5
-2 6 -1
*/

int main() {
    int n, k;
    cin>>n>>k;
    vector<int> num(n);
    for(int i=0;i<n;i++) {
        cin>>num[i];
    }
    sort(num.begin(), num.end());
    int cnt = 0;
    for(int i=0;i<n-2;i++) {
        int l=i+1;
        int r=n-1;
        while(l<r) {
            //cout<<i<<" "<<l<<" "<<r<<" "<<endl;
            if(num[i]+num[l]+num[r]==k) {
                cnt++;
                l++;
            }
            else if(num[i]+num[l]+num[r]<k) {
                l++;
            }
            else r--;
        }
    }
    cout<<cnt<<endl;
    system("pause");
    return 0;
}