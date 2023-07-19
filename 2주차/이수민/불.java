import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int dist;

		public Point(int r, int c, int dist) {
			this.r = r;
			this.c = c;
			this.dist = dist;
		}

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}

	static char[][] map;
	static int T, W, H;
	static Queue<Point> skQue;
	static Queue<Point> fireQue;
	static int answer;
	static boolean[][] smap;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());

		for (int t = 1; t <= T; t++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			W = Integer.parseInt(st.nextToken());
			H = Integer.parseInt(st.nextToken());

			map = new char[H][W];
			smap = new boolean[H][W];
			answer = 0;

			skQue = new LinkedList<>();
			fireQue = new LinkedList<>();

			for (int r = 0; r < H; r++) {
				map[r] = br.readLine().toCharArray();
			}

			for (int r = 0; r < H; r++) {
				for (int c = 0; c < W; c++) {
					if (map[r][c] == '@') {
						skQue.offer(new Point(r, c, 0));
						smap[r][c] = true;
					}
					if (map[r][c] == '*') {
						fireQue.offer(new Point(r, c));
					}
				}
			}

			bfs();
			System.out.println(answer == 0 ? "IMPOSSIBLE" : answer);
		}

	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs() {

		while (true) {
			int fsize = fireQue.size();
			while (fsize-- > 0) {
				Point cur = fireQue.poll();

				for (int d = 0; d < 4; d++) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc) || map[nr][nc] == '#')
						continue;

					if (map[nr][nc] == '.') {
						map[nr][nc] = '*';
						fireQue.offer(new Point(nr, nc));
					}

				}
			}
			int ssize = skQue.size();
			if (ssize == 0) {
				break;
			}
			while (ssize-- > 0) {
				Point cur = skQue.poll();

				for (int d = 0; d < 4; d++) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc)) {
						answer = cur.dist + 1;
						return;
					}
					if (map[nr][nc] == '.' && !smap[nr][nc]) {
						skQue.offer(new Point(nr, nc, cur.dist + 1));
						smap[nr][nc] = true;
					}
				}
			}
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < H && nc >= 0 && nc < W;
	}
}
// 6틀 -> 메모리 초과 / 알고보니 상근이 위치 방문체크 안해줬음 계속 방문했던 애들이 들어오게됐었음!
// 시간이 너무 오래걸리길래 size만큼 돌게로 로직 바꿈
