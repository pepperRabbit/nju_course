#include <iostream>
using namespace std;

/*��Ŀ��ͬ���ַ���

��Ŀ������

���������ַ��� s �� t���ж������Ƿ���ͬ���ġ�

��� s �е��ַ����Ա��滻�õ� t ����ô�������ַ�����ͬ���ġ�

���г��ֵ��ַ�����������һ���ַ��滻��ͬʱ�����ַ���˳�������ַ�����ӳ�䵽ͬһ���ַ��ϣ����ַ�����ӳ���Լ�����

ʾ�� 1:

����: egg add ���: true

ʾ�� 2:

����: foo bar ���: false

ʾ�� 3:

����: paper title ���: true

˵��: ����Լ��� s �� t ������ͬ�ĳ��ȡ�
*/

int main() {
	int count_s[26] = { 0 };
	int count_t[26] = { 0 };
	string s, t;
	cin >> s >> t;
	for (int i = 0; i < s.length(); i++) {
		count_s[s[i] - 'a']++;
		count_t[t[i] - 'a']++;
	}
	for (int i = 0; i < 26; i++) {
		if (count_s[i] > 0) {
			for (int j = 0; j < 26; j++) {
				if (count_s[i]==count_t[j]) {
					count_t[j] = 0;
					break;
				}
				else if (j == 25) {
					cout << "false" << endl;
					return 0;
				}
			}
		}
	}
	cout << "true" << endl;
	return 0;
}