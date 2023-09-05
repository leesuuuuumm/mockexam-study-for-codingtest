import java.io.*;
import java.util.*;

public class Main {
	static class Point implements Comparable<Point> {
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

		@Override
		public int compareTo(Point o) {
			if (this.dist == o.dist) {
				if (this.r == o.r) {
					return Integer.compare(this.c, o.c);
				}
				return Integer.compare(this.r, o.r);
			}
			return Integer.compare(this.dist, o.dist);
		}

	}

	static int[][] map;
	static boolean[][] v;
	static Point[] arrived;
	static int M, N, F; // N은 map크기, M은 승객 개수, F는 연료
	static PriorityQueue<Point> pq;
	static Queue<Point> que;
	static int tr, tc; // 택시 위치

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		F = Integer.parseInt(st.nextToken());

		map = new int[N][N];
		arrived = new Point[M + 1];
		v = new boolean[N][N];
		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken()) * -1;
			}
		}

		st = new StringTokenizer(br.readLine());
		tr = Integer.parseInt(st.nextToken()) - 1;
		tc = Integer.parseInt(st.nextToken()) - 1;

		for (int i = 1; i <= M; i++) {
			st = new StringTokenizer(br.readLine());
			map[Integer.parseInt(st.nextToken()) - 1][Integer.parseInt(st.nextToken()) - 1] = i;
			arrived[i] = new Point(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1);
		}

		for (int t = 1; t <= M; t++) {
			init();
			if (!searchPassenger()) {
				System.out.println(-1);
				return;
			}
			init();
			if (!getOutOfTheTexi()) {
				System.out.println(-1);
				return;
			}

		}
		System.out.println(F);
	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	// 거리가 가장 짧은 승객 찾아주기
	private static boolean searchPassenger() {
		pq = new PriorityQueue<>();
		if (map[tr][tc] != 0)
			return true;

		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc] || map[nr][nc] == -1)
					continue;

				que.offer(new Point(nr, nc, cur.dist + 1));
				v[nr][nc] = true;
				if (map[nr][nc] != 0) {
					pq.offer(new Point(nr, nc, cur.dist + 1));
				}
			}
		}

		if (pq.isEmpty() || pq.peek().dist > F)
			return false;
		Point cur = pq.poll();

		F -= cur.dist;
		tr = cur.r;
		tc = cur.c;

		return true;
	}

	private static boolean getOutOfTheTexi() {
		int er = arrived[map[tr][tc]].r;
		int ec = arrived[map[tr][tc]].c;
		map[tr][tc] = 0;
		while (!que.isEmpty()) {
			Point cur = que.poll();

			if (cur.r == er && cur.c == ec) {
				if (cur.dist > F)
					return false;

				F += cur.dist;
				tr = cur.r;
				tc = cur.c;
				return true;

			}

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || map[nr][nc] == -1 || v[nr][nc])
					continue;

				que.offer(new Point(nr, nc, cur.dist + 1));
				v[nr][nc] = true;
			}

		}

		return false;

	}

	private static void init() {
		v = new boolean[N][N];
		que = new LinkedList<>();
		que.offer(new Point(tr, tc, 0));
		v[tr][tc] = true;
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
