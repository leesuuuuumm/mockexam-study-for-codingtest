import java.io.*;
import java.util.*;

public class Main {

	static int N;
	static int[][] map;
	static int tr, tc;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];

		for (int r = 0; r < N; r++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}
		answer = 0;
		tr = N / 2;
		tc = N / 2;

		moveTornado();
		System.out.println(answer);

	}

	static int[][][] td = { { { 0, 0, -1, 1, -1, 1, -2, 2, -1, 1, 0 }, { -1, -2, 0, 0, -1, -1, -1, -1, -2, -2, -3 } },
			{ { 1, 2, 0, 0, 1, 1, 1, 1, 2, 2, 3 }, { 0, 0, -1, 1, -1, 1, -2, 2, -1, 1, 0 } },
			{ { 0, 0, -1, 1, -1, 1, -2, 2, -1, 1, 0 }, { 1, 2, 0, 0, 1, 1, 1, 1, 2, 2, 3 } },
			{ { -1, -2, 0, 0, -1, -1, -1, -1, -2, -2, -3 }, { 0, 0, -1, 1, -1, 1, -2, 2, -1, 1, 0 } } };
	static double[] rate = { 0, 0, 0.01, 0.01, 0.07, 0.07, 0.02, 0.02, 0.1, 0.1, 0.05 };

	static int[] dr = { 0, 1, 0, -1 };
	static int[] dc = { -1, 0, 1, 0 };

	private static void moveTornado() {
		int k = 1;
		int dir = 0;
		e: while (true) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < k; j++) {
					start(dir);
					tr += dr[dir];
					tc += dc[dir];

					if (tr == 0 && tc == 0)
						break e;
				}

				dir = (dir + 1) % 4;
			}
			k++;
		}
	}

	static int answer;

	private static void start(int dir) {
		int y = map[tr + td[dir][0][0]][tc + td[dir][1][0]];
		map[tr + td[dir][0][0]][tc + td[dir][1][0]] = 0;
		int rSum = 0;

		for (int i = 2; i < 11; i++) {
			int nr = tr + td[dir][0][i];
			int nc = tc + td[dir][1][i];

			if (!check(nr, nc)) {
				answer += (int) (y * rate[i]);
			} else {
				map[nr][nc] += (int) (y * rate[i]);
			}
			rSum += (y * rate[i]);

		}
		y -= rSum;

		if (!check(tr + td[dir][0][1], tc + td[dir][1][1])) {
			answer += y;
		} else {
			map[tr + td[dir][0][1]][tc + td[dir][1][1]] += y;
		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}

}
