#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int n;
int m;
int t;

deque<int> dq[51];

void erase() {

	vector<pair<int, int>> erase_list; //���� �͵�
	
	//������ ����.
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m - 1; j++) {
			if (dq[i][j] == dq[i][j + 1] && dq[i][j] != -1) {
				erase_list.push_back({ i,j });
				erase_list.push_back({ i,j + 1 });
			}
		}

		if (dq[i][0] == dq[i][m - 1] && dq[i][0] != -1) {
			erase_list.push_back({ i,0 });
			erase_list.push_back({ i, m - 1 });
		}
	}

	//�� �Ʒ��� ����.
	for (int j = 0; j < m; j++) {
		for (int i = 1; i < n; i++) {
			if (dq[i][j] == dq[i + 1][j] && dq[i][j] != -1) {
				erase_list.push_back({ i,j });
				erase_list.push_back({ i + 1, j });
			}
		}
	}

	for (int i = 0; i < erase_list.size(); i++) {
		int x = erase_list[i].first;
		int y = erase_list[i].second;

		dq[x][y] = -1;
	}

	if (erase_list.size() == 0) {
		//���� ���� �� ���ٸ�

		double sum = 0;
		double average = 0;
		double cnt = 0;

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < m; j++) {
				if (dq[i][j] != -1) {
					sum += dq[i][j];
					cnt++;
				}
			}
		}

		average = sum / cnt;

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < m; j++) {
				if (dq[i][j] != -1) {

					if (dq[i][j] > average) {
						dq[i][j] -= 1;
					}
					else if (dq[i][j] < average) {
						dq[i][j] += 1;
					}
				}
			}
		}

	}

}
void rotate(int xi, int di, int ki) {
	//xi�� ����� ������ di �������� kiĭ ȸ����Ų��.

	if (di == 0) { //�ð���� 

		for (int i = xi; i <= n; i += xi) {
			for (int j = 0; j < ki; j++) {
				int back = dq[i].back();
				dq[i].pop_back();
				dq[i].push_front(back);
			}
		}

	}
	else { //�ݽð����

		for (int i = xi; i <= n; i += xi) {
			for (int j = 0; j < ki; j++) {
				int front = dq[i].front();
				dq[i].pop_front();
				dq[i].push_back(front);
			}
		}
	}
}

void output() {

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			if (dq[i][j] != -1) {
				ans += dq[i][j];
			}
		}
	}

	cout << ans;
}

void input() {

	cin >> n >> m >> t;

	for (int i = 1; i <= n; i++) {
		
		for (int j = 1; j <= m; j++) {
			int num;
			cin >> num;
			dq[i].push_back(num);
		}
	}

	for (int i = 0; i < t; i++) {
		int xi, di, ki;
		cin >> xi >> di >> ki;

		rotate(xi, di, ki);
		erase();
	}

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	output();
}