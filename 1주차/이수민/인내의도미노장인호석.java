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

	static int N, M, R, score;
	static int[][] map, copy;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());

		map = new int[N][M];
		copy = new int[N][M];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				copy[r][c] = map[r][c];
			}
		}
		score = 0;
		for (int i = 0; i < R; i++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			String s = st.nextToken();
			int d = 0;

			if (s.equals("W"))
				d = 1;
			else if (s.equals("S"))
				d = 2;
			else if (s.equals("N"))
				d = 3;

			st = new StringTokenizer(br.readLine());

			attackDMN(r, c, d);

			defend(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1);
		}

		System.out.println(score);
		for (int k = 0; k < N; k++) {
			for (int j = 0; j < M; j++) {
				if(map[k][j] == 6) {
					System.out.print("F ");
				}else {
					System.out.print("S ");
				}
			}
			System.out.println();
		}
	}

	static int[] dr = { 0, 0, 1, -1 };
	static int[] dc = { 1, -1, 0, 0 };

	private static void attackDMN(int r, int c, int d) {
		Queue<Point> que = new LinkedList<>();
		if (map[r][c] != 6) {
			map[r][c] = 6;
			score += 1;
			que.offer(new Point(r, c));
		}

		while (!que.isEmpty()) {
			Point cur = que.poll();
			int nr = cur.r;
			int nc = cur.c;
			int K = copy[nr][nc];

			for (int i = 0; i < K - 1; i++) {
				nr += dr[d];
				nc += dc[d];

				if (!check(nr, nc))
					return;

				if (map[nr][nc] != 6) {
					que.offer(new Point(nr, nc));
					map[nr][nc] = 6;
					score++;
				}
			}
		}
	}

	private static void defend(int r, int c) {
		if (map[r][c] != 6)
			return;
    
		map[r][c] = copy[r][c];
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
