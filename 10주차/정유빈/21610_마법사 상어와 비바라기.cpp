#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
int m;
int map[51][51];

pair<int, int> cloud_move_info[101];
bool iscloud[51][51];

int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int times = 0;

vector<pair<int, int>> clouds;

int di, si;

pair<int, int> cloud_move(int x, int y) {
	//(x,y) 구름이 이동한다.

	di = cloud_move_info[times].first; //방향
	si = cloud_move_info[times].second; //칸 수

	int nx = x + dx[di] * si;
	int ny = y + dy[di] * si;


	if (nx == 0) {
		nx = n;
	}
	else if (nx > n) {

		if (nx % n == 0) {
			nx = n;
		}
		else {
			nx = nx % n;
		}
	}
	else if(nx < 0) {
		
		if (abs(nx) % n == 0) {
			nx = n;
		}
		else {
			nx = n - abs(nx) % n;
		}
	}

	if (ny == 0) {
		ny = n;
	}
	else if (ny > n) {

		if (ny % n == 0) {
			ny = n;
		}
		else {
			ny = ny % n;
		}
	}
	else if(ny < 0) {

		if (abs(ny) % n == 0) {
			ny = n;
		}
		else {
			ny = n - abs(ny) % n;
		}
	}

	return { nx,ny };

}

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void all_cloud_move() {
	//모든 구름이 di 방향으로 si칸 이동한다.

	vector<pair<int, int>> new_clouds;

	int size = clouds.size();

	for (int i = 0; i < size; i++) {
		int cloud_x = clouds[i].first;
		int cloud_y = clouds[i].second;

		pair<int,int> new_cloud = cloud_move(cloud_x, cloud_y);

		new_clouds.push_back(new_cloud);
	}

	clouds = new_clouds;
}

void rain() {

	int size = clouds.size();

	for (int i = 0; i < size; i++) {
		map[clouds[i].first][clouds[i].second]++;
	}
}

void all_cloud_plus_rain() {
	//대각선에 물이 생긴다.

	vector < pair<pair<int, int>, int>> plus_info; 

	int cloud_dx[4] = { 1,1,-1, -1 };
	int cloud_dy[4] = { -1,1,1,-1 };

	int size = clouds.size();

	for (int i = 0; i < size; i++) {
		
		int cloud_x = clouds[i].first;
		int cloud_y = clouds[i].second; 
		
		int time = 0;

		for (int j = 0; j < 4; j++) {
			int nx = cloud_x + cloud_dx[j];
			int ny = cloud_y + cloud_dy[j];

			if (inrange(nx, ny) && map[nx][ny] > 0) {
				time++;
			}
		}
		plus_info.push_back({ {cloud_x, cloud_y}, time });
	}

	for (int i = 0; i < plus_info.size(); i++) {
		map[plus_info[i].first.first][plus_info[i].first.second] += plus_info[i].second;
	}

}

void not_cloud_make_cloud() {
	//구름이 아닌 칸들 물의 양이 2인 칸에 구름이 생긴다.

	memset(iscloud, false, sizeof(iscloud));

	for (int i = 0; i < clouds.size(); i++) {
		iscloud[clouds[i].first][clouds[i].second] = true;
	}


	clouds.clear();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] >= 2 && !iscloud[i][j]) {
				clouds.push_back({ i,j });
				map[i][j] -= 2;
			}
		}
	}
}

void one_turn() {
	
	all_cloud_move();

	rain();

	all_cloud_plus_rain();

	not_cloud_make_cloud();
}
void solution() {

	clouds.push_back({ n, 1 });
	clouds.push_back({ n,2 });
	clouds.push_back({ n - 1, 1 });
	clouds.push_back({ n - 1, 2 });

	for (times = 0; times < m; times++) {
		one_turn();
	}

	int ans = 0; 

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += map[i][j];
		}
	}

	cout <<  ans;

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
		cloud_move_info[i] = { di,si };
	}

}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}