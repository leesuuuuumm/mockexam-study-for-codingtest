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
			inputMarbleInQueue();
			removeMarble();
			divideMarble();
			makeMap();

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

	private static void inputMarbleInQueue() {
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

	}

	private static void removeMarble() {
		boolean stop = false;
		while (!stop) {
			stop = true;
			if (que.isEmpty()) {
				break;
			}
			int size = que.size();
			int cur = que.poll();
			int count = 1;

			for (int i = 0; i < size - 1; i++) {
				if (cur == que.peek()) {
					count++;
				} else {
					if (count > 3) {
						sum[cur] += count;
						stop = false;
					} else {
						for (int j = 0; j < count; j++) {
							que.offer(cur);
						}
					}
					count = 1;
				}
				cur = que.poll();
			}

			if (count < 4) {
				for (int j = 0; j < count; j++) {
					que.offer(cur);
				}
			} else {
				sum[cur] += count;
				stop = false;
			}
		}
	}

	static int[] sum;
	private static void divideMarble() {
		int count = 1;
		if (que.isEmpty()) {
			return;
		}
		int size = que.size();
		int cur = que.poll();
		for (int i = 0; i < size - 1; i++) {
			if (cur == que.peek()) {
				count++;
			} else {
				que.offer(count);
				que.offer(cur);

				count = 1;
			}
			cur = que.poll();
		}
		que.offer(count);
		que.offer(cur);
	}

	private static void makeMap() {
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

					if (que.isEmpty() || !check(sr, sc))
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
