import java.io.*;
import java.util.*;

// ArrayDequeue로 풀어보기 -> 시간 감소할 수 있음
public class Main {
	static class Tree implements Comparable<Tree> {
		int r;
		int c;
		int age;

		public Tree(int r, int c, int age) {
			this.r = r;
			this.c = c;
			this.age = age;
		}

		public int compareTo(Tree o) {
			return Integer.compare(this.age, o.age);
		}
	}

	static int[][] yangbun;
	static int[][] map;
	static int N, M, K;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		map = new int[N][N];
		yangbun = new int[N][N];

		pq = new PriorityQueue<>();

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				yangbun[r][c] = Integer.parseInt(st.nextToken());
				map[r][c] = 5;
			}
		}

		pq = new PriorityQueue<>();
		tq = new LinkedList<>();
		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(br.readLine());
			pq.offer(new Tree(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1,
					Integer.parseInt(st.nextToken())));
		}
		die = new LinkedList<>();

		while (K-- > 0) {
			spring();
			summer();
			fall();
			winter();
		}

		System.out.println(pq.size());

	}

	static Queue<Tree> die;
	static Queue<Tree> tq; // 나무들이 들어있는 큐
	static PriorityQueue<Tree> pq;

	private static void spring() {
		// 자신의 나이만큼 양분을 먹고 한살 증가 (나이 어린순으로 먹기)
		while (!pq.isEmpty()) {
			Tree cur = pq.poll();

			if (map[cur.r][cur.c] < cur.age) {
				die.offer(new Tree(cur.r, cur.c, cur.age));
			} else {
				tq.offer(new Tree(cur.r, cur.c, cur.age + 1));
				map[cur.r][cur.c] -= cur.age;
			}
		}

	}

	private static void summer() {
		while (!die.isEmpty()) {
			Tree cur = die.poll();
			map[cur.r][cur.c] += (cur.age / 2);
		}
	}

	static int[] dr = { 0, 1, -1, 0, 1, 1, -1, -1 };
	static int[] dc = { 1, 0, 0, -1, 1, -1, 1, -1 };

	private static void fall() {
		// 나무 번식쓰
		while (!tq.isEmpty()) {
			Tree cur = tq.poll();

			if (cur.age % 5 == 0) {
				pq.offer(new Tree(cur.r, cur.c, cur.age));
				for (int d = 0; d < 8; d++) {
					int nr = cur.r + dr[d];
					int nc = cur.c + dc[d];

					if (!check(nr, nc))
						continue;

					pq.offer(new Tree(nr, nc, 1));
				}
			} else {
				pq.offer(new Tree(cur.r, cur.c, cur.age));
			}
		}

	}

	private static void winter() {
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				map[r][c] += yangbun[r][c];
			}
		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}

}
