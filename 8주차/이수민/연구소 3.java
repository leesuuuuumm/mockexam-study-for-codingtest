import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int dist;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}

		public Point(int r, int c, int dist) {
			this.r = r;
			this.c = c;
			this.dist = dist;
		}
	}

	static int[][] map;
	static int[][] v;
	static int N, M;
	static ArrayList<Point> list;
	static Point[] select;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		select = new Point[M];

		map = new int[N][N];
		list = new ArrayList<>();

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				if (map[r][c] == 2) {
					list.add(new Point(r, c));
				}
			}
		}

		time = Integer.MAX_VALUE;
		nCr(0, 0);

		System.out.println(time == Integer.MAX_VALUE ? -1 : time);

	}

	static Queue<Point> que;
	static int time;

	private static void nCr(int cnt, int start) {
		if (cnt == M) {
			que = new LinkedList<>();
			v = new int[N][N];

			for (int i = 0; i < select.length; i++) {
				que.offer(new Point(select[i].r, select[i].c, 0));

			}
			bfs();
			checkSpread();
			return;
		}

		for (int i = start; i < list.size(); i++) {
			select[cnt] = list.get(i);

			nCr(cnt + 1, i + 1);
		}
	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || map[nr][nc] == 1 || v[nr][nc] != 0 && v[nr][nc] <= cur.dist + 1)
					continue;

				v[nr][nc] = cur.dist + 1;
				que.offer(new Point(nr, nc, cur.dist + 1));
			}

		}

	}

	private static void checkSpread() {
		int max = 0;

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (map[r][c] == 0 && v[r][c] == 0) {
					return;
				}
				if (map[r][c] == 2)
					continue;
				max = Math.max(max, v[r][c]);
			}
		}
		time = Math.min(max, time);

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
