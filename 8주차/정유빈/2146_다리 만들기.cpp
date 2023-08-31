#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int n;
int map[101][101];
int land_map[101][101];
int land_dist[101][101];
bool visited[101][101];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans = 9999999;

int land_num = 1;
bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void check_land_bfs(int x, int y) {

	queue<pair<int, int>> q;

	q.push({ x,y });
	visited[x][y] = true;

	while (!q.empty()) {

		int a = q.front().first;
		int b = q.front().second;
		land_map[a][b] = land_num;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[a][b] == map[nx][ny]) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
			}
		}
	}

	land_num += 1;
}

void check_land_num() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j] && map[i][j] != 0) {
				check_land_bfs(i, j);
			}
		}
	}
}

void check_land_dist(int x, int y) {

	memset(visited, false, sizeof(visited));


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			land_dist[i][j] = 9999999;
		}
	}

	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;
	land_dist[x][y] = 0;

	while (!q.empty()) {

		int a = q.front().first;
		int b = q.front().second;
		int d = land_dist[a][b]; //거리

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny]) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
				land_dist[nx][ny] = d + 1;

				//다른 대륙이면
				if (land_map[nx][ny] != land_map[x][y] && land_map[nx][ny]) {
					ans = min(ans, d);
				}
			}
		}
	}

}

void check_land_dist() {
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] != 0) {
				check_land_dist(i, j);
			}
		}
	}
	

	
}

void solution() {

	check_land_num();
	check_land_dist();

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