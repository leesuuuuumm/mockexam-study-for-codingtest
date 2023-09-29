import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int sum;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}

		public Point(int r, int c, int sum) {
			this.r = r;
			this.c = c;
			this.sum = sum;
		}
	}

	static int[][] map;
	static int N, L, R;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		L = Integer.parseInt(st.nextToken());
		R = Integer.parseInt(st.nextToken());
		map = new int[N][N];
		que = new LinkedList<>();

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}

		answer = 0;
		while (true) {
			flag = false;
			moveEggs();
			if (!flag) {
				break;
			}
			answer++;

		}
		System.out.println(answer);

		// 1. 계란이 L<=map[r][c]<=R 이동 가능
		// 2. 분리된 계란들을 하나로 합치고 다시 분리한다 -> (합쳐진 계란의 총 합)/(합쳐진 계란들의 개수)

	}

	static Queue<Point> que;
	static boolean[][] v;
	static boolean flag;
	static int answer;

	private static void moveEggs() {
		v = new boolean[N][N];
		tmp = new LinkedList<>();
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (!v[r][c]) {
					que.offer(new Point(r, c));
					v[r][c] = true;
					bfs();
				}
			}
		}
		move();
	}

	static int[] dr = { 1, 0, -1, 0 };
	static int[] dc = { 0, -1, 0, 1 };
	static Queue<Point> tmp;

	private static void bfs() {
		ArrayList<Point> list = new ArrayList<>();
		int sum = map[que.peek().r][que.peek().c];
		list.add(new Point(que.peek().r, que.peek().c));
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				if (Math.abs(map[cur.r][cur.c] - map[nr][nc]) <= R && Math.abs(map[cur.r][cur.c] - map[nr][nc]) >= L) {
					list.add(new Point(nr, nc));
					que.offer(new Point(nr, nc));
					sum += map[nr][nc];
					v[nr][nc] = true;
				}
			}
		}

		if (list.size() == 1) {
			return;
		}
		int ans = sum / list.size();

		flag = true;
		for (Point i : list) {
			tmp.offer(new Point(i.r, i.c, ans));
		}

	}

	private static void move() {
		while (!tmp.isEmpty()) {
			Point cur = tmp.poll();
			map[cur.r][cur.c] = cur.sum;
		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}

}
