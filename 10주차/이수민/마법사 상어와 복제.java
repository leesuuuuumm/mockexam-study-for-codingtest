import java.io.*;
import java.util.*;

public class Main {

	static class Point {
		int r;
		int c;
		int d;

		public Point(int r, int c, int d) {
			this.r = r;
			this.c = c;
			this.d = d;
		}
	}

	static int M, S; // m개의 물고기,s번 돌기
	static int[][] map;
	static ArrayList<Integer>[][] fmap;
	static ArrayList<Integer>[][] copyfmap;
	static int sr, sc;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		M = Integer.parseInt(st.nextToken());
		S = Integer.parseInt(st.nextToken());

		map = new int[4][4];
		fmap = new ArrayList[4][4];
		copyfmap = new ArrayList[4][4];

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				fmap[r][c] = new ArrayList<>();
				copyfmap[r][c] = new ArrayList<>();
			}
		}

		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			int d = Integer.parseInt(st.nextToken()) - 1;

			fmap[r][c].add(d);
			copyfmap[r][c].add(d);
		}
		st = new StringTokenizer(br.readLine());
		sr = Integer.parseInt(st.nextToken()) - 1;
		sc = Integer.parseInt(st.nextToken()) - 1;

		list = new ArrayList<>();
		n = new int[3];
		k = 0;
		duplicateNPR(0);
		while (S-- > 0) {
			moveFishes();
			moveShark();

			removeSmell();

			sharkMagic();

		}

		System.out.println(answer());

	}

	static ArrayList<int[]> list;
	static int[] n;
	static int k;

	private static void duplicateNPR(int cnt) {
		if (cnt == 3) {
			list.add(new int[3]);
			for (int i = 0; i < 3; i++) {
				list.get(k)[i] = n[i];
			}
			k++;
			return;
		}
		for (int i = 0; i < 4; i++) {
			n[cnt] = i;
			duplicateNPR(cnt + 1);

		}

	}

	static int[] dr = { 0, -1, -1, -1, 0, 1, 1, 1 };
	static int[] dc = { -1, -1, 0, 1, 1, 1, 0, -1 };

	private static void moveFishes() {
		Queue<Point> tmp = new LinkedList<>();

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {

				e: for (int i = 0; i < fmap[r][c].size(); i++) {
					int curd = fmap[r][c].get(i);

					for (int d = 0; d < 8; d++) {
						if (d > 0) {
							if (curd == 0)
								curd = 8;
							curd -= 1;
						}
						int nr = r + dr[curd];
						int nc = c + dc[curd];
						if (!check(nr, nc) || (sr == nr && sc == nc) || map[nr][nc] != 0)
							continue;


						tmp.offer(new Point(nr, nc, curd));
						continue e;
					}
					tmp.offer(new Point(r, c, fmap[r][c].get(i)));
				}
				fmap[r][c] = new ArrayList<>();

			}
		}

		while (!tmp.isEmpty()) {
			Point cur = tmp.poll();
			fmap[cur.r][cur.c].add(cur.d);
		}
	}

	static int[] sdr = { -1, 0, 1, 0 };
	static int[] sdc = { 0, -1, 0, 1 };

	private static void moveShark() {
		int max = -1;
		int mr = sr;
		int mc = sc;
		int mi = 0;
		e: for (int i = 0; i < list.size(); i++) {
			int nr = sr;
			int nc = sc;
			int fcnt = 0;
			boolean[][] v = new boolean[4][4];

			for (int j = 0; j < 3; j++) {
				int d = list.get(i)[j];

				nr += sdr[d];
				nc += sdc[d];

				if (!check(nr, nc))
					continue e;

				if (!v[nr][nc]) {
					fcnt += fmap[nr][nc].size();
					v[nr][nc] = true;
				}
			}
			if (list.get(i)[0] == 3 && list.get(i)[1] == 3 && list.get(i)[2] == 2) {

			}

			if (fcnt > max) {
				max = fcnt;
				mr = nr;
				mc = nc;
				mi = i;

			}
		}

		int nr = sr;
		int nc = sc;
		for (int i = 0; i < 3; i++) {
			nr += sdr[list.get(mi)[i]];
			nc += sdc[list.get(mi)[i]];
			if (fmap[nr][nc].size() > 0) {
				map[nr][nc] = 3;
				fmap[nr][nc] = new ArrayList<>();
			}
		}
		sr = mr;
		sc = mc;

	}

	private static void removeSmell() {
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				if (map[r][c] > 0) {
					map[r][c]--;
				}
			}
		}
	}

	private static void sharkMagic() {
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				for (int i = 0; i < copyfmap[r][c].size(); i++) {
					fmap[r][c].add(copyfmap[r][c].get(i));
				}
				copyfmap[r][c] = new ArrayList<>();
			}
		}

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				for (int i = 0; i < fmap[r][c].size(); i++) {
					copyfmap[r][c].add(fmap[r][c].get(i));
				}
			}
		}
	}

	private static int answer() {
		int fishCnt = 0;
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				fishCnt += fmap[r][c].size();
			}
		}

		return fishCnt;
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < 4 && nc >= 0 && nc < 4;
	}
}
