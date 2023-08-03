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

	static int[][][] map;
	static int N, M;
	static int[][] v;
	static Queue<Point> que;
	static int roomCnt;
	static int roomMaxSize;
	static ArrayList<Integer> roomSize;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		M = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());

		map = new int[N][M][4];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				int i = 0;
				int num = Integer.parseInt(st.nextToken());
				while (num > 0) {
					map[r][c][i] = num % 2;
					i++;
					num /= 2;
				}
			}
		}
		que = new LinkedList<>();
		v = new int[N][M];
		roomCnt = 0;
		roomMaxSize = 0;
		roomSize = new ArrayList<>();
		roomSize.add(0);

		int cnt = 0;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {

				if (v[r][c] == 0) {
					que.offer(new Point(r, c));
					v[r][c] = ++cnt;
					bfs(cnt);
				}

			}
		}
		roomCnt = cnt;
		hm = new HashMap<>();

		for (int i = 1; i < roomSize.size(); i++) {
			hm.put(i, new ArrayList<>());

		}

		breakThewall();
		System.out.println(roomCnt);
		System.out.println(roomMaxSize);
		System.out.println(JoinRoom);

	}

	static int[] dr = { 0, -1, 0, 1 }; // 서, 북, 동, 남
	static int[] dc = { -1, 0, 1, 0 };

	private static void bfs(int cnt) {
		int size = 1;
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				if (map[cur.r][cur.c][d] == 0) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc))
						continue;

					if (v[nr][nc] == 0) {
						v[nr][nc] = cnt;
						size++;
						que.offer(new Point(nr, nc));
					}

				}

			}

		}
		roomSize.add(size);
		roomMaxSize = Math.max(size, roomMaxSize);

	}

	static HashMap<Integer, ArrayList<Integer>> hm;

	// 얼마나 근접해있는지 보기
	private static void breakThewall() {
		que.clear();
		boolean[][] ck = new boolean[N][M];

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (!ck[r][c]) {
					que.offer(new Point(r, c));
					ck[r][c] = true;
					boolean[] nCk = new boolean[roomSize.size()];

					while (!que.isEmpty()) {
						Point cur = que.poll();

						for (int d = 0; d < 4; d++) {
							int nr = cur.r + dr[d];
							int nc = cur.c + dc[d];

							if (!check(nr, nc) || ck[nr][nc])
								continue;

							if (!nCk[v[nr][nc]] && v[nr][nc] != v[r][c]) {
								hm.get(v[r][c]).add(v[nr][nc]);
								nCk[v[nr][nc]] = true;
							}

							if (v[nr][nc] == v[r][c]) {
								ck[nr][nc] = true;
								que.offer(new Point(nr, nc));
							}
						}
					}
				}
			}
		}

		JoinRoom = 0;
    
		for (Integer i : hm.keySet()) {
			for (int j = 0; j < hm.get(i).size(); j++) {
				JoinRoom = Math.max(JoinRoom, (roomSize.get(i) + roomSize.get(hm.get(i).get(j))));
			}
		}
	}

	static int JoinRoom;

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}

}
