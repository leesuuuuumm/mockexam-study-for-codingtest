#include <iostream>
#include <vector>
#include <cmath>
#include <deque>

using namespace std;

deque<int> dq[5];

int k; //회전 횟수

vector<pair<int, int> > info; 
//톱니바퀴 번호, 방향(1: 시계방향, -1: 반시계방향)

void unclock(int num) {
	//num 번 톱니바퀴를 반시계 방향으로

	int front = dq[num].front();
	dq[num].pop_front();
	dq[num].push_back(front);
}

void clock(int num) {
	//num 번 톱니바퀴를 시계 방향으로

	int back = dq[num].back();
	dq[num].pop_back();
	dq[num].push_front(back);
}
void rotate(int num, int dir) {

	vector<pair<int, int>> rotate_info; //회전시킬 정보
	if (num == 1) { //1번째 톱니 회전

		if (dir == 1) { //시계 방향

			rotate_info.push_back({ 1, 1 });

			if (dq[1][2] != dq[2][6]) { //같지 않으면
				rotate_info.push_back({ 2, -1 }); //2는 반시계 방향으로 

				if (dq[2][2] != dq[3][6]) { //같지 않으면
					rotate_info.push_back({ 3, 1 }); //3은 시계 방향으로

					if (dq[3][2] != dq[4][6]) { //같지 않으면
						rotate_info.push_back({ 4, -1 }); //4은 반시계 방향으로 
					}
				}
			}
			
			

		}
		else { //반시계 방향

			rotate_info.push_back({ 1, -1 });

			if (dq[1][2] != dq[2][6]) { //같지 않으면
				rotate_info.push_back({ 2, 1 }); //2는 시계 방향으로 

				if (dq[2][2] != dq[3][6]) { //같지 않으면
					rotate_info.push_back({ 3, -1 }); //3은 반시계 방향으로 

					if (dq[3][2] != dq[4][6]) { //같지 않으면
						rotate_info.push_back({ 4, 1 }); //4은 시계 방향으로 
					}
				}
				
			}
			
		}

	}
	else if (num == 2) { //2번째 톱니 회전

		if (dir == 1) { //시계 방향

			rotate_info.push_back({ 2, 1 });

			if (dq[1][2] != dq[2][6]) { //같지 않으면
				rotate_info.push_back({ 1, -1}); //1은 반시계 방향으로 
			}

			if (dq[2][2] != dq[3][6]) { //같지 않으면
				rotate_info.push_back({ 3, -1 }); //3은 반시계 방향으로 

				if (dq[3][2] != dq[4][6]) { //같지 않으면
					rotate_info.push_back({ 4, 1 }); //4은 시계 방향으로 
				}
			}

		}
		else { //반시계 방향

			rotate_info.push_back({ 2, -1 });

			if (dq[1][2] != dq[2][6]) { //같지 않으면
				rotate_info.push_back({ 1, 1 }); //1은 시계 방향으로 
			}

			if (dq[2][2] != dq[3][6]) { //같지 않으면
				rotate_info.push_back({ 3, 1 }); //3은 시계 방향으로 

				if (dq[3][2] != dq[4][6]) { //같지 않으면
					rotate_info.push_back({ 4, -1 }); //4은 반시계 방향으로 
				}
			}
		}

	}
	else if (num == 3) { //3번째 톱니 회전

		if (dir == 1) { //시계 방향

			rotate_info.push_back({ 3, 1 });

			if (dq[2][2] != dq[3][6]) { //같지 않으면
				rotate_info.push_back({ 2, -1 }); //2는 반시계 방향으로 

				if (dq[1][2] != dq[2][6]) {
					rotate_info.push_back({ 1, 1 }); //1은 시계 방향으로 
				}
			}
			if (dq[3][2] != dq[4][6]) { //같지 않으면
				rotate_info.push_back({ 4, -1 }); //4은 반시계 방향으로 
			}

		}
		else { //반시계 방향
			rotate_info.push_back({ 3, -1 });

			if (dq[2][2] != dq[3][6]) { //같지 않으면
				rotate_info.push_back({ 2, 1 }); //2는 시계 방향으로 

				if (dq[1][2] != dq[2][6]) {
					rotate_info.push_back({ 1, -1 }); //1은 반시계 방향으로 
				}
			}
			if (dq[3][2] != dq[4][6]) { //같지 않으면
				rotate_info.push_back({ 4, 1 }); //4은 시계 방향으로 
			}
		}

	}
	else { //4번째 톱니 회전

		if (dir == 1) { //시계 방향
			rotate_info.push_back({ 4, 1 });

			
			if (dq[3][2] != dq[4][6]) { //같지 않으면
				rotate_info.push_back({ 3, -1 }); //3은 반시계 방향으로 

				if (dq[2][2] != dq[3][6]) { //같지 않으면
					rotate_info.push_back({ 2, 1 }); //2는 시계 방향으로 

					if (dq[1][2] != dq[2][6]) { //같지 않으면
						rotate_info.push_back({ 1, -1 }); //1은 반시계 방향으로 
					}
				}
			}
		}
		else { //반시계 방향
			rotate_info.push_back({ 4, -1 });

			if (dq[3][2] != dq[4][6]) { //같지 않으면
				rotate_info.push_back({ 3, 1 }); //3은 시계 방향으로 

				if (dq[2][2] != dq[3][6]) { //같지 않으면
					rotate_info.push_back({ 2, -1 }); //2는 반시계 방향으로 

					if (dq[1][2] != dq[2][6]) { //같지 않으면
						rotate_info.push_back({ 1, 1 }); //1은 시계 방향으로 
					}
				}
			}

		}

	}

	for (int i = 0; i < rotate_info.size(); i++) {
		int num = rotate_info[i].first;
		int dir = rotate_info[i].second;

		if (dir == 1) {
			clock(num);
			continue;
		}
		unclock(num);
	}
}
void solution() {

	for (int i = 0; i < k; i++) {
		pair<int, int> p = info[i];

		rotate(p.first, p.second);
	}

	int ans = 0;

	for (int i = 1; i <= 4; i++) {
		if (dq[i][0] == '1') {
			ans += pow(2, i - 1);
		}
	}

	cout <<  ans;

}
void input() {

	for (int i = 1; i <= 4; i++) {
		string st;
		cin >> st;

		for (int j = 0; j < 8; j++) {
			dq[i].push_back(st[j]); 
		}
	}

	cin >> k;

	for (int i = 0; i < k; i++) {
		int num, dir;
		cin >> num >> dir;
		info.push_back({ num, dir });
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}