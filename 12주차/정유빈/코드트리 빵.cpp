#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>


using namespace std;

int n; //���� ũ��
int m; //��� ��

int map[16][16];
int dist[16][16];
bool visited[16][16];
bool can_pass[16][16];

pair<int, int> convenience_stores[250]; //������ ��ġ

int dx[4] = { 1,0,0,-1 };
int dy[4] = { 0,-1,1,0 };

pair<int, int> people_pos[250];
bool arrived[150];
int times = 1;

int convenince_arrive_num = 0;

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

pair<int,int> go_back_to_basecamp_bfs(int target_x, int target_y, int x, int y) {

	memset(visited, false, sizeof(visited));

	queue<pair<int, int>> q;
	q.push({ target_x, target_y });

	while (!q.empty()) {
		int a = q.front().first;
		int b = q.front().second;


		if (dist[a][b] == 1) {
			return { a,b };
		}
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];

			if (inrange(nx, ny) && dist[nx][ny] < dist[a][b]) {
				q.push({ nx,ny });
			}
		}
	}

}

pair<int,int> move_bfs(int x, int y, int target_x, int target_y) {

	memset(visited, false, sizeof(visited));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = 999999;
		}
	}

	queue<pair<pair<int, int>, int>> q;

	q.push({ {x,y}, 0 });
	visited[x][y] = true;
	dist[x][y] = 0;

	while (!q.empty()) {
		int a = q.front().first.first;
		int b = q.front().first.second;
		int d = q.front().second;

		q.pop();

		if (a == target_x && b == target_y) {
			continue;
		}

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i];
			
			if (inrange(nx, ny) && map[nx][ny] == 0 && d + 1 < dist[nx][ny] && !visited[nx][ny] && can_pass[nx][ny]) {
				dist[nx][ny] = d + 1;
				visited[nx][ny] = true;
				q.push({ {nx,ny}, d + 1 });
			}
		}
	}

	return go_back_to_basecamp_bfs(target_x, target_y, x, y);
}
void one_people_move(int people_num) {
	//people_num�� �����δ�.

	int x = people_pos[people_num].first;
	int y = people_pos[people_num].second;

	int convenience_store_x = convenience_stores[people_num].first;
	int convenience_store_y = convenience_stores[people_num].second;



	//���� �̹� ������ �����ߴٸ� ����
	if (x == convenience_store_x && y == convenience_store_y) {
		return;
	}

	pair<int, int> next_pos = move_bfs(x, y, convenience_store_x, convenience_store_y);

	//���� ���������� �� ��, ans�� ���� ��
	if (next_pos.first == convenience_store_x && next_pos.second == convenience_store_y) {
		arrived[people_num] = true;
		convenince_arrive_num++;
		arrived[people_num] = true;

		if (convenince_arrive_num == m) {
			cout << times << "\n";
			exit(0);
		}
	}

	people_pos[people_num] = next_pos;
	
	//������ ���� ����������
	if (next_pos.first == convenience_store_x && next_pos.second == convenience_store_y) {
		can_pass[convenience_store_x][convenience_store_y] = false;
	}
}
void all_people_move() {
	//��� ������� �����δ�. 

	for (int i = 1; i <= m; i++) {

		//���� ���̽�ķ�� ���� ���� �ʾҴٸ�
		if (i >= times) {
			break;
		}
		one_people_move(i);
	}
}

vector<pair<int, int>> bfs(int x, int y) {
	//���� ������ �ִ� ���̽�ķ���� ����.
	
	memset(visited, false, sizeof(visited)); 

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dist[i][j] = 9999999;
		}
	}

	int min_dist = 999999;
	vector<pair<int, int>> conveninece_store_v;

	//��ġ�� �Ÿ�
	queue<pair<pair<int, int>, int>> q;
	q.push({ { x,y }, 0 });
	visited[x][y] = true;
	dist[x][y] = 0;

	while (!q.empty()) {
		int a = q.front().first.first;
		int b = q.front().first.second; 
		int d = q.front().second; 

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = a + dx[i];
			int ny = b + dy[i]; 

			
			if (inrange(nx, ny) && can_pass[nx][ny] && !visited[nx][ny] && d + 1 < dist[nx][ny]) {
				q.push({ {nx,ny}, d + 1 });
				visited[nx][ny] = true;

				//����� ���̽�ķ���� �ִٸ�
				if (map[nx][ny] == 1) {

					if (min_dist > d + 1) {
						min_dist = d + 1;
						conveninece_store_v.clear();
						conveninece_store_v.push_back({ nx,ny });
					}
					else if (min_dist == d + 1) {
						conveninece_store_v.push_back({ nx,ny });
					}
				}
			}
		}
	}

	return conveninece_store_v;
}

void t_people_go_basecamp(int people_num) {
	//t�п� t�� ����� �ڽ��� ���� ���� �������� ���� ������ �ִ� ���̽� ķ���� ����.

	int conveninece_store_x = convenience_stores[people_num].first;
	int conveninece_store_y = convenience_stores[people_num].second;

	vector<pair<int,int>> base_camp_pos = bfs(conveninece_store_x, conveninece_store_y);


	sort(base_camp_pos.begin(), base_camp_pos.end());

	int basecamp_x = base_camp_pos[0].first;
	int basecamp_y = base_camp_pos[0].second;

	//���� ���̽�ķ���� ������ �� ����
	can_pass[basecamp_x][basecamp_y] = false;

	//��� ��ġ ���̽�ķ���� 
	people_pos[people_num] = { basecamp_x, basecamp_y };
}
void one_minute() {

	all_people_move();

	if (times <= m) {
		t_people_go_basecamp(times);
	}
}
void solution() {

	memset(can_pass, true, sizeof(can_pass));

	for (times = 1;; times++) {
		one_minute();
	}

}
void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		convenience_stores[i] = { x,y };
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}