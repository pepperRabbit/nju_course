#include <iostream>
using namespace std;

/*
题目：[算法设计与分析]有序数组中寻找指定数对

题目描述：

<h2>题目描述</h2>

给定一个 int 数组 arr，元素按照升序排列且各不相同。另外有一个目标数 c，请你找出 arr 中所有的数对 a, b，使得 a + b = c。

输入

输入为三行，第一行为 arr 的元素个数，第二行为 arr，元素以空格分隔，第三行为目标数 c。

输出

所有符合条件的数对 a, b。a 和 b 以空格分开，每个数对占据一行。每行中 a  b，所有数对以它的第一个数（也就是 a 的值）升序排列。

10
1 3 4 5 7 9 10 11 13 15
16
*/

void solve(int arr[],int l,int r,int c){
    if(l<r){
        int res=arr[l]+arr[r];
        if(res<c) return;
        else if(res==c){
            cout<<arr[l]<<" "<<arr[r]<<endl;
            return;
        }
        else solve(arr,l,r-1,c);
    }
}

int main(){
    int n,c;
    cin>>n;
    int* arr=new int[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cin>>c;
    for(int i=0;i<n;i++){
        solve(arr,i,n-1,c);
    }
    system("pause");
    return 0;
}