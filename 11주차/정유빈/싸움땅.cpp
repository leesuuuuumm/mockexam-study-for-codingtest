#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n; //격자 크기 
int m; //플레이어 수
int k; //라운드 수

vector<int> guns[21][21];
//0: 빈칸, 0보다 크면 총의 공격력

vector<int> players[21][21];
//플레이어들

struct info {
	int x; //위치
	int y;
	int d; //방향
	int s; //초기 능력치
	int gun; //총 있으면
};

info player[41];
int answer_point[41];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

int change_dir(int d) {

	if (d == 0) {
		return 2;
	}
	else if (d == 1) {
		return 3;
	}
	else if (d == 2) {
		return 0;
	}
	else {
		return 1;
	}
}
void one_player_move(int player_num) {
	//player_num이 움직인다

	//플레이어 위치
	int x = player[player_num].x;
	int y = player[player_num].y;
    
	//플레이어 방향
	int d = player[player_num].d;
	//플레이어 초기 능력치
	int s = player[player_num].s;
	int gun = player[player_num].gun;

	int nx = x + dx[d];
	int ny = y + dy[d];

	//격자를 벗어나면 정반대 방향으로 바꾸어서 1만큼 이동
	if (!inrange(nx, ny)) {
		d = change_dir(d);
		nx = x + dx[d];
		ny = y + dy[d];
	}

	player[player_num] = { nx,ny,d,s, gun };

	vector<int> v = players[x][y]; //4
	int idx = find(v.begin(), v.end(), player_num) - v.begin();
	players[x][y].erase(players[x][y].begin() + idx); //해당 플레이어 지운다
	players[nx][ny].push_back(player_num); //5,4

}

void one_player_compete(int player_num) {
	//player_num이 움직인 후 경쟁한다.

	int x = player[player_num].x;
	int y = player[player_num].y;
	int gun = player[player_num].gun;

	if (players[x][y].size() == 1) {
		//플레이어가 없다면

		sort(guns[x][y].begin(), guns[x][y].end());

		if (!guns[x][y].empty() && guns[x][y].back() > gun) {
			//해당 칸에 총이 있고 가지고 있는 총보다 세다면
			//가장 큰 총을 하나 빼앗는다.
			player[player_num].gun = guns[x][y].back();
			guns[x][y].pop_back();

			if (gun != 0) {
				guns[x][y].push_back(gun);
			}
		}
	}
	else {
		//플레이어가 있다면 두 플레이어가 싸운다.

		int player1_num = players[x][y][0];
		int player2_num = players[x][y][1];

		int player1_s = player[player1_num].s;
		int player1_gun = player[player1_num].gun;
		int player1_sum = player1_s + player1_gun;
		int player1_d = player[player1_num].d;

		int player2_s = player[player2_num].s;
		int player2_gun = player[player2_num].gun;
		int player2_sum = player2_s + player2_gun;
		int player2_d = player[player2_num].d;

		if ((player1_sum < player2_sum) || (player1_sum == player2_sum && (player1_s < player2_s))) {

			//player2의 합이 더 높으면 각 플레이어의 초기 능력치와 가지고 있는 총의 공격력의 합의 차이 포인트 획득
			answer_point[player2_num] += (player2_sum - player1_sum);

			//진 플레이어는 본인이 가지고 있는 총을 해당 격자에 내려놓는다.
			if (player1_gun != 0) {
				guns[x][y].push_back(player1_gun);
				player[player1_num].gun = 0; //총을 내려놓는다.
			}

			bool player1_move = false;

			

			for (int d = player1_d; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				//만약 격자 안이고 비어있다면
				if (inrange(nx, ny) && players[nx][ny].empty()) {
					//만약 총이 있다면
					sort(guns[nx][ny].begin(), guns[nx][ny].end());

					if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
						player[player1_num].gun = guns[nx][ny].back();
						guns[nx][ny].pop_back();
					}

					player1_move = true;

					//이동한다.
					int idx = find(players[x][y].begin(), players[x][y].end(), player1_num) - players[x][y].begin();
					players[x][y].erase(players[x][y].begin() + idx);
					player[player1_num].x = nx;
					player[player1_num].y = ny;
					player[player1_num].d = d;
					players[nx][ny].push_back(player1_num);
					break;
				}
			}

			if (!player1_move) {
				for (int d = 0; d < player1_d; d++) {
					int nx = x + dx[d];
					int ny = y + dy[d];

					if (inrange(nx, ny) && players[nx][ny].empty()) {
						//만약 격자 안이고 비어있다면
						//만약 총이 있다면
						sort(guns[nx][ny].begin(), guns[nx][ny].end());

						if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
							player[player1_num].gun = guns[nx][ny].back();
							guns[nx][ny].pop_back();
						}

						//이동한다.
						int idx = find(players[x][y].begin(), players[x][y].end(), player1_num) - players[x][y].begin();
						players[x][y].erase(players[x][y].begin() + idx);

						player[player1_num].x = nx;
						player[player1_num].y = ny;
						player[player1_num].d = d;
						players[nx][ny].push_back(player1_num);
						break;
					}
				}
			}

			//이긴 플레이어는 승리한 칸에 떨어져 있는 총과 원래 들고 있는 총 중 가장 공격력이 높은 총을 획득한다.
			sort(guns[x][y].begin(), guns[x][y].end());
			if (!guns[x][y].empty() && guns[x][y].back() > player2_gun) {
				player[player2_num].gun = guns[x][y].back();
				guns[x][y].pop_back();

				if (player2_gun != 0) {
					guns[x][y].push_back(player2_gun);
				}
			}

		}
		else if ((player1_sum > player2_sum) || (player1_sum == player2_sum && player1_s > player2_s)) {
			//player1의 합이 더 높으면 각 플레이어의 초기 능력치와 가지고 있는 총의 공격력의 합의 차이 포인트 획득
			answer_point[player1_num] += (player1_sum - player2_sum);

			//진 플레이어는 본인이 가지고 있는 총을 해당 격자에 내려놓는다.
			if (player2_gun != 0) {
				guns[x][y].push_back(player2_gun);
				player[player2_num].gun = 0; //총을 내려놓는다.
			}
			bool player2_move = false;

			

			for (int d = player2_d; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				//만약 격자 안이고 비어있다면
				if (inrange(nx, ny) && players[nx][ny].empty()) {
					sort(guns[nx][ny].begin(), guns[nx][ny].end());

					//만약 총이 있다면
					if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
						player[player2_num].gun = guns[nx][ny].back();
						guns[nx][ny].pop_back();
					}

					//이동한다.
					int idx = find(players[x][y].begin(), players[x][y].end(), player2_num) - players[x][y].begin();
					players[x][y].erase(players[x][y].begin() + idx);

					player2_move = true;
					player[player2_num].x = nx;
					player[player2_num].y = ny;
					player[player2_num].d = d;
					players[nx][ny].push_back(player2_num);
					break;
				}
			}

			if (!player2_move) {
				for (int d = 0; d < player2_d; d++) {
					int nx = x + dx[d];
					int ny = y + dy[d];

					if (inrange(nx, ny) && players[nx][ny].empty()) {
						//만약 격자 안이고 비어있다면
						//만약 총이 있다면
						sort(guns[nx][ny].begin(), guns[nx][ny].end());

						if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
							player[player2_num].gun = guns[nx][ny].back();
							guns[nx][ny].pop_back();
						}

						//이동한다.
						int idx = find(players[x][y].begin(), players[x][y].end(), player2_num) - players[x][y].begin();
						players[x][y].erase(players[x][y].begin() + idx);

						player[player2_num].x = nx;
						player[player2_num].y = ny;
						player[player2_num].d = d;

						players[nx][ny].push_back(player2_num);
						break;
					}
				}
			}

			//이긴 플레이어는 승리한 칸에 떨어져 있는 총과 원래 들고 있는 총 중 가장 공격력이 높은 총을 획득한다.
			sort(guns[x][y].begin(), guns[x][y].end());
			if (!guns[x][y].empty() && guns[x][y].back() > player1_gun) {
				player[player1_num].gun = guns[x][y].back();
				guns[x][y].pop_back();

				if (player1_gun != 0) {
					guns[x][y].push_back(player1_gun);
				}
			}
		}


	}


}

void one_round() {
	//한 라운드

	for (int i = 1; i <= m; i++) {
		one_player_move(i);
		one_player_compete(i);
	}
}
void solution() {

	for (int i = 1; i <= k; i++) {
		one_round();
	}

	for (int i = 1; i <= m; i++) {
		cout << answer_point[i] << " ";
	}
}
void input() {

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int num;
			cin >> num;
			guns[i][j].push_back(num);
		}
	}

	for (int i = 1; i <= m; i++) {
		int x, y, d, s;
		cin >> x >> y >> d >> s;
		players[x][y].push_back(i);
		player[i] = { x,y,d,s,0 };
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}