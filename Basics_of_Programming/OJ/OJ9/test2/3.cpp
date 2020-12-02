#include <iostream>
using namespace std;

/*
题目：Problem 3 猫和老鼠

题目描述：

morse

在一列火车上，有一只来回巡视的机器猫和一只机灵的老鼠。火车由n节车厢组成，用编号1~n表示从火车头到火车尾的每一节车厢。

机器猫的运动方式如下：

在每1分钟里，机器猫都只会笨笨地沿着一个给定的方向从一节车厢移动到相邻的另一节车厢；
当机器猫到达火车头时，它会改变它的运动方向，即它下1分钟会移动到2号车厢并且朝着火车尾方向移动；
同理，当机器猫到达火车尾，它会改变运动方向，即它下1分钟会移动到n-1号车厢并且朝着火车头的方向移动；如此反复。
火车在每1分钟内都会有一个状态：或者是处在行驶状态用0表示，或者是处在停止状态，用1表示。(即到站停靠)

老鼠的运动方式如下：

每1分钟里，如果当前火车是行驶状态，那么老鼠只能移动到它相邻的车厢，或者待在原来的车厢不动。
每1分钟里，如果当前火车是停止状态，那么老鼠会在先下车，然后选择1~n中的任意一节车厢上车。
运动顺序：每一分钟内，如果火车是行驶状态：老鼠先进行移动，然后机器猫再移动。如果火车是停止状态，老鼠先下车，然后机器猫移动，最后老鼠再上车。同时，机智的老鼠利用它的耗子尾汁可以知道每一分钟内，机器猫的位置和运动方向。

如果在某一时刻机器猫和老鼠在同一节车厢，那么老鼠会被机器猫捉住。

问：在给定火车在t分钟内的运动状态序列，老鼠和机器猫的初始位置，以及机器猫的初始方向的情况下，假设老鼠每一分钟都会选择最好移动方式（最好的移动方式是唯一的，可以手动模拟一下试试）来避免被捉或者尽可能地拖延被捉，老鼠在t分钟内能否被机器猫捉到；如果能，最后在哪节车厢被捉？

提示：需要动动脑筋，使用学过的知识可以解决，但是需要细心，思考其中的细节。

输入格式：

第一行：3个整数n,m,k，分别表示车厢的节数，老鼠一开始所在的车厢号，机器猫一开始所在的车厢号。(2<=n<=50,1<=m,k<=n,m != k)

第二行：1个数d，只有-1,1两种取值，表示机器猫初始的运动方向（-1表示向火车头方向运动，1表示向火车尾方向运动)

第三行：1个数t，表示火车运动状态序列的时间跨度为t分钟 (1<=t<=200)

第四行：t个数，用空格隔开，表示在这t分钟内的每一分钟内火车的状态，只有0,1两种取值，0表示行驶状态，1表示停止状态。

输出格式：

一行：如果机器猫不能捉住老鼠，输出-1；如果能捉住老鼠，输出老鼠被捉住时所在的车厢号

样例输入：

输入1： 5 3 2 -1 7 0 0 0 1 0 0 1
输出1： -1
输入2： 3 2 1 1 4 0 0 0 1
输出2： 3*/

int main() {
	int n, m, k, d, t, turns[202] = { 0 };
	cin >> n >> m >> k >> d >> t;
	for (int i = 1; i <= t; i++) {
		cin >> turns[i];
	}
	int i = 1;
	while (m != k && i <= t) {
		//cout << "turn" << i;
		if (turns[i] == 0) {//train move
			int distance = abs(m - k);
			if (m > 1 && abs(m - 1 - k) > distance) {//mouse move left
				m--;
			}
			else if (m<n && abs(m + 1 - k)>distance) {//mouse move right
				m++;
			}
			if (d == -1) {//cat move left
				if (k == 1) d = 1;
			}
			else {//cat move right
				if (k == n) d = -1;
			}
			k += d;	//cat move
		}
		else if (turns[i] == 1) {//train stop
			if (d == -1) {//cat move left
				if (k == 1) d = 1;
			}
			else {//cat move right
				if (k == n) d = -1;
			}
			k += d;	//cat move
			if (d == -1) {
				if (k == n) m = 1;
				else m = n;
			}
			else if (d == 1) {
				if (k == 1) m = n;
				else m = 1;
			}
		}
		i++;
		//cout << ": " << m << " " << k << endl;
	}
	if (k == m) cout << k << endl;
	else cout << -1 << endl;
	return 0;
}
