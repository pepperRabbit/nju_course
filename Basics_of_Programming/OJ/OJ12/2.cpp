#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

/*
题目：字谜

题目描述：

描述：
Most crossword puzzle fans are used to anagrams — groups of words with the same letters in different orders — for example OPTS, SPOT, STOP, POTS and POST. Some words however do not have this attribute, no matter how you rearrange their letters, you cannot form another word. Such words are called ananagrams, an example is QUIZ. Obviously such definitions depend on the domain within which we are working; you might think that ATHENE is an ananagram, whereas any chemist would quickly produce ETHANE. One possible domain would be the entire English language, but this could lead to some problems. One could restrict the domain to, say, Music, in which case SCALE becomes a relative ananagram (LACES is not in the same domain) but NOTE is not since it can produce TONE. Write a program that will read in the dictionary of a restricted domain and determine the relative ananagrams. Note that single letter words are, ipso facto, relative ananagrams since they cannot be “rearranged” at all. The dictionary will contain no more than 1000 words.

输入：
Input will consist of a series of lines. No line will be more than 80 characters long, but may contain any number of words. Words consist of up to 20 upper and/or lower case letters, and will not be broken across lines. Spaces may appear freely around words, and at least one space separates multiple words on the same line. Note that words that contain the same letters but of differing case are considered to be anagrams of each other, thus ‘tIeD’ and ‘EdiT’ are anagrams. The file will be terminated by a line consisting of a single ‘#’.

输出：
Output will consist of a series of lines. Each line will consist of a single word that is a relative ananagram in the input dictionary. Words must be output in lexicographic (case-sensitive) order. There will always be at least one relative ananagram.

样例1：
输入：

ladder came tape soon leader acme RIDE lone Dreis peat

ScAlE orb eye Rides dealer NotE derail LaCeS drIed

noel dire Disk mace Rob dries #

输出：

Disk

NotE

derail

drIed

eye

ladder

soon*/

bool cmp(string a, string b)
{
	return a < b;
}

int main() {
    string word;
    vector<string> ans;
    map<string, int> num;
    map<string, string> initial;
    map<string, int>::iterator it;
    while (cin >> word) {
        if (word == "#") break;
        string now = word;
        for (int i = 0; i < now.size(); ++i) {
            now[i] = tolower(now[i]);
        }
        sort(now.begin(), now.end());
        initial[now] = word;
        num[now]++;
    }
    it = num.begin();
    while (it != num.end()){
        if (it->second == 1)
            //cout<<initial[it->first]<<endl;
            ans.push_back(initial[it->first]);
        it++;
    }
    sort(ans.begin(), ans.end(), cmp);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << endl;
    }
	return 0;
}