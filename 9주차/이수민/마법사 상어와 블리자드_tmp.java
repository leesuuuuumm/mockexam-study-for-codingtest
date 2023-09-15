import java.io.*;
import java.util.*;

public class Main {

	static int[][] map;
	static int N, M;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		map = new int[N][N];
		que = new LinkedList<>();
		tmp = new LinkedList<>();
		sum = new int[4];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}

		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			int dir = Integer.parseInt(st.nextToken()) - 1;
			int S = Integer.parseInt(st.nextToken());

			DoingBlizzard(dir, S);
			pullingMarble();

			divideMarble();
			inputMarble();
		}
		System.out.println(sum[1] + (2 * sum[2]) + (3 * sum[3]));
	}

	static int[] dr = { -1, 1, 0, 0 };
	static int[] dc = { 0, 0, -1, 1 };

	private static void DoingBlizzard(int dir, int S) {
		int nr = N / 2;
		int nc = N / 2;

		for (int s = 0; s < S; s++) {
			nr += dr[dir];
			nc += dc[dir];

			if (!check(nr, nc))
				break;
			map[nr][nc] = 0;
		}
	}

	static int[] sdir = { 2, 1, 3, 0 };
	static Queue<Integer> que;
	static Queue<Integer> tmp;

	private static void pullingMarble() {
		int sr = (N / 2);
		int sc = (N / 2);
		int sd = 0;
		int cnt = 1;
		e: while (true) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < cnt; j++) {
					sr += dr[sdir[sd]];
					sc += dc[sdir[sd]];

					if (!check(sr, sc))
						break e;
					if (map[sr][sc] != 0) {
						que.offer(map[sr][sc]);
					}
				}
				sd = (sd + 1) % 4;
			}
			cnt++;
		}

		int count = 1;
		boolean stop = false;
		while (!stop) {
			stop = true;
			while (!que.isEmpty()) {
				int cur = que.poll();

				if (que.isEmpty() || cur != que.peek()) {
					if (count < 4) {
						for (int i = 0; i < count; i++) {
							tmp.offer(cur);
						}
					} else {
						sum[cur] += count;
						stop = false;
					}
					count = 1;

				} else if (cur == que.peek()) {
					count++;
				}
			}

			inputQueue();
		}
	}

	static int[] sum;

	private static void inputQueue() {
		while (!tmp.isEmpty()) {
			que.offer(tmp.poll());
		}
	}

	private static void divideMarble() {
		int count = 1;
		while (!que.isEmpty()) {
			int cur = que.poll();
			if (que.isEmpty() || cur != que.peek()) {
				tmp.offer(count);
				tmp.offer(cur);
				count = 1;
			} else if (cur == que.peek()) {
				count++;
			}
		}
		inputQueue();
	}

	private static void inputMarble() {
		int sr = (N / 2);
		int sc = (N / 2);
		int sd = 0;
		int cnt = 1;
		map = new int[N][N];
		e: while (true) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < cnt; j++) {
					sr += dr[sdir[sd]];
					sc += dc[sdir[sd]];

					if (que.isEmpty() || sr == -1 || sc == -1)
						break e;
					map[sr][sc] = que.poll();
				}
				sd = (sd + 1) % 4;
			}
			cnt++;
		}
		que.clear();
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
