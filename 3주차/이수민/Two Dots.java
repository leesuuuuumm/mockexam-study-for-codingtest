import java.io.*;
import java.util.*;

public class Main {

	static char[][] map;
	static boolean[][] v;
	static int N, M;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new char[N][M];
		v = new boolean[N][M];
		for (int r = 0; r < N; r++) {
			map[r] = br.readLine().toCharArray();
		}
		flag = false;

		a: for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				v[r][c] = true;
				dfs(r, c, 1, r, c);
				v[r][c] = false;

				if (flag) {
					break a;
				}

			}
		}
		System.out.println(flag ? "Yes" : "No");
	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { -1, 0, 0, 1 };
	static boolean flag;

	private static void dfs(int r, int c, int cnt, int sr, int sc) {
		if (flag)
			return;

		for (int d = 0; d < 4; d++) {
			int nr = r + dr[d];
			int nc = c + dc[d];

			if (cnt >= 4 && (nr == sr && nc == sc)) {
				flag = true;
				return;
			}

			if (!check(nr, nc) || v[nr][nc])
				continue;

			if (map[nr][nc] == map[r][c]) {
				v[nr][nc] = true;
				cnt++;
				dfs(nr, nc, cnt, sr, sc);
				v[nr][nc] = false;
				cnt--;
			}

		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
