import java.io.*;
import java.util.*;
// 1h 16m
public class Main {
	static class Point {
		int r;
		int c;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}

	static int N, Q;
	static int[][] map;
	static boolean[][] v;
	static Queue<Point> que;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = (int) Math.pow(2, Integer.parseInt(st.nextToken()));
		Q = Integer.parseInt(st.nextToken());
		map = new int[N][N];
		v = new boolean[N][N];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}

		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < Q; i++) {
			int L = (int) Math.pow(2, Integer.parseInt(st.nextToken()));

			rotatePieceOfIce(L);
			meltIce();
		}

		int area = 0;
		int sum = 0;
		que = new LinkedList<>();
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (map[r][c] != 0) {
					if (!v[r][c]) {
						v[r][c] = true;
						que.offer(new Point(r, c));
						area = Math.max(area, bfs());
					}
					sum += map[r][c];
				}
			}
		}
		System.out.println(sum);
		System.out.println(area);
	}

	private static void rotatePieceOfIce(int L) {
		int[][] tmp = new int[N][N];
		for (int i = 0; i < N; i += L) {
			for (int j = 0; j < N; j += L) {
				for (int r = 0; r < L; r++) {
					for (int c = 0; c < L; c++) {
						tmp[c + i][j + L - 1 - r] = map[i + r][j + c];
					}
				}
			}
		}

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				map[r][c] = tmp[r][c];
			}
		}
	}

	static int[] dr = { 1, -1, 0, 0 };
	static int[] dc = { 0, 0, -1, 1 };

	private static void meltIce() {
		Queue<Point> tmp = new LinkedList<>();
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (map[r][c] != 0) {
					int cnt = 0;
					for (int d = 0; d < 4; d++) {
						int nr = r + dr[d];
						int nc = c + dc[d];

						if (!check(nr, nc) || map[nr][nc] == 0)
							continue;
						cnt++;
					}
					if (cnt < 3) {
						tmp.offer(new Point(r, c));
					}

				}

			}
		}

		while (!tmp.isEmpty()) {
			Point cur = tmp.poll();
			map[cur.r][cur.c]--;
		}
	}

	private static int bfs() {
		int cnt = 1;
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || map[nr][nc] == 0 || v[nr][nc])
					continue;

				que.offer(new Point(nr, nc));
				v[nr][nc] = true;
				cnt++;
			}
		}
		return cnt;

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}

}
