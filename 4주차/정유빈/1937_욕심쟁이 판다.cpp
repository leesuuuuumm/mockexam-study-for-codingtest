#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int n; //대나무 숲의 크기
int map[501][501];
bool visited[501][501];
int dp[501][501];
int ans = 0;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
int dfs(int x, int y) {

	if (dp[x][y] != 0) {
		return dp[x][y];
	}

	dp[x][y] = 1;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (inrange(nx, ny) && map[x][y] < map[nx][ny]) {
			dp[x][y] = max(dp[x][y], dfs(nx, ny) + 1);
		}
	}

	return dp[x][y];
}
void solution() {

	memset(dp, 0, sizeof(dp));
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dp[i][j] == 0) {
				ans = max(ans, dfs(i, j));
			}
		}
	}
	
	cout << ans;

}
void input() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
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