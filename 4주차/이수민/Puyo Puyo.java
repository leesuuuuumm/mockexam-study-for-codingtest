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
	static boolean[][] v;
	static Queue<Point> que;
	static boolean flag;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		map = new char[12][6];

		for (int r = 0; r < 12; r++) {
			map[r] = br.readLine().toCharArray();
		}

		que = new LinkedList<>();
		int answer = 0;

		while (true) {
			v = new boolean[12][6];
			flag = false;

			for (int r = 0; r < 12; r++) {
				for (int c = 0; c < 6; c++) {
					if (map[r][c] != '.' && !v[r][c]) {
						v[r][c] = true;
						que.offer(new Point(r, c));
						bfs();
					}

				}
			}

			if (!flag)
				break;
			++answer;
			fallThePuyo();

		}
		System.out.println(answer);
	}

	static int[] dr = { 1, 0, -1, 0 };
	static int[] dc = { 0, -1, 0, 1 };

	private static void bfs() {
		Queue<Point> tmp = new LinkedList<>();
		tmp.offer(new Point(que.peek().r, que.peek().c));
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				if (map[nr][nc] == map[cur.r][cur.c]) {
					tmp.offer(new Point(nr, nc));
					que.offer(new Point(nr, nc));
					v[nr][nc] = true;
				}

			}

		}
		if (tmp.size() < 4)
			return;

		flag = true;
		while (!tmp.isEmpty()) {
			Point cur = tmp.poll();

			map[cur.r][cur.c] = '.';
		}

	}

	private static void fallThePuyo() {
		ArrayList<Character> list = new ArrayList<>();

		for (int i = 0; i < 6; i++) {
			for (int j = 11; j >= 0; j--) {
				if (map[j][i] != '.') {
					list.add(map[j][i]);
					map[j][i] = '.';
				}
			}

			int k = 11;
			for (Character j : list) {
				map[k--][i] = j;
			}
			list.clear();

		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < 12 && nc >= 0 && nc < 6;
	}

}
