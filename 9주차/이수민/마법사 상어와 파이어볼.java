import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int m;
		int s;
		int d;

		public Point(int r, int c, int m, int s, int d) {
			this.r = r;
			this.c = c;
			this.m = m;
			this.s = s;
			this.d = d;
		}

		public Point(int m, int s, int d) {
			this.m = m;
			this.s = s;
			this.d = d;

		}
	}

	static ArrayList<Point>[][] map;
	static int N, M, K;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		map = new ArrayList[N][N];
		fb = new LinkedList<>();

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				map[r][c] = new ArrayList<>();
			}
		}

		for (int i = 0; i < M; i++) { // r,c,m,s,d
			st = new StringTokenizer(br.readLine());
			fb.offer(new Point(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1,
					Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()),
					Integer.parseInt(st.nextToken())));
		}

		while (K-- > 0) {
			moveFireball();
			divideFireball();
		}
		int ans = 0;
		while (!fb.isEmpty()) {
			ans += fb.poll().m;

		}
		System.out.println(ans);

	}

	static Queue<Point> fb;
	static int[] dr = { -1, -1, 0, 1, 1, 1, 0, -1 };
	static int[] dc = { 0, 1, 1, 1, 0, -1, -1, -1 };

	private static void moveFireball() {
		while (!fb.isEmpty()) {
			Point cur = fb.poll();
			int nr = cur.r + (dr[cur.d] * cur.s) % N;
			int nc = cur.c + (dc[cur.d] * cur.s) % N;
			if (nr < 0) {
				nr = N + nr;
			} else if (nr >= N) {
				nr %= N;
			}
			if (nc < 0) {
				nc = N + nc;
			} else if (nc >= N) {
				nc %= N;
			}
			map[nr][nc].add(new Point(cur.m, cur.s, cur.d));
		}

	}

	private static void divideFireball() {
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (map[r][c].size() == 1) {
					fb.offer(new Point(r, c, map[r][c].get(0).m, map[r][c].get(0).s, map[r][c].get(0).d));
					map[r][c] = new ArrayList<>();

				} else if (map[r][c].size() > 1) {
					int nm = 0;
					int ns = 0;

					int j = 0;
					int h = 0;
					for (int i = 0; i < map[r][c].size(); i++) {
						nm += map[r][c].get(i).m;
						ns += map[r][c].get(i).s;

						if (map[r][c].get(i).d % 2 == 0) {
							j++;
						}
						if (map[r][c].get(i).d % 2 == 1) {
							h++;
						}
					}
					int size = map[r][c].size();
					map[r][c] = new ArrayList<>();
					if (nm < 5)
						continue;

					if (j == size || h == size) {
						for (int dir = 0; dir < 4; dir++) {
							fb.offer(new Point(r, c, nm / 5, ns / size, dir * 2));
						}
					} else {
						for (int dir = 0; dir < 4; dir++) {
							fb.offer(new Point(r, c, nm / 5, ns / size, dir * 2 + 1));
						}
					}
				}

			}
		}
	}

}
