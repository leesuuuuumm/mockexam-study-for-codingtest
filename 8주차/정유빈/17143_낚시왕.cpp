#include <iostream>

using namespace std;

int r; //�� ũ�� 
int c; //�� ũ��
int m; //��� ��
int map[101][101];
long ans = 0;

struct shark_info {
	int s; //�ӷ�
	int d; //�̵� ����
	int z; //ũ��
};

shark_info shark_map[101][101]; 

//1: ��, 2: �Ʒ�, 3: ������, 4: ����
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
	//�� ������ �� ��ġ�� ���� ����

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
			d = change_dir(d); //������ �ٲ۴�.
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
				//��ġ�� ����
  	
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

	//���ÿ��� �ִ� ���� �ִ� ��� �߿��� ���� ���� ����� �� ��´�.

	for (int row = 1; row <= r; row++) {
		if (shark_map[row][col].d != 0) { //�� ������
			ans += shark_map[row][col].z; //�� ��´�.
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