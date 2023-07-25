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
	static Queue<Point> fq; // 불큐
	static Queue<Point> jq; // 지훈이큐
	static int time;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());

		map = new char[R][C];
		fq = new LinkedList<>();
		jq = new LinkedList<>();

		time = 0;

		// 지훈 이동했던 부분은 1
		for (int r = 0; r < R; r++) {
			map[r] = br.readLine().toCharArray();

			for (int c = 0; c < C; c++) {
				if (map[r][c] == 'J') {
					jq.offer(new Point(r, c, 0));
				} else if (map[r][c] == 'F') {
					fq.offer(new Point(r, c));
				}
			}
		}

		bfs();

		System.out.println(time == 0 ? "IMPOSSIBLE" : time);
	}

	static int[] dr = { 0, -1, 1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs() {
		while (true) {
			int size = jq.size();

			for (int i = 0; i < size; i++) {
				Point cur = jq.poll();
				
				if(map[cur.r][cur.c] == 'F') continue;

				for (int d = 0; d < 4; d++) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc)) {
						time = cur.dist + 1;
						return;
					}

					if (map[nr][nc] == '.') {
						map[nr][nc] = 'J';
						jq.offer(new Point(nr, nc, cur.dist + 1));
					}

				}
			}

			if (jq.size() == 0) {
				return;
			}

			size = fq.size();

			for (int i = 0; i < size; i++) {
				Point cur = fq.poll();

				for (int d = 0; d < 4; d++) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc) || map[nr][nc] == '#')
						continue;

					if (map[nr][nc] == '.' || map[nr][nc] == 'J') {
						map[nr][nc] = 'F';
						fq.offer(new Point(nr, nc));
					}
				}
			}

		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < R && nc >= 0 && nc < C;
	}
}
