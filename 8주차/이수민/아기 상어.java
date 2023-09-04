import java.io.*;
import java.util.*;

public class Main {
	static class Point implements Comparable<Point> {
		int r;
		int c;
		int dist;

		public Point(int r, int c, int dist) {
			this.r = r;
			this.c = c;
			this.dist = dist;
		}

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

	static class Shark {
		int sr;
		int sc;
		int dist;

		public Shark(int sr, int sc, int dist) {
			this.sr = sr;
			this.sc = sc;
			this.dist = dist;
		}
	}

	static int N;
	static int[][] map;
	static PriorityQueue<Point> pq;
	static boolean[][] v;
	static int sharkSize;
	static int eatCnt;
	static int time;
	static boolean stop;
	static Shark shark;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];
		pq = new PriorityQueue<>();
		v = new boolean[N][N];

		for (int r = 0; r < N; r++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				if (map[r][c] == 9) {
					shark = new Shark(r, c, 0);
					map[r][c] = 0;
				}
			}
		}
		sharkSize = 2;
		eatCnt = 0;

		while (true) {
			init();
			pq.offer(new Point(shark.sr, shark.sc, shark.dist));
			v[shark.sr][shark.sc] = true;
			bfs();
			if (!stop)
				break;
		}
		System.out.println(shark.dist);
	}

	private static void init() {
		stop = false;
		pq = new PriorityQueue<>();
		v = new boolean[N][N];
	}

	static int[] dr = { -1, 0, 0, 1 };
	static int[] dc = { 0, -1, 1, 0 };

	private static void bfs() {
		while (!pq.isEmpty()) {
			Point cur = pq.poll();

			// 자기보다 작은 물고기 크기 상관없이 자기 크기만큼 먹으면 +1된다.
			if (map[cur.r][cur.c] != 0 && map[cur.r][cur.c] < sharkSize) {
				eatCnt++;
				map[cur.r][cur.c] = 0;
				if (eatCnt == sharkSize) {
					sharkSize++;
					eatCnt = 0;
				}
				stop = true;
				shark = new Shark(cur.r, cur.c, cur.dist);
				return;
			}
			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc] || map[nr][nc] > sharkSize)
					continue;

				v[nr][nc] = true;
				pq.offer(new Point(nr, nc, cur.dist + 1));

			}
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
