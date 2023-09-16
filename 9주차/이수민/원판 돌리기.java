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
	static boolean[][] v;

	static int N, M, T;
	static Queue<Point> que;
	static boolean ck;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());

		map = new int[N][M];
		que = new LinkedList<>();

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}

		for (int t = 0; t < T; t++) {
			st = new StringTokenizer(br.readLine());
			int n = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());

			for (int i = 1; i <= N; i++) {
				if (i % n == 0) {
					rotation(i - 1, d, k);
				}
			}

			v = new boolean[N][M];
			ck = false;

			for (int r = 0; r < N; r++) {
				for (int c = 0; c < M; c++) {
					if (!v[r][c] && map[r][c] != 0) {
						que.offer(new Point(r, c));
						v[r][c] = true;
						searchSameNumber(r, c, map[r][c]);
						if (f) {
							map[r][c] = 0;
						}
					}
				}
			}

			if (!ck) {
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
				double avg = (double) sum / (double) cnt;
				for (int r = 0; r < N; r++) {
					for (int c = 0; c < M; c++) {
						if (map[r][c] != 0) {
							if (avg > map[r][c]) {
								map[r][c] += 1;
							} else if (avg < map[r][c]) {
								map[r][c] -= 1;
							}
						}
					}
				}
			}
		}
		System.out.println(answer());

	}

	private static void rotation(int r, int d, int k) { // d = 0 시계, d = 1 반시계
		int[] tmp = new int[M];

		if (d == 0) {
			for (int c = 0; c < M; c++) {
				tmp[(c + k) % M] = map[r][c];
			}
		} else {
			for (int c = 0; c < M; c++) {
				if (c - (k % M) < 0) {
					tmp[M - Math.abs(c - (k % M))] = map[r][c];
				} else {
					tmp[c - (k % M)] = map[r][c];
				}
			}
		}

		for (int c = 0; c < M; c++) {
			map[r][c] = tmp[c];
		}
	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };
	static boolean f;

	private static void searchSameNumber(int r, int c, int num) {
		f = false;
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr))
					continue;

				if (nc < 0)
					nc = M - 1;
				if (nc > M - 1)
					nc = 0;

				if (!v[nr][nc] && map[nr][nc] == num) {
					que.offer(new Point(nr, nc));
					map[nr][nc] = 0;
					f = true;
					ck = true;
				}

			}
		}
	}

	private static int answer() {
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
}
