#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n; //공간 크기
int m; //물고기 개수
int map[21][21];
bool visited[21][21];

int baby_shark_size = 2; 
int eating_fish_cnt = 0;

int baby_shark_x; //아기 상어 행
int baby_shark_y; //아기 상어 열

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ans = 0;

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
bool find_eating_fish() {
	//먹을 물고기를 찾는다.

	memset(visited, false, sizeof(visited));
	//먹을 수 있는 물고기 거리와 위치
	vector < pair<int, pair<int, int>>> v;

	//위치와 거리
	queue<pair<pair<int, int>, int>> q;

	q.push({ {baby_shark_x, baby_shark_y}, 0 });
	visited[baby_shark_x][baby_shark_y] = true;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			//자신의 크기보다 같거나 작으면
			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] <= baby_shark_size) {
				q.push({ {nx,ny}, d + 1 });
				visited[nx][ny] = true;

				//먹을 수 있는 물고기면
				if (map[nx][ny] < baby_shark_size && map[nx][ny] != 0) {
					v.push_back({ d + 1, {nx,ny} });
				}
			}
		}
	}


	if (v.size() == 0) {
		return false;
	}

	sort(v.begin(), v.end());

	ans += v[0].first;

	//원래 아기상어 위치는 0으로 
	map[baby_shark_x][baby_shark_y] = 0;

	//미래 아기상어 위치는 9로
	map[v[0].second.first][v[0].second.second] = 9;

	baby_shark_x = v[0].second.first;
	baby_shark_y = v[0].second.second;

	//먹은 물고기 개수 1 증가
	eating_fish_cnt++;


	//자신의 크기와 같은 수의 물고기를 먹을 때마다 크기 1 증가
	if (eating_fish_cnt == baby_shark_size) {
		baby_shark_size++;
		eating_fish_cnt = 0;
	}

	return true;
}
void solution() {
	
	for (int times = 0;; times++) {
		bool eating = find_eating_fish();

		//못 먹었으면
		if (!eating) {
			cout <<  ans;
			exit(0);
		}
	}
	

}
void input() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];

			if (map[i][j] == 9) {
				baby_shark_x = i;
				baby_shark_y = j;
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