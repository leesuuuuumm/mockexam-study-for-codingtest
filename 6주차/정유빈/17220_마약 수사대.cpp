#include <iostream>
#include <vector>
#include <cstring>

int n; //마약 공급책 수
int m; //마약 공급책 관계 수

using namespace std;

vector<int> v[30];


//검거된 마약책들
bool catched[30];
int wonsanji; //원산지
int wonsanji_arr[30];
//안 받았으면 0, 준 적이 있으면 1, 받은 적 했으면 2

int answer[30]; //답
int real_ans = 0;

void dfs(int start) {
	//c가 시작해서 간다.

	answer[start] = true; 

	for (int i = 0; i < v[start].size(); i++) {
		int next = v[start][i]; 

		if (!catched[next]) {
			dfs(next);
		}
	}
}
void solution() {
	
	int minus_wonsanji = 0; //원산지 개수

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

		if (1 > wonsanji_arr[num1]) { //주면
			wonsanji_arr[num1] = 1;
		}
		if (2 > wonsanji_arr[num2]) { //받으면
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