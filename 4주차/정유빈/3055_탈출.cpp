#include <iostream>
#include <queue>

using namespace std;

int r;
int c;

int gosum_x; //S로 표시
int gosum_y;

int biber_x; //D로 표시
int biber_y;

char map[51][51];
int water_time[51][51];
bool visited[51][51];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans = 9999999;


bool inrange(int x, int y) {

	if (1 <= x && x <= r && 1 <= y && y <= c) {
		return true;
	}
	return false;
}

void water_bfs(int x, int y) {

	queue<pair<pair<int, int>, int>> q;
	q.push({ {x,y}, 0 });
	water_time[x][y] = 0;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int t = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && water_time[nx][ny] > t + 1 && map[nx][ny] != 'X' && map[nx][ny] != 'D') {
				water_time[nx][ny] = t + 1;
				q.push({ {nx,ny}, t + 1 });
			}
		}
	}
}
void water_spread() {

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			water_time[i][j] = 9999999;
		}
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (map[i][j] == '*') {
				water_bfs(i, j);
			}
		}
	}

}

void gosum_bfs() {

	queue<pair<pair<int, int>, int>> q;
	q.push({ {gosum_x, gosum_y}, 0 });
	visited[gosum_x][gosum_y] = true;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int t = q.front().second;


		if (map[a][b] == 'D') { //비버소굴로 도착했다면
			ans = min(ans, t);
		}

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] != 'X' && t + 1 < water_time[nx][ny]) {
				visited[nx][ny] = true;
				q.push({ {nx,ny}, t + 1 });
			}
		}
	}

}
void gosum_run() {

	memset(visited, false, sizeof(visited));
	gosum_bfs();
	
}
//고슴도치는 비버의 굴로 빨리 도망가 홍수를 피하려고 한다.
void solution() {

	water_spread();
	gosum_run();

	if (ans == 9999999) {
		cout << "KAKTUS";
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
			if (map[i][j] == 'S') {
				gosum_x = i;
				gosum_y = j; 
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