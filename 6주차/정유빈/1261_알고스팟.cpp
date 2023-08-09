#include <iostream>
#include <queue>


using namespace std;

int m; //가로 크기
int n; //세로 크기
char map[101][101];
//0: 빈방, 1: 벽

int breaks[101][101];
//몇번만에 깨고 도착하는지
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (0 <= x && x < n && 0 <= y && y < m) {
		return true;
	}
	return false;
}
void solution() {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			breaks[i][j] = 9999999;
		}
	}
	queue<pair<pair<int, int>, int>> q;
	q.push({ {0,0}, 0 });

	breaks[0][0] = 0;

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int break_cnt = q.front().second;
		
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inrange(nx, ny)) {

				//빈방이고,
				if (map[nx][ny] == '0' && breaks[nx][ny] > break_cnt) {
					breaks[nx][ny] = break_cnt;
					q.push({ {nx,ny}, break_cnt});
				} //벽이고 깨야 할 때,
				else if (map[nx][ny] == '1' && breaks[nx][ny] > break_cnt + 1) {
					breaks[nx][ny] = break_cnt + 1;
					q.push({ {nx,ny}, break_cnt + 1 });
				}
			}
		}
	}

	cout << breaks[n - 1][m - 1];
}

void input() {

	cin >> m >> n;

	for (int i = 0; i < n; i++) {
		string st;
		cin >> st;
		for (int j = 0; j < m; j++) {
			map[i][j] = st[j];
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