#include <iostream>
#include <algorithm>
#include <utility>
#include <map>
#include <vector>
using namespace std;

/*
题目：[算法设计与分析作业]变位词

题目描述：

题目描述
请大家在做oj题之前，仔细阅读关于抄袭的说明http://www.bigoh.net/JudgeOnline/.
变位词是指由相同的字母组成的单词，如eat、tea是变位词。本次问题给出一串单词，你需要找到所有的变
位词。


输入
输入由两行组成：第一行是所有单词的总数，第二行是由空格分隔的单词列表。两行末尾都有空格。
 

输出
这次需要大家先输出一个字符串，它是“我已阅读关于抄袭的说明”的汉语拼音.输出此行的提交我们将认
为已经完全阅读并了解了“关于抄袭的说明”公告.
第二行是变位词组的个数，后面是所有的变位词。每个输出的变位词占一行。一组变位词只需要输出一个字
典序最小的代表即可，如eat、tea中eat字典序小于tea，所以输出eat。变位词与变位词也按照字典序从小
到大排列，如eat和el中eat字典序小于el所以eat在el前面。
输出的每一行最后都没有空格。

样例输入

9 a
ew vc tea oe eat zoo el le
 

样例输出

wo yi yue du guan yu chao xi de shuo ming
2 
eat
el*/

int main()
{
  cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
  int n;
  cin >> n;
  string s;
  map<string, pair<int, string>> m;
  map<string, pair<int, string>>::iterator iter;
  for (int i = 0; i < n; i++)
  {
    cin >> s;
    string temp = s;
    sort(temp.begin(), temp.end());
    //iter=m.find(s);
    if (m[temp].first == 0)
    {
      m[temp].first = 1;
      m[temp].second = s;
    }
    else
    {
      m[temp].first++;
      if (s < m[temp].second)
        m[temp].second = s;
    }
  }
  vector<string> ans;
  for (iter = m.begin(); iter != m.end(); iter++)
  {
    if (iter->second.first > 1)
      ans.push_back(iter->second.second);
  }
  cout << ans.size() << endl;
  sort(ans.begin(), ans.end());
  vector<string>::iterator iter2;
  for (iter2 = ans.begin(); iter2 != ans.end(); iter2++)
  {
    cout << (*iter2) << endl;
  }
  system("pause");
  return 0;
}