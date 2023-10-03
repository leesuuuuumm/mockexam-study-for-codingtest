import java.io.*;
import java.util.*;
public class Main {

	static class Point implements Comparable<Point> {
		int r;
		int c;
		int maxR;
		int minC;
		int redCnt;
		ArrayList<Point> list = new ArrayList<>();

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}

		public Point(int maxR, int minC, int redCnt, ArrayList<Point> list) {
			this.maxR = maxR;
			this.minC = minC;
			this.redCnt = redCnt;
			this.list = list;
		}

		public int compareTo(Point o) {
			if (this.list.size() == o.list.size()) {
				if (this.redCnt == o.redCnt) {
					if (o.maxR == this.maxR) {
						return Integer.compare(this.minC, o.minC);
					}
					return Integer.compare(o.maxR, this.maxR);
				}
				return Integer.compare(this.redCnt, o.redCnt);
			}
			return Integer.compare(o.list.size(), this.list.size());
		}
	}

	static int[][] map;
	static int N, M;
	static boolean[][] v;
	static PriorityQueue<Point> pq;
	static int score;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		map = new int[N][N];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}
		flag = true;
		score = 0;

		while (true) {
			searchBombs();
			if (!flag)
				break;
			gravity();
			reverseRotation();
			gravity();
		}
		System.out.println(score);

	}

	static Queue<Point> que;
	static boolean flag;

	private static void searchBombs() {
		que = new LinkedList<>();
		pq = new PriorityQueue<>();
		v = new boolean[N][N];

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (map[r][c] > 0 && map[r][c] <= M) {
					v[r][c] = true;
					que.offer(new Point(r, c));
					bfs(map[r][c]);
				}
			}
		}
		if (pq.size() == 0) {
			flag = false;
			return;
		}
		score += getScore();
		removeBombs();
	}

	static int[] dr = { 0, 1, 0, -1 };
	static int[] dc = { 1, 0, -1, 0 };

	private static void bfs(int color) {
		ArrayList<Point> list = new ArrayList<>();
		ArrayList<Point> redList = new ArrayList<>();
		list.add(new Point(que.peek().r, que.peek().c));
		int maxR = que.peek().r;
		int minC = que.peek().c;

		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc] || map[nr][nc] != 0 && map[nr][nc] != color)
					continue;

				if (map[nr][nc] == 0) {
					redList.add(new Point(nr, nc));
				} else if (map[nr][nc] == color) {
					maxR = Math.max(maxR, nr);
					minC = Math.min(minC, nc);
				}
				list.add(new Point(nr, nc));
				que.offer(new Point(nr, nc));
				v[nr][nc] = true;
			}

		}

		if (list.size() == 1)
			return;
		pq.offer(new Point(maxR, minC, redList.size(), list));
		for (Point i : redList) {
			v[i.r][i.c] = false;
		}
	}

	private static void removeBombs() {
		Point cur = pq.poll();
		for (Point i : cur.list) {
			map[i.r][i.c] = M + 1;
		}
	}

	private static int getScore() {
		return pq.peek().list.size() * pq.peek().list.size();
	}

	private static void gravity() {
		for (int c = 0; c < N; c++) {
			ArrayList<Integer> list = new ArrayList<>();
			for (int r = N - 1; r >= 0; r--) {
				if (map[r][c] >= 0 && map[r][c] <= M) {
					list.add(map[r][c]);
					map[r][c] = M + 1;
				} else if (map[r][c] == -1) {
					list.add(-1);
				}
			}
			for (int r = N - 1; r >= 0; r--) {
				if (list.size() == 0)
					break;
				if (list.get(0) == -1) {
					if (map[r][c] == -1) {
						list.remove(0);
					}
					continue;
				}
				map[r][c] = list.remove(0);
			}

		}

	}

	private static void reverseRotation() {
		int[][] tmp = new int[N][N];
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				tmp[N - 1 - c][r] = map[r][c];
			}
		}
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				map[r][c] = tmp[r][c];
			}
		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
//  1h59m
