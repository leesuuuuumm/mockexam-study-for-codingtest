#include <iostream>
#include <cstring>

using namespace std;

int n;
int m;
char map[51][51];
bool visited[51][51];
bool cycle = false;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= m) {
		return true;
	}
	return false;
}
void dfs(int x, int y, int start_x, int start_y, int cnt) {

	//만약 거리가 1이라면
	if (inrange(x, y) && (abs(x - start_x) + abs(y - start_y) == 1) && cnt >= 4) {
		cycle = true;
	//	cout << "x: " << x << " y: " << y << " start_x: " << start_x << " start_y: " << start_y << " cnt: " << cnt << "\n";
		cout << "Yes";
		exit(0);
	}
	visited[x][y] = true;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		//동서남북에 같은 알파벳이 있으면
		if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] == map[x][y]) {
			dfs(nx, ny, start_x, start_y, cnt + 1);
		}
	}

	visited[x][y] = false;
}

void solution() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			memset(visited, false, sizeof(visited));
			dfs(i, j, i, j, 1);
		}
	}

	cout << "No";
}
void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		string st;
		cin >> st;

		for (int j = 0; j < m; j++) {
			map[i][j + 1] = st[j];
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