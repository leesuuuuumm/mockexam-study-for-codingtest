import java.io.*;
import java.util.*;

public class Solution {

	static int[][] map;
	static int T, N, X;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		for (int t = 1; t <= T; t++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			X = Integer.parseInt(st.nextToken());

			map = new int[N][N];

			for (int r = 0; r < N; r++) {
				st = new StringTokenizer(br.readLine());
				for (int c = 0; c < N; c++) {
					map[r][c] = Integer.parseInt(st.nextToken());
				}
			}
			int answer = 0;

			a: for (int r = 0; r < N; r++) {
				int c = 0;
				int cnt = 1;

				while (c < N - 1) {

					if (Math.abs(map[r][c] - map[r][c + 1]) >= 2)
						continue a;

					if (map[r][c] < map[r][c + 1] && cnt < X)
						continue a;

					if (map[r][c] > map[r][c + 1]) {
						cnt = 1;

						for (int i = c + 2; i <= c + X; i++) {
							if (i >= N) {
								continue a;
							}
							if (map[r][c + 1] != map[r][i]) {
								continue a;
							}

						}
						c += X;
						if (c + 1 < N && map[r][c + 1] == map[r][c]) {
							cnt = 0;
						}
						continue;

					}

					if (map[r][c] == map[r][c + 1]) {
						cnt++;
					} else {
						cnt = 1;
					}
					c++;

				}
				answer++;
			}
			a: for (int c = 0; c < N; c++) {
				int r = 0;
				int cnt = 1;

				while (r < N - 1) {

					if (Math.abs(map[r][c] - map[r + 1][c]) >= 2)
						continue a;

					if (map[r][c] < map[r + 1][c] && cnt < X)
						continue a;

					if (map[r][c] > map[r + 1][c]) {
						cnt = 1;

						for (int i = r + 2; i <= r + X; i++) {
							if (i >= N) {
								continue a;
							}
							if (map[r + 1][c] != map[i][c]) {
								continue a;
							}

						}
						r += X;
						if (r + 1 < N && map[r + 1][c] == map[r][c]) {
							cnt = 0;
						}
						continue;
					}

					if (map[r][c] == map[r + 1][c]) {
						cnt++;
					} else {
						cnt = 1;
					}
					r++;

				}
				answer++;
			}
			System.out.println("#" + t + " " + answer);

		}

	}
}
