#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int n; //연구소 크기
int m; //바이러스 개수

int map[51][51];
bool visited[51][51];
int dist[51][51];

vector<pair<int, int>> virus;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans = 99999999;
bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void bfs(int x, int y) {

	queue<pair<pair<int,int>, int>> q;
	q.push({ {x,y }, 0 });
	dist[x][y] = 0;

	while (!q.empty()) {
		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && dist[nx][ny] > d + 1 && map[nx][ny] != 1) {
				q.push({ {nx,ny}, d + 1 });
				dist[nx][ny] = d + 1;
			}
		}
	}
}
void check(vector<pair<int, int>> comb) {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = 9999999;
		}
	}

	for (int i = 0; i < comb.size(); i++) {
		bfs(comb[i].first, comb[i].second);
	}

	int tmp_max_time = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] != 1 && dist[i][j] == 9999999) {
				//만약 빈칸이 아닌데 거리가 있다면
				return;
			}
			if (dist[i][j] != 9999999) {
				tmp_max_time = max(tmp_max_time, dist[i][j]);
			}
		}
	}


	ans = min(tmp_max_time, ans);

}
void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {

	if (r == 0) {
		check(comb);
	}
	else if (arr.size() == depth) {
		return;
	}
	else{
		comb[idx] = arr[depth];

		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}
void solution() {


	vector<pair<int, int>> comb(m);

	combination(virus, comb, m, 0, 0);

	if (ans == 99999999) {
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
