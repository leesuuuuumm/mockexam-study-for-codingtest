import java.io.*;
import java.util.*;

public class Main {

	static class Shark {
		int r;
		int c;
		int s; // 속력
		int d; // 방향
		int z; // 크기

		public Shark(int r, int c, int d) {
			this.r = r;
			this.c = c;
			this.d = d;
		}

		public Shark(int s, int z) {
			this.s = s;
			this.z = z;
		}
	}

	static int[][] map;
	static Shark[] sk; // 상어
	static Shark[] sInfo;

	static int R, C, M;
	static int sum;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		map = new int[R][C];
		sk = new Shark[M + 1];
		sInfo = new Shark[M + 1];
		sum = 0;

		for (int i = 1; i <= M; i++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			int s = Integer.parseInt(st.nextToken());
			int d = Integer.parseInt(st.nextToken()) - 1;
			int z = Integer.parseInt(st.nextToken());

			map[r][c] = i;
			sk[i] = new Shark(r, c, d);
			sInfo[i] = new Shark(s, z);
		}

		for (int c = 0; c < C; c++) {
			catchTheShark(c);
			movingSharks();
		}
		System.out.println(sum);

	}

	private static void catchTheShark(int c) {
		for (int r = 0; r < R; r++) {
			if (map[r][c] != 0) {
				sum += sInfo[map[r][c]].z;
				sk[map[r][c]] = null;
				map[r][c] = 0;
				break;
			}
		}
	}

	static int[] dr = { -1, 1, 0, 0 }; // 상하우좌
	static int[] dc = { 0, 0, 1, -1 };

	private static void movingSharks() {
		for (int i = 1; i <= M; i++) {
			if (sk[i] == null)
				continue;

			Shark cur = sk[i];
			map[cur.r][cur.c] = 0;

			int s = sInfo[i].s;
			int nr = cur.r;
			int nc = cur.c;

			if (cur.d == 0 || cur.d == 1) {
				s %= ((R - 1) * 2);

				for (int dir = 0; dir < s; dir++) {
					if (nr == 0)
						cur.d = 1;
					else if (nr == R - 1)
						cur.d = 0;

					nr += dr[cur.d];

				}
			} else {
				s %= ((C - 1) * 2);

				for (int dir = 0; dir < s; dir++) {
					if (nc == 0)
						cur.d = 2;
					if (nc == C - 1)
						cur.d = 3;
					nc += dc[cur.d];
				}
			}

			sk[i] = new Shark(nr, nc, cur.d);
		}

		start();
	}

	private static void start() {
		for (int i = 1; i <= M; i++) {
			if (sk[i] == null)
				continue;
			Shark cur = sk[i];
			if (map[cur.r][cur.c] == 0) {
				map[cur.r][cur.c] = i;
			} else {
				if (sInfo[i].z > sInfo[map[cur.r][cur.c]].z) {
					sk[map[cur.r][cur.c]] = null;
					map[cur.r][cur.c] = i;
				} else {
					sk[i] = null;
				}
			}

		}

	}
}
