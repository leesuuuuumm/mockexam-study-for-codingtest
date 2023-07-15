import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}

	static int[][] map;
	static int N, M, D;
	static int[] selc;
	static ArrayList<Point> rrenemy;

  		// 궁수 3 명 배치 성이 있는 칸에 배치할 수 있음
		// 궁수는 적 공격 -> 동시에 공격
		// D이하인 적중에서 가장 가까운 적, 가장 왼쪽에 있는 적 공격
		// 여러 궁수에게 공격당할 수 있는데 공격 받으면 적은 게임에서 제외된다.
		// 이동 -> 아래로 한칸 이동, 성이 있는 칸으로 이동하면 게임에서 제외됨
		// 모든 적이 제외되면 게임 끝남

		// 궁수의 공격으로 제거할 수 있는 적의 최대 수 구하기
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		D = Integer.parseInt(st.nextToken());

		map = new int[N + 1][M];
		selc = new int[3];
		rrenemy = new ArrayList<>();
		answer = 0;

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				if (map[r][c] == 1) {
					rrenemy.add(new Point(r, c));
				}
			}
		}

		nCr(0, 0);
		System.out.println(answer);

	}

	static int[][] tmp;
	static ArrayList<Point> enemy;

	static int sum;
	static int answer;

	private static void nCr(int cnt, int start) {
		if (cnt == 3) {
			tmp = new int[N][M];
			enemy = new ArrayList<>();
			for (int r = 0; r < N; r++) {
				for (int c = 0; c < M; c++) {
					tmp[r][c] = map[r][c];
				}
			}

			for (Point i : rrenemy) {
				enemy.add(new Point(i.r, i.c));
			}
			sum = 0;

			while (enemy.size() > 0) {
				startGame();
			}
			answer = Math.max(answer, sum);

			return;
		}

		for (int i = start; i < M; i++) {
			selc[cnt] = i;
			nCr(cnt + 1, i + 1);

		}
	}

	private static void startGame() {
		ArrayList<Point> em = new ArrayList<>();
		
		for (int i = 0; i < selc.length; i++) {
			int min = Integer.MAX_VALUE;
			int r = -1;
			int c = -1;

			for (int j = 0; j < enemy.size(); j++) {

				int dist = Math.abs(N - enemy.get(j).r) + Math.abs(selc[i] - enemy.get(j).c);

				if (dist > D)
					continue;

				if (min > dist || min == dist && c > enemy.get(j).c) {
					min = dist;
					r = enemy.get(j).r;
					c = enemy.get(j).c;
				}
			}

			if (r != -1 || c != -1) {
				em.add(new Point(r, c));
			}

		}
		
		for (int i = 0; i < em.size(); i++) {
			int r = em.get(i).r;
			int c = em.get(i).c;

			if (tmp[r][c] == 1) {
				tmp[r][c] = 0;
				sum += 1;
			}
		}

		moveEnemy();
	}

	private static void moveEnemy() {
		enemy.clear();
		for (int r = N - 1; r >= 0; r--) {
			for (int c = 0; c < M; c++) {
				if (tmp[r][c] == 1) {
					if (r + 1 == N)
						continue;
					enemy.add(new Point(r + 1, c));
					tmp[r + 1][c] = 1;
					tmp[r][c] = 0;

				}
			}
		}

	}
}
