import java.io.*;
import java.util.*;
public class Main {
	static class Point {
		int r;
		int c;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}

	static int[][] map;
	static int N, M;
	static ArrayList<Point> list;
	static Point[] select;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		map = new int[N][N];
		list = new ArrayList<>();
		select = new Point[M];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				if (map[r][c] == 2) {
					list.add(new Point(r, c));
				}
			}
		}

		dist = Integer.MAX_VALUE;

		nCr(0, 0);
		System.out.println(dist);

	}

	private static void nCr(int cnt, int start) {
		if (cnt == M) {
			dist = Math.min(dist, minDistance());
			return;
		}

		for (int i = start; i < list.size(); i++) {
			select[cnt] = list.get(i);
			nCr(cnt + 1, i + 1);

		}
	}

	static int dist;

	private static int minDistance() {
		int sum = 0;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				int min = Integer.MAX_VALUE;
				if (map[r][c] == 1) {

					for (int i = 0; i < M; i++) {
						min = Math.min(min, (Math.abs(r - select[i].r) + Math.abs(c - select[i].c)));
					}

					sum += min;
				}
			}
		}
		return sum;

	}
}
