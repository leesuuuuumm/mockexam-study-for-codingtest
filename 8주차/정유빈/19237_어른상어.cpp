#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, m, k; //n: 격자크기, m: 상어 수

int shark_now_dir[401]; //상어 지금 방향
bool shark_die[401];

pair<pair<int, int>, int> tmp_shark_next_position[401]; //상어 나중 위치 저장
pair<int, int> shark_position[401]; //상어 위치
pair<int, int> smell_info[21][21]; //냄새남긴 상어 번호와 남은 초

//상어 우선순위
//1: 위, 2: 아래, 3: 왼쪽, 4: 오른쪽
vector<int> sharks_favorite_dir[401][5];
int times;

int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,-1,1 };

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void one_shark_check_move(int shark_num) {
	//shark_num 상어가 움직인다.

	//상어 위치
	int shark_x = shark_position[shark_num].first;
	int shark_y = shark_position[shark_num].second;

	//상어 방향
	int shark_dir = shark_now_dir[shark_num];

	//1. 아무 냄새가 없는 칸의 방향으로 잡는다.
	for (int i = 0; i < 4; i++) {
		int next_dir = sharks_favorite_dir[shark_num][shark_dir][i];

		int next_x = shark_x + dx[next_dir];
		int next_y = shark_y + dy[next_dir];

		//냄새가 없으면 == 상어가 들어오지 않았다면
		if (inrange(next_x, next_y) && smell_info[next_x][next_y].first == 0) {
			tmp_shark_next_position[shark_num] = { {next_x, next_y}, next_dir };
			return;
		}
	}

	//2. 자신의 냄새가 있는 방향으로 잡는다.
	for (int i = 0; i < 4; i++) {
		int next_dir = sharks_favorite_dir[shark_num][shark_dir][i];

		int next_x = shark_x + dx[next_dir];
		int next_y = shark_y + dy[next_dir];

		//자신의 냄새가 있으면 == 상어가 아직 들어오지 않아다면
		if (inrange(next_x, next_y) && smell_info[next_x][next_y].first == shark_num) {
			tmp_shark_next_position[shark_num] = { {next_x, next_y}, next_dir };
			return;
		}
	}

}

void one_shark_smell(int shark_num) {

	//상어가 냄새를 뿌린다.
	int shark_x = shark_position[shark_num].first;
	int shark_y = shark_position[shark_num].second;

	smell_info[shark_x][shark_y] = { shark_num, k };
}


void all_shark_real_move() {

	int survival_num = 0;

	for (int shark_num = 1; shark_num <= m; shark_num++) {

		if (shark_die[shark_num]) {
			continue;
		}


		int next_x = tmp_shark_next_position[shark_num].first.first;
		int next_y = tmp_shark_next_position[shark_num].first.second;
		int next_dir = tmp_shark_next_position[shark_num].second;

		//상어 위치
		int shark_x = shark_position[shark_num].first;
		int shark_y = shark_position[shark_num].second;

		//원래 있던 곳의 냄새 초는 1 줄어든다.

		//다른 상어가 존재한다면
		if (smell_info[next_x][next_y].second == k) {
			shark_die[shark_num] = true;
			continue;
		}

		survival_num++;

		//냄새를 채운다.
		smell_info[next_x][next_y] = { shark_num, k };

		//상어 방향
		int shark_dir = shark_now_dir[shark_num];

		shark_position[shark_num] = { next_x, next_y };
		shark_now_dir[shark_num] = next_dir;


	}

	if (survival_num == 1) {
		cout << times << "\n";
		exit(0);
	}
}

void all_smell_minus() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

			if (smell_info[i][j].second > 0) {
				smell_info[i][j].second -= 1;
			}

			if (smell_info[i][j].second == 0) {
				smell_info[i][j] = { 0,0 };
			}
		}
	}
}
void one_time() {
	//1초에 일어나는 일

	for (int i = 1; i <= m; i++) {

		if (!shark_die[i]) {
			one_shark_check_move(i);
		}
	}

	all_smell_minus();
	all_shark_real_move();
}
void solution() {

	//처음에만 냄새를 바로 뿌린다.
	for (int i = 1; i <= m; i++) {
		one_shark_smell(i); //각자 자리에 냄새를 뿌린다.
	}

	for (times = 1; times <= 1000; times++) {
		one_time();
	}

	cout << -1;
}

void input() {

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int num;
			cin >> num;
			if (num != 0) {
				shark_position[num] = { i,j };
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		cin >> shark_now_dir[i];
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= 4; j++) {
			vector<int> v;
			for (int k = 1; k <= 4; k++) {
				int num;
				cin >> num;
				v.push_back(num);
			}
			sharks_favorite_dir[i][j] = v;
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
