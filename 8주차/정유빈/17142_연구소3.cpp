#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int n;//연구소 크기
int m; //바이러스 개수
int map[51][51];
int dist[51][51];
int times = 1;
int ans = 9999999;
vector<pair<int, int>> virus;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void check(vector<pair<int, int>> comb) {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = 9999999;
		}
	}

	queue<pair<pair<int, int>, int>> q;

	for (int i = 0; i < comb.size(); i++) {
		q.push({ {comb[i].first, comb[i].second }, 0 });
		dist[comb[i].first][comb[i].second] = 0;
	}

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;
		
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && d + 1 < dist[nx][ny] && map[nx][ny] != 1) {
				dist[nx][ny] = d + 1;
				q.push({ {nx,ny}, d + 1 });
			}
		}
	}
	
	//다 퍼졌는지 체크

	int tmp_ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 0) { //빈 칸
				if (dist[i][j] == 9999999) { //도착 못했으면
					return;
				}
				else {
					tmp_ans = max(tmp_ans, dist[i][j]);
				}

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
	else if (depth == arr.size()) {
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
	combination(virus, comb, m, 0, 0);

	if (ans == 9999999) {
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
				virus.push_back({ i,j });
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