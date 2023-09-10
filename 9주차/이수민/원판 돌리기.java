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
	static int N, M, T;

	static int x, d, k; 

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());

		map = new int[N][M];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}

		while (T-- > 0) {
			st = new StringTokenizer(br.readLine());
			x = Integer.parseInt(st.nextToken());
			d = Integer.parseInt(st.nextToken());
			k = Integer.parseInt(st.nextToken());

			TurnCircle();
			getSameNumber();
		}

		System.out.println(sumCircleNumber());
	}

	private static void TurnCircle() {

		for (int r = x; r <= N; r += x) {
			for (int i = 0; i < k; i++) {
				// 시계
				if (d == 0) {
					int tmp = map[r - 1][M - 1];
					for (int c = M - 2; c >= 0; c--) {
						map[r - 1][c + 1] = map[r - 1][c];
					}
					map[r - 1][0] = tmp;
				} else if (d == 1) { // 반시계
					int tmp = map[r - 1][0];

					for (int c = 1; c < M; c++) {
						map[r - 1][c - 1] = map[r - 1][c];
					}
					map[r - 1][M - 1] = tmp;
				}
			}
		}
	}

	static Queue<Point> que;
	static int sameNumber;
	static List<Point> list;
	static boolean flag;
	static boolean aF;

	private static void getSameNumber() {
		que = new LinkedList<>();
		sameNumber = 0;
		aF = false;

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] != 0) {
					flag = false;
					sameNumber = map[r][c];
					que.offer(new Point(r, c));

					bfs();
					if (flag) {
						aF = true;
						map[r][c] = 0;
					}
				}
			}
		}

		if (!aF) {
			getAverage();
		}
	}

	static int[] dr = { 0, 0, -1, 1 };
	static int[] dc = { -1, 1, 0, 0 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int dd = 0; dd < 4; dd++) {
				int nr = cur.r + dr[dd];
				int nc = cur.c + dc[dd];

				if (!check(nr)) {
					continue;
				}

				if (nc < 0) {
					if (map[nr][M - 1] == sameNumber) {
						map[nr][M - 1] = 0;
						que.offer(new Point(nr, M - 1));
						flag = true;

					}
				} else if (nc == M) {
					if (map[nr][0] == sameNumber) {
						map[nr][0] = 0;
						que.offer(new Point(nr, 0));
						flag = true;

					}
				} else {
					if (map[nr][nc] == sameNumber) {
						map[nr][nc] = 0;
						que.offer(new Point(nr, nc));
						flag = true;

					}

				}

			}
		}
	}

	private static int sumCircleNumber() {
		int sum = 0;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] != 0) {
					sum += map[r][c];
				}
			}
		}
		return sum;
	}

	private static boolean check(int nr) {
		return nr >= 0 && nr < N;
	}

	private static void getAverage() {
		int sum = 0;
		int cnt = 0;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] != 0) {
					sum += map[r][c];
					cnt++;
				}
			}
		}
		double avg = ((double) sum / (double) cnt);

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] > 0) {
					if (map[r][c] < avg) {
						map[r][c]++;
					} else if (map[r][c] > avg) {
						map[r][c]--;
					}
				}

			}
		}
	}

}
