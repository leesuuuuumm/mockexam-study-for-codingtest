#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int n; //숲 크기
int map[501][501];
int dist[501][501];

int ans = 0;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

int dfs(int x, int y) {

	if (dist[x][y] != 0) {
		return dist[x][y];
	}

	//자기 자신 1
	dist[x][y] = 1;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (inrange(nx, ny) && map[nx][ny] < map[x][y]) {
			dist[x][y] = max(dist[x][y], dfs(nx, ny) + 1);
		}
	}

	return dist[x][y];

}
void solution() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dist[i][j] == 0) {
				dfs(i, j);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans = max(ans, dist[i][j]);
		}
	}
	cout << ans;
}
void input() {

	cin >> n;

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