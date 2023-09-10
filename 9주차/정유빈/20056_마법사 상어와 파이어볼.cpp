#include <iostream>
#include <vector>

using namespace std;

int n, m, k;

struct info {
	int mi; //����
	int si; //�ӷ�
	int di; //����
};

vector<info> map[51][51]; //���̾ ���ڰ� ��

int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };

pair<int, int> next_pos(int x, int y) {

	pair<int, int> p;

	if (x < 0) {
		p.first = n - abs(x)  % n;
	}
	else if (x == 0) {
		p.first = n;
	}
	else {

		if (x % n == 0) {
			p.first = n;
		}
		else {
			p.first = x % n;
		}
	}

	if (y < 0) {
		p.second = n - abs(y) % n;
	}
	else if (y == 0) {
		p.second = n;
	}
	else {

		if (y % n == 0) {
			p.second = n;
		}
		else {
			p.second = y % n;
		}
	}

	return p;
}
void one_stage() {
	//1. ��� ���̾�� �ڽ��� ���� di�� �ӷ� siĭ ��ŭ �̵��Ѵ�.

	vector<info> new_map[51][51];

	//��� ���̾�� �ڽ��� ���� di�� �ӷ� si��ŭ �̵��Ѵ�.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			vector<info> v = map[i][j];
			int size = v.size();

			for (int k = 0; k < size; k++) {
				int mi = v[k].mi;
				int si = v[k].si;
				int di = v[k].di;

				int nx = i + dx[di] * si;
				int ny = j + dy[di] * si;

				pair<int, int> next_p = next_pos(nx, ny);

				nx = next_p.first;
				ny = next_p.second;

				new_map[nx][ny].push_back({ mi,si,di });
			}
		}
	}


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = new_map[i][j];
		}
	}
}

void split(int x, int y) {
	//(x,y)�� �ִ� ���̾�� 4���� ����������.

	vector<info> v = map[x][y];

	int sum_mi = 0; //���� ��
	int sum_si = 0; //�ӷ� ��
	bool all_odd = true; //��� Ȧ������
	bool all_even = true; //��� ¦������

	for (int i = 0; i < v.size(); i++) {
		int mi = v[i].mi;
		int si = v[i].si;
		int di = v[i].di;

		sum_mi += mi;
		sum_si += si;

		if (di % 2 == 0) {
			all_odd = false;
		}
		else {
			all_even = false;
		}
	}

	int divided_mi = sum_mi / 5;
	int divided_si = sum_si / v.size();
	
	map[x][y].clear();

	//�������� ���̾�� ������ ��� Ȧ���̰ų� ��� ¦���̸�, 
	//������ 0, 2, 4, 6�� �ǰ�, �׷��� ������ 1, 3, 5, 7�� �ȴ�.

	if (divided_mi == 0) { //������ 0�� ���̾�� �Ҹ�Ǿ� ��������.
		return;
	}

	if (all_even || all_odd) {

		for (int i = 0; i < 4; i++) {
			
			map[x][y].push_back({divided_mi, divided_si,2 * i});
		}
	}
	else {

		for (int i = 0; i < 4; i++) {
			map[x][y].push_back({ divided_mi, divided_si,2 * i + 1});
		}
	}

	


}

void two_stage() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j].size() >= 2) {
				split(i, j);
			}
		}
	}
}

void solution() {

	for (int i = 0; i < k; i++) {
		one_stage();

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (map[i][j].size() >= 2) {
				}
			}
		}
		two_stage();
	}



	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			vector<info> v = map[i][j];
			int size = v.size();
			for (int k = 0; k < size; k++) {
				ans += v[k].mi;
			}
		}
	}

	cout <<  ans;

}
void input() {

	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		int ri, ci, mi, di, si;
		cin >> ri >> ci >> mi >> si >> di;

		map[ri][ci].push_back({mi,si,di});
	}

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}