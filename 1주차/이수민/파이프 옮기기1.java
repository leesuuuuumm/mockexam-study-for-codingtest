import java.io.*;
import java.util.*;

public class Main {

	static int[][] map;
	static int N;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];
		for (int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for (int j = 0; j < N; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		map[0][0] = 2;
		map[0][1] = 2;
		// 숫자 2는 파이프
		// 1은 벽
		answer = 0;
		dfs(0, 0, 0, 0, 1);
		System.out.println(answer);

	}

	// 파이프 방향
	static int answer;

	private static void dfs(int d, int fr, int fc, int sr, int sc) { // 첫번째 rc 두번째 rc
		if (sr == N - 1 && sc == N - 1) {
			answer++;
			return;
		}

		if (d == 0) { // 가로
			int nr = sr;
			int nc = sc + 1;
			if (check(nr, nc) && map[nr][nc] == 0) {
				map[fr][fc] = 0;
				map[nr][nc] = 2;
				dfs(d, sr, sc, nr, nc);
				map[fr][fc] = 2;
				map[nr][nc] = 0;
			}

			nr = sr + 1;
			nc = sc + 1;
			if (check(nr, nc) && check(nr, nc - 1) && check(nr - 1, nc) && map[nr][nc] == 0 && map[nr][nc - 1] == 0
					&& map[nr - 1][nc] == 0) {

				map[fr][fc] = 0;
				map[nr][nc] = 2;
				dfs(2, sr, sc, nr, nc);
				map[fr][fc] = 2;
				map[nr][nc] = 0;
			}

		} else if (d == 1) { // 새로
			int nr = sr + 1;
			int nc = sc;

			if (check(nr, nc) && map[nr][nc] == 0) {
				map[fr][fc] = 0;
				map[nr][nc] = 2;
				dfs(d, sr, sc, nr, nc);
				map[fr][fc] = 2;
				map[nr][nc] = 0;
			}

			nr = sr + 1;
			nc = sc + 1;
			if (check(nr, nc) && check(nr, nc - 1) && check(nr - 1, nc) && map[nr][nc] == 0 && map[nr][nc - 1] == 0
					&& map[nr - 1][nc] == 0) {
				map[fr][fc] = 0;
				map[nr][nc] = 2;
				dfs(2, sr, sc, nr, nc);
				map[fr][fc] = 2;
				map[nr][nc] = 0;
			}

		} else if (d == 2) { // 대각선
			int nr = sr;
			int nc = sc + 1;
			if (check(nr, nc) && map[nr][nc] == 0) {
				map[fr][fc] = 0;
				map[nr][nc] = 2;
				dfs(0, sr, sc, nr, nc);
				map[fr][fc] = 2;
				map[nr][nc] = 0;
			}
			nr = sr + 1;
			nc = sc;

			if (check(nr, nc) && map[nr][nc] == 0) {
				map[fr][fc] = 0;
				map[nr][nc] = 2;
				dfs(1, sr, sc, nr, nc);
				map[fr][fc] = 2;
				map[nr][nc] = 0;
			}

			nr = sr + 1;
			nc = sc + 1;
			if (check(nr, nc) && check(nr, nc - 1) && check(nr - 1, nc) && map[nr][nc] == 0 && map[nr][nc - 1] == 0
					&& map[nr - 1][nc] == 0) {
				map[fr][fc] = 0;
				map[nr][nc] = 2;
				dfs(2, sr, sc, nr, nc);
				map[fr][fc] = 2;
				map[nr][nc] = 0;
			}
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
