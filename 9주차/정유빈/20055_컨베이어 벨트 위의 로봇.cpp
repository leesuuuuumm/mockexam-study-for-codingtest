#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int n, k;
deque<pair<int,bool>> dq;
//내구도와 로봇 유무

int stage = 1;

void check_robot() {
	//로봇이 내린다.

	if (dq[n - 1].second) {
		dq[n - 1].second = false;
	}
}
void one_stage() {
	//벨트가 각 칸에 있는 로봇과 함께 한칸 회전한다.

	pair<int, int> back = dq.back();
	dq.pop_back();
	dq.push_front(back); 

	check_robot();

	//가장 먼저 벨트에 올라간 로봇부터,
	//벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동한다.
	//만약 이동할 수 없다면 가만히 있는다.
	//로봇이 이동하기 위해서는 이동하려는 칸에 로봇이 없으며
	//그 칸의 내구도가 1이상 남아 있어야 한다.

	if (dq[n - 2].second && !dq[n - 1].second && dq[n - 1].first > 0) {
		dq[n - 2].second = false;
		dq[n - 1].second = false; //n으로 가자마자 로봇을 내린다.
		dq[n - 1].first -= 1;
	}

	for (int i = n - 2; i >= 0; i--) {
		if (dq[i].second && !dq[i + 1].second && dq[i + 1].first > 0) {
			dq[i].second = false;
			dq[i + 1].second = true;
			dq[i + 1].first -= 1;
		}
	}
	
	//올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.

	if (dq[0].first > 0) {
		dq[0].second = true;
		dq[0].first -= 1;
	}

	//내구도가 0인 칸의 개수가 k개 이상이라면 과정을 종료한다.
	int cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (dq[i].first == 0) {
			cnt++;
		}
	}

	if (cnt >= k) {
		cout << stage << "\n";
		exit(0);
	}
}

void solution() {

	for (stage = 1;; stage++) {
		one_stage();
	}
}
void input() {

	cin >> n >> k;

	for (int i = 1; i <= 2 * n; i++) {
		int num;
		cin >> num;
		dq.push_back({num, false});
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}