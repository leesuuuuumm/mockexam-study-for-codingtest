#include <iostream>
#include <queue>
#include <cstring>
#include <tuple>
#include<algorithm>


using namespace std;

int t; //테스트 케이스 개수
int tc = 1;
int n; //한 변 길이
int map[9][9]; 
bool visited[9][9];
int max_height = 0;
int k; //자를 수 있는 높이
int ans = 0;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}


void start_dfs(int x, int y, bool cut, int cnt, int height) {

	ans = max(ans, cnt);
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (inrange(nx, ny) && !visited[nx][ny]) {

			//만약 깍지 않았는데 더 내려간다면
			if (!cut && height > map[nx][ny]) {
				visited[nx][ny] = true;
				start_dfs(nx, ny, false, cnt + 1, map[nx][ny]);
				visited[nx][ny] = false;
			} //만약 깍지 않았는데 깍은게 더 작다면
			else if (!cut && map[x][y] > map[nx][ny] - k) {

				visited[nx][ny] = true;
				start_dfs(nx, ny, true, cnt + 1, map[x][y] - 1);
				visited[nx][ny] = false;
			}
			else if (cut && height > map[nx][ny]) {
				visited[nx][ny] = true;
				start_dfs(nx, ny, true, cnt + 1, map[nx][ny]);
				visited[nx][ny] = false;
			}
		}
	}
}
void solution() {

	memset(visited, false, sizeof(visited));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == max_height) {
				visited[i][j] = true;
				start_dfs(i, j, false, 1, map[i][j]);
				visited[i][j] = false;
			}
		}
	}
	
	cout << "#" << tc << " " << ans << "\n";

}

void input() {

	cin >> t;

	for (tc = 1; tc <= t; tc++) {
		cin >> n >> k;
		max_height = 0;
		ans = 0;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
				max_height = max(max_height, map[i][j]);
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