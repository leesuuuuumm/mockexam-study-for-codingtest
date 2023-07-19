#include <iostream>
#include <cstring>

using namespace std;

int t;
int tc;
int n; //��
int x; //Ȱ�ַ� ����
int map[21][21];
bool whaljuro[21][21]; //Ȱ�ַ�

int ans = 0;

bool inrange(int m) {
	if (1 <= m && m <= n) {
		return true;
	}
	return false;
}
void solution() {

	memset(whaljuro, false, sizeof(whaljuro));
	ans = 0;
	//����
	for (int i = 1; i <= n; i++) {
		bool flag = true;
		for (int j = 1; j < n; j++) {
			//���̰� 1�̻� ���� ���ٸ�
			if (abs(map[i][j] - map[i][j + 1]) > 1) { 
				flag = false;
				break; 
			} //�������ٸ�
			else if (map[i][j] - map[i][j + 1] == -1) {
				int up_height = map[i][j + 1];
				for (int k = j; k >= j - x + 1; k--) {
					if (inrange(k) && map[i][k] == up_height - 1 && !whaljuro[i][k]) {
						whaljuro[i][k] = true;
					}
					else {
						flag = false;
						break;
					}
				}
			} //�������ٸ�
			else if (map[i][j] - map[i][j + 1] == 1) {
				int tmp_height = map[i][j];
				for (int k = j + 1; k <= j + x; k++) {
					if (inrange(k) && tmp_height == map[i][k] + 1 && !whaljuro[i][k]) {
						whaljuro[i][k] = true;
					}
					else {
						flag = false;
						break;
					}
				}
				j += x - 1;

			}	
		}
		if (flag) {
			ans++;
		}
	}
	memset(whaljuro, false, sizeof(whaljuro));

	//����
	for (int j = 1; j <= n; j++) {
		bool flag = true;
		for (int i = 1; i < n; i++) {
			//���̰� 1�̻� ���� ���ٸ�
			if (abs(map[i][j] - map[i + 1][j]) > 1) {
				flag = false;
				break;
			} //�������ٸ�
			else if (map[i][j] - map[i + 1][j] == -1) {
				int up_height = map[i + 1][j];
				for (int k = i; k >= i - x + 1; k--) {
					if (inrange(k)  && map[k][j] == up_height - 1 && !whaljuro[k][j]) {
						whaljuro[k][j] = true;
					}
					else {
						flag = false;
						break;
					}
				}
			} //�������ٸ�
			else if (map[i][j] - map[i + 1][j] == 1) {
				int tmp_height = map[i][j];
				for (int k = i + 1; k <= i + x; k++) {
					if (inrange(k) && tmp_height == map[k][j] + 1 && !whaljuro[k][j]) {
						whaljuro[k][j] = true;
					}
					else {
						flag = false;
						break;
					}
				}
				i += x - 1;
			}
		}

		if (flag) {
			ans++;
		}
	}
	cout << "#" << tc << " " <<  ans << "\n";

}

void input() {

	cin >> t;

	for (tc = 1; tc <= t; tc++) {
		cin >> n >> x;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
			}
		}
		solution();
	}

}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
}