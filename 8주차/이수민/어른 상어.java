import java.io.*;
import java.util.*;

public class Main {
	static class Shark {
		int r;
		int c;
		int num;
		int d;
		int k; // 냄새
		boolean flag; // 존재 유무

		public Shark(int r, int c, int d) {
			this.r = r;
			this.c = c;
			this.d = d;
		}

		public Shark(int num, int k, boolean flag) {
			this.num = num;
			this.k = k;
			this.flag = flag;
		}
	}

	static int N, M, K; // N: map 크기, M: 상어 수, K: 처음 상어가 가지고 있는 냄새
	static Shark[][] map;
	static Shark[] shark;
	static int[][][] dir;
	static boolean[][] v;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		map = new Shark[N][N];
		shark = new Shark[M + 1];
		dir = new int[M][4][4];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());

			for (int c = 0; c < N; c++) {
				int num = Integer.parseInt(st.nextToken());

				if (num != 0) {
					map[r][c] = new Shark(num, K, true);
					shark[num] = new Shark(r, c, 0);
				} else {
					map[r][c] = null;
				}
			}
		}
		st = new StringTokenizer(br.readLine());

		for (int i = 1; i <= M; i++) { // 상어도 1번부터 시작
			Shark s = shark[i];
			shark[i] = new Shark(s.r, s.c, Integer.parseInt(st.nextToken()) - 1);
		}

		for (int i = 0; i < M; i++) {
			for (int r = 0; r < 4; r++) {
				st = new StringTokenizer(br.readLine());
				for (int c = 0; c < 4; c++) {
					dir[i][r][c] = Integer.parseInt(st.nextToken()) - 1;
				}
			}
		}
		int time = 0;
		while (true) {
			if (time == 1000) {
				time = -1;
				break;
			}

			moveShark();
			++time;
			if (stopShark()) {
				break;
			}
		}

		System.out.println(time);

	}

	static int[] dr = { -1, 1, 0, 0 };
	static int[] dc = { 0, 0, -1, 1 }; // 상하좌우

	private static void moveShark() {
		a: for (int i = 1; i <= M; i++) {
			if (shark[i] != null) {
				Shark cur = shark[i];
				int pr = -1;
				int pc = -1;
				int pd = -1;

				for (int d = 0; d < 4; d++) {
					int nr = cur.r + dr[dir[i - 1][cur.d][d]];
					int nc = cur.c + dc[dir[i - 1][cur.d][d]];

					if (!check(nr, nc))
						continue;

					if (map[nr][nc] == null) {
						int k = map[cur.r][cur.c].k;
						map[cur.r][cur.c] = new Shark(i, k, false);
						shark[i] = new Shark(nr, nc, dir[i - 1][cur.d][d]);
						continue a;
					} else if (map[nr][nc].num == i && pr == -1 && pc == -1) {
						pr = nr;
						pc = nc;
						pd = dir[i - 1][cur.d][d];
					}
				}

				if (pr != -1 && pc != -1) {
					map[cur.r][cur.c] = new Shark(i, map[cur.r][cur.c].k, false);
					shark[i] = new Shark(pr, pc, pd);
				}
			}

		}
		start();

	}

	private static void start() {
		for (int i = 1; i <= M; i++) {
			if (shark[i] != null) {
				Shark cur = shark[i];

				if (map[cur.r][cur.c] == null || map[cur.r][cur.c].num == i) {
					map[cur.r][cur.c] = new Shark(i, K + 1, true);
				} else {
					shark[i] = null;
				}

			}
		}

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (map[r][c] != null) {
					if (map[r][c].k > 1) {
						map[r][c] = new Shark(map[r][c].num, map[r][c].k - 1, map[r][c].flag);
					} else {
						map[r][c] = null;
					}
				}
			}
		}
	}

	private static boolean stopShark() {
		for (int i = 2; i <= M; i++) {
			if (shark[i] != null) {
				return false;
			}
		}
		return true;
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}

}
