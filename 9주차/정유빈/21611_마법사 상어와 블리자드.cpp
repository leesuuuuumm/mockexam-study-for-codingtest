#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
int m;
int map[50][50];

vector<pair<int, int>> v;

int shark_x;
int shark_y;

int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,-1,1 };

vector<int> gusul;
vector<pair<int, int>> gusul_info;

int bomb_cnt[4];

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void bleezard_magic(int di, int si) {
	//di�������� siĭ �����Ѵ�.

	for (int i = 1; i <= si; i++) {
		int nx = shark_x + i * dx[di];
		int ny = shark_y + i * dy[di];

		if (inrange(nx, ny)) {
			map[nx][ny] = -1;
		}
	}
}

void gusul_collect() {

	gusul.clear();

	int x = shark_x;
	int y = shark_y;

	for (int i = 1; i < n; i += 2) {

		//����
		for (int j = 0; j < i; j++) {
			y -= 1;

			if (map[x][y] != -1 && map[x][y] != 0) {
				gusul.push_back(map[x][y]);
			}
		}

		//�Ʒ�
		for (int j = 0; j < i; j++) {
			x += 1;

			if (map[x][y] != -1 && map[x][y] != 0) {
				gusul.push_back(map[x][y]);
			}
		}

		//������
		for (int j = 0; j < i + 1; j++) {
			y += 1;

			if (map[x][y] != -1 && map[x][y] != 0) {
				gusul.push_back(map[x][y]);
			}
		}

		//����
		for (int j = 0; j < i + 1; j++) {
			x -= 1;

			if (map[x][y] != -1 && map[x][y] != 0) {
				gusul.push_back(map[x][y]);
			}
		}
	}

	for (int i = 1; i < n; i++) {
		//���� 

		y -= 1;

		if (map[x][y] != -1 && map[x][y] != 0) {
			gusul.push_back(map[x][y]);
		}
	}
}

void gusul_put() {

	memset(map, 0, sizeof(map));

	int x = shark_x;
	int y = shark_y;
	int cnt = 0;

	for (int i = 1; i < n; i += 2) {

		//����
		for (int j = 0; j < i; j++) {
			y -= 1;

			if (cnt >= gusul.size()) {
				return;
			}
			map[x][y] = gusul[cnt++];
		}

		//�Ʒ�
		for (int j = 0; j < i; j++) {
			x += 1;

			if (cnt >= gusul.size()) {
				return;
			}
			map[x][y] = gusul[cnt++];
		}

		//������
		for (int j = 0; j < i + 1; j++) {
			y += 1;

			if (cnt >= gusul.size()) {
				return;
			}
			map[x][y] = gusul[cnt++];
		}

		//����
		for (int j = 0; j < i + 1; j++) {
			x -= 1;

			if (cnt >= gusul.size()) {
				return;
			}
			map[x][y] = gusul[cnt++];
		}
	}

	for (int i = 1; i < n; i++) {
		//���� 
		
		y -= 1;

		if (cnt >= gusul.size()) {
			return;
		}
		map[x][y] = gusul[cnt++];
	}

}
void gusul_move() {

	gusul_collect(); //������ gusul ���Ϳ� �����ϰ�
	gusul_put(); //������ ���´�.

}

void gusul_num_calculate() {
	//���� ���� ���

	gusul_info.clear();

	int cnt = 1;
	//���� ���ڶ� ����
	for (int i = 1; i < gusul.size(); i++) {


		int num = gusul[i];

		//�ٸ� �����̸�
		if (gusul[i - 1] != gusul[i]) {
			gusul_info.push_back({ gusul[i - 1], cnt });
			cnt = 1;

			if (i == gusul.size() - 1) { //������ ������ ��´�.
				gusul_info.push_back({ gusul[i], cnt });
			}
			continue;
		}

		//���� �����̸�
		cnt++;

		//������ ������ ��´�.
		if (i == gusul.size() - 1) {
			gusul_info.push_back({ gusul[i], cnt });
		}
	}

	if (gusul.size() == 1) {
		gusul_info.push_back({ gusul[0], cnt });
	}

}
bool bomb() {
	//������ �����ϴ� �ܰ�

	bool again = false; //4�� �̻��� ������ �ٽ� 

	gusul_num_calculate();
	gusul.clear();

	for (int i = 0; i < gusul_info.size(); i++) {

		int num = gusul_info[i].first;
		int cnt = gusul_info[i].second;

		if (cnt >= 4) { //4�� �̻��̸� ���ش�.
			again = true;

			bomb_cnt[num] += cnt;
			continue; 
		}

		for (int j = 0; j < cnt; j++) {
			gusul.push_back(num);
		}
	}

	gusul_put();

	return again;
}

void gusul_cnt_put() {

	gusul_num_calculate();

	gusul.clear();

	for (int i = 0; i < gusul_info.size(); i++) {
		gusul.push_back(gusul_info[i].second);
		gusul.push_back(gusul_info[i].first);
	}

	gusul_put();
}
void solution() {

	shark_x = n / 2 + 1;
	shark_y = n / 2 + 1;

	for (int i = 0; i < m; i++) {
		int di = v[i].first;
		int si = v[i].second;

		bleezard_magic(di, si); 
		gusul_move();

		while (true) {
			bool flag = bomb();

	

			if (!flag) {
				break;
			}
		}
		
		gusul_cnt_put(); //���� ������ŭ ���´�.
	}


	long long ans = 0;
	for (int i = 1; i <= 3; i++) {
		ans += i * bomb_cnt[i];
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

	for (int i = 0; i < m; i++) {
		int di, si;
		cin >> di >> si;
		v.push_back({ di,si });
	}

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}