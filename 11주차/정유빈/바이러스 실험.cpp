#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int n; //���� ũ��
int m; //���̷��� ����
int k; //����Ŭ ��

int plus_nutrient[11][11]; //�߰��Ǵ� ��� ��
int nutrient[11][11];
vector<int> virus[11][11];

int cycle = 1;

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void one_stage() {
	//1. ������ ���̷����� ������ ���� ĭ�� �ִ� ����� �����Ѵ�.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			sort(virus[i][j].begin(), virus[i][j].end());

			//���� ���̷����� �����Ѵٸ�
			if (virus[i][j].size() > 0) {
				for (int k = 0; k < virus[i][j].size(); k++) {
					int virus_age = virus[i][j][k];

					if (virus_age <= nutrient[i][j]) {
						nutrient[i][j] -= virus_age;
						virus[i][j][k] ++; //����� ������ ���̷����� ���̰� 1 �����Ѵ�.
					}
					else {
						virus[i][j][k] *= -1;
					}
				}
			}

		}
	}
}

void two_stage() {
	//��� ���̷����� ���븦 ���� �� ���� ���̷����� ������� ���Ѵ�.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (virus[i][j].size() > 0) {

				int size = virus[i][j].size();
				for (int k = size - 1; k >= 0; k--) {
					
					if (virus[i][j][k] < 0) {
						int plus = -1 * virus[i][j][k] / 2;
						nutrient[i][j] += plus;
						virus[i][j].pop_back();
					}
					else {
						break; 
					}
				}
			}
		}
	}
}

void three_stage() {
	//���̷����� ������ �����Ѵ�.

//	cout << "����" << "\n";
	vector<int> plus_virus[11][11];

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < virus[i][j].size(); k++) {
				if (virus[i][j][k] % 5 == 0) {
					//5�� ����� ���̸� ���� ���̷������
				//	cout << "i: " << i << " j: " << j << "\n";
					for (int t = 0; t < 8; t++) {
						int nx = i + dx[t];
						int ny = j + dy[t];

						if (inrange(nx, ny)) {
				//			cout << "nx: " << nx << " ny: " << ny << "\n";
							plus_virus[nx][ny].push_back(1);
						}
					}
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < plus_virus[i][j].size(); k++) {
				virus[i][j].push_back(plus_virus[i][j][k]);
			}
		}
	}
}

void four_stage() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			nutrient[i][j] += plus_nutrient[i][j];
		}
	}
}
void one_cycle() {

	one_stage();
	two_stage();
	three_stage();
	four_stage();
}
void solution() {


	for (cycle = 1; cycle <= k; cycle++) {
		one_cycle();
	}

	int ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += virus[i][j].size();
		}
	}

	cout << ans;
}
void input() {

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> plus_nutrient[i][j];
			nutrient[i][j] = 5; 
		}
	}

	for (int i = 0; i < m; i++) {
		int r, c, age;
		cin >> r >> c >> age;
		virus[r][c].push_back(age);
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}