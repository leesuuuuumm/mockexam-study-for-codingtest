#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n; //ĭ�� ũ��
int map[51][51];
bool visited[51][51];
int l; //��� �̵��� ������ �ּڰ�
int r; //��� �̵��� ������ �ִ�
int times; //Ƚ��

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool flag = false;

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void bfs(int x, int y) {

	vector<pair<int, int>> v;

	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	int sum = 0;

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;
		v.push_back({ a,b });
		sum += map[a][b];

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny]) {

				int diff = abs(map[nx][ny] - map[a][b]); //����

				if (l <= diff && diff <= r) {
					q.push({ nx,ny });
					visited[nx][ny] = true;
				}	
			}
		}
	}

	int cnt = v.size();

	//���
	int avg = sum / cnt;

	for (int i = 0; i < cnt; i++) {
		map[v[i].first][v[i].second] = avg;
	}

	if (cnt > 1) {
		//�̵��� �Ͼ
		flag = true;
	}
}
void one_time() {

	memset(visited, false, sizeof(visited));
	flag = false;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j]) {
				bfs(i, j);
			}
		}
	}

	//�̵��� �� �Ͼ��
	if (!flag) {
		cout << times;
		exit(0);
	}
}
void solution() {

	for (times = 0; times < 10; times++) {
		one_time();
	}

}
void input() {

	cin >> n >> l >> r;

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