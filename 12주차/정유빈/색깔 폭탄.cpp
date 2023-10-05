#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int n; //���� ũ��
int m; //��ź ����

int map[21][21];
//-1 : ������ ��
//0: ������ ��ź
//1 ~ m : �ٸ� �� ��ź

bool visited[21][21];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int ans = 0;

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true; 
	}
	return false;
}

bool compare(pair<int, int> p1, pair<int, int> p2) {
	//���� ū ���ʷ�, ���� ���� ���ʷ�
	if (p1.first == p2.first) {
		return p1.second < p2.second;
	}
	return p1.first > p2.first; 
}

bool compare2(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2) {
	if (p1.first.first == p2.first.first) {
		return p1.first.second < p2.first.second;
	}
	return p1.first.first > p2.first.first;
}

bool compare3(pair<int, vector<pair<int, int>>> p1, pair<int, vector<pair<int, int>>> p2) {

	return p1.first < p2.first;
}
pair<int, vector<pair<int, int>>> bfs(int x, int y) {
	
	//�������� ���ԉ����
	bool tmp_visited_red_map[21][21] = { false, };
	
	int red_bomb_cnt = 0;

	int bomb_c = map[x][y]; 

	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;
	vector<pair<int, int>> tmp_v; 

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;

		if (map[a][b] == 0) {
			red_bomb_cnt++;
		}
		tmp_v.push_back({ a,b });

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny)) {

				if (!visited[nx][ny] && map[nx][ny] == bomb_c) {
					q.push({ nx,ny });
					visited[nx][ny] = true;
				}

				if (map[nx][ny] == 0 && !tmp_visited_red_map[nx][ny]) {
					tmp_visited_red_map[nx][ny] = true;
					q.push({ nx,ny });
				}
				
			}
		}
	}

	return { red_bomb_cnt, tmp_v };

}

void find_biggest_bomb() {
	//���� ū ��ź ������ ã�´�.

	memset(visited, false, sizeof(visited));

	//������ ��ź ������ ��ź ��ġ��
	vector<pair<int,vector<pair<int, int>>>> biggest_bomb_v;
	int max_bomb_cnt = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] > 0 && !visited[i][j]) {
				pair<int, vector<pair<int, int>>> tmp_v = bfs(i, j);

				if (tmp_v.second.size() == 1) {
					continue;
				}

				if (tmp_v.second.size() > max_bomb_cnt) {
					max_bomb_cnt = tmp_v.second.size();
					biggest_bomb_v.clear();
					biggest_bomb_v.push_back(tmp_v);
				}
				else if (tmp_v.second.size() == max_bomb_cnt) {
					biggest_bomb_v.push_back(tmp_v);
				}
			}
		}
	}

	//�Ͷ߸� ��ź�� ���ٸ�
	if (biggest_bomb_v.size() == 0) {
		cout << ans;
		exit(0);
	}

	sort(biggest_bomb_v.begin(), biggest_bomb_v.end(), compare3);

	int mini_red_bomb_cnt = biggest_bomb_v[0].first;

	for (int i = biggest_bomb_v.size() - 1; i >= 0; i--) {
		if (biggest_bomb_v[i].first != mini_red_bomb_cnt) {
			biggest_bomb_v.pop_back();
		}
	}

	//�� ��ź ������ ������ �� ���� ���� ū ��ź ���� ����
	vector <pair<pair<int,int>, int>> gizun_row_biggest_v;
	//�������� ��ȣ

	for (int i = 0; i < biggest_bomb_v.size(); i++) {
		vector<pair<int, int>> tmp_v = biggest_bomb_v[i].second;

		sort(tmp_v.begin(), tmp_v.end(), compare);
		int tmp_v_x;
		int tmp_v_y;

		for (int j = 0; j < tmp_v.size(); j++) {
			int x = tmp_v[j].first;
			int y = tmp_v[j].second;

			if (map[x][y] != 0) { //�������� �ƴ϶��
				tmp_v_x = x;
				tmp_v_y = y;
				gizun_row_biggest_v.push_back({ {tmp_v_x, tmp_v_y}, i});
				break;
			}
		}

	}


	sort(gizun_row_biggest_v.begin(), gizun_row_biggest_v.end(), compare2);


	int disappear_bomb_idx = gizun_row_biggest_v[0].second;

	//������ ��ź
	vector<pair<int, int>> disappear_bomb_v = biggest_bomb_v[disappear_bomb_idx].second;
	
	int size = disappear_bomb_v.size();

	ans += size * size;

	for (int i = 0; i < size; i++) {	
		map[disappear_bomb_v[i].first][disappear_bomb_v[i].second] = -2;
	}

}

void gravity() {
	//�߷��� �ۿ��Ѵ�.
	//�� ���� ��������.

	for (int j = 1; j <= n; j++) {
		for (int i = n; i >= 1; i--) {
			if (map[i][j] >= 0) {
				int num = map[i][j];
				int nx = i;

				for (int k = i + 1; k <= n; k++) {
					if (map[k][j] == -2) { //��ĭ�̸� ������
						nx = k;
					}
					else {
						break;
					}
				}

				map[i][j] = -2;
				map[nx][j] = num;
			}
		}
	}
}

void rotate(int x, int y, int num) {

	int tmp_map[21][21];

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			tmp_map[i - 1][j - 1] = map[x + num - j][y + i - 1];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[x + i - 1][y + j - 1] = tmp_map[i - 1][j - 1];
		}
	}
}

void one_round() {

	find_biggest_bomb();

	gravity();


	for (int i = 1; i <= 3; i++) {
		rotate(1, 1, n);
	}

	gravity();

}
void solution() {

	while (true) {
		one_round();
	}
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