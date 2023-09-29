#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n; //���� ũ�� 
int m; //�÷��̾� ��
int k; //���� ��

vector<int> guns[21][21];
//0: ��ĭ, 0���� ũ�� ���� ���ݷ�

vector<int> players[21][21];
//�÷��̾��

struct info {
	int x; //��ġ
	int y;
	int d; //����
	int s; //�ʱ� �ɷ�ġ
	int gun; //�� ������
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
	//player_num�� �����δ�

	//�÷��̾� ��ġ
	int x = player[player_num].x;
	int y = player[player_num].y;
    
	//�÷��̾� ����
	int d = player[player_num].d;
	//�÷��̾� �ʱ� �ɷ�ġ
	int s = player[player_num].s;
	int gun = player[player_num].gun;

	int nx = x + dx[d];
	int ny = y + dy[d];

	//���ڸ� ����� ���ݴ� �������� �ٲپ 1��ŭ �̵�
	if (!inrange(nx, ny)) {
		d = change_dir(d);
		nx = x + dx[d];
		ny = y + dy[d];
	}

	player[player_num] = { nx,ny,d,s, gun };

	vector<int> v = players[x][y]; //4
	int idx = find(v.begin(), v.end(), player_num) - v.begin();
	players[x][y].erase(players[x][y].begin() + idx); //�ش� �÷��̾� �����
	players[nx][ny].push_back(player_num); //5,4

}

void one_player_compete(int player_num) {
	//player_num�� ������ �� �����Ѵ�.

	int x = player[player_num].x;
	int y = player[player_num].y;
	int gun = player[player_num].gun;

	if (players[x][y].size() == 1) {
		//�÷��̾ ���ٸ�

		sort(guns[x][y].begin(), guns[x][y].end());

		if (!guns[x][y].empty() && guns[x][y].back() > gun) {
			//�ش� ĭ�� ���� �ְ� ������ �ִ� �Ѻ��� ���ٸ�
			//���� ū ���� �ϳ� ���Ѵ´�.
			player[player_num].gun = guns[x][y].back();
			guns[x][y].pop_back();

			if (gun != 0) {
				guns[x][y].push_back(gun);
			}
		}
	}
	else {
		//�÷��̾ �ִٸ� �� �÷��̾ �ο��.

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

			//player2�� ���� �� ������ �� �÷��̾��� �ʱ� �ɷ�ġ�� ������ �ִ� ���� ���ݷ��� ���� ���� ����Ʈ ȹ��
			answer_point[player2_num] += (player2_sum - player1_sum);

			//�� �÷��̾�� ������ ������ �ִ� ���� �ش� ���ڿ� �������´�.
			if (player1_gun != 0) {
				guns[x][y].push_back(player1_gun);
				player[player1_num].gun = 0; //���� �������´�.
			}

			bool player1_move = false;

			

			for (int d = player1_d; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				//���� ���� ���̰� ����ִٸ�
				if (inrange(nx, ny) && players[nx][ny].empty()) {
					//���� ���� �ִٸ�
					sort(guns[nx][ny].begin(), guns[nx][ny].end());

					if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
						player[player1_num].gun = guns[nx][ny].back();
						guns[nx][ny].pop_back();
					}

					player1_move = true;

					//�̵��Ѵ�.
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
						//���� ���� ���̰� ����ִٸ�
						//���� ���� �ִٸ�
						sort(guns[nx][ny].begin(), guns[nx][ny].end());

						if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
							player[player1_num].gun = guns[nx][ny].back();
							guns[nx][ny].pop_back();
						}

						//�̵��Ѵ�.
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

			//�̱� �÷��̾�� �¸��� ĭ�� ������ �ִ� �Ѱ� ���� ��� �ִ� �� �� ���� ���ݷ��� ���� ���� ȹ���Ѵ�.
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
			//player1�� ���� �� ������ �� �÷��̾��� �ʱ� �ɷ�ġ�� ������ �ִ� ���� ���ݷ��� ���� ���� ����Ʈ ȹ��
			answer_point[player1_num] += (player1_sum - player2_sum);

			//�� �÷��̾�� ������ ������ �ִ� ���� �ش� ���ڿ� �������´�.
			if (player2_gun != 0) {
				guns[x][y].push_back(player2_gun);
				player[player2_num].gun = 0; //���� �������´�.
			}
			bool player2_move = false;

			

			for (int d = player2_d; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];

				//���� ���� ���̰� ����ִٸ�
				if (inrange(nx, ny) && players[nx][ny].empty()) {
					sort(guns[nx][ny].begin(), guns[nx][ny].end());

					//���� ���� �ִٸ�
					if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
						player[player2_num].gun = guns[nx][ny].back();
						guns[nx][ny].pop_back();
					}

					//�̵��Ѵ�.
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
						//���� ���� ���̰� ����ִٸ�
						//���� ���� �ִٸ�
						sort(guns[nx][ny].begin(), guns[nx][ny].end());

						if (!guns[nx][ny].empty() && guns[nx][ny].back() > 0) {
							player[player2_num].gun = guns[nx][ny].back();
							guns[nx][ny].pop_back();
						}

						//�̵��Ѵ�.
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

			//�̱� �÷��̾�� �¸��� ĭ�� ������ �ִ� �Ѱ� ���� ��� �ִ� �� �� ���� ���ݷ��� ���� ���� ȹ���Ѵ�.
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
	//�� ����

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