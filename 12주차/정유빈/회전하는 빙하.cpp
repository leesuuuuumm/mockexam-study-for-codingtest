#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int n; //회전 가능 레벨
int q; //회전 횟수

int map[70][70];
bool can_melt[70][70];
bool visited[70][70];

vector<int> rotate_level; //회전 레벨

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans1 = 0;
int ans2 = 0; 

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void mini_rotate(int x, int y, int num) {

	int tmp_map[70][70];

	for (int i = x; i < x + num; i++) {
		for (int j = y; j < y + num; j++) {
			tmp_map[i][j] = map[i][j];
		}
	}

	//4구역 처음 시작 점
	int mid_num = num / 2; 
	int mid_x = x + mid_num; 
	int mid_y = y + mid_num; 
	
	//1구역
	for (int i = x; i < mid_x; i++) {
		for (int j = y; j < mid_y; j++) {
			map[i][j] = tmp_map[i + mid_num][j];
		}
	}

	//2구역
	for (int i = x; i < mid_x; i++) {
		for (int j = mid_y; j < y + num; j++) {
			map[i][j] = tmp_map[i][j - mid_num];
		}
	}

	//3구역
	for (int i = mid_x; i < x + num; i++) {
		for (int j = y; j < y + num; j++) {
			map[i][j] = tmp_map[i][j + mid_num];
		}
	}

	//4구역
	for (int i = mid_x; i < x+ num; i++) {
		for (int j = mid_y; j < y + num; j++) {
			map[i][j] = tmp_map[i - mid_num][j];
		}
	}
}
void rotate(int level) {
	//level이 1이면 2만큼 회전

	int num = pow(2, level);
	for (int i = 1; i <= n; i += num) {
		for (int j = 1; j <= n; j += num) {
			mini_rotate(i, j, num);
		}
	}
}



void bfs(int x, int y) {

	int tmp_ans = 0;
	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;
		tmp_ans++;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] > 0) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
			}
		}
	}

	ans2 = max(ans2, tmp_ans);
}
void ice_melt() {

	memset(can_melt, false, sizeof(can_melt));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

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

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (can_melt[i][j]) {
				map[i][j] --;
			}
		}
	}
}
void solution() {

	for (int i = 0; i < q; i++) {
		int level = rotate_level[i];
		rotate(level);
		ice_melt();

	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans1 += map[i][j];
		}
	}

	memset(visited, false, sizeof(visited));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j] && map[i][j] > 0) {
				bfs(i, j);
			}
		}
		
	}

	cout << ans1 << "\n" << ans2 << "\n";

}
void input() {

	cin >> n >> q;

	n = pow(2, n);
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < q; i++) {
		int num;
		cin >> num;
		rotate_level.push_back(num);
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}