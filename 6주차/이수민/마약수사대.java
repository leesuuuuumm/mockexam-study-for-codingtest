import java.io.*;
import java.util.*;

public class Main {
	static int N, M;
	static ArrayList<ArrayList<Integer>> list;
	static int[] v;
	static Queue<Integer> que;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		list = new ArrayList<>();
		v = new int[N];
		que = new LinkedList<>();

		for (int i = 0; i < N; i++) {
			list.add(new ArrayList<>());
		}

		for (int i = 0; i < M; i++) {
			char[] ch = br.readLine().toCharArray();
			list.get(ch[0] - 65).add(ch[2] - 65);
		}

		st = new StringTokenizer(br.readLine());
		int end = Integer.parseInt(st.nextToken());
		for (int i = 0; i < end; i++) {
			int num = st.nextToken().charAt(0) - 65;
			v[num] = 1;
			dfs(num);
		}
		answer = 0;

		for (int i = 0; i < N; i++) {
			if (list.get(i).size() == 0 || v[i] != 0)
				continue;

			v[i] = 1;
			que.offer(i);
			bfs();
		}
		System.out.println(answer);
	}

	private static void dfs(int num) {

		for (int i = 0; i < list.get(num).size(); i++) {
			if (v[list.get(num).get(i)] == 0) {
				v[list.get(num).get(i)] = 2;
				dfs(list.get(num).get(i));
			}
		}

	}

	static int answer;

	private static void bfs() {
		while (!que.isEmpty()) {
			int cur = que.poll();

			for (int i = 0; i < list.get(cur).size(); i++) {

				if (v[list.get(cur).get(i)] != 1) {
					v[list.get(cur).get(i)] = 1;
					que.offer(list.get(cur).get(i));
					answer++;

				}

			}
		}
	}

}
