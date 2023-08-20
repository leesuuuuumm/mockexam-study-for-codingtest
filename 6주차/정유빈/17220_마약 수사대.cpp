#include <iostream>
#include <vector>
#include <cstring>

int n; //���� ����å ��
int m; //���� ����å ���� ��

using namespace std;

vector<int> v[30];


//�˰ŵ� ����å��
bool catched[30];
int wonsanji; //������
int wonsanji_arr[30];
//�� �޾����� 0, �� ���� ������ 1, ���� �� ������ 2

int answer[30]; //��
int real_ans = 0;

void dfs(int start) {
	//c�� �����ؼ� ����.

	answer[start] = true; 

	for (int i = 0; i < v[start].size(); i++) {
		int next = v[start][i]; 

		if (!catched[next]) {
			dfs(next);
		}
	}
}
void solution() {
	
	int minus_wonsanji = 0; //������ ����

	for (int i = 0; i < 26; i++) {
		if (wonsanji_arr[i] == 1 && !catched[i]) {
			minus_wonsanji++;
			dfs(i);
		}
	}

	for (int i = 0; i < 26; i++) {
		if (answer[i]) {
			real_ans++;
		}
	}
	cout << real_ans - minus_wonsanji;

}
void input() {

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		char a, b;
		cin >> a >> b;
		int num1 = a - 'A';
		int num2 = b - 'A';

		if (1 > wonsanji_arr[num1]) { //�ָ�
			wonsanji_arr[num1] = 1;
		}
		if (2 > wonsanji_arr[num2]) { //������
			wonsanji_arr[num2] = 2;
		}


		v[num1].push_back(num2);
	}

	memset(answer, false, sizeof(answer));

	int tmp_num;
	cin >> tmp_num;

	for (int i = 0; i < tmp_num; i++) {
		char c;
		cin >> c;
		int tmp_num2 = c - 'A';

		v[tmp_num2].clear();
		catched[tmp_num2] = true;
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}