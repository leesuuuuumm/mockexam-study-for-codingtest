import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int num;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}

		public Point(int r, int c, int num) {
			this.r = r;
			this.c = c;
			this.num = num;
		}
	}

	static int[][] map;
	static int N, M;
	static int ck;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		map = new int[N][M];
		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}
		year = 0;
		flag = false;
		que = new LinkedList<>();

		while (true) {
			divIceberg();
			if (flag) {
				break;
			}
			meltTheIceberg();

		}
		System.out.println(year);

	}

	static int[] dr = { 0, -1, 0, 1 };
	static int[] dc = { 1, 0, -1, 0 };

	private static void meltTheIceberg() {
		Queue<Point> q = new LinkedList<>();
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] != 0) {

					int cnt = 0;
					for (int d = 0; d < 4; d++) {
						int nr = r + dr[d];
						int nc = c + dc[d];

						if (!check(nr, nc))
							continue;

						if (map[nr][nc] == 0) {
							cnt++;
						}
					}

					q.offer(new Point(r, c, cnt));
				}

			}
		}

		while (!q.isEmpty()) {
			Point cur = q.poll();
			int iceberg = map[cur.r][cur.c] - cur.num;

			if (iceberg <= 0) {
				map[cur.r][cur.c] = 0;
			} else {
				map[cur.r][cur.c] = iceberg;
			}
		}
		year++;

	}

	static Queue<Point> que;
	static boolean[][] v;
	static boolean flag;

	private static void divIceberg() {
		que = new LinkedList<>();
		v = new boolean[N][M];
		ck = 0;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] != 0 && !v[r][c]) {
					v[r][c] = true;
					que.offer(new Point(r, c));
					bfs();
					ck++;
				}
				if (ck >= 2) {
					flag = true;
					return;
				}

			}
		}
		if (ck == 0) {
			year = 0;
			flag = true;
			return;
		}
	}

	static int year;

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc))
					continue;

				if (map[nr][nc] != 0 && !v[nr][nc]) {
					que.offer(new Point(nr, nc));
					v[nr][nc] = true;
				}
			}
		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
