#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

char map[5][5];
bool visited[5][5];
bool checking[5][5];

vector<pair<int, int>> arr;
int ans = 0;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (0 <= x && x < 5 && 0 <= y && y < 5) {
		return true;
	}
	return false;
}


void check(vector<pair<int, int>> comb) {

	//	cout << "ans: " << ans << "\n";
	memset(visited, false, sizeof(visited));


	queue<pair<int, int>> q;
	q.push({ comb[0].first, comb[0].second });
	visited[comb[0].first][comb[0].second] = true;

	while (!q.empty()) {

		int a = q.front().first;
		int b = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && checking[nx][ny] && !visited[nx][ny]) {
				if (map[nx][ny] == 'S') {
					visited[nx][ny] = true;
					q.push({ nx,ny });
				}
				else {
					visited[nx][ny] = true;
					q.push({ nx,ny });
				}
			}
		}
	}



	int cnt1 = 0;
	int cnt2 = 0;

	for (int i = 0; i < comb.size(); i++) {
		if (!visited[comb[i].first][comb[i].second]) { //방문하지 않은 곳이 있다면
			return;
		}
		else if (map[comb[i].first][comb[i].second] == 'Y') {
			cnt2++;
		}
		else {
			cnt1++;
		}
	}


	if (cnt1 >= 4) {
		ans++;
	}

}
void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {

	if (r == 0) {

		for (int i = 0; i < comb.size(); i++) {
			checking[comb[i].first][comb[i].second] = true;
		}

		check(comb);


		for (int i = 0; i < comb.size(); i++) {
			checking[comb[i].first][comb[i].second] = false;
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

	vector<pair<int, int>> comb(7);
	combination(arr, comb, 7, 0, 0);
	cout << ans << "\n";
}

void input() {

	for (int i = 0; i < 5; i++) {
		string st;
		cin >> st;

		for (int j = 0; j < 5; j++) {
			map[i][j] = st[j];
			arr.push_back({ i,j });
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
