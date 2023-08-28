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

	static char[][] map;
	static Queue<Point> que;
	static boolean[][] v;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		map = new char[8][8];

		for (int r = 0; r < 8; r++) {
			map[r] = br.readLine().toCharArray();
		}
		que = new LinkedList<>();

		que.offer(new Point(7, 0));
		stop = 0;
		flag = false;

		while (!flag) {
			moveOJ();
			moveWall();
		}
		System.out.println(stop);

	}

	static int stop;
	static boolean flag;

	static int[] dr = { 0, 0, 1, 0, -1, 1, 1, -1, -1 };
	static int[] dc = { 0, 1, 0, -1, 0, -1, 1, 1, -1 };

	private static void moveOJ() {
		ArrayList<Point> list = new ArrayList<>();
		v = new boolean[8][8];

		while (!que.isEmpty()) {
			Point cur = que.poll();

			if (map[cur.r][cur.c] == '#')
				continue;

			if (cur.r == 0 && cur.c == 7) {
				stop = 1;
				flag = true;
				return;
			}

			for (int d = 0; d < 9; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				if (map[nr][nc] == '.') {
					list.add(new Point(nr, nc));
					v[nr][nc] = true;
				}

			}
		}

		if (list.size() == 0) {
			flag = true;
			return;
		}

		for (Point i : list) {
			que.offer(new Point(i.r, i.c));
		}

	}

	private static void moveWall() {
		ArrayList<Point> list = new ArrayList<>();

		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (map[r][c] == '#') {
					list.add(new Point(r, c));
					map[r][c] = '.';
				}
			}
		}

		for (Point i : list) {
			if (!check(i.r + 1, i.c))
				continue;
			map[i.r + 1][i.c] = '#';
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < 8 && nc >= 0 && nc < 8;
	}
}
