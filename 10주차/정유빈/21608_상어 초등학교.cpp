#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int map[21][21];

int student_seq[401];


set<int> like_student[401];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int score[5] = { 0,1,10,100,1000 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void  most_vincan(int student_num, vector<pair<int,int>> v) {
	//°¡Àå ºóÄ­ÀÌ °¡Àå ¸¹Àº Ä­

	int most_vincan_no = 0;

	vector<pair<int,pair<int, int>>> most_vincan_v;

	for (int i = 0; i < v.size(); i++) {
		int x = v[i].first;
		int y = v[i].second;

		int vincan = 0;

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];

			if (inrange(nx, ny) && map[nx][ny] == 0) {
				vincan++;
			}
		}

		if (most_vincan_no < vincan) {
			most_vincan_v.clear();
			most_vincan_v.push_back({-vincan,{x, y }});
			most_vincan_no = vincan;
		}
		else if (most_vincan_no == vincan) {
			most_vincan_v.push_back({ -vincan, {x,y} });
		}

	}

	sort(most_vincan_v.begin(), most_vincan_v.end());

	map[most_vincan_v[0].second.first][most_vincan_v[0].second.second] = student_num;

}

vector <pair<int, int>> find_most_like_student(int student_num) {

	vector <pair<int, int>> like_student_v;
	int most_like_student_no = 0;


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

			if (map[i][j] != 0) {
				continue;
			}

			set<int> like_students = like_student[student_num];
			int like_student_no = 0;

			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny)) {

					//ÁÖÀ§ »ç¶÷
					int num = map[nx][ny];

					if (like_students.find(num) != like_students.end()) {
						like_student_no++;
					}
				}
			}
//			cout << "i: " << i << " j: " << j << " like_student_no: " << like_student_no << "\n";

			if (most_like_student_no < like_student_no) {
				most_like_student_no = like_student_no;
				like_student_v.clear();
				like_student_v.push_back({ i,j });
			}
			else if (most_like_student_no == like_student_no) {
				like_student_v.push_back({ i,j });
			}
		}
	}

//	cout << "ÁÁ¾ÆÇÏ´Â ÀÚ¸®" << "\n";

//	cout << "size: " << like_student_v.size() << "\n";

	return like_student_v;
}
void sit_down(int student_num) {
	//¾É±â

	vector<pair<int, int>> v = find_most_like_student(student_num);

	if (v.size() == 1) {
		//°¡Àå ºóÄ­ÀÌ ¸¹Àº Ä­ÀÌ ÇÏ³ª¸é
		map[v[0].first][v[0].second] = student_num;
		return;
	}

	most_vincan(student_num, v);


}

void print() {

	cout << "----------" << "\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}

void output() {

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int student_num = map[i][j];
			set<int> like_student_v	= like_student[student_num];

			int like_student_no = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny)){

					int next_student_no = map[nx][ny];

					if (like_student_v.find(next_student_no) != like_student_v.end()) {
						like_student_no++;
					}
				}
			}
		//	cout << "student_num: " << student_num << "\n";
		//	cout << "like_stduent_no: " << like_student_no << "\n";

			ans += score[like_student_no];
		}
	}

	cout << ans;
}
void solution() {

	//sit_down(4);
	//print();
	//sit_down(3);

	for (int i = 0; i < n * n; i++) {
		int student_num = student_seq[i];
		sit_down(student_num);
	//	print();
	}

	output();
	
}


void input() {

	cin >> n;

	for (int i = 0; i < n * n; i++) {

		int student_num; 
		cin >> student_num;

		set<int> like_student_set;

		for (int j = 0; j < 4; j++) {
			int like_student_num;
			cin >> like_student_num;
			like_student_set.insert(like_student_num);
		}
		
		student_seq[i] = student_num;
		like_student[student_num] = like_student_set;
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}