import java.io.*;
import java.util.*;

public class Main {

	static int N, M, K;
	static int[][] map;
	static int[][] sticker;
	static int[][] tmp;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		map = new int[N][M];

		for (int i = 0; i < K; i++) {
			st = new StringTokenizer(br.readLine());
			int R = Integer.parseInt(st.nextToken());
			int C = Integer.parseInt(st.nextToken());
			sticker = new int[R][C];
			for (int r = 0; r < R; r++) {
				st = new StringTokenizer(br.readLine());
				for (int c = 0; c < C; c++) {
					sticker[r][c] = Integer.parseInt(st.nextToken());
				}
			}
			flag = false;

			// (1)회전 안한 상태로 스티커 붙여보기
			putASticker(R, C);


			for (int d = 0; d < 3; d++) {
				if (flag)
					break;

				// (2) 1번이 실패되면 회전 한번 해주고 스티커 붙여주기 (회전은 총 3번해야함)
				if (d == 0 || d == 2) {

					copyArr(R, C);
					rotation(C, R);
					putASticker(C, R);


				} else {
					copyArr(C, R);
					rotation(R, C);
					putASticker(R, C);

				}

			}

		}
		int answer = 0;
		for(int r=0;r<N;r++) {
			for(int c=0;c<M;c++) {
				if(map[r][c] == 1)answer++;
			}
		}
		System.out.println(answer);
	}


	private static void copyArr(int R, int C) {
		tmp = new int[R][C];

		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				tmp[r][c] = sticker[r][c];
			}
		}

	}

	private static void rotation(int R, int C) {
		sticker = new int[R][C]; // [r][c] => [c][r] / [c][r] => [r][c]
		// 2,5
		for (int r = 0; r < C; r++) { // 5
			for (int c = 0; c < R; c++) { // 2
				sticker[c][C - 1 - r] = tmp[r][c];
			}
		}

	}

	static boolean flag;

	private static void putASticker(int R, int C) {
		for (int r = 0; r < N; r++) {
			e: for (int c = 0; c < M; c++) {

				for (int sr = r; sr < r + R; sr++) {
					for (int sc = c; sc < c + C; sc++) {
						if (!check(sr, sc)) {
							continue e;
						}

						if (map[sr][sc] == 1 && sticker[sr - r][sc - c] == 1) {
							continue e;
						}

					}
				}
				for (int sr = r; sr < r + R; sr++) {
					for (int sc = c; sc < c + C; sc++) {
						if(sticker[sr-r][sc-c] == 0) continue;
						map[sr][sc] = sticker[sr - r][sc - c];
					}
				}
				flag = true;
				return;

			}
		}

	}

	private static boolean check(int sr, int sc) {
		return sr >= 0 && sr < N && sc >= 0 && sc < M;
	}

}
