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

	static int N, M;
	static int[][] map;
	static Queue<Point> que;
	static boolean[][] v;
	static boolean stop;
	static int piece;
	static int time;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		map = new int[N][M];
		piece = 0;
		time = 0;
		stop = false;

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());

				if (map[r][c] == 1)
					piece++;
			}
		}

		que = new LinkedList<>();

		while (!stop) {
			v = new boolean[N][M];
			que.offer(new Point(0, 0));
			v[0][0] = true;

			meltCheese();
			time++;

		}
		System.out.println(time);
		System.out.println(piece);

	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void meltCheese() {
		ArrayList<Point> meltList = new ArrayList<>();
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				if (map[nr][nc] == 0) {
					que.offer(new Point(nr, nc));
				} else if (map[nr][nc] == 1) {
					meltList.add(new Point(nr, nc));
				}
				v[nr][nc] = true;

			}
		}

		if (piece - meltList.size() == 0) {
			stop = true;
			return;
		}

		for (Point i : meltList) {
			map[i.r][i.c] = 0;
		}
		piece-=meltList.size();

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}

}
