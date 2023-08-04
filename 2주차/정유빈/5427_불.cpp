#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int t;
int w; //너비
int h; //높이;

char map[1002][1002];
int fire_dist[1002][1002];
int sanggun_pos[1002][1002];
bool visited[1002][1002];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

//상근
int sanggun_x;
int sanggun_y;

queue<pair<int, int>> fire_q;

bool inrange(int x, int y) {

	if (1 <= x && x <= h && 1 <= y && y <= w) {
		return true;
	}
	return false;
}
void fire_bfs() {

	while (!fire_q.empty()) {
		int a = fire_q.front().first;
		int b = fire_q.front().second;
		int d = fire_dist[a][b];

		fire_q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && fire_dist[nx][ny] > d + 1 && map[nx][ny] != '#') {
				fire_q.push({ nx,ny });
				fire_dist[nx][ny] = d + 1;
			}
		}
	}
}
void fire_spread() {

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			fire_dist[i][j] = 99999999;
		}
	}

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (map[i][j] == '*') {
				fire_q.push({ i,j });
				fire_dist[i][j] = 0;
			}
		}
	}

	fire_bfs();
}

void sanngun_bfs(int x, int y) {

	queue<pair<pair<int, int>, int>> q;
	q.push({ {x,y}, 0 });
	visited[x][y] = true;
	sanggun_pos[sanggun_x][sanggun_y] = 0;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] != '#' && fire_dist[nx][ny] > d + 1) {
				q.push({ {nx,ny}, d + 1 });
				sanggun_pos[nx][ny] = d + 1;
				visited[nx][ny] = true;
			}
		}
	}
}
void sanggun_run() {

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			sanggun_pos[i][j] = 999999999;
		}
	}

	memset(visited, false, sizeof(visited));
	sanngun_bfs(sanggun_x, sanggun_y);

}
void solution() {

	fire_spread();
	sanggun_run();

	int ans = 999999999;

	//위
	for (int j = 1; j <= w; j++) {
		if (sanggun_pos[1][j] != 999999999) {
			ans = min(ans, sanggun_pos[1][j] + 1);
		}
	}

	//아래
	for (int j = 1; j <= w; j++) {
		if (sanggun_pos[h][j] != 999999999) {
			ans = min(ans, sanggun_pos[h][j] + 1);
		}
	}

	//왼쪽
	for (int i = 1; i <= h; i++) {
		if (sanggun_pos[i][1] != 999999999) {
			ans = min(ans, sanggun_pos[i][1] + 1);
		}
	}

	//오른쪽
	for (int i = 1; i <= h; i++) {
		if (sanggun_pos[i][w] != 999999999) {
			ans = min(ans, sanggun_pos[i][w] + 1);
		}
	}

	if (ans == 999999999) {
		cout << "IMPOSSIBLE" << "\n";
	}
	else {
		cout << ans << "\n";
	}


}

void input() {

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> w >> h;

		for (int i = 0; i < h; i++) {
			string st;
			cin >> st;
			for (int j = 0; j < w; j++) {
				map[i + 1][j + 1] = st[j];
				if (map[i + 1][j + 1] == '@') {
					sanggun_x = i + 1;
					sanggun_y = j + 1;
				}
			}
		}
		solution();

	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
}