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

	static int N;
	static ArrayList<ArrayList<Integer>> list;
	static boolean[] v;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		list = new ArrayList<>();
		for (int i = 0; i <= N; i++) {
			list.add(new ArrayList<>());
		}

		for (int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			list.get(a).add(b);
			list.get(b).add(a);
		}
		f = false;

		// 순환된 부분을 dfs로 찾고 -> bfs로 거리 계산해주기!!!
		for (int i = 1; i <= N; i++) {
			v = new boolean[N + 1];
			v[i] = true;

			dfs(i, 0, i);
			if(f) {
				break;
			}
		}
		sb = new StringBuilder();

		// bfs로 최단 경로 찾아주기
		for (int i = 1; i <= N; i++) {
			que = new LinkedList<>();
			ck = new boolean[N + 1];
			if (!v[i]) {
				que.offer(new Point(i, 0));
				bfs();
			} else {
				sb.append(0).append(" ");
			}
		}
		System.out.println(sb.toString().trim());

	}

	static boolean f;
	static boolean[] ck;

	private static void dfs(int i, int pre, int now) {
		if (f) {
			return;
		}

		for (int j = 0; j < list.get(now).size(); j++) {
			if (list.get(now).get(j) != pre) {
				if (list.get(now).get(j) == i) {
					f = true;
					return;
				}
				if (!v[list.get(now).get(j)]) {
					v[list.get(now).get(j)] = true;

					dfs(i, now, list.get(now).get(j));
					if (f) {
						return;
					}
					v[list.get(now).get(j)] = false;

				}

			}
		}

	}

	static Queue<Point> que;
	static StringBuilder sb;

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();
			for (int j = 0; j < list.get(cur.num).size(); j++) {
				if (v[list.get(cur.num).get(j)]) {
					sb.append(cur.dist + 1).append(" ");
					return;
				}
				if (!ck[list.get(cur.num).get(j)]) {
					que.offer(new Point(list.get(cur.num).get(j), cur.dist + 1));
					ck[list.get(cur.num).get(j)] = true;
				}
			}
		}

	}
}
