#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <queue>

using namespace std;

int n, q;
int map[150][150];
bool can_melt[150][150];
bool visited[150][150];

vector<int> stages;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int second_ans = 0;

bool inrange(int x, int y) {

	if (0 <= x && x < n && 0 <= y && y < n) {
		return true;
	}
	return false;
}
void mini_rotate(int x, int y, int num) {

	int tmp_map[151][151];

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			tmp_map[i][j] = map[x + num - 1 - j][y + i];
		}
	}

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			map[x + i][y + j] = tmp_map[i][j];
		}
	}
}
void rotate(int num) {

	//num개씩 잘라서 회전한다.

	num = pow(2, num);

	//2개씩 잘라서 회전한다고 가정
	
	for (int i = 0; i < n; i += num) {
		for (int j = 0; j < n; j += num) {
			mini_rotate(i, j, num);
		}
	}

	
}

void print() {
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}

void melt() {
	//얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다

	memset(can_melt, false, sizeof(can_melt));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if (map[i][j] == 0) {
				continue;
			}
			int cnt = 0;

			for (int k = 0; k < 4; k++) {

				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny) && map[nx][ny] > 0) {
					cnt++;
				}
			}

			if (cnt < 3) {
				can_melt[i][j] = true;
			}

		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (can_melt[i][j]) { //녹을 수 있으면
				map[i][j] -= 1;
			}
		}
	}
}

void dfs(int x, int y) {

	queue<pair<int, int>> q;

	q.push({ x,y });
	visited[x][y] = true;

	int tmp_ans = 0;

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;

		tmp_ans++;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && map[nx][ny] > 0 && !visited[nx][ny]) {
				q.push({ nx,ny });
				visited[nx][ny] = true; 
			}
		}
	}

	second_ans = max(second_ans, tmp_ans);

}
void output() {

	int first_ans = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			first_ans += map[i][j];
		}
	}

	cout <<  first_ans << "\n";

	memset(visited, false, sizeof(visited));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] > 0  && !visited[i][j]) {
				dfs(i, j);
			}
		}
	}

	cout <<  second_ans << "\n";
}
void solution() {

	for (int i = 0; i < q; i++) {

		rotate(stages[i]);
		melt();
	}

}
void input() {

	cin >> n >> q;

	n = pow(2, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < q; i++) {
		int num;
		cin >> num;
		stages.push_back(num);
	}
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
	output();
}