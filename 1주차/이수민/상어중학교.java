import java.io.*;
import java.util.*;

public class Main {
	static class Block implements Comparable<Block> {
		int r;
		int c;
		int rbCnt;
		int size;

		ArrayList<Block> list = new ArrayList<>();

		public Block(int r, int c) {
			this.r = r;
			this.c = c;
		}

		public Block(int r, int c, int rbCnt, int size, ArrayList<Block> list) {
			this.r = r;
			this.c = c;
			this.rbCnt = rbCnt;
			this.size = size;
			this.list = list;

		}

		public int compareTo(Block o) {
			if (o.size == this.size) {
				if (this.rbCnt == o.rbCnt) {
					if (this.r == o.r) {
						return Integer.compare(o.c, this.c);
					}
					return Integer.compare(o.r, this.r);
				}
				return Integer.compare(o.rbCnt, this.rbCnt);
			}
			return Integer.compare(o.size, this.size);
		}
	}

	static int[][] map;
	static int N, M;
	static Queue<Block> que;
	static boolean[][] v;
	static PriorityQueue<Block> pq;
	static boolean flag;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new int[N][N];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
			}
		}
		int score = 0;
		flag = true;

		while (true) {
			flag = false;
			pq = new PriorityQueue<>();
			v = new boolean[N][N];
			que = new LinkedList<>();

			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					if (map[r][c] > 0 && map[r][c] <= M && !v[r][c]) {
						que.offer(new Block(r, c));
						v[r][c] = true;
						bfs(r, c);
					}

				}
			}
			if (pq.size() == 0)
				break;

			Block b = pq.poll();

			for (int i = 0; i < b.list.size(); i++) {
				Block cur = b.list.get(i);
				map[cur.r][cur.c] = M + 1;
			}
			
			score += (int) Math.pow(b.size, 2);

			grivaityMap();
			rotationMap();
			grivaityMap();
		}
		System.out.println(score);
	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { -1, 0, 0, 1 };

	private static void bfs(int r, int c) {
		int rbCnt = 0;
		int size = 1;
		ArrayList<Block> list = new ArrayList<>();
		list.add(new Block(que.peek().r, que.peek().c));
		ArrayList<Block> zero = new ArrayList<>();
		while (!que.isEmpty()) {
			Block cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc] || map[nr][nc] != map[r][c] && map[nr][nc] != 0) {
					continue;
				}

				if (map[nr][nc] == 0) {
					rbCnt++;
					zero.add(new Block(nr, nc));
				} else if (map[nr][nc] == map[r][c]) {
					size++;
				}
				v[nr][nc] = true;
				que.offer(new Block(nr, nc));
				list.add(new Block(nr, nc));
			}
		}

		for (int i = 0; i < zero.size(); i++) {
			v[zero.get(i).r][zero.get(i).c] = false;
		}

		if (size + rbCnt < 2)
			return;

		pq.offer(new Block(r, c, rbCnt, size + rbCnt, list));
	}

	private static void grivaityMap() {

		for (int c = 0; c < N; c++) {
			ArrayList<Integer> lt = new ArrayList<>();

			for (int r = N - 1; r >= 0; r--) {
				if (map[r][c] != M + 1) {
					lt.add(map[r][c]);
				}
				if (map[r][c] != -1) {
					map[r][c] = M + 1;
				}
			}

			if (lt.size() == 0)
				continue;

			for (int i = N - 1; i >= 0; i--) {
				if (map[i][c] == M + 1 && lt.get(0) != -1) {
					map[i][c] = lt.get(0);
					lt.remove(0);
				} else if (map[i][c] == -1 && lt.get(0) == -1) {
					lt.remove(0);
				}

				if (lt.size() == 0)
					break;

			}
		}
	}

	private static void rotationMap() {
		Queue<Integer> tmp = new LinkedList<>();
		for (int r = 0; r < N; r++) {
			for (int c = N - 1; c >= 0; c--) {
				tmp.offer(map[r][c]);
			}
		}
		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				map[r][c] = tmp.poll();
			}
		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
