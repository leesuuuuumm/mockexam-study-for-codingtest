import java.io.*;
import java.util.*;
public class Main {
	static class Player {
		int r;
		int c;
		int d;
		int s;
		int g;

		public Player(int r, int c, int d, int s, int g) {
			this.r = r;
			this.c = c;
			this.d = d;
			this.s = s;
			this.g = g;
		}
	}

	static int[] score;
	static Player[] player;
	static ArrayList<Integer>[][] gun;
	static int[][] map;
	static int N, M, K;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		map = new int[N][N];
		gun = new ArrayList[N][N];
		score = new int[M + 1];
		player = new Player[M + 1];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				gun[r][c] = new ArrayList<>();
				int g = Integer.parseInt(st.nextToken());
				if (g > 0) {
					gun[r][c].add(g);
				}
			}
		}

		for (int m = 1; m <= M; m++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			player[m] = new Player(r, c, Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), 0);
			map[r][c] = m;
		}

		while (K-- > 0) {
			movePlayers();
		}

		for (int m = 1; m <= M; m++) {
			System.out.print(score[m] + " ");
		}

	}

	static int[] dr = { -1, 0, 1, 0 };
	static int[] dc = { 0, 1, 0, -1 };

	private static void movePlayers() {
		for (int m = 1; m <= M; m++) {
			Player cur = player[m];
			int d = cur.d;

			if (!check(cur.r + dr[d], cur.c + dc[d])) {
				d = changeDir(cur.d);
			}
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];

			if (map[nr][nc] != 0) { // 싸움 하고

				Player nP = player[map[nr][nc]];

				cur = new Player(cur.r, cur.c, d, cur.s, cur.g);
				fightPlayers(m, map[nr][nc], cur, nP);

			} else { // 옮겨주고, 총획득
				map[nr][nc] = m;
				map[cur.r][cur.c] = 0;
				player[m] = new Player(nr, nc, d, cur.s, searchGun(nr, nc, m));
			}

		}

	}

	private static void fightPlayers(int P1, int P2, Player p1, Player p2) {
		int f1 = p1.s + p1.g;
		int f2 = p2.s + p2.g;
		int fr = p2.r;
		int fc = p2.c;

		// 이동하는 애는 우선 map에서 옮겨진거임
		map[p1.r][p1.c] = 0;

		// p2 (가만히 있는 애) 지금 싸우는 위치는 p2위치임

		if (f1 > f2 || (f1 == f2) && p1.s > p2.s) { // 이동한 애가 이김
			moveLosePlayer(fr, fc, P2, p2);

			moveWinPlayer(f1 - f2, fr, fc, P1, p1);

		} else if (f1 < f2 || (f1 == f2) && p2.s > p1.s) { // 이동한 애가 짐
			moveLosePlayer(fr, fc, P1, p1);
			moveWinPlayer(f2 - f1, fr, fc, P2, p2);

		}

	}

	private static void moveWinPlayer(int sc, int r, int c, int num, Player p) {
		score[num] += sc;
		map[r][c] = num;
		player[num] = new Player(r, c, p.d, p.s, searchGun(r, c, num));
	}

	private static void moveLosePlayer(int r, int c, int num, Player p) {
		// 그 자리에 총 버려야함
		if (p.g > 0) {
			gun[r][c].add(p.g);
		}
		// 다른 플레이어가 있거나 격자 범위 밖인 경우 오른쪽으로 90도 회전함
		for (int dir = 0; dir < 5; dir++) {
			int nd = (p.d + dir) % 4;

			int nr = r + dr[nd];
			int nc = c + dc[nd];

			if (!check(nr, nc) || map[nr][nc] != 0) {
				continue;
			}

			map[nr][nc] = num;
			player[num] = new Player(nr, nc, nd, p.s, getGun(nr, nc));
			break;
		}

	}

	private static int getGun(int nr, int nc) {
		int maxG = 0;
		int mi = 0;
		for (int i = 0; i < gun[nr][nc].size(); i++) {
			if (maxG < gun[nr][nc].get(i)) {
				maxG = gun[nr][nc].get(i);
				mi = i;
			}
		}
		if (gun[nr][nc].size() > 0) {
			gun[nr][nc].remove(mi);
		}
		return maxG;
	}

	private static int searchGun(int nr, int nc, int num) {
		int curG = player[num].g;

		int maxG = 0;
		int mi = 0;
		for (int i = 0; i < gun[nr][nc].size(); i++) {
			if (maxG < gun[nr][nc].get(i)) {
				maxG = gun[nr][nc].get(i);
				mi = i;
			}
		}

		if (curG < maxG) {
			gun[nr][nc].remove(mi);
			if (curG > 0) {
				gun[nr][nc].add(curG);
			}
			curG = maxG;
		}
		return curG;
	}

	private static int changeDir(int d) {
		if (d == 0 || d == 1) {
			d += 2;
		} else {
			d -= 2;
		}
		return d;
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
