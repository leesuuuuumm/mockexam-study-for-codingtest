#include <iostream>

using namespace std;

int t;

int day;
int month;
int three_month;
int years;

int info[4];
int dp[15];
int month_num[13];
int one_day_info[13];
int tc = 1;

int solution() {

	for (int i = 1; i <= 12; i++) {
		dp[i] = 999999;
	}
	dp[0] = 0;

	//1월까지 (1일 or 1달)
	dp[1] = min(day * month_num[1], month);

	//2월까지 (1월 + 1일 or 1월 + 1달)
	dp[2] = min(dp[1] + month_num[2] * day, dp[1] + month);

	for (int i = 3; i <= 12; i++) {
		dp[i] = min(dp[i - 1] + day * month_num[i], dp[i - 1] + month);
		dp[i] = min(dp[i], dp[i - 3] + three_month);
	}

	if (dp[12] > years) {
		dp[12] = years;
	}

	return dp[12]; 
}

void input() {

	cin >> t;

	for (tc = 1; tc <= t; tc++) {

		cin >> day >> month >> three_month >> years;

		for (int i = 1; i <= 12; i++) {
			int num;
			cin >> num;
			month_num[i] = num;
		}

		cout << "#" <<  tc << " " << solution() << "\n";
	}
	
	
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
}