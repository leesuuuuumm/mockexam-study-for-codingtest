#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n; //격자 크기
int m; //병원 수

int map[51][51];
//0: 바이러스, 1: 벽, 2: 병원

bool visited[51][51];

vector<pair<int, int>> hospitals;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ans = 999999;

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void check(vector<pair<int, int>> comb) {

	int dist[11][11] = { 0, };

	memset(visited, false, sizeof(visited));
	queue<pair<pair<int, int>, int>> q;
	
	int size = comb.size();

	for (int i = 0; i < size; i++) {
		q.push({ {comb[i].first, comb[i].second}, 0 });
		visited[comb[i].first][comb[i].second] = true;
	}

	int tmp_ans = 0;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;
		dist[a][b] = d;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && map[nx][ny] != 1 && !visited[nx][ny]) {
				q.push({ {nx,ny}, d + 1 });
				visited[nx][ny] = true;

				if (map[nx][ny] == 0) {
					tmp_ans = max(tmp_ans, d + 1);
				}
			}
		}
	}


	for (int i = 1; i<= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 0 && !visited[i][j]) {
				return;
			}
		}
	}

	ans = min(ans, tmp_ans);

}
void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {

	if (r == 0) {

		check(comb);
		return;
	}
	else if (arr.size() == depth) {
		return;
	}
	else {

		comb[idx] = arr[depth];

		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}
void solution() {

	vector<pair<int, int>> comb(m);

	combination(hospitals, comb, m, 0, 0);


	if (ans == 999999) {
		cout << -1;
	}
	else {
		cout << ans;
	}
	
}
void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				hospitals.push_back({ i,j });
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