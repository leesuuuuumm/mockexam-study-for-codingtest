import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int num;
		int dist;

		public Point(int num, int dist) {
			this.num = num;
			this.dist = dist;
		}
	}

	static int N, T, G;
	static Queue<Point> que;
	static int[] v;
	static int answer;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());
		G = Integer.parseInt(st.nextToken());

		que = new LinkedList<>();
		v = new int[100000];

		Arrays.fill(v, Integer.MAX_VALUE);

		que.offer(new Point(N, 0));

		v[N] = 0;
		answer = -1;
		bfs();
		System.out.println(answer == -1 ? "ANG" : answer);

	}

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			if (cur.dist > T) {
				return;
			}

			if (cur.num == G) {
				answer = Math.min(v[cur.num], cur.dist);
				return;
			}

			pushButton(cur.num + 1, cur.dist + 1, true);
			if (cur.num > 0) {
				pushButton(cur.num * 2, cur.dist + 1, false);
			}
		}

	}

	private static void pushButton(int cur, int dist, boolean ck) {
		if (!check(cur))
			return;

		if (!ck) {
			if (cur < 100000 && cur >= 10000) {
				cur -= 10000;
			} else if (cur < 10000 && cur >= 1000) {
				cur -= 1000;
			} else if (cur < 1000 && cur >= 100) {
				cur -= 100;
			} else if (cur < 100 && cur >= 10) {
				cur -= 10;
			} else {
				if (cur > 0)
					cur -= 1;
			}

		}

		if (v[cur] > dist) {
			v[cur] = dist;
			que.offer(new Point(cur, dist));
		}

	}

	private static boolean check(int now) {
		return now >= 0 && now <= 99999;

	}
}
