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

	static char[][] map;
	static int R, C;
	static int[][] v;
	static Queue<Point> hq; // 두더지 큐
	static Queue<Point> wq; // 물 큐
	static int time;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		hq = new LinkedList<>();
		wq = new LinkedList<>();

		map = new char[R][C];
		v = new int[R][C];

		for (int r = 0; r < R; r++) {
			map[r] = br.readLine().toCharArray();

			for (int c = 0; c < C; c++) {
				if (map[r][c] == 'S') {
					hq.offer(new Point(r, c, 0));
					v[r][c] = 2;
					map[r][c] = '.';
				} else if (map[r][c] == '*') {
					wq.offer(new Point(r, c));
					v[r][c] = 1;
				}

			}
		}
		time = 0;

		bfs();
		System.out.println(time == 0 ? "KAKTUS" : time);

	}

	static int[] dr = { 0, 1, 0, -1 };
	static int[] dc = { 1, 0, -1, 0 };

	private static void bfs() {
		while (true) {
			// 물 확장
			int size = wq.size();

			for (int i = 0; i < size; i++) {
				Point cur = wq.poll();

				for (int d = 0; d < 4; d++) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc) || map[nr][nc] == 'D' || map[nr][nc] == 'X')
						continue;

					// 1은 물이 이미 있는 곳
					if (v[nr][nc] != 1 && map[nr][nc] == '.') {
						v[nr][nc] = 1;
						map[nr][nc] = '*';
						wq.offer(new Point(nr, nc));
					}

				}
			}

			int dize = hq.size();

			if (dize == 0) {
				return;
			}

			for (int i = 0; i < dize; i++) {
				Point cur = hq.poll();

				for (int d = 0; d < 4; d++) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc) || map[nr][nc] == '*' || map[nr][nc] == 'X')
						continue;

					if (map[nr][nc] == 'D') {
						time = cur.dist + 1;
						return;
					}

					if (v[nr][nc] == 0 && map[nr][nc] == '.') {
						hq.offer(new Point(nr, nc, cur.dist + 1));
						v[nr][nc] = 2;
					}
				}
			}

		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < R && nc >= 0 && nc < C;
	}
}
