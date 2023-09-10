#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int n, k;
deque<pair<int,bool>> dq;
//�������� �κ� ����

int stage = 1;

void check_robot() {
	//�κ��� ������.

	if (dq[n - 1].second) {
		dq[n - 1].second = false;
	}
}
void one_stage() {
	//��Ʈ�� �� ĭ�� �ִ� �κ��� �Բ� ��ĭ ȸ���Ѵ�.

	pair<int, int> back = dq.back();
	dq.pop_back();
	dq.push_front(back); 

	check_robot();

	//���� ���� ��Ʈ�� �ö� �κ�����,
	//��Ʈ�� ȸ���ϴ� �������� �� ĭ �̵��� �� �ִٸ� �̵��Ѵ�.
	//���� �̵��� �� ���ٸ� ������ �ִ´�.
	//�κ��� �̵��ϱ� ���ؼ��� �̵��Ϸ��� ĭ�� �κ��� ������
	//�� ĭ�� �������� 1�̻� ���� �־�� �Ѵ�.

	if (dq[n - 2].second && !dq[n - 1].second && dq[n - 1].first > 0) {
		dq[n - 2].second = false;
		dq[n - 1].second = false; //n���� ���ڸ��� �κ��� ������.
		dq[n - 1].first -= 1;
	}

	for (int i = n - 2; i >= 0; i--) {
		if (dq[i].second && !dq[i + 1].second && dq[i + 1].first > 0) {
			dq[i].second = false;
			dq[i + 1].second = true;
			dq[i + 1].first -= 1;
		}
	}
	
	//�ø��� ��ġ�� �ִ� ĭ�� �������� 0�� �ƴϸ� �ø��� ��ġ�� �κ��� �ø���.

	if (dq[0].first > 0) {
		dq[0].second = true;
		dq[0].first -= 1;
	}

	//�������� 0�� ĭ�� ������ k�� �̻��̶�� ������ �����Ѵ�.
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