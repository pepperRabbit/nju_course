#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
题目：中位数附近2k+1个数(v2)

题目描述：

题目描述
给出一串字符串数组 a1,a2,...,an 以及一个较小的常数 k，找出这串字符串的中位数 m 和最接近 m 的小于等于 m 的 k 个数，以及最接近 m 的大于等于 m 的 k 个数。将这 2k+1 个字符串按升序排序后输出。

中位数定义：如果数串的大小是偶数 2j，中位数是从小到大排列的第 j 个数；如果数串的大小是奇数 2j+1，中位数是从小到大排列的第 j+1 个数。

输入
第一行是 n 的值和数串的长度 k。

第二行是以空格隔开的 n 个字符串，这n个字符串不重复，最后一个字符串后面有空格。

输出
按升序排列的 2k+1 个数，以空格分开，最后一个数后面没有空格。结果不可能出现重复的数。

样例输入
10 2
cz dk be bf ch ab ad ci ac bc 
样例输出
ad bc be bf ch

10 2
cz dk be bf ch ab ad ci ac bc 

26 10
a b c d e f g h i j k l m n o p q r s t u v w x y z
*/

int part(vector<string> &s, int l, int r) {
    int tmp = l, pivot = r;
    int i = l;
    while(i<=r) {
        if(s[i]<s[pivot]){
            if(i!=tmp) swap(s[tmp], s[i]);
            tmp++;
        }
        i++;
    }
    swap(s[tmp], s[pivot]);
    return tmp;
}

void mid(vector<string> &s, int l, int r, int m) {
    int pivot = part(s, l, r);
    if(pivot<m) mid(s, pivot+1, r, m);
    else if(pivot>m) mid(s, l, pivot-1, m);
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<string> s(n);
    for(int i=0;i<n;i++) {
        cin>>s[i];
    }
    int m = (n-1)/2;
    mid(s, 0, n-1, m);
    /*cout<<m<<s[m]<<endl;
    for(int i=0;i<n;i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;*/
    priority_queue<string, vector<string>, less<string>> left;
    priority_queue<string, vector<string>, greater<string>> right;
    for(int i=0;i<m;i++) {
        left.push(s[i]);
    }
    for(int i=m+1;i<n;i++) {
        right.push(s[i]);
    }
    vector<string> res(k);
    for(int i=0;i<k;i++) {
        res[k-i-1]=left.top();
        left.pop();
    }
    for(int i=0;i<k;i++){
        cout<<res[i]<<" ";
    }
    cout<<s[m]<<" ";
    for(int i=0;i<k;i++){
        cout<<right.top();
        if(i!=k-1) cout<<" ";
        right.pop();
    }
    system("pause");
    return 0;
}