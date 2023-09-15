import java.io.*;
import java.util.*;

public class Main {

	static class Horse {
		int r;
		int c;
		int dir;

		public Horse(int r, int c, int dir) {
			this.r = r;
			this.c = c;
			this.dir = dir;
		}
	}

	static int[][] map;
	static ArrayList<Integer>[][] lm;
	static int N, K;
	static Horse[] h;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		map = new int[N][N];
		lm = new ArrayList[N][N];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				lm[r][c] = new ArrayList<>();
			}
		}

		h = new Horse[K + 1];
		dq = new ArrayDeque<>();
		for (int k = 1; k <= K; k++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			int d = Integer.parseInt(st.nextToken()) - 1;

			h[k] = new Horse(r, c, d);
			lm[r][c].add(k);
		}


		flag = false;
		int turn = 0;
		int ans = -1;
		e: while (turn++ <= 1000) {
			// 게임 턴 시작
			for (int k = 1; k <= K; k++) {
				move(k);
				if (flag) {
					ans = turn;
					break e;
				}

			}
		}
		System.out.println(ans);

	}


	static int[] dr = { 0, 0, -1, 1 };
	static int[] dc = { 1, -1, 0, 0 };
	static Deque<Integer> dq;

	private static void move(int k) {
		Horse cur = h[k];

		int nr = cur.r + dr[cur.dir];
		int nc = cur.c + dc[cur.dir];

		if (!check(nr, nc) || map[nr][nc] == 2) {
			if (!blue(cur.r, cur.c, cur.dir, k))
				return;
			nr = cur.r + dr[h[k].dir];
			nc = cur.c + dc[h[k].dir];
		}

		int s = lm[cur.r][cur.c].size();
		for (int i = 0; i < s; i++) {
			if (lm[cur.r][cur.c].get(i) == k) {
				for (int j = i; j < s; j++) {
					dq.addLast(lm[cur.r][cur.c].remove(i));
				}
				break;
			}
		}

		if (map[nr][nc] == 0) {
			white(nr, nc);
		} else if (map[nr][nc] == 1) {
			red(nr, nc);
		}
	}

	static boolean flag;

	private static void white(int nr, int nc) {
		if (dq.size() + lm[nr][nc].size() >= 4) {
			flag = true;
			return;
		}
		// 말이 있는 경우에는 맨위로 놓기
		while (!dq.isEmpty()) {
			int cur = dq.pollFirst();
			lm[nr][nc].add(cur);
			h[cur] = new Horse(nr, nc, h[cur].dir);
		}
	}

	private static void red(int nr, int nc) {
		if (dq.size() + lm[nr][nc].size() >= 4) {
			flag = true;
			return;
		}
		// 반대로 넣어주기
		while (!dq.isEmpty()) {
			int cur = dq.pollLast();
			lm[nr][nc].add(cur);
			h[cur] = new Horse(nr, nc, h[cur].dir);
		}
	}

	private static boolean blue(int r, int c, int d, int k) {
		// 방향 바꿔주고 한칸 이동해야하는데.
		if (d == 0 || d == 2) {
			d += 1;
		} else {
			d -= 1;
		}

		int nr = r + dr[d];
		int nc = c + dc[d];

		h[k] = new Horse(r, c, d);

		if (!check(nr, nc) || map[nr][nc] == 2) {
			return false;
		}
		return true;

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
