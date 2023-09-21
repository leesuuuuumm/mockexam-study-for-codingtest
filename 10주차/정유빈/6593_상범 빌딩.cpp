#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

int l; //상범 빌딩의 층 수
int r, c; //행과 열의 개수
char map[31][31][31];
int dist[31][31][31];
bool visited[31][31][31];

int start_x, start_y, start_z;
int end_x, end_y, end_z;

int dx[6] = { 1,-1,0,0,0,0 };
int dy[6] = { 0,0,1,-1,0,0 };
int dz[6] = { 0,0,0,0,1,-1 };
int times = 0;

bool inrange(int x, int y, int z) {

	if (1 <= x && x <= l && 1 <= y && y <= r && 1 <= z && z <= c) {
		return true;
	}
	return false;
}
void solution() {

	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= r; j++) {
			for (int k = 1; k <= c; k++) {
				dist[i][j][k] = 999999;
			}
		}
	}

	memset(visited, false, sizeof(visited));

	queue<tuple<int, int, int>> q;
	q.push({ start_x, start_y, start_z });
	dist[start_x][start_y][start_z] = 0;
	visited[start_x][start_y][start_z] = true;

	while (!q.empty()) {
		int a = get<0>(q.front());
		int b = get<1>(q.front());
		int c = get<2>(q.front());
		int d = dist[a][b][c];

		q.pop();

		if (a == end_x && b == end_y && c == end_z) {
			cout << "Escaped in " << d << " minute(s)." << "\n";
			return;
		}

		for (int i = 0; i < 6; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];
			int nz = c + dz[i];

			if (inrange(nx, ny, nz) && !visited[nx][ny][nz] &&
				map[nx][ny][nz] != '#' && dist[nx][ny][nz] > d + 1) {
				q.push({ nx,ny,nz });
				dist[nx][ny][nz] = d + 1;
				visited[nx][ny][nz] = true;
			}
		}
	}

	cout << "Trapped!" << "\n";

}
void input() {

	for (int tc = 1; tc <= 10; tc++) {
		cin >> l >> r >> c;

		if (l == 0 && r == 0 && c == 0) {
			break;
		}

		for (int i = 1; i <= l; i++) {
			for (int j = 1; j <= r; j++) {

				string st;
				cin >> st;

				for (int k = 1; k <= c; k++) {
					map[i][j][k] = st[k - 1];

					if (map[i][j][k] == 'S') {
						start_x = i;
						start_y = j;
						start_z = k;
					}
					else if (map[i][j][k] == 'E') {
						end_x = i;
						end_y = j;
						end_z = k;
					}
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