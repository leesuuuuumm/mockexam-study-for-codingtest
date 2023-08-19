#include <iostream>
#include <queue>

using namespace std;

int n; //행
int m; //열
int k;

char map[1001][1001];
//0: 이동할 수 있는 곳
//1: 벽

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int dist_map[1001][1001][11];
//0 : 안 부실 때 거리
//1: 부실 때 거리

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= m) {
		return true;
	}
	return false;
}


void bfs() {

	queue < pair<pair<int, int>, pair<int, int>>> q;

	dist_map[1][1][0] = 0;
	q.push({ {1,1}, {0,0} });

	while (!q.empty()) {

		int x = q.front().first.first;
		int y = q.front().first.second;

		int dist = q.front().second.first;
		int break_cnt = q.front().second.second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inrange(nx, ny)) {

				//만약 다음으로 이동할 수 있고
				if (map[nx][ny] == '0') {
					if (dist + 1 < dist_map[nx][ny][break_cnt]) {
						dist_map[nx][ny][break_cnt] = dist + 1;
						q.push({ {nx,ny}, {dist + 1, break_cnt} });
					}
				} //만약 벽이고, 깨야할 때
				else if (map[nx][ny] == '1') {
					if (break_cnt + 1 <= k && dist + 1 < dist_map[nx][ny][break_cnt + 1]) {
						dist_map[nx][ny][break_cnt + 1] = dist + 1;
						q.push({ {nx,ny}, {dist + 1, break_cnt + 1} });
					}
				}
			}
		}
	}
}
void solution() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k <= 10; k++) {
				dist_map[i][j][k] = 99999999;
			}
		}
	}

	bfs();

	int ans = 99999999;

	for (int i = 0; i <= 10; i++) {
		ans = min(ans, dist_map[n][m][i]);
	}

	if (ans == 99999999) {
		cout << -1;
	}
	else {
		cout << ans + 1;
	}
}

void input() {

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		string st;
		cin >> st;

		for (int j = 1; j <= m; j++) {
			map[i][j] = st[j - 1];
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
