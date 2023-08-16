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

	static Point[] selected;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		map = new char[5][5];

		for (int r = 0; r < 5; r++) {
			map[r] = br.readLine().toCharArray();
		}

		selected = new Point[7];
		answer = 0;

		nCr(0, 0);
		System.out.println(answer);

	}

	static int answer;
	static int[] dr = { 0, -1, 1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void nCr(int cnt, int start) {
		if (cnt == 7) {
			int y = 0;
			for (int i = 0; i < 7; i++) {
				if (map[selected[i].r][selected[i].c] == 'Y') {
					y++;
				}
			}
			if (y > 3)
				return;

			checkedSeat();
			return;
		}

		for (int i = start; i < 25; i++) {
			selected[cnt] = new Point(i / 5, i % 5);
			nCr(cnt + 1, i + 1);
		}

	}

	static boolean[][] v;
	static Queue<Point> que;

	private static void checkedSeat() {
		v = new boolean[5][5];
		que = new LinkedList<>();
		que.offer(new Point(selected[0].r, selected[0].c));
		v[selected[0].r][selected[0].c] = true;
		bfs();
	}

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				for (int i = 1; i < selected.length; i++) {
					if (selected[i].r == nr && selected[i].c == nc && !v[nr][nc]) {
						que.offer(new Point(nr, nc));
						
						v[nr][nc] = true;
					}
				}

			}

		}
		for (int i = 1; i < selected.length; i++) {
			if (!v[selected[i].r][selected[i].c]) {
				return;
			}
		}
		answer++;

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < 5 && nc >= 0 && nc < 5;
	}
}
