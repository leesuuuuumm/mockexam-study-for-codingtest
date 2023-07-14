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
	static Queue<Point> que;
	static Queue<Point> tmp;
	static int N, M;
	static int answer;
	static boolean flag;

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
		answer = 0;

		while (true) {
			que = new LinkedList<>();
			flag = false;

			// 외부 공기, 내부공기 나눠주기
			outerAir();

			// 치즈 소멸 시켜주기!
			meltTheCheese();
			if (!flag) {
				break;
			}
			answer++;

		}
		System.out.println(answer);
	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void outerAir() {
		boolean[][] v = new boolean[N][M];
		que.offer(new Point(0, 0));
		map[0][0] = -1;
		v[0][0] = true;

		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				if (map[nr][nc] == 0 || map[nr][nc] == -1) {
					que.offer(new Point(nr, nc));
					map[nr][nc] = -1;
					v[nr][nc] = true;
				}

			}
		}
	}

	private static void meltTheCheese() {
		tmp = new LinkedList<>();
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (map[r][c] == 1) {
					start(r, c);
				}

			}
		}

		while (!tmp.isEmpty()) {
			Point cur = tmp.poll();
			map[cur.r][cur.c] = -1;
		}
	}

	private static void start(int r, int c) {
		int cnt = 0;
		for (int d = 0; d < 4; d++) {
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (map[nr][nc] == -1) {
				cnt++;
			}

			if (cnt >= 2) {
				tmp.add(new Point(r, c));
				flag = true;
				return;
			}
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
