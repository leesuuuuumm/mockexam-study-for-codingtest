import java.io.*;
import java.util.*;

public class Main {

	static int[][] gear;
	static int[] dir;
	static int score;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		gear = new int[4][8];
		score = 0;

		for (int i = 0; i < 4; i++) {
			char[] ch = br.readLine().toCharArray();
			for (int j = 0; j < ch.length; j++) {
				gear[i][j] = ch[j] - '0';
			}
		}
		int K = Integer.parseInt(br.readLine());

		for (int i = 0; i < K; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine());

			dir = new int[4];
			int num = Integer.parseInt(st.nextToken()) - 1;
			dir[num] = Integer.parseInt(st.nextToken());

			decideDir(num);

			rotationGear();

		}
		getScoreSum();
		System.out.println(score);
	}

	private static void rotationGear() {
		for (int i = 0; i < dir.length; i++) {
			if (dir[i] == 1) { // 시계방향
				int tmp = gear[i][7];

				for (int j = 7; j > 0; j--) {
					gear[i][j] = gear[i][j - 1];
				}
				gear[i][0] = tmp;

			} else if (dir[i] == -1) { // 반시계방향
				int tmp = gear[i][0];

				for (int j = 0; j < 7; j++) {
					gear[i][j] = gear[i][j + 1];
				}
				gear[i][7] = tmp;
			}

		}
	}
	private static void decideDir(int num) {

		for (int left = num - 1; left >= 0; left--) {
			if (gear[left][2] != gear[left + 1][6]) {
				dir[left] = dir[left + 1] * -1;
			}
		}
		for (int right = num; right < 3; right++) {
			if (gear[right][2] != gear[right + 1][6]) {
				dir[right + 1] = dir[right] * -1;

			}
		}
	}

	private static void getScoreSum() {
		int c = 1;
		for (int i = 0; i < 4; i++) {
			if (gear[i][0] == 1) {
				score += c;
			}
			c *= 2;

		}

	}
}
