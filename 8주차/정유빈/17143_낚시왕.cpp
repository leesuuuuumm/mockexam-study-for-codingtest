#include <iostream>

using namespace std;

int r; //행 크기 
int c; //열 크기
int m; //상어 수
int map[101][101];
long ans = 0;

struct shark_info {
	int s; //속력
	int d; //이동 방향
	int z; //크기
};

shark_info shark_map[101][101]; 

//1: 위, 2: 아래, 3: 오른쪽, 4: 왼쪽
int dx[5] = { 0,-1,1,0,0 }; 
int dy[5] = { 0,0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= r && 1 <= y && y <= c) {
		return true;
	}
	return false;
}

int change_dir(int d) {

	if (d == 1) {
		return 2;
	}
	else if (d == 2) {
		return 1;
	}
	else if (d == 3) {
		return 4;
	}
	else {
		return 3;
	}
}
pair<pair<int,int>, int> move(int x, int y, int s, int d) {
	//상어가 움직인 뒤 위치와 방향 리턴

	if (d <= 2) {
		s = s % (2 * r - 2);
	}
	else {
		s = s % (2 * c - 2);
	}


	for (int i = 0; i < s; i++) {
		int nx = x + dx[d];
		int ny = y + dy[d];

		if (inrange(nx, ny)) {
			x = nx;
			y = ny;
		}
		else {
			d = change_dir(d); //방향을 바꾼다.
			i--; 
		}
	}
	return { {x,y}, d };
}

void all_shark_move() {

	shark_info tmp_shark_map[101][101];

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			tmp_shark_map[i][j] = { 0,0,0 };
		}
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {

			if (shark_map[i][j].d == 0) {
				continue;
			}
			else {
				//위치와 방향
  	
				 pair<pair<int,int>, int> p = move(i, j, shark_map[i][j].s, shark_map[i][j].d);

	
				 if (tmp_shark_map[p.first.first][p.first.second].z < shark_map[i][j].z) {
					 tmp_shark_map[p.first.first][p.first.second] = { shark_map[i][j].s, p.second, shark_map[i][j].z };
				 }				 
			}
		}
	}

	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			shark_map[i][j] = tmp_shark_map[i][j];
		}
	}
}
void one_col(int col) {

	//낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡는다.

	for (int row = 1; row <= r; row++) {
		if (shark_map[row][col].d != 0) { //상어가 있으면
			ans += shark_map[row][col].z; //상어를 잡는다.
			shark_map[row][col] = { 0,0,0 };
			break;
		}
	}

	all_shark_move();
}
void solution() {

	
	for (int col = 1; col <= c; col++) {
		one_col(col); 
	}

	cout <<  ans;
	
}
void input() {

	cin >> r >> c >> m;

	for (int i = 0; i < m; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		shark_map[r][c] = { s, d, z };
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}