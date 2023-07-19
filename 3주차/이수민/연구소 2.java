import java.io.*;
import java.util.*;

public class Main {
	static class Point implements Comparable<Point> {
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

		public int compareTo(Point o) {
			return Integer.compare(this.dist, o.dist);
		}
	}

	static int[][] map;
	static int N, M, answer;
	static Point[] input;
	static ArrayList<Point> list;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new int[N][N];
		input = new Point[M];
		list = new ArrayList<>();

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				if (map[r][c] == 2) {
					list.add(new Point(r, c));
				}
			}
		}
		answer = Integer.MAX_VALUE;

		nCr(0, 0);
		System.out.println(answer == Integer.MAX_VALUE ? -1 : answer);

	}

	static int[][] tmp;
	static PriorityQueue<Point> pq;

	private static void nCr(int cnt, int start) {
		if (cnt == M) {
			tmp = new int[N][N];
			pq = new PriorityQueue<>();

			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					if (map[r][c] == 1) {
						tmp[r][c] = -1;
					}
				}
			}
			for (int i = 0; i < input.length; i++) {
				pq.offer(new Point(input[i].r, input[i].c, 0));
				tmp[input[i].r][input[i].c] = -2;
			}
			max = 0;
			bfs();
			answer = Math.min(max, answer);

			return;
		}

		for (int i = start; i < list.size(); i++) {
			input[cnt] = list.get(i);
			nCr(cnt + 1, i + 1);

		}

	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };
	static int max;

	private static void bfs() {
		while (!pq.isEmpty()) {
			Point cur = pq.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || tmp[nr][nc] < 0)
					continue;

				if (tmp[nr][nc] == 0) {
					pq.offer(new Point(nr, nc, cur.dist + 1));
					tmp[nr][nc] = cur.dist + 1;
				}
			}

		}

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (tmp[r][c] == 0) {
					max = Integer.MAX_VALUE;
					return;
				} else {
					max = Math.max(max, tmp[r][c]);
				}
			}
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}

}
