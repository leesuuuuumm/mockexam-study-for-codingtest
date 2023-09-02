#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n; //���� ũ��
int m; //����� ����
int map[21][21];
bool visited[21][21];

int baby_shark_size = 2; 
int eating_fish_cnt = 0;

int baby_shark_x; //�Ʊ� ��� ��
int baby_shark_y; //�Ʊ� ��� ��

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ans = 0;

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
bool find_eating_fish() {
	//���� ����⸦ ã�´�.

	memset(visited, false, sizeof(visited));
	//���� �� �ִ� ����� �Ÿ��� ��ġ
	vector < pair<int, pair<int, int>>> v;

	//��ġ�� �Ÿ�
	queue<pair<pair<int, int>, int>> q;

	q.push({ {baby_shark_x, baby_shark_y}, 0 });
	visited[baby_shark_x][baby_shark_y] = true;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			//�ڽ��� ũ�⺸�� ���ų� ������
			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] <= baby_shark_size) {
				q.push({ {nx,ny}, d + 1 });
				visited[nx][ny] = true;

				//���� �� �ִ� ������
				if (map[nx][ny] < baby_shark_size && map[nx][ny] != 0) {
					v.push_back({ d + 1, {nx,ny} });
				}
			}
		}
	}


	if (v.size() == 0) {
		return false;
	}

	sort(v.begin(), v.end());

	ans += v[0].first;

	//���� �Ʊ��� ��ġ�� 0���� 
	map[baby_shark_x][baby_shark_y] = 0;

	//�̷� �Ʊ��� ��ġ�� 9��
	map[v[0].second.first][v[0].second.second] = 9;

	baby_shark_x = v[0].second.first;
	baby_shark_y = v[0].second.second;

	//���� ����� ���� 1 ����
	eating_fish_cnt++;


	//�ڽ��� ũ��� ���� ���� ����⸦ ���� ������ ũ�� 1 ����
	if (eating_fish_cnt == baby_shark_size) {
		baby_shark_size++;
		eating_fish_cnt = 0;
	}

	return true;
}
void solution() {
	
	for (int times = 0;; times++) {
		bool eating = find_eating_fish();

		//�� �Ծ�����
		if (!eating) {
			cout <<  ans;
			exit(0);
		}
	}
	

}
void input() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];

			if (map[i][j] == 9) {
				baby_shark_x = i;
				baby_shark_y = j;
			}
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