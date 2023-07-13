#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n; //세로 크기
int m; //가로 크기
int map[9][9];
//0: 빈칸, 1: 벽, 2: 바이러스
bool visited[9][9];

vector<pair<int, int>> v;

int cnt = 0;
int ans = 0;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= m) {
		return true;
	}
	
	return false;
}
void bfs(int x, int y) {

	queue<pair<int, int>> q; 
	q.push({ x,y });
	visited[x][y] = true;

	while (!q.empty()) {

		int a = q.front().first;
		int b = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && map[nx][ny] == 0 && !visited[nx][ny]) {
				visited[nx][ny] = true;
				q.push({ nx,ny });
			}
		}
	}
}
void spread(vector<pair<int, int>> comb) {

	//comb는 추가적인 벽 설치

	memset(visited, false, sizeof(visited));


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == 2) {
				bfs(i, j);
			}
		}
	}
}

void check() {

	int tmp_ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == 0 && !visited[i][j]) {
				tmp_ans++;
			}
		}
	}

	ans = max(ans, tmp_ans);
}
void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {
	
	if (r == 0) {

		for (int i = 0; i < comb.size(); i++) {
			map[comb[i].first][comb[i].second] = 1;
		}

		spread(comb);
		check();

		for (int i = 0; i < comb.size(); i++) {
			map[comb[i].first][comb[i].second] = 0;
		}

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

	vector<pair<int, int>> comb(3);

	combination(v, comb, 3, 0, 0);
	cout <<  ans;
}

void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) {
				v.push_back({ i,j });
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
