#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

int n; //열 크기
int m; //행 크기
int map[51][51];
bool wall[51][51][4];
bool visited[51][51];
pair<int, int> map_info[51][51];
vector<pair<int, int>> v;
int global_room_num = 0;


int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };

int ans[3];

bool inrange(int x, int y) {

	if (1 <= x && x <= m && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void make_wall(int x, int y, int num) {
	//(x,y)에 num 벽을 세운다.

	for (int i = 3; i >= 0; i--) {

		if (num >= pow(2, i)) {
			wall[x][y][i] = true;
			num -= pow(2, i);
		}
	}
}

void bfs(int x, int y) {

	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	v.clear();

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;
		v.push_back({ a,b });

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !wall[a][b][i] && !visited[nx][ny]) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
			}
		}
	}

	int vnum = v.size(); //방의 개수
	ans[1] = max(ans[1], vnum); //가장 큰 방의 넓이 갱신

	for (int i = 0; i < v.size(); i++) {
		int vx = v[i].first;
		int vy = v[i].second;

		map_info[vx][vy] = { global_room_num , vnum };
	}
}
void room_num() {
	//이 성에 있는 방의 개수

	memset(visited, false, sizeof(visited));

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j]) {
	//			cout << "i: " << i << " j: " << j << "\n";
				global_room_num++;
				bfs(i, j);
			}
		}
	}

	ans[0] = global_room_num;
}

void third_ans() {
	//하나의 벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				//벽이 있으면서
				if (inrange(nx, ny) && wall[i][j][k] && map_info[i][j].first != map_info[nx][ny].first) {
					ans[2] = max(ans[2], map_info[i][j].second + map_info[nx][ny].second);
				}
			}
		}
	}


}
void solution() {

	memset(wall, false, sizeof(wall));

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			int num = map[i][j];
			make_wall(i, j, num);
		}
	}

	room_num();
	third_ans();

	cout << ans[0] << "\n" << ans[1] << "\n" << ans[2] << "\n";
}
void input() {

	cin >> n >> m;

	for (int i = 1; i <= m; i++) {
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