import java.io.*;
import java.util.*;

public class Solution {
	static class Point {
		int r;
		int c;
		int dist;
		int d;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}

		public Point(int r, int c, int dist) {
			this.r = r;
			this.c = c;
			this.dist = dist;
		}
	}

	static int N, W, H, T;
	static int[] input;
	static int[][] map;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		for (int t = 1; t <= T; t++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			N = Integer.parseInt(st.nextToken());
			W = Integer.parseInt(st.nextToken());
			H = Integer.parseInt(st.nextToken());
			input = new int[N];
			map = new int[H][W];
			for (int i = 0; i < H; i++) {
				st = new StringTokenizer(br.readLine());
				for (int j = 0; j < W; j++) {
					map[i][j] = Integer.parseInt(st.nextToken());
				}
			}

			min = Integer.MAX_VALUE;
			que = new LinkedList<>();
			duplicateNpR(0);
			System.out.println("#" + t + " " + min);

		}
	}

	static int[][] tmp;
	static int min;

	// 중복 순열로 순서 구해줘야함!
	private static void duplicateNpR(int cnt) {

		if (cnt == N) {
			tmp = new int[H][W];
			for (int r = 0; r < H; r++) {
				for (int c = 0; c < W; c++) {
					tmp[r][c] = map[r][c];
				}
			}

			// System.out.println(Arrays.toString(input));
			startGame();
			int b = 0;

			for (int r = 0; r < H; r++) {
				for (int c = 0; c < W; c++) {
					if (tmp[r][c] != 0) {
						b++;
					}
				}
			}
			min = Math.min(b, min);
			return;
		}

		for (int j = 0; j < W; j++) {
			input[cnt] = j;
			duplicateNpR(cnt + 1);
		}
	}

	private static void startGame() {
		for (int i = 0; i < input.length; i++) {
			for (int r = 0; r < H; r++) {

				if (tmp[r][input[i]] != 0) {

					if (tmp[r][input[i]] > 1) {
						que.offer(new Point(r, input[i], tmp[r][input[i]]));
						breakBrick();
					}
					tmp[r][input[i]] = 0;
					// print();
					fallTheBrick();
					// print();
					break;
				}
			}
		}
	}
  
	// 범위만큼 더해주지 않았음!!!!! -> 2를 먹었으면 해당애애서 더 넓히기 
	static int[] dr = { 0, -1, 1, 0 };
	static int[] dc = { 1, 0, 0, -1 };
	static Queue<Point> que;

	private static void breakBrick() {
		while (!que.isEmpty()) {
			Point cur = que.poll();
			for (int d = 0; d < 4; d++) {
				int nr = cur.r;
				int nc = cur.c;

				for (int i = 0; i < cur.dist - 1; i++) {
					nr += dr[d];
					nc += dc[d];

					if (!check(nr, nc))
						break;

					if (tmp[nr][nc] != 0) {
						if (tmp[nr][nc] > 1) {
							que.offer(new Point(nr, nc, tmp[nr][nc]));
						}
						tmp[nr][nc] = 0;
					}

				}

			}
		}

	}

	private static void fallTheBrick() {
		for (int c = 0; c < W; c++) {
			ArrayList<Integer> list = new ArrayList<>();
			for (int r = H - 1; r >= 0; r--) {
				if (tmp[r][c] != 0) {
					list.add(tmp[r][c]);
					tmp[r][c] = 0;
				}
			}
			int r = H - 1;
			for (Integer i : list) {
				tmp[r][c] = i;
				r--;
			}
		}

	}

//	private static void print() {
//		for (int r = 0; r < H; r++) {
//			for (int c = 0; c < W; c++) {
//				System.out.print(tmp[r][c] + " ");
//			}
//			System.out.println();
//		}
//		System.out.println();
//	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < H && nc >= 0 && nc < W;
	}
}
