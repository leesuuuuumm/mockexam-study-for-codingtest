#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int n; //격자 크기
int m; //팀 개수
int k; //라운드 수

int map[21][21];
//0: 빈칸
//1: 머리사람
//2: 머리사람과 꼬리사람이 아닌 나머지
//3: 꼬리 사람
//4: 이동 선

bool visited[21][21];

vector < vector<pair<int, int>>> line_v;
//이동 선 위치

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int turn = 1;

struct ball_throw_info {
	//공 던지는 시작 위치
	int x;
	int y;
	//방향
	int dir;
};

vector<ball_throw_info> ball_infos;

int total_score = 0;


bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

bool head_dir(int x, int y, int dir) {
	//2가 가르키는 방향이 머리 방향인지

	memset(visited, false, sizeof(visited));

	visited[x][y] = true;

	int now_x = x;
	int now_y = y;
	visited[now_x][now_y] = true;

	now_x = x + dx[dir];
	now_y = y + dy[dir];
	visited[now_x][now_y] = true;

	while (true) {

		if (map[now_x][now_y] == 1) {
			return true;
		}
		else if (map[now_x][now_y] == 3) {
			return false;
		}

		for (int i = 0; i < 4; i++) {
			int nx = now_x + dx[i];
			int ny = now_y + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && 1 <= map[nx][ny] && map[nx][ny] <= 3) {
				now_x = nx;
				now_y = ny;
				visited[now_x][now_y] = true;
				break;
			}
		}

	}
}

void all_team_one_move() {
	//먼저 각 팀은 머리사람을 따라서 한 칸 이동합니다.

	int new_map[21][21] = { 0, };

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 1) {
				//머리 사람이면

				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];

					if (inrange(nx, ny) && map[nx][ny] >= 3) {
						new_map[nx][ny] = 1;
						break;
					}
				}
			}
			else if (map[i][j] == 2) {
				//중간 사람이면 1이 있으면 1 먼저 따라가고 없으면 2 따라가야 함

				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];

					if (inrange(nx, ny) && (map[nx][ny] == 1)) {
						new_map[nx][ny] = 2;
						break;
					}
				}
				//2따라 갈때 앞 뒤가 2이면 누가 앞인지 알아야 함

				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];

					if (inrange(nx, ny) && (map[nx][ny] == 2) && head_dir(i, j, k)) {
						new_map[nx][ny] = 2;
					//	break;
					}
				}
			}
			else if (map[i][j] == 3) {
				//꼬리 사람이면

				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];

					if (inrange(nx, ny) && map[nx][ny] == 2) {
						new_map[nx][ny] = 3;
						break;
					}
				}
			}
		}
	}

	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (new_map[i][j] > 0) {
				map[i][j] = new_map[i][j];
			}
			else if (new_map[i][j] == 0 && map[i][j] >= 1) {
				map[i][j] = 4;
			}
		}
	}
}



void define_ball_throw_info() {
	//공을 던진다.

	vector<ball_throw_info> v;

	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };

	//왼쪽에서 오른쪽으로
	for (int i = 1; i <= n; i++) {
		v.push_back({ i,1,2 });
	}

	//아래에서 위로
	for (int j = 1; j <= n; j++) {
		v.push_back({ n, j, 1 });
	}

	//오른쪽에서 왼쪽으로
	for (int i = n; i >= 1; i--) {
		v.push_back({ i, n, 3 });
	}

	//위에서 아래로
	for (int j = n; j >= 1; j--) {
		v.push_back({ 1, j, 0 });
	}

	int size = v.size();
	while (true) {
		
		for (int i = 0; i < size; i++) {
			ball_infos.push_back(v[i]);
		}

		if (ball_infos.size() >= k) {
			break;
		}
	}
}

void get_score(int x, int y) {
	//(x,y)에 있는 사람이 공을 맞는다.

	int now_x = x; 
	int now_y = y;

	//앞으로만 간다.
	int front_person_cnt = 0;

	while (true) {

		front_person_cnt++;

		if (map[now_x][now_y] == 1) {
			break;
		}
		else if (map[now_x][now_y] == 2) {

			bool found = false;
			for (int k = 0; k < 4; k++) {
				int nx = now_x + dx[k];
				int ny = now_y + dy[k];

				//앞으로 갈 수 있으면
				if (inrange(nx, ny) && map[nx][ny] == 1) {
					now_x = nx;
					now_y = ny;
					found = true;
					break;
				}
			}

			if (found) {
				continue;
			}

			for (int k = 0; k < 4; k++) {
				int nx = now_x + dx[k];
				int ny = now_y + dy[k];

				//앞으로 갈 수 있으면
				if (inrange(nx, ny) && map[nx][ny] == 2 && head_dir(now_x,now_y, k)) {
					now_x = nx;
					now_y = ny;
					break;
				}
			}

		}
		else if (map[now_x][now_y] == 3) {

			for (int k = 0; k < 4; k++) {
				int nx = now_x + dx[k];
				int ny = now_y + dy[k];

				//앞으로 갈 수 있으면
				if (inrange(nx, ny) && map[nx][ny] == 2) {
					now_x = nx;
					now_y = ny;
					break;
				}
			}

		}
	}

	int tmp = front_person_cnt * front_person_cnt;
	total_score += front_person_cnt * front_person_cnt;
}

void change_team_dir(int x, int y) {
	//(x,y)가 속한 팀의 머리와 꼬리를 바꾼다.

	int tail_x;
	int tail_y;

	int head_x;
	int head_y;

	memset(visited, false, sizeof(visited));

	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;

	while (!q.empty()) {

		int a = q.front().first;
		int b = q.front().second;

		if (map[a][b] == 1) {
			head_x = a;
			head_y = b;
		}
		else if (map[a][b] == 3) {
			tail_x = a;
			tail_y = b;
		}

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] >= 1) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
			}
		}
	}

	map[head_x][head_y] = 3;
	map[tail_x][tail_y] = 1;

}
void ball_throw() {

	int ball_x = ball_infos[turn - 1].x;
	int ball_y = ball_infos[turn - 1].y;
	int ball_dir = ball_infos[turn - 1].dir;

	for (int i = 0; i < n; i++) {
		int nx = ball_x + dx[ball_dir] * i;
		int ny = ball_y + dy[ball_dir] * i; 

		if (map[nx][ny] >= 1 && map[nx][ny] <= 3) {
			get_score(nx, ny);
			change_team_dir(nx, ny);
			break;
		}
	}

}
void one_round() {

	all_team_one_move();
	ball_throw();
	
}
void solution() {

	define_ball_throw_info();

	for (turn = 1; turn <= k; turn++) {
		one_round();
	}
	cout <<  total_score << "\n";


}
void input() {

	cin >> n >> m >> k;

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

