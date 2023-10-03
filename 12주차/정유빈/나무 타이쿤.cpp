#include <iostream>
#include <vector>

using namespace std;

int n; //격자 크기
int m; //리브로수 키우는 총 년 수
int map[16][16];

vector<pair<int, int>> nutrients; //특수 영양제

vector<pair<int, int>> move_rules; //이동 방향과 이동 칸 수

int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int dy[9] = { 0,1,1,0,-1,-1,-1,0,1 };

pair<int, int> check_pos(int x, int y) {

	if (n < x) {

		if (x % n == 0) {
			x = n;
		}
		else {
			x = x % n;
		}
	}
	else if (x == 0) {
		x = n; 
	}
	else if(x < 0) {
		x = n - abs(x) % n;
	}

	if (n < y) {

		if (y % n == 0) {
			y = n;
		}
		else {
			y = y % n;
		}
	}
	else if (y == 0) {
		y = n;
	}
	else if (y < 0) {
		y = n - abs(y) % n;
	}

	return { x,y };
}

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false; 
}

void nutrients_move(int d, int p) {
	
	vector<pair<int,int>> new_nutrients;

	int size = nutrients.size();
	for (int i = 0; i < size; i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;

		int nx = x + dx[d] * p;
		int ny = y + dy[d] * p;

		pair<int, int> p = check_pos(nx, ny);
		nx = p.first;
		ny = p.second; 

		new_nutrients.push_back({ nx, ny });
	}

	nutrients = new_nutrients;
}

void nutrients_make_grow() {
	//특수영양제가 있는 땅의 리브로수는 높이가 증가한다.

	int size = nutrients.size();

	//특수 영양제가 있는 땅의 리브로수는 높이가 1 증가한다.
	for (int i = 0; i < size; i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;

		map[x][y]++;
	}
	
	//대각선으로 인접한 높이 1이상의 리브로수 개수만큼 높이가 증가한다
	int ndx[4] = {1,1, -1, -1};
	int ndy[4] = {1, -1,1,-1 };

	int plus_map[15][15] = { 0, };

	for (int i = 0; i < size; i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;

		int cnt = 0;
		for (int k = 0; k < 4; k++) {
			int nx = x + ndx[k];
			int ny = y + ndy[k];

			if (inrange(nx,ny) && map[nx][ny] > 0) {
				cnt++;
			}
		}

		plus_map[x][y] += cnt;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += plus_map[i][j];
		}
	}

}

void nutrients_change() {

	bool isnutrients[15][15] = { false, };
	int size = nutrients.size();
	
	vector<pair<int, int>> new_nutrients;

	//1: 원래 있던 영양제 위치
	for (int i = 0; i < size; i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;

		isnutrients[x][y] = true;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!isnutrients[i][j] && map[i][j] >= 2) {
				map[i][j] -= 2;
				new_nutrients.push_back({ i,j });
			}
		}
	}

	nutrients = new_nutrients;
}
void one_year(int d, int p) {

	nutrients_move(d, p);
	nutrients_make_grow();
	nutrients_change();
}

void first_nutrient() {

	nutrients.push_back({ n, 1 });
	nutrients.push_back({ n,2 });
	nutrients.push_back({ n - 1, 1 });
	nutrients.push_back({ n - 1,2 });
}
void solution() {

	first_nutrient();

	for (int i = 0; i < m; i++) {
		int d, p;
		d = move_rules[i].first; //이동 방향
		p = move_rules[i].second; //이동 칸 수
		one_year(d, p);
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += map[i][j];
		}
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
		int d, p;
		cin >> d >> p;
		move_rules.push_back({ d,p });
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution(); 
}