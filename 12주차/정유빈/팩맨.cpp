#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>


using namespace std;

int m; //���� ���� ��
int t; //���� ��

//�Ѹ� ��ġ
int packman_r; 
int packman_c;

vector<int> after_move_monsters[5][5];
vector<int> monsters[5][5];
vector<int> monster_eggs[5][5];
vector<int> dead_monsters_bodys[5][5]; //���� ��ü
bool visited[5][5]; 

int dx[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int dy[9] = { 0,0,-1,-1,-1,0,1,1,1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= 4 && 1 <= y && y <= 4) {
		return true;
	}
	return false;
}

bool compare(pair<int, string> p1, pair<int, string> p2) {
	//int ���� ���� ���� => �� ���� string ��������

	if (p1.first == p2.first) {
		return p1.second < p2.second;
	}

	return p1.first > p2.first;
}

void all_monster_copy_try() {
	//���� ���� �õ�

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			monster_eggs[i][j] = monsters[i][j];
		}
	}
}

void one_monster_move(int x, int y, int dir) {
	//(x,y)�� �ִ� dir ������ ���� ���Ͱ� �̵��Ѵ�.


	for (int d = dir; d <= 8; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];

		if (inrange(nx, ny) && !(packman_r == nx && packman_c == ny) && dead_monsters_bodys[nx][ny].size() == 0) {
			after_move_monsters[nx][ny].push_back(d);
			return;
		}
	}
	for (int d = 1; d < dir; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];

		if (inrange(nx, ny) && !(packman_r == nx && packman_c == ny) && dead_monsters_bodys[nx][ny].size() == 0) {
			after_move_monsters[nx][ny].push_back(d);
			return;
		}
	}

	after_move_monsters[x][y].push_back(dir);
}

void all_monster_move() {
	//���� �̵�

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			after_move_monsters[i][j].clear();
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int size = monsters[i][j].size();
			for (int k = 0; k < size; k++) {
				int dir = monsters[i][j][k]; //���� ����
				one_monster_move(i, j, dir);
			}
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			monsters[i][j] = after_move_monsters[i][j]; 
		}
	}
}

int check_can_eat_monster_num(string st) {
	//st��ŭ ���� ���� �� ����

	memset(visited, false, sizeof(visited));

	int can_eat_monster_num = 0;

	int x = packman_r;
	int y = packman_c;

	for (int i = 0; i < 3; i++) {
		char c = st[i];
		int dir = c - '0';

		if (dir == 1 && inrange(x - 1, y)) { //��
			x--;

			if (!visited[x][y]) {
				can_eat_monster_num += monsters[x][y].size();
				visited[x][y] = true;
			}
		}
		else if (dir == 2 && inrange(x, y - 1)) { //��
			y--;

			if (!visited[x][y]) {
				can_eat_monster_num += monsters[x][y].size();
				visited[x][y] = true;
			}
		}
		else if (dir == 3 && inrange(x + 1, y)) { //��
			x++;

			if (!visited[x][y]) {
				can_eat_monster_num += monsters[x][y].size();
				visited[x][y] = true;
			}
		}
		else if (dir == 4 && inrange(x, y + 1)) { //��
			y++;

			if (!visited[x][y]) {
				can_eat_monster_num += monsters[x][y].size();
				visited[x][y] = true;
			}
		}
		else {
			return - 1;
		}
	}

	return can_eat_monster_num;
}
void packman_move() {
	//�� 3ĭ�� �̵��ϰ� �ȴ�.

	vector<pair<int, string>> v;

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				char c1 = i + '0';
				char c2 = j + '0';
				char c3 = k + '0';
				string st = "";
				st += c1;
				st += c2;
				st += c3;
				int can_eat_monster_num = check_can_eat_monster_num(st);

				if (can_eat_monster_num != -1) {
					v.push_back({ can_eat_monster_num, st });
				}
				
			}
		}
	}

	sort(v.begin(), v.end(), compare);

	string move_info = v.front().second;

	for (int i = 0; i < 3; i++) {
		int dir = move_info[i] - '0'; //����

		if (dir == 1) { //��
			packman_r--;
		}
		else if (dir == 2) { //��
			packman_c--;
		}
		else if (dir == 3) { //��
			packman_r++;
		}
		else { //��
			packman_c++;
		}

		//��ü ����
		int size = monsters[packman_r][packman_c].size();
		for (int k = 0; k < size; k++) {
			dead_monsters_bodys[packman_r][packman_c].push_back(3);
		}
		monsters[packman_r][packman_c].clear();
	}
}

void all_monster_copy_complete() {
	//���� ���� �ϼ�

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int size = monster_eggs[i][j].size();
			for (int k = 0; k < size; k++) {
				monsters[i][j].push_back(monster_eggs[i][j][k]); 
			}
			monster_eggs[i][j].clear();
		}
	}
}

void dead_monsters_arrange() {
	//��ü ����

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int size = dead_monsters_bodys[i][j].size();

			if (size == 0) {
				continue;
			}
			sort(dead_monsters_bodys[i][j].rbegin(), dead_monsters_bodys[i][j].rend());
			for (int k = size - 1; k >= 0; k--) {
				if (dead_monsters_bodys[i][j][k] == 1) {
					dead_monsters_bodys[i][j].pop_back();
				}
				else {
					dead_monsters_bodys[i][j][k] --;
				}
			}

		}
	}
}
void one_turn() {
	
	all_monster_copy_try();

	all_monster_move();

	packman_move();

	all_monster_copy_complete();

	dead_monsters_arrange();

}
void solution() {

	for (int i = 0; i < t; i++) {
		one_turn();
	}

	int ans = 0;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			ans += monsters[i][j].size();
		}
	}
	cout << ans;
}
void input() {
	cin >> m >> t;
	cin >> packman_r >> packman_c;

	for (int i = 0; i < m; i++) {
		int r, c; //���� ��ġ
		int d; //���� ���� ����
		cin >> r >> c >> d;
		monsters[r][c].push_back(d);
	}

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
