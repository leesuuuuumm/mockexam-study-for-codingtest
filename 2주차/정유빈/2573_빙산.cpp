#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int n;
int m;
int map[301][301];
bool visited[301][301];

int times;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= m) {
		return true;
	}
	return false;
}
void all_ice_melt() {

	int melting[301][301];
	memset(melting, 0, sizeof(melting));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] > 0) {
				int cnt = 0;
				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];

					if (inrange(nx, ny) && map[nx][ny] == 0) {
						cnt++;
					}
				}
				melting[i][j] -= cnt;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			map[i][j] += melting[i][j];
			if (map[i][j] < 0) {
				map[i][j] = 0;
			}
		}
	}
}

void bfs(int x, int y) {

	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;
		
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] > 0) {
				visited[nx][ny] = true;
				q.push({ nx,ny });
			}
		}
	}
}
void split_check() {

	int split_cnt = 0;
	bool all_melt = true; //다 녹았는지 체크
	memset(visited, false, sizeof(visited));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] > 0 && !visited[i][j]) {
				bfs(i, j);
				split_cnt++;
				all_melt = false;
			}
		}
	}


	if (split_cnt >= 2) { //2개로 분리되었다면
		cout << times;
		exit(0);
	}

	if (all_melt) { //다 녹았다면
		cout << 0;
		exit(0);
	}
}
void solution() {

	for (times = 1;; times++) {
		all_ice_melt();
		split_check();
	}
	

}

void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
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