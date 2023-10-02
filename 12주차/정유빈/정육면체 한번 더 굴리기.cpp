#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int n; //격자 크기
int m; //굴리는 횟수

int map[21][21];
bool visited[21][21];

int dice_x;
int dice_y;
int dice_d; //주사위 방향

int dice[6] = { 5,4,1,3,2,6 }; //주사위

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans = 0;

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void dice_move() {

	if (dice_d == 1 && !inrange(dice_x - 1, dice_y)) {
		dice_d = 2; 
	}
	else if (dice_d == 2 && !inrange(dice_x + 1, dice_y)) {
		dice_d = 1;
	}
	else if (dice_d == 3 && !inrange(dice_x, dice_y - 1)) {
		dice_d = 4;
	}
	else if (dice_d == 4 && !inrange(dice_x, dice_y + 1)) {
		dice_d = 3;
	}

	int new_dice[6];

	if (dice_d == 1) { //상
		new_dice[0] = dice[2];
		new_dice[1] = dice[1];
		new_dice[2] = dice[4];
		new_dice[3] = dice[3];
		new_dice[4] = dice[5];
		new_dice[5] = dice[0];

		dice_x--;
	}
	else if (dice_d == 2) { //하
		new_dice[0] = dice[5];
		new_dice[1] = dice[1];
		new_dice[2] = dice[0];
		new_dice[3] = dice[3]; 
		new_dice[4] = dice[2];
		new_dice[5] = dice[4];

		dice_x++;
	}
	else if (dice_d == 3) { //좌
		new_dice[0] = dice[0];
		new_dice[1] = dice[2];
		new_dice[2] = dice[3];
		new_dice[3] = dice[5];
		new_dice[4] = dice[4];
		new_dice[5] = dice[1];

		dice_y--;
	}
	else { //우
		new_dice[0] = dice[0];
		new_dice[1] = dice[5];
		new_dice[2] = dice[1];
		new_dice[3] = dice[2];
		new_dice[4] = dice[4];
		new_dice[5] = dice[3];

		dice_y++;
	}

	for (int i = 0; i < 6; i++) {
		dice[i] = new_dice[i];
	}
}

void dice_dir_change() {
	//주사위 방향 바꾼다.

	int dice_bottom = dice[5];
	int board_num = map[dice_x][dice_y];

	//주사위 아랫면이 보드의 해당 칸에 있는 숫자보다 크면
	//90도 시계방향으로 회전하여 다시 이동 진행
	if (dice_bottom > board_num) {
		if (dice_d == 1) { //상
			dice_d = 4; //우로
		}
		else if (dice_d == 2) { //하
			dice_d = 3; //좌로
		}
		else if (dice_d == 3) { //좌
			dice_d = 1; //상으로
		}
		else if (dice_d == 4) { //우
			dice_d = 2; //하로
		}
	}
	else if (dice_bottom < board_num) {
		//주사위 아랫면이 보드의 해당 칸에 있는 숫자보다 작으면
		//90도 반시계방향으로 회전하여 다시 이동 진행
		if (dice_d == 1) { //상
			dice_d = 3; //좌로
		}
		else if (dice_d == 2) { //하
			dice_d = 4; //우로
		}
		else if (dice_d == 3) { //좌
			dice_d = 2; //하로
		}
		else if (dice_d == 4) { //우
			dice_d = 1; //상으로
		}
	}
}

void get_score() {
	//점수를 얻는다.

	memset(visited, false, sizeof(visited));

	vector<pair<int, int>> v;
	queue<pair<int, int>> q;
	q.push({ dice_x, dice_y });
	visited[dice_x][dice_y] = true;

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

	ans += v.size() * map[dice_x][dice_y];

}
void solution() {

	dice_d = 4;
	dice_x = 1;
	dice_y = 1;

	for (int i = 0; i < m; i++) {
		dice_move();
		get_score();
		dice_dir_change();
	}

	cout << ans;
}
void input() {

	cin >> n >> m;

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
