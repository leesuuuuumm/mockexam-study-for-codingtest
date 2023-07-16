import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int V = Integer.parseInt(st.nextToken());
		int E = Integer.parseInt(st.nextToken());

		int[][] map = new int[V + 1][V + 1];
		for (int i = 1; i < map.length; i++) {
			for (int j = 1; j < map.length; j++) {
				if (i != j) {
					map[i][j] = Integer.MAX_VALUE;
				}
			}
		}

		for (int i = 0; i < E; i++) {
			st = new StringTokenizer(br.readLine());
			map[Integer.parseInt(st.nextToken())][Integer.parseInt(st.nextToken())] = Integer.parseInt(st.nextToken());
		}

		for (int k = 1; k <= V; k++) {
			for (int i = 1; i <= V; i++) {
				for (int j = 1; j <= V; j++) {
					if (i == j || map[i][k] == Integer.MAX_VALUE || map[k][j] == Integer.MAX_VALUE)
						continue;

					if (map[i][j] > map[i][k] + map[k][j]) {
						map[i][j] = map[i][k] + map[k][j];
					}

				}
			}
		}

		int min = Integer.MAX_VALUE;
		int answer = Integer.MAX_VALUE;

		for (int i = 1; i <= V; i++) {
			for (int j = 1; j <= V; j++) {
				if (i == j)
					continue;

				if (map[i][j] != Integer.MAX_VALUE && map[j][i] != Integer.MAX_VALUE) {
					answer = Math.min(answer, map[i][j] + map[j][i]);
				}
			}
		}
		System.out.println(answer == Integer.MAX_VALUE ? -1 : answer);

	}
}
