import java.io.*;
import java.util.*;

public class Main {

	static int N;
	static int[] peopleCnt;
	static boolean[] v;
	static ArrayList<ArrayList<Integer>> list;
	static int answer;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		peopleCnt = new int[N];
		v = new boolean[N];
		list = new ArrayList<>();

		StringTokenizer st = new StringTokenizer(br.readLine());
		for (int i = 0; i < N; i++) {
			peopleCnt[i] = Integer.parseInt(st.nextToken());
		}

		for (int i = 0; i <= N; i++) {
			list.add(new ArrayList<>());
		}

		for (int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine());

			int k = Integer.parseInt(st.nextToken());
			for (int j = 0; j < k; j++) {
				int c = Integer.parseInt(st.nextToken());
				list.get(i).add(c);
			}
		}

		answer = Integer.MAX_VALUE;

		subset(0);
		System.out.println(answer == Integer.MAX_VALUE ? -1 : answer);

	}

	private static void subset(int cnt) {
		if (cnt == N) {
			int tCnt = 0;
			int fCnt = 0;
			for (int i = 0; i < N; i++) {
				if (v[i])
					tCnt++;
				else
					fCnt++;
			}

			if (tCnt == 0 || tCnt == N)
				return;

			if (tCnt > 1) {

				for (int i = 0; i < N; i++) {
					check = new boolean[N];
					if (v[i]) {
						check[i] = true;
						tdfs(i, -1);
						for (int j = 0; j < N; j++) {
							if (v[j] && !check[j]) {
								return;
							}
						}
						break;
					}
				}
			}
			if (fCnt > 1) {
				for (int i = 0; i < N; i++) {
					check = new boolean[N];

					if (!v[i]) {
						check[i] = true;
						fdfs(i, -1);
						for (int j = 0; j < check.length; j++) {
							if (!v[j] && !check[j]) {
								return;
							}
						}
						break;
					}

				}
			}
			int a = 0;
			int b = 0;

			for (int i = 0; i < N; i++) {
				if (v[i]) {
					a += peopleCnt[i];
				} else {
					b += peopleCnt[i];
				}
			}
			answer = Math.min(answer, Math.abs(a - b));
			return;
		}

		v[cnt] = true;
		subset(cnt + 1);
		v[cnt] = false;
		subset(cnt + 1);
	}

	static boolean[] check;

	private static void tdfs(int num, int pre) {
		for (int j = 0; j < list.get(num + 1).size(); j++) {
			if (check[list.get(num + 1).get(j) - 1])
				continue;

			if (list.get(num + 1).get(j) - 1 != pre && v[list.get(num + 1).get(j) - 1]) {
				check[list.get(num + 1).get(j) - 1] = true;
				tdfs(list.get(num + 1).get(j) - 1, num);
			}
		}
	}

	private static void fdfs(int num, int pre) {
		for (int j = 0; j < list.get(num + 1).size(); j++) {
			if (check[list.get(num + 1).get(j) - 1])
				continue;

			if (list.get(num + 1).get(j) - 1 != pre && !v[list.get(num + 1).get(j) - 1]) {
				check[list.get(num + 1).get(j) - 1] = true;
				fdfs(list.get(num + 1).get(j) - 1, num);
			}
		}
	}
}
