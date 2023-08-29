#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

int n; //세로
int m; //가로

char map[101][101];
bool visited[101][101];
bool can_melt[101][101];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ans = 0;
int times = 1;

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= m) {
		return true;
	}

	return false;
}
void bfs(int x, int y) {

	bool all_melted = true;
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

			if (inrange(nx, ny) && map[nx][ny] == '0' && !visited[nx][ny]) {
				visited[nx][ny] = true;
				q.push({ nx,ny });

				for (int j = 0; j < 4; j++) {
					int nx2 = nx + dx[j];
					int ny2 = ny + dy[j];

					if (inrange(nx2, ny2) && map[nx2][ny2] == '1') {
						can_melt[nx2][ny2] = true;
						all_melted = false;
					}
				}
			}
		}
	}

	if (all_melted) {
		cout << times << "\n";
		cout << ans;
		exit(0);
	}

	ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (can_melt[i][j]) {
				ans++;
				map[i][j] = '0';
			}
		}
	}
}
void all_cheese_melt() {
	//모든 치즈가 녹는다.

	memset(visited, false, sizeof(visited));
	memset(can_melt, false, sizeof(can_melt));

	bfs(1, 1);
}

void solution() {


	for (times = 0;; times++) {
		all_cheese_melt();
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