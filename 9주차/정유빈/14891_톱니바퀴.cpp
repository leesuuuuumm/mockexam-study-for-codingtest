#include <iostream>
#include <vector>
#include <cmath>
#include <deque>

using namespace std;

deque<int> dq[5];

int k; //ȸ�� Ƚ��

vector<pair<int, int> > info; 
//��Ϲ��� ��ȣ, ����(1: �ð����, -1: �ݽð����)

void unclock(int num) {
	//num �� ��Ϲ����� �ݽð� ��������

	int front = dq[num].front();
	dq[num].pop_front();
	dq[num].push_back(front);
}

void clock(int num) {
	//num �� ��Ϲ����� �ð� ��������

	int back = dq[num].back();
	dq[num].pop_back();
	dq[num].push_front(back);
}
void rotate(int num, int dir) {

	vector<pair<int, int>> rotate_info; //ȸ����ų ����
	if (num == 1) { //1��° ��� ȸ��

		if (dir == 1) { //�ð� ����

			rotate_info.push_back({ 1, 1 });

			if (dq[1][2] != dq[2][6]) { //���� ������
				rotate_info.push_back({ 2, -1 }); //2�� �ݽð� �������� 

				if (dq[2][2] != dq[3][6]) { //���� ������
					rotate_info.push_back({ 3, 1 }); //3�� �ð� ��������

					if (dq[3][2] != dq[4][6]) { //���� ������
						rotate_info.push_back({ 4, -1 }); //4�� �ݽð� �������� 
					}
				}
			}
			
			

		}
		else { //�ݽð� ����

			rotate_info.push_back({ 1, -1 });

			if (dq[1][2] != dq[2][6]) { //���� ������
				rotate_info.push_back({ 2, 1 }); //2�� �ð� �������� 

				if (dq[2][2] != dq[3][6]) { //���� ������
					rotate_info.push_back({ 3, -1 }); //3�� �ݽð� �������� 

					if (dq[3][2] != dq[4][6]) { //���� ������
						rotate_info.push_back({ 4, 1 }); //4�� �ð� �������� 
					}
				}
				
			}
			
		}

	}
	else if (num == 2) { //2��° ��� ȸ��

		if (dir == 1) { //�ð� ����

			rotate_info.push_back({ 2, 1 });

			if (dq[1][2] != dq[2][6]) { //���� ������
				rotate_info.push_back({ 1, -1}); //1�� �ݽð� �������� 
			}

			if (dq[2][2] != dq[3][6]) { //���� ������
				rotate_info.push_back({ 3, -1 }); //3�� �ݽð� �������� 

				if (dq[3][2] != dq[4][6]) { //���� ������
					rotate_info.push_back({ 4, 1 }); //4�� �ð� �������� 
				}
			}

		}
		else { //�ݽð� ����

			rotate_info.push_back({ 2, -1 });

			if (dq[1][2] != dq[2][6]) { //���� ������
				rotate_info.push_back({ 1, 1 }); //1�� �ð� �������� 
			}

			if (dq[2][2] != dq[3][6]) { //���� ������
				rotate_info.push_back({ 3, 1 }); //3�� �ð� �������� 

				if (dq[3][2] != dq[4][6]) { //���� ������
					rotate_info.push_back({ 4, -1 }); //4�� �ݽð� �������� 
				}
			}
		}

	}
	else if (num == 3) { //3��° ��� ȸ��

		if (dir == 1) { //�ð� ����

			rotate_info.push_back({ 3, 1 });

			if (dq[2][2] != dq[3][6]) { //���� ������
				rotate_info.push_back({ 2, -1 }); //2�� �ݽð� �������� 

				if (dq[1][2] != dq[2][6]) {
					rotate_info.push_back({ 1, 1 }); //1�� �ð� �������� 
				}
			}
			if (dq[3][2] != dq[4][6]) { //���� ������
				rotate_info.push_back({ 4, -1 }); //4�� �ݽð� �������� 
			}

		}
		else { //�ݽð� ����
			rotate_info.push_back({ 3, -1 });

			if (dq[2][2] != dq[3][6]) { //���� ������
				rotate_info.push_back({ 2, 1 }); //2�� �ð� �������� 

				if (dq[1][2] != dq[2][6]) {
					rotate_info.push_back({ 1, -1 }); //1�� �ݽð� �������� 
				}
			}
			if (dq[3][2] != dq[4][6]) { //���� ������
				rotate_info.push_back({ 4, 1 }); //4�� �ð� �������� 
			}
		}

	}
	else { //4��° ��� ȸ��

		if (dir == 1) { //�ð� ����
			rotate_info.push_back({ 4, 1 });

			
			if (dq[3][2] != dq[4][6]) { //���� ������
				rotate_info.push_back({ 3, -1 }); //3�� �ݽð� �������� 

				if (dq[2][2] != dq[3][6]) { //���� ������
					rotate_info.push_back({ 2, 1 }); //2�� �ð� �������� 

					if (dq[1][2] != dq[2][6]) { //���� ������
						rotate_info.push_back({ 1, -1 }); //1�� �ݽð� �������� 
					}
				}
			}
		}
		else { //�ݽð� ����
			rotate_info.push_back({ 4, -1 });

			if (dq[3][2] != dq[4][6]) { //���� ������
				rotate_info.push_back({ 3, 1 }); //3�� �ð� �������� 

				if (dq[2][2] != dq[3][6]) { //���� ������
					rotate_info.push_back({ 2, -1 }); //2�� �ݽð� �������� 

					if (dq[1][2] != dq[2][6]) { //���� ������
						rotate_info.push_back({ 1, 1 }); //1�� �ð� �������� 
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