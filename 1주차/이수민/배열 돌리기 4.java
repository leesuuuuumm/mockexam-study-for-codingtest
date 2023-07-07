import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int s;

		public Point(int r, int c, int s) {
			this.r = r;
			this.c = c;
			this.s = s;
		}
	}

	static int[][] map;
	static int N, M, K;
	static Point[] arr;
	static int[] selc;
	static boolean[] v;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		map = new int[N][M];
		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}
		arr = new Point[K];

		for (int i = 0; i < K; i++) {
			st = new StringTokenizer(br.readLine());
			arr[i] = new Point(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1,
					Integer.parseInt(st.nextToken()));
		}
		selc = new int[K];
		v = new boolean[K];
		answer = Integer.MAX_VALUE;
		nPr(0);
		System.out.println(answer);
	}

	static int[][] copy;
	static int answer;

	private static void nPr(int cnt) {
		if (cnt == K) {
			copy = new int[N][M];
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					copy[i][j] = map[i][j];
				}
			}

			for (int i = 0; i < selc.length; i++) {
				rotateArr(selc[i]);
			}
			answer = Math.min(sumArr(), answer);
			return;
		}

		for (int i = 0; i < K; i++) {
			if (v[i])
				continue;

			selc[cnt] = i;
			v[i] = true;
			nPr(cnt + 1);
			v[i] = false;

		}

	}

	private static void rotateArr(int num) {
		Point cur = arr[num];

		int sr = cur.r - cur.s; 
		int sc = cur.c - cur.s;
		int ir = cur.r + cur.s;
		int ic = cur.c + cur.s;

		while (true) {
			int tmp = copy[sr][sc];

			for (int j = sr; j < ir; j++) {
				copy[j][sc] = copy[j + 1][sc];
			}

			for (int j = sc; j < ic; j++) {
				copy[ir][j] = copy[ir][j + 1];
			}
			for (int j = ir; j > sr; j--) {
				copy[j][ic] = copy[j - 1][ic];
			}
			for (int j = ic; j > sc + 1; j--) {
				copy[sr][j] = copy[sr][j - 1];
			}
			copy[sr][sc + 1] = tmp;
			
			sr += 1;
			sc += 1;
			ir -= 1;
			ic -= 1;

			if (sr == ir && sc == ic)
				break;

		}
	}

	private static int sumArr() {

		int min = Integer.MAX_VALUE;
		for (int i = 0; i < N; i++) {
			int sum = 0;
			for (int j = 0; j < M; j++) {
				sum += copy[i][j];
			}
			min = Math.min(min, sum);
		}
		return min;
	}

}
