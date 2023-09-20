#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int m; //물고기 수
int s; //상어가 마법을 연습한 횟수
int sx, sy; //상어 위치

int smell[5][5]; //냄새
vector<int> map[5][5];
vector<int> copy_map[5][5]; //복제 

int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };

//1: 상, 2: 좌, 3: 하, 4: 우
int sdx[5] = { 0,-1,0,1,0 };
int sdy[5] = { 0,0,-1,0,1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= 4 && 1 <= y && y <= 4) {
		return true;
	}
	return false;
}

void all_fish_copy() {

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			copy_map[i][j].clear(); 
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int size = map[i][j].size();
			for (int k = 0; k < size; k++) {
				copy_map[i][j].push_back(map[i][j][k]);
			}
		}
	}
}

void all_fish_move() {
	//모든 물고기가 한칸 이동한다.

	vector<int> after_move[5][5]; //물고기가 이동한 후

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int size = map[i][j].size();

			for (int k = 0; k < size; k++) {
				bool moved = false;

				int dir = map[i][j][k]; //방향

				for (int d = dir; d >= 1; d--) {
					int nx = i + dx[d];
					int ny = j + dy[d];
				
					//상어 없고, 격자 안이고 냄새 없으면
					if (inrange(nx, ny) && !(nx == sx && ny == sy) && !smell[nx][ny]) {
						after_move[nx][ny].push_back(d); 
						moved = true;
						break;
					}
				}

				if (moved) { //만약 이동했으면
					continue;
				}

				for (int d  = 8; d > dir; d--) {
					int nx = i + dx[d];
					int ny = j + dy[d];

					//상어 없고, 격자 안이고 냄새 없으면
					if (inrange(nx, ny) && !(nx == sx && ny == sy) && !smell[nx][ny]) {
						after_move[nx][ny].push_back(d);
						moved = true;
						break;
					}
				}

				if (!moved) {
					after_move[i][j].push_back(dir);
				}
			}
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			map[i][j] = after_move[i][j];
		}
	}


}

int shark_move_fish_cnt(string st) {
	//물고기 개수 새기

	int fish_cnt = 0;
	int nx = sx;
	int ny = sy;

	bool visited[5][5];
	memset(visited, false, sizeof(visited));

	for (int i = 0; i < st.size(); i++) {
		char c = st[i];
		int d = c - '0'; //물고기 방향

		nx += sdx[d];
		ny += sdy[d];

		if (inrange(nx, ny)) {

			if (!visited[nx][ny]) {
				fish_cnt += map[nx][ny].size();
				visited[nx][ny] = true;
			}
		}
		else {
			return -1; //격자를 넘으면
		}
	}

	return fish_cnt;

}
void shark_move() {
	//상어가 연속해서 3칸 이동한다.
	//1: 상, 2: 좌, 3: 하, 4: 우

	vector<pair<int, string>> info; 

	//111부터 444까지
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				char a = i + '0';
				char b = j + '0';
				char c = k + '0';
				string st = "";
				st += a;
				st += b;
				st += c;
				int fish_cnt = shark_move_fish_cnt(st);

				if (fish_cnt != -1) {
					info.push_back({ -1 * fish_cnt, st });
				}
			}
		}
	}

	sort(info.begin(), info.end());

	//상어가 이렇게 이동한다.
	string st = info[0].second;

	for (int i = 0; i < st.size(); i++) {
		char c = st[i];
		int dir = c - '0'; //방향

		//상어 이동
		sx += sdx[dir];
		sy += sdy[dir];

		if (map[sx][sy].size() > 0) {
			map[sx][sy].clear(); //물고기가 죽는다.
			smell[sx][sy] = 3; //냄새를 남긴다.
		}
	}

}

void smell_remove() {
	//2번 전 연습에서 물고기 냄새가 격자에서 사라진다.

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (smell[i][j] > 0) {
				smell[i][j] -= 1;
			}
		}
	}
}

void copy_fish_copy() {

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int size = copy_map[i][j].size();
			for (int k = 0; k < size; k++) {
				map[i][j].push_back(copy_map[i][j][k]);
			}
		}
	}
}
void one_time() {

	//모든 물고기가 복제한다.
	all_fish_copy();
	
	//모든 물고기가 한칸 이동한다.
	all_fish_move();

	//상어가 연속해서 3칸 이동한다.
	shark_move();

	//2번 전 연습에서 물고기 냄새가 격자에서 사라진다.
	smell_remove();

	//복제된 물고기가 복제된다
	copy_fish_copy();

	

}
void solution() {

	for (int i = 0; i < s; i++) {
		one_time();
	}

	int ans = 0;

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			ans += map[i][j].size();
		}
	}

	cout  << ans;
}
void input() {

	cin >> m >> s;

	for (int i = 0; i < m; i++) {
		int fx, fy; //물고기 위치
		int d; //방향
		cin >> fx >> fy >> d;
		map[fx][fy].push_back(d);
	}

	cin >> sx >> sy; //상어 위치
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
