#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int w, h;
char map[101][101];
int dp[101][101][4];

int start_x;
int start_y;

int end_x;
int end_y;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int ans = 9999999;

bool inrange(int x, int y) {

	if (1 <= x && x <= h && 1 <= y && y <= w) {
		return true;
	}
	return false;
}

void print() {

	cout << "--------------" << "\n";

	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cout << "i: " << i << " j: " << j << "\n";
			for (int k = 0; k < 4; k++) {
				cout << dp[i][j][k] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
}
void solution() {

	queue<pair<pair<int, int>, pair<int,int>>> q;
	//위치와 방향

	q.push({ {start_x, start_y}, {0, 0} });
	q.push({ {start_x, start_y}, {1, 0} });
	q.push({ {start_x, start_y}, {2, 0} });
	q.push({ {start_x, start_y}, {3, 0} });

	dp[start_x][start_y][0] = 0;
	dp[start_x][start_y][1] = 0;
	dp[start_x][start_y][2] = 0;
	dp[start_x][start_y][3] = 0;	

	while (!q.empty()) {

		int x = q.front().first.first;
		int y = q.front().first.second;
		int dir = q.front().second.first;
		int cnt = q.front().second.second;

		q.pop();


		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			
			if (inrange(nx, ny) && map[nx][ny] != '*') {

				//정반대라면
				if (dir != i && (dir + i) % 2 == 0) {
					continue;
				}

				if (dir == i && cnt < dp[nx][ny][i]) {
					dp[nx][ny][i] = cnt;
					q.push({ {nx,ny}, {i, cnt } });
				}
				else if (dir != i && cnt + 1 < dp[nx][ny][i]) {
					dp[nx][ny][i] = cnt + 1;
					q.push({ {nx,ny}, {i, cnt + 1} });
				}
			}
		}
	}

}

void output() {

	for (int i = 0; i < 4; i++) {
		ans = min(ans, dp[end_x][end_y][i]);
	}

	cout << ans;
}
void input() {

	cin >> w >> h;

	for (int i = 1; i <= h; i++) {
		string st;
		cin >> st;

		for (int j = 1; j <= w; j++) {
			map[i][j] = st[j - 1];

			if (map[i][j] == 'C') {
				if (start_x == 0) {
					start_x = i;
					start_y = j;
				}
				else {
					end_x = i;
					end_y = j;
				}
			}

			for (int k = 0; k < 4; k++) {
				dp[i][j][k] = 9999999;
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
	output();
}
