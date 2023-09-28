#include <iostream>
#include <vector>

using namespace std;

int n;
int m;

int map[51][51];
//0: ºóÄ­, 1: »ç¶÷, 2: º´¿ø

vector<pair<int, int>> people;
vector<pair<int, int>> hospitals; 
int ans = 999999;

void check(vector<pair<int, int>> comb) {

	int tmp_ans = 0;

	for (int i = 0; i < people.size(); i++) {
		int people_x = people[i].first;
		int people_y = people[i].second;

		int min_dist = 9999999;

		for (int j = 0; j < comb.size(); j++) {
			int hospital_x = comb[j].first;
			int hospital_y = comb[j].second;

			int dist = abs(people_x - hospital_x) + abs(people_y - hospital_y);

			min_dist = min(dist, min_dist);
 		}
		tmp_ans += min_dist; 
	}

	ans = min(ans, tmp_ans);
}
void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {

	if (r == 0) {
		check(comb);
		return;
	}
	else if (arr.size() == depth) {
		return;
	}
	else {

		comb[idx] = arr[depth];

		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}
void solution() {

	vector<pair<int, int>> comb(m);

	combination(hospitals, comb, m, 0, 0);

	cout << ans;

}
void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n;j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				hospitals.push_back({ i,j });
			}
			else if (map[i][j] == 1) {
				people.push_back({ i,j });
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