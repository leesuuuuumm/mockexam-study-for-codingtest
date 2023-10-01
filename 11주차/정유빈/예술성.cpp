#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int n;
int map[30][30];
bool visited[30][30];
int connected[30][30][11];

//개수
int connected_num[901][901];

pair<int, int> num_map[900]; //개수, 진짜 숫자

pair<int, int> info[30][30];
//번호와 개수

int times;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans = 0; 

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void bfs(int x, int y, int num) {

	vector<pair<int, int>> v;
	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;
		v.push_back({ a,b });

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[a][b] == map[nx][ny]) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
			}
		}
	}

	int size = v.size();

	num_map[num] = { map[x][y], size };

	for (int i = 0; i < size; i++) {
		info[v[i].first][v[i].second] = { num, size };
	}
}

void check_connect(int x, int y) {


	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	int cnt = 0;

	while (!q.empty()) {

		int a = q.front().first;
		int b = q.front().second;
		int num = info[a][b].first; //숫자

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny)) {

				int num2 = info[nx][ny].first;

				//숫자가 다르고 안 이어져 있다면
				if (num != num2 && !connected[a][b][i]) {
					connected[a][b][i] = true;
			//		cout << "a: " << a << " b: " << b << " i: " << i << "\n";
					connected_num[num][num2]++;
				}
				else if (num == num2 && !visited[nx][ny]) {
					q.push({ nx,ny });
					visited[nx][ny] = true;
				}
			}
		}
	}
}

void answer_change() {

	memset(visited, false, sizeof(visited));
	memset(connected, false, sizeof(connected));
	memset(connected_num, 0, sizeof(connected_num));

	int num = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j]) {
				num++;
				bfs(i, j, num);
			}
		}
	}
	

	
	memset(visited, false, sizeof(visited));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j]) {
				check_connect(i, j);
			}
		}
	}

	for (int i = 1; i <= num; i++) {
		for (int j = i + 1; j <= num; j++) {
			if (connected_num[i][j] == 0) {
				continue;
			}

			//그룹 a에 속한 칸의 수
			int a_num_cnt = num_map[i].second;
			int a_real_num = num_map[i].first;

			int b_num_cnt = num_map[j].second;
			int b_real_num = num_map[j].first;

			int connected_cnt = connected_num[i][j];

			int tmp_ans = (a_num_cnt + b_num_cnt) * a_real_num * b_real_num * connected_cnt;
			ans += tmp_ans;
		}
	}
}

void mini_rotate(int x, int y, int num) {

	int tmp_map[30][30];

	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			//i랑 j가 1씩 늘음
			//0 -> x + 1 이었으면
			//1 -> x 여야 함
			tmp_map[i - 1][j - 1] = map[x + num - j][y + i - 1];
		}
	}

	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			map[x + i - 1][y + j - 1] = tmp_map[i - 1][j - 1];
		}
	}
}
void rotate() {
	//십자모양의 경우 통졔로 반시계방향으로 90도 회전

	vector<int> v[4];

	//정중앙
	int cx = n / 2 + 1;
	int cy = n / 2 + 1;

	//위
	for (int i = cx - 1; i >= 1; i--) {
		v[0].push_back(map[i][cy]);
	}

	//왼쪽
	for (int j = cy - 1; j >= 1; j--) {
		v[1].push_back(map[cx][j]); 
	}

	//오른쪽
	for (int j = cy + 1; j <= n; j++) {
		v[2].push_back(map[cx][j]);
	}

	//아래쪽
	for (int i = cx + 1; i <= n; i++) {
		v[3].push_back(map[i][cy]);
	}

	//위 <- 오른쪽
	for (int i = 1; i < cx; i++) {
		map[i][cy] = v[2].back();
		v[2].pop_back();
	}

	//왼쪽 <- 위
	for (int j = 1; j < cy; j++) {
		map[cx][j] = v[0].back();
		v[0].pop_back();
	}

	//아래 <- 왼쪽
	for (int i = n; i > cx; i--) {
		map[i][cy] = v[1].back();
		v[1].pop_back();
	}

	//오른쪽 <- 아래
	for (int j = n; j > cy; j--) {
		map[cx][j] = v[3].back();
		v[3].pop_back();
	}

	mini_rotate(1, 1, n / 2);
	mini_rotate(1, cy + 1, n / 2);
	mini_rotate(cx + 1, 1, n / 2);
	mini_rotate(cx + 1, cy + 1, n / 2);
}
void one_time() {

	rotate();
	answer_change();
}
void solution() {

	answer_change();
	for (times = 1; times <= 3; times++) {
		one_time();
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