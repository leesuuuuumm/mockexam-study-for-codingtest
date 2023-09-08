#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n; //체스판 크기
int k; //말 개수

int map[13][13];
//0: 흰색, 1: 빨간색, 2: 파란색

vector<int> horse_map[13][13]; //몇 번째 말이 있는지

int times = 1;

struct info {
	int x;
	int y;
	int dir;
};

info horses[150];
//1: 오른쪽, 2: 왼쪽, 3: 위쪽,  4: 아래쪽

int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void move_to_white(int x, int y, int dir, int horse_num) {
	//(x,y)에 있는 horse_num 말이 dir 방향으로 이동


	//아래부터 horse_num

	vector<int> v = horse_map[x][y];

	int idx = find(v.begin(), v.end(), horse_num) - v.begin();

	int nx = x + dx[dir];
	int ny = y + dy[dir];

	for (int i = idx; i < v.size(); i++) {
		horse_map[nx][ny].push_back(v[i]);

		horses[v[i]].x = nx;
		horses[v[i]].y = ny;
	}

	if (horse_map[nx][ny].size() >= 4) {
		cout << times << "\n";
		exit(0);
	}

	for (int i = idx; i < v.size(); i++) {
		horse_map[x][y].pop_back();
	}
}

void move_to_red(int x, int y, int dir, int horse_num) {
	//(x,y)에 있는 horse_num 말이 dir 방향으로 이동

	//아래부터 horse_num

	vector<int> v = horse_map[x][y];

	int idx = find(v.begin(), v.end(), horse_num) - v.begin();

	int nx = x + dx[dir];
	int ny = y + dy[dir];

	for (int i = v.size() - 1; i >= idx; i--) {
		horse_map[nx][ny].push_back(v[i]);

		horses[v[i]].x = nx;
		horses[v[i]].y = ny;
	}

	if (horse_map[nx][ny].size() >= 4) {
		cout << times << "\n";
		exit(0);
	}

	for (int i = idx; i < v.size(); i++) {
		horse_map[x][y].pop_back();
	}

}

int change_dir(int dir) {

	if (dir % 2 == 1) {
		return dir + 1;
	}
	return dir - 1;
}
void move(int x, int y, int dir, int horse_num, bool again) {

	int nx;
	int ny;

	if (again) { //다시 하는 거라면

		nx = x + dx[dir];
		ny = y + dy[dir];

		if (inrange(nx, ny)) {
			if (map[nx][ny] == 0) { //흰색이라면
				move_to_white(x, y, dir, horse_num);
			}
			else if (map[nx][ny] == 1) { //빨간색이면
				move_to_red(x, y, dir, horse_num);
			}
		}

		return;
	}

	//다음 위치
	nx = x + dx[dir];
	ny = y + dy[dir];

	if (inrange(nx, ny)) {

		if (map[nx][ny] == 0) { //흰색이라면
			move_to_white(x, y, dir, horse_num);
		}
		else if (map[nx][ny] == 1) { //빨간색이면
			move_to_red(x, y, dir, horse_num);
		}
		else if (map[nx][ny] == 2) { //파란색이면
			dir = change_dir(dir);
			horses[horse_num] = { x,y, dir };
			move(x, y, dir, horse_num, true);
		}
	}
	else {
		dir = change_dir(dir);
		horses[horse_num] = { x,y, dir };
		move(x, y, dir, horse_num, true);
	}
}
void one_turn() {
	
	for (int i = 1; i <= k; i++) {
		int x = horses[i].x;
		int y = horses[i].y; 
		int dir = horses[i].dir;

		move(x, y, dir, i, false);

	}

}

void solution() {

	for (times = 1; times <= 1000; times++) {
		one_turn();
	}

	cout << -1;

	
}

void input() {

	cin >> n >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
	
	for (int i = 1; i <= k; i++) {
		int x, y, dir;
		cin >> x >> y >> dir;
		horses[i] = { x,y,dir };
		horse_map[x][y].push_back(i);
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0); 
	cout.tie(0);

	input();
	solution();
}