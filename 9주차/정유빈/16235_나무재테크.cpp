#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int n, m, k;

int nutrient[11][11]; //양분
int plus_nutrient[11][11];

deque<int> trees[11][11];

int dx[9] = { -1,-1,-1,0,0,1,1,1 };
int dy[9] = { -1,0,1,-1,1,-1,0,1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void spring() {
	//나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다.
	//하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다.
	//만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 죽는다.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (trees[i][j].size() > 0) {

				sort(trees[i][j].begin(), trees[i][j].end()); //나이가 적은 나무부터

				for (int k = 0; k < trees[i][j].size(); k++) {
					int age = trees[i][j][k];

					//땅의 양분을 먹을 수 있으면
					if (nutrient[i][j] >= age) {
						nutrient[i][j] -= age; // 양분을 먹고
						trees[i][j][k] += 1; //나이가 증가한다.
					}
					else {
						trees[i][j][k] *= -1; //나무 죽은 표시
					}
				}

			}
		}
	}
}

void summer() {
	// 봄에 죽은 나무가 양분으로 변하게 된다. 
	// 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다. 
	// 소수점 아래는 버린다.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			
			//나무가 있으면
			if (trees[i][j].size() > 0) {
	
				int size = trees[i][j].size();

				for (int k = size - 1; k >= 0; k--) {

					if (trees[i][j][k] < 0) { //죽은 나무면
						trees[i][j][k] *= -1;
						int plus = trees[i][j][k] / 2; 
						nutrient[i][j] += plus;
						trees[i][j].pop_back();
					}
					else {
						break;
					}
				}
			}
		}
	}
}

void authum() {
	//나무가 번식한다.

	vector<int> plus_trees[11][11];

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (trees[i][j].size() > 0) {

				for (int k = 0; k < trees[i][j].size(); k++) {
					if (trees[i][j][k] % 5 == 0) { //5의 배수이면

						for (int t = 0; t < 8; t++) { //인접한 8개 칸에 나이가 1인 나무가 생긴다.

							int nx = i + dx[t];
							int ny = j + dy[t]; 

							if (inrange(nx, ny)) {
								plus_trees[nx][ny].push_back(1);
							}
						}
					}
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < plus_trees[i][j].size(); k++) {
				trees[i][j].push_front(plus_trees[i][j][k]);
			}
		}
	}
}

void winter() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			nutrient[i][j] += plus_nutrient[i][j];
		}
	}
}
void one_year() {

	spring();
	summer();
	authum();
	winter();
	
}
void solution() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			nutrient[i][j] = 5;
		}
	}

	for (int i = 0; i < k; i++) {
		one_year();
	}

	int ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += trees[i][j].size();
		}
	}
	
	cout <<  ans;
}

void input() {

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> plus_nutrient[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		trees[x][y].push_back(z);
	}


}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
