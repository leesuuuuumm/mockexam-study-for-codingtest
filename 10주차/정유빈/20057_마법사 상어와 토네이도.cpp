#include <iostream>

using namespace std;

int n;
int map[500][500];

int start_x;
int start_y;
int ans = 0;

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void inrange_move(int x, int y, int amount) {

	if (inrange(x, y)) {
		map[x][y] += amount;
	}
	else {
		ans += amount;
	}
}
void up() {

	int amount = map[start_x - 1][start_y];

	int one_percent = amount * 1 / 100;
	int seven_percent = amount * 7 / 100;
	int two_percent = amount * 2 / 100;
	int ten_percent = amount * 10 / 100;
	int five_percent = amount * 5 / 100;

	inrange_move(start_x, start_y - 1, one_percent);
	inrange_move(start_x, start_y + 1, one_percent);

	inrange_move(start_x - 1, start_y - 1, seven_percent);
	inrange_move(start_x - 1, start_y + 1, seven_percent);

	inrange_move(start_x - 1, start_y + 2, two_percent);
	inrange_move(start_x - 1, start_y - 2, two_percent);

	inrange_move(start_x - 2, start_y - 1, ten_percent);
	inrange_move(start_x - 2, start_y + 1, ten_percent);

	inrange_move(start_x - 3, start_y, five_percent);


	int remained_amount = amount - (one_percent + two_percent + seven_percent + ten_percent) * 2 - five_percent;

	inrange_move(start_x - 2, start_y, remained_amount);

	map[start_x - 1][start_y] = 0;
	start_x -= 1;
}
void down() {

	int amount = map[start_x + 1][start_y];

	int one_percent = amount * 1 / 100;
	int seven_percent = amount * 7 / 100;
	int two_percent = amount * 2 / 100;
	int ten_percent = amount * 10 / 100;
	int five_percent = amount * 5 / 100;

	inrange_move(start_x, start_y - 1, one_percent);
	inrange_move(start_x, start_y + 1, one_percent);

	inrange_move(start_x + 1, start_y - 1, seven_percent);
	inrange_move(start_x + 1, start_y + 1, seven_percent);

	inrange_move(start_x + 1, start_y + 2, two_percent);
	inrange_move(start_x + 1, start_y - 2, two_percent);

	inrange_move(start_x + 2, start_y - 1, ten_percent);
	inrange_move(start_x + 2, start_y + 1, ten_percent);

	inrange_move(start_x + 3, start_y, five_percent);

	int remained_amount = amount - (one_percent + two_percent + seven_percent + ten_percent) * 2 - five_percent;
	
	inrange_move(start_x + 2, start_y, remained_amount);

	map[start_x + 1][start_y] = 0;

	start_x += 1;
}
void right() {

	int amount = map[start_x][start_y + 1];

	int one_percent = amount * 1 / 100;
	int seven_percent = amount * 7 / 100;
	int two_percent = amount * 2 / 100;
	int ten_percent = amount * 10 / 100;
	int five_percent = amount * 5 / 100;

	inrange_move(start_x - 1, start_y, one_percent);
	inrange_move(start_x + 1, start_y, one_percent);

	inrange_move(start_x - 1, start_y + 1, seven_percent);
	inrange_move(start_x + 1, start_y + 1, seven_percent);

	inrange_move(start_x - 2, start_y + 1, two_percent);
	inrange_move(start_x + 2, start_y + 1, two_percent);

	inrange_move(start_x - 1, start_y + 2, ten_percent);
	inrange_move(start_x + 1, start_y + 2, ten_percent);

	inrange_move(start_x, start_y + 3, five_percent);


	int remained_amount = amount - (one_percent + two_percent + seven_percent + ten_percent) * 2 - five_percent;
	
	inrange_move(start_x, start_y + 2, remained_amount);

	map[start_x][start_y + 1] = 0;

	start_y += 1;
}
void left() {

	int amount = map[start_x][start_y - 1];

	int one_percent = amount * 1 / 100;
	int seven_percent = amount * 7 / 100;
	int two_percent = amount * 2 / 100;
	int ten_percent = amount * 10 / 100;
	int five_percent = amount * 5 / 100;

	inrange_move(start_x - 1, start_y, one_percent);
	inrange_move(start_x + 1, start_y, one_percent);

	inrange_move(start_x - 1, start_y - 1, seven_percent);
	inrange_move(start_x + 1, start_y - 1, seven_percent);

	inrange_move(start_x - 2, start_y - 1, two_percent);
	inrange_move(start_x + 2, start_y - 1, two_percent);

	inrange_move(start_x - 1 , start_y - 2, ten_percent);
	inrange_move(start_x  + 1, start_y - 2, ten_percent);

	inrange_move(start_x , start_y - 3, five_percent);

	int remained_amount = amount - (one_percent + two_percent + seven_percent + ten_percent) * 2 - five_percent;

	inrange_move(start_x, start_y - 2, remained_amount);

	map[start_x][start_y - 1] = 0;


	start_y -= 1;

}


void solution() {

	start_x = n / 2 + 1;
	start_y = n / 2 + 1;

	for (int i = 1; i < n; i += 2) {

		for (int j = 1; j <= i; j++) {
			left();
		}

		for (int j = 1; j <= i; j++) {
			down();
		}

		for (int j = 1; j <= i + 1; j++) {
			right();
		}
		for (int j = 1; j <= i + 1; j++) {
			up();
		}
	}

	for (int i = 1; i < n; i++) {
		left(); 
	}

	cout << ans;

	
}
void input() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j]; 
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