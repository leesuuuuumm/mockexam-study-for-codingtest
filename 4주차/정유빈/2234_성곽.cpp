#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

int n, m;
int map[51][51];
pair<int,int> connected[51][51];
int wall[51][51][4];
bool visited[51][51];

int second_answer = 0; //가장 넓은 방의 넓이
int third_answer = 0; //하나의 벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기

vector < pair<pair<int, int>, int>> break_wall_positions;
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };

bool inrange(int x, int y) {

	if (1 <= x && x <= m && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void bfs(int x, int y, int room_num) {

	vector<pair<int, int>> v;
	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	int tmp_second_answer = 0;

	while (!q.empty()) {

		int a = q.front().first;
		int b = q.front().second;
		v.push_back({ a,b });
		tmp_second_answer++;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && !wall[a][b][i]) {
				visited[nx][ny] = true;
				q.push({ nx,ny });
			}
		}
	}

	for (int i = 0; i < v.size(); i++) {
		connected[v[i].first][v[i].second] = {room_num, tmp_second_answer};
	}

	second_answer = max(second_answer, tmp_second_answer);
}

void get_first_second_answer() {
	//이 성에 있는 방의 개수 구하기

	int first_answer = 0;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {

			if (!visited[i][j]) {
				bfs(i, j, first_answer);
				first_answer++;
			}
		}
	}
	cout << first_answer << "\n";
	cout << second_answer << "\n";
}

void get_third_answer() {
	//하나의 벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {

			if (wall[i][j][0] && inrange(i, j - 1) && connected[i][j].first != connected[i][j - 1].first) { //서쪽
				int tmp_answer = connected[i][j].second + connected[i][j - 1].second;
				third_answer = max(third_answer, tmp_answer);
			}
			if (wall[i][j][1] && inrange(i - 1, j) && connected[i][j].first != connected[i - 1][j].first) { //북쪽
				int tmp_answer = connected[i][j].second + connected[i - 1][j].second;
				third_answer = max(third_answer, tmp_answer);
			}
			if (wall[i][j][2] && inrange(i,j + 1) && connected[i][j].first != connected[i][j + 1].first) { //동쪽
				int tmp_answer = connected[i][j].second + connected[i][j + 1].second;
				third_answer = max(third_answer, tmp_answer);
			}
			if (wall[i][j][3] && inrange(i + 1, j) && connected[i][j].first != connected[i + 1][j].first) { //남쪽
				int tmp_answer = connected[i][j].second + connected[i + 1][j].second;
				third_answer = max(third_answer, tmp_answer);
			}
		}
	}

	cout << third_answer << "\n";
}
void solution() {

	get_first_second_answer();
	get_third_answer();
	
}

void get_wall(int x, int y, int num) {

	for (int i = 3; i >= 0; i--) {

		if (num == 0) {
			break;
		}

		if (num >= pow(2, i)) {
			num -= pow(2, i);
			wall[x][y][i] = true;
			break_wall_positions.push_back({ {x,y}, i });
		}
	}
}
void input() {

	cin >> n >> m;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			get_wall(i, j, map[i][j]);
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