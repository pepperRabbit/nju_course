#include <iostream>
using namespace std;

/*题目：[算法设计与分析作业]中位数及前后k个数

题目描述：

题目描述

给出一串整型数 a1,a2,...,an;以及一个较小的常数 k，找出这串数的中位数m和最接近m的小于等于m的 k 个数，以及最接近m的大于等于m的 k 个数。将这 2k+1 个数按升序排序后输出。

中位数定义：如果数串的大小是偶数 2j，中位数是从小到大排列的第 j 个数；如果数串的大小是奇数 2j+1，中位数是从小到大排列的第 j+1 个数。

输入

第一行是 k 的值和数串的长度 n。

第二行是以空格隔开的 n 个整型数，最后一个数后面有空格。

按升序排列的 2k+1 个数，以空格分开，最后一个数后面没有空格。结果可能出现重复的数。

样例输入

2 10
7 2 5 7 2 10 7 7 13 15

输出

按升序排列的 2k+1 个数，以空格分开，最后一个数后面没有空格。结果可能出现重复的数。

样例输出
5 7 7 7 7*/

int get_pivot(int num[], int i, int j){
	int temp=num[i];
	while(i<j){
		while(i<j&&num[j]>=temp){
			j--;
		}
		if(i<j) {
            swap(num[i],num[j]);
        }
		while(i<j&&num[i]<temp){
			i++;
		}
		if(i<j) {
            swap(num[i],num[j]);
        }
	}
	num[i]=temp;
	return i;
}

void quick_sort(int num[],int i, int j){
	if(i<j){
        int pivot=get_pivot(num,i,j);
	    quick_sort(num,i,pivot-1);
	    quick_sort(num,pivot+1,j); 
    }
}

int main(){
	int k,n;
	cin>>k>>n;
	int* num=new int[n];
	for(int i=0;i<n;i++){
		cin>>num[i];
	}
	quick_sort(num,0,n-1);
    int start=(n-1)/2-k;
    for(int i=start;i<=start+2*k;i++){
        cout<<num[i];
        if(i!=start+2*k) cout<<" ";
    }
    system("pause");
	return 0;
} 