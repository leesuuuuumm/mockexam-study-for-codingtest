#include <iostream>
#include <vector>
using namespace std;

int n; //격자 크기
int m;
int h;
int k; //턴 수

vector<pair<int, int>> run_awayers[100][100];

vector<pair<pair<int, int>, pair<int, int>>> after_move_run_awayers;
//나중 위치와 방향1, 방향 2

bool trees[100][100];

int man_x; //술래 위치
int man_y;
int man_d; //술래 방향


vector<pair<pair<int, int>, int>> man_pos_v; //술래 위치와 방향

int turn = 1;
int ans = 0;

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void check_man_pos_v() {

	man_x = n / 2 + 1;
	man_y = n / 2 + 1;

	int x = man_x;
	int y = man_y;

	for (int i = 1; i < n; i += 2) {

		for (int j = 1; j <= i; j++) {
			man_pos_v.push_back({ {x, y}, 1 });
			x--;
		}

		for (int j = 1; j <= i; j++) {
			man_pos_v.push_back({ {x,y},4 });
			y++;
		}
		for (int j = 1; j <= i + 1; j++) {
			man_pos_v.push_back({ {x,y},2 });
			x++;
		}
		for (int j = 1; j <= i + 1; j++) {
			man_pos_v.push_back({ {x,y}, 3 });
			y--;
		}
	}

	for (int i = 1; i < n; i++) {
		man_pos_v.push_back({ {x,y}, 1 });
		x--;
	}

	for (int i = 1; i < n; i++) {
		man_pos_v.push_back({ {x,y}, 2 });
		x++;
	}

	for (int i = n - 1; i > 1; i -= 2) {
		for (int j = 1; j <= i; j++) {
			man_pos_v.push_back({ {x,y}, 4 });
			y++;
		}

		for (int j = 1; j <= i; j++) {
			man_pos_v.push_back({ {x,y}, 1 });
			x--;
		}

		for (int j = 1; j < i; j++) {
			man_pos_v.push_back({ {x,y}, 3 });
			y--;
		}

		for (int j = 1; j < i; j++) {
			man_pos_v.push_back({ {x,y}, 2 });
			x++;
		}
	}

	int size = man_pos_v.size();
	while (true) {

		for (int i = 0; i < size; i++) {
			man_pos_v.push_back(man_pos_v[i]);
		}

		if (man_pos_v.size() > 100) {
			break;
		}
	}
}
pair<int, int> move(int x, int y, int d1, int d2) {

	int nx;
	int ny;

	if (d1 == 1) { //좌우로 움직임

		if (d2 == 1) { //왼쪽을 바라보면
			nx = x;
			ny = y - 1;
		}
		else if (d2 == 2) { //오른쪽을 바라보면
			nx = x;
			ny = y + 1;
		}
	}
	else if (d1 == 2) { //상하로 움직임

		if (d2 == 1) { //위쪽을 바라보면
			nx = x - 1;
			ny = y;
		}
		else if (d2 == 2) { //아래를 바라보면
			nx = x + 1;
			ny = y;
		}
	}

	return { nx,ny };
}
void one_run_away(int x, int y) {
	// (x,y) 에 있는 도망자가 도망간다. 

	int size = run_awayers[x][y].size();

	int nx;
	int ny;

	for (int i = 0; i < size; i++) {
		int d1 = run_awayers[x][y][i].first;
		int d2 = run_awayers[x][y][i].second;

		pair<int, int> next_pos = move(x, y, d1, d2);
		nx = next_pos.first;
		ny = next_pos.second;

		//격자를 벗어나지 않는 경우
		if (inrange(nx, ny)) {
			//움직이려는 칸에 술래가 있다면 움직이지 않는다
			if (man_x == nx && man_y == ny) {
				after_move_run_awayers.push_back({ {x,y}, {d1, d2} });
			}
			else { //술래가 없다면 움직인다.
				after_move_run_awayers.push_back({ {nx,ny}, {d1, d2} });
			}
		}
		else {
			//격자를 벗어나는 경우

			if (d2 == 1) {
				next_pos = move(x, y, d1, 2); //나중 위치
			}
			else if (d2 == 2) {
				next_pos = move(x, y, d1, 1); //나중 위치
			}

			nx = next_pos.first;
			ny = next_pos.second;

			//술래가 없다면
			if (!(man_x == nx && man_y == ny)) {
				if (d2 == 1) {
					after_move_run_awayers.push_back({ {nx,ny}, {d1, 2} });
				}
				else if (d2 == 2) {
					after_move_run_awayers.push_back({ {nx,ny}, {d1, 1} });
				}
			}
			else {
				if (d2 == 1) {
					after_move_run_awayers.push_back({ {x,y}, {d1, 2} });
				}
				else if (d2 == 2) {
					after_move_run_awayers.push_back({ {x,y}, {d1, 1} });
				}
			}
		}
	}

}
void all_run_away() {

	//도망자 이동 후 위치
	after_move_run_awayers.clear();

	int start_x = man_x - 3;
	int start_y = man_y - 3;
	int end_x = man_x + 3;
	int end_y = man_y + 3;

	for (int i = start_x; i <= end_x; i++) {
		for (int j = start_y; j <= end_y; j++) {
			int dist_diff = abs(i - man_x) + abs(j - man_y);
			//거리가 3 이하이고 나무가 없다면
			if (inrange(i, j) && dist_diff <= 3 && run_awayers[i][j].size() > 0) {
				one_run_away(i, j);
				run_awayers[i][j].clear();
			}
		}
	}

	int size = after_move_run_awayers.size();

	for (int i = 0; i < size; i++) {
		int nx = after_move_run_awayers[i].first.first;
		int ny = after_move_run_awayers[i].first.second;
		int d1 = after_move_run_awayers[i].second.first;
		int d2 = after_move_run_awayers[i].second.second;
		run_awayers[nx][ny].push_back({ d1,d2 });
	}

}

void man_move() {
	//술래가 이동한다

	man_x = man_pos_v[turn].first.first;
	man_y = man_pos_v[turn].first.second;
	man_d = man_pos_v[turn].second;


	int catch_cnt = 0;
	int dx[5] = { 0,-1,1,0,0 };
	int dy[5] = { 0,0,0,-1,1 };


	for (int i = 0; i < 3; i++) {
		int nx = man_x + dx[man_d] * i;
		int ny = man_y + dy[man_d] * i;

		if (inrange(nx, ny) && !trees[nx][ny]) {
			catch_cnt += run_awayers[nx][ny].size();
			run_awayers[nx][ny].clear();
		}
	}

	ans += turn * catch_cnt;
}
void one_turn() {

	all_run_away();
	man_move();
}
void solution() {

	check_man_pos_v();

	for (turn = 1; turn <= k; turn++) {
		one_turn();
	}

	cout << ans;
}
void input() {

	cin >> n >> m >> h >> k;

	for (int i = 0; i < m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		run_awayers[x][y].push_back({ d,2 });
	}

	for (int i = 0; i < h; i++) {
		int x, y;
		cin >> x >> y;
		trees[x][y] = true;
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();

}