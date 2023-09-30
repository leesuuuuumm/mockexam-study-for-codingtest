#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>


using namespace std;

int n; //���� ũ��
int m; //�ڸ��� ����Ǵ� �� ��
int k; //�������� Ȯ�� ����
int c; //�������� �����ִ� �� ��

int map[21][21];
//0: ��ĭ, -1: ��
int iskilled[21][21];
//�������� �ѷ����� ���� �� ��

int year = 1;

//�����¿�
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans = 0; //�ڸ��� ������ �׷� ��

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void trees_grow() {

	int plus_map[21][21] = { 0, };

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

			if (map[i][j] <= 0) {
				continue;
			}
			int cnt = 0;

			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny) && map[nx][ny] > 0 && !iskilled[i][j]) {
					cnt++;
				}
			}
			plus_map[i][j] += cnt; 
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += plus_map[i][j];
		}
	}
}

void trees_spread() {
	//��, �ٸ� ����, ������ ��� ���� ĭ�� ������ ����

	int plus_map[21][21] = { 0, };

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

			if (map[i][j] <= 0 || iskilled[i][j]) {
				continue;
			}

			int cnt = 0;

			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny) && map[nx][ny] == 0 && iskilled[nx][ny] == 0) {
					cnt++;
				}
			}

			if (cnt == 0) {
				continue;
			}

			int avg = map[i][j] / cnt;

			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny) && map[nx][ny] == 0 && iskilled[nx][ny] == 0) {
					plus_map[nx][ny] += avg;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += plus_map[i][j];
		}
	}
}

void killer_spread() {
	//�������� �Ѹ���.

	int killer_map[21][21] = { 0, };

	vector < pair<int, pair<int, int>>> v;

	//������ �Ѹ� ��ġ
	int max_x;
	int max_y;
	//���� ���� �Ѹ��� ������ ��
	int max_killer_cnt = 0;

	//�밢��
	int ddx[4] = { 1,1,-1,-1 };
	int ddy[4] = { 1,-1,1,-1 };

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

			//���� �Ѹ���
			if (map[i][j] == -1) {
				continue;
			}
			int cnt = 0;

			//������ ���� ĭ�� �������� �Ѹ���
			if (map[i][j] > 0) {
				cnt += map[i][j];
			}
			else {
				killer_map[i][j] = 0;
				v.push_back({ 0, {i,j} });
				continue;
			}

			for (int d = 0; d < 4; d++) {
				for (int t = 1; t <= k; t++) {

					int nx = i + ddx[d] * t;
					int ny = j + ddy[d] * t;

					if (inrange(nx, ny) && map[nx][ny] > 0) {
						cnt += map[nx][ny];
					}
					else {
						break;
					}
				}
			}

			max_killer_cnt = max(max_killer_cnt, cnt);
			v.push_back({ - 1 * cnt, {i,j} });
			killer_map[i][j] += cnt;
		}
	}

	sort(v.begin(), v.end());

	max_x = v[0].second.first;
	max_y = v[0].second.second;

	ans += max_killer_cnt;

	for (int d = 0; d < 4; d++) {
		for (int t = 1; t <= k; t++) {
			int nx = max_x + ddx[d] * t;
			int ny = max_y + ddy[d] * t;

			if (inrange(nx, ny)) {
				iskilled[nx][ny] = c + 1;

				//������ �ƿ� ���ų� ���� ������
				if (map[nx][ny] <= 0) {
					break;
				}

				map[nx][ny] = 0;
			}
			else {
				break;
			}
		}
	}

	//������ �Ѹ� ��ġ
	map[max_x][max_y] = 0;
	iskilled[max_x][max_y] = c + 1;

	//������ �Ѹ� ��ġ
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (iskilled[i][j] > 0) {
				iskilled[i][j]--;
			}
		}
	}
}
void one_year() {
	//1�⵿�� ������ ����� ����

	trees_grow();

	trees_spread();

	killer_spread();

}
void solution() {

	for (year = 1; year <= m; year++) {
		one_year();
	}
	cout << ans << "\n";


}
void input() {

	cin >> n >> m >> k >> c;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j]; 
		}
	}

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input(); 
	solution();
}