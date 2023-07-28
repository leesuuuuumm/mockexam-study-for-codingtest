import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int wCnt;

		public Point(int r, int c, int wCnt) {
			this.r = r;
			this.c = c;
			this.wCnt = wCnt;
		}
	}

	static int[][] map;
	static int N;
	static Queue<Point> que;

	static int[][] v;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());

		map = new int[N][N];
		que = new LinkedList<>();
		v = new int[N][N];

		for (int r = 0; r < N; r++) {
			char[] ch = br.readLine().toCharArray();

			for (int c = 0; c < N; c++) {
				map[r][c] = ch[c] - '0';
			}
		}
		que.offer(new Point(0, 0, 0));
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				v[r][c] = Integer.MAX_VALUE;
			}
		}
		v[0][0] = 0;

		bfs();
		System.out.println(v[N-1][N-1]);

	}

	static int[] dr = { 0, -1, 1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc))
					continue;

				// 흰색 문이고
				if (map[nr][nc] == 1 && v[nr][nc] > cur.wCnt) {
					v[nr][nc] = cur.wCnt;
					que.offer(new Point(nr, nc, cur.wCnt));
				}
				// 검정색 문이면 뚫고 가야하는데
				else if (map[nr][nc] == 0 && v[nr][nc] > cur.wCnt + 1) {
					v[nr][nc] = cur.wCnt + 1;
					que.offer(new Point(nr, nc, cur.wCnt + 1));
				}

			}
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
