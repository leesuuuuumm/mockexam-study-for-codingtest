#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int r, c;
char map[1001][1001];
int fire_dist[1001][1001];
int jihun_dist[1001][1001];
bool visited[1001][1001];

int jihun_x;
int jihun_y;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ans = 99999999;

bool inrange(int x, int y) {

	if (1 <= x && x <= r && 1 <= y && y <= c) {
		return true;
	}
	return false;
}

void fire_bfs(int x, int y) {

	queue<pair<pair<int, int>, int>> q;
	q.push({ {x,y}, 0 });
	fire_dist[x][y] = 0;

	while (!q.empty()) {
		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];
			
			if (inrange(nx, ny) && fire_dist[nx][ny] > d + 1 && map[nx][ny] != '#') {
				q.push({ {nx,ny}, d + 1 });
				fire_dist[nx][ny] = d + 1;
			}
		}
	}

}
void fire_spread() {

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			fire_dist[i][j] = 999999999;
		}
	}
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (map[i][j] == 'F') {
				fire_bfs(i, j);
			}
		}
	}
}

bool gajangjari(int x, int y) {

	if (x == 1 || x == r || y == 1 || y == c) {
		return true;
	}
	return false;
}
void jihun_bfs() {

	queue<pair<pair<int, int>, int>> q;
	q.push({ {jihun_x, jihun_y}, 0 });
	jihun_dist[jihun_x][jihun_y] = 0;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		if (gajangjari(a, b)) { //가장자리라면
			ans = min(ans, d + 1);
		}

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && jihun_dist[nx][ny] > d + 1 && map[nx][ny] != '#' && fire_dist[nx][ny] > d + 1) {
				jihun_dist[nx][ny] = d + 1;
				q.push({ {nx,ny}, d + 1 });
			}
		}
	}
}
void jihun_run() {


	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			jihun_dist[i][j] = 999999999;
		}
	}

	jihun_bfs();
}
void solution() {

	fire_spread();
	jihun_run();

	if (ans == 99999999) {
		cout << "IMPOSSIBLE";
	}
	else {
		cout << ans;
	}
}

void input() {

	cin >> r >> c;

	for (int i = 1; i <= r; i++) {
		string st;
		cin >> st;
		for (int j = 1; j <= c; j++) {
			map[i][j] = st[j - 1];

			if (map[i][j] == 'J') {
				jihun_x = i;
				jihun_y = j;
			}
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
