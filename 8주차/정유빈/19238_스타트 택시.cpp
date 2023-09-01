#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int m;
int fuel;

int map[21][21];
int dist[21][21];
bool visited[21][21];

int taxi_x, taxi_y;
pair<int, int> customer[21][21];
//�� �°����� ������ ����

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

int bfs(int start_x, int start_y, int end_x, int end_y) {

	memset(visited, false, sizeof(visited));

	queue<pair<pair<int, int>, int>> q;
	q.push({ { start_x, start_y }, 0 });
	visited[start_x][start_y] = true;

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		if (a == end_x && b == end_y) {
			return d;
		}

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] == 0) {
				visited[nx][ny] = true;
				q.push({ {nx,ny}, d + 1 });
			}
		}
	}

	//������ �� ������
	return -1;
}
bool taxi_go() {
	//�ýð� �մ��¿췯 ����.
	memset(visited, false, sizeof(visited));

	//�¿� �� �ִ� �մ� ��ġ ����
	vector<pair<int, pair<int, int>>> v; 

	queue<pair<pair<int, int>, int>> q;
	q.push({ {taxi_x, taxi_y}, 0 });
	visited[taxi_x][taxi_y] = true;

	dist[taxi_x][taxi_y] = 0;

	if (customer[taxi_x][taxi_y].first != 0) {
		v.push_back({ 0, { taxi_x, taxi_y }});
	}

	while (!q.empty()) {

		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && map[nx][ny] == 0 && !visited[nx][ny]) {
				visited[nx][ny] = true;

				dist[nx][ny] = d + 1;
				q.push({ {nx,ny}, d + 1 });

				//���� �� �ڸ��� �մ��� ������
				if (customer[nx][ny].first != 0) {
					v.push_back({ d + 1, {nx,ny} });
				}
			}
		}
	}

	sort(v.begin(), v.end());

	//�¿� �մ��� ���ٸ�
	if (v.size() == 0) {
		return false;
	}

	//�¿���� �մ� ��� ��ġ
	int customer_start_x = v[0].second.first;
	int customer_start_y = v[0].second.second;
	int taxi_customer_dist = v[0].first; //�ýð� �մ� �¿� ������ �Ÿ�

	//�մ��� �¿� �� �ִٸ�
	if (fuel >= taxi_customer_dist) {
		fuel -= taxi_customer_dist;
	}
	else {
		return false;
	}

	//�¿���� �մ� ���� ��ġ
	int customer_end_x = customer[customer_start_x][customer_start_y].first;
	int customer_end_y = customer[customer_start_x][customer_start_y].second;

	customer[customer_start_x][customer_start_y] = { 0,0 };

	//�մ� ��������� ���������� �Ÿ�
	int customer_start_to_end = bfs(customer_start_x, customer_start_y, customer_end_x, customer_end_y);

	//�մ��� ���������� �¿� �� �ִٸ�
	if (fuel >= customer_start_to_end && customer_start_to_end != -1) {
		fuel += customer_start_to_end;
	}
	else {
		return false;
	}

	//�ýô� �մ��� ������ ��ġ
	taxi_x = customer_end_x;
	taxi_y = customer_end_y;
	return true;

}

void solution() {
	
	for (int i = 0; i < m; i++) {
		bool possible = taxi_go();

		if (!possible) {
			cout << -1;
			exit(0);
		}
	}
	
	cout << fuel;
}
void input() {

	cin >> n >> m >> fuel;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	cin >> taxi_x >> taxi_y;

	for (int i = 0; i < m; i++) {
		int start_x, start_y;
		int end_x, end_y;

		cin >> start_x >> start_y >> end_x >> end_y;
		customer[start_x][start_y] = { end_x, end_y };
	}

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}