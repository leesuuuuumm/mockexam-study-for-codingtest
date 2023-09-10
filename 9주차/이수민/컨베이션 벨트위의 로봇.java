import java.io.*;
import java.util.*;

public class Main {

	static boolean[] rb;
	static int[] cb;
	static int N, K;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		rb = new boolean[N * 2];
		cb = new int[N * 2];
		st = new StringTokenizer(br.readLine());

		for (int i = 0; i < N * 2; i++) {
			cb[i] = Integer.parseInt(st.nextToken());
		}
		stop = false;
		int count = 0;

		while (!stop) {
			// 벨트가 각 칸 위에 있는 로봇과 함께 회전
			moveRobot();
			moveConveyorBelt();
			// 가장 먼저 올라간 로봇부터, 벨트가 회전하는 방향으로 한칸 이동 가능 (로봇이 없을때, 내구도 1인 이상)
			moveTheOnlyRobot();

			// cb[0] >=1 로봇 올림

			inputRobot();

			// 내구도 0인칸 k개 이상이면 종료
			checkDurability();
			count++;
		}

		System.out.println(count);

	}

	// N 위치에 오면 로봇 무조건 내림
	private static void moveRobot() {
		for (int i = N - 1; i >= 1; i--) {
			rb[i] = rb[i - 1];
		}
		rb[N - 1] = false;
		rb[0] = false;
	}

	private static void moveConveyorBelt() {
		int tmp = cb[2 * N - 1];
		for (int i = 2 * N - 1; i >= 1; i--) {
			cb[i] = cb[i - 1];
		}
		cb[0] = tmp;
	}

	private static void moveTheOnlyRobot() {
		for (int i = N - 1; i >= 1; i--) {
			if (!rb[i]) {
				if (rb[i - 1] && cb[i] >= 1) {
					rb[i] = true;
					rb[i - 1] = false;
					cb[i] -= 1;
				}
			}
		}
		rb[N - 1] = false;
	}

	private static void inputRobot() {
		if (cb[0] >= 1) {
			rb[0] = true;
			cb[0] -= 1;
		}
	}

	static boolean stop;

	private static void checkDurability() {
		int cnt = 0;
		for (int i = 0; i < N * 2; i++) {
			if (cb[i] == 0)
				cnt++;

			if (cnt >= K) {
				stop = true;
			}

		}

	}
}
