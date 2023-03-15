#include <iostream>

int N, K;	// N: 컨베이어 벨트의 길이, K: 내구도가 0인 칸의 수
int topBelt[101];
int lowBelt[101];
int topBeltRobot[101];

void moveRobot() {
	for (int i = N - 2; i >= 0; i--) {
		if (topBeltRobot[i] == 0) continue;	// 로봇이 없는 경우는 continue

		if (topBeltRobot[i + 1] != 0) continue;	// 이동하려는 칸에 로봇 있으면 continue
		if (topBelt[i + 1] == 0) continue;	// 이동하려는 칸의 내구도가 0이면 continue

		// 로봇 한칸 앞으로 이동
		topBeltRobot[i + 1] = 1;
		topBeltRobot[i] = 0;

		topBelt[i + 1]--;	// 내구도 감소
	}

	return;
}

void robotRoll() {	// 로봇 회전 -> 벨트와 함께 회전하므로 내구도 감소 없음
	for (int i = N - 2; i >= 0; i--) {
		if (topBeltRobot[i] == 0) continue;	// 로봇이 없는 경우는 continue

		topBeltRobot[i + 1] = 1;	// 로봇을 다음 칸으로 옮기고
		topBeltRobot[i] = 0;	// 원래 있던 칸은 비움
	}

	return;
}

void beltRoll() {	// 벨트 회전
	int topN = topBelt[N - 1];
	int low2N = lowBelt[0];

	for (int i = N - 2; i >= 0; i--) {	// 윗 벨트
		topBelt[i + 1] = topBelt[i];
	}
	for (int i = 1; i <= N; i++) {	// 아래 벨트
		lowBelt[i - 1] = lowBelt[i];
	}
	topBelt[0] = low2N;
	lowBelt[N - 1] = topN;

	return;
}

int zeroChk() {	// 내구도 검사
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (topBelt[i] <= 0)
			cnt++;
		if (lowBelt[i] <= 0)
			cnt++;
	}

	return cnt;
}

int sol() {
	int cycle = 0;	// cycle: 단계
	if (zeroChk() >= K)	// 0 단계 일 때 내구도가 0인 칸의 수가 K보다 많은지 검사
		return cycle;

	while (true) {
		cycle++;	// 단계 증가

		// 벨트가 각 칸 위에 있는 로봇과 함께 한 칸 회전
		beltRoll();	// 벨트 회전
		robotRoll();	// 로봇 회전 -> 벨트와 함께 회전함으로 내구도 닳지 않음
		topBeltRobot[N - 1] = 0;	// 내리는 위치에 로봇이 있다면 제거

		// 가장 먼저 벨트에 올라간 로봇부터, 한 칸 이동
		// 이동하려는 칸에 로봇이 없어야 하고, 그 칸의 내구도 1 이상
		moveRobot();	// 로봇 회전 -> 내구도 감소
		topBeltRobot[N - 1] = 0;	// 내리는 위치에 로봇이 있다면 제거

		// 로봇 올리기
		if (topBelt[0] > 0) {	// 내구도가 0이상 있으면
			topBeltRobot[0] = 1;	// 로봇 올리고
			topBelt[0]--;	// 내구도 감소
		}

		if (zeroChk() >= K)	// 내구도가 0인 칸의 개수 검사
			return cycle;
		
	}

}

void input() {
	std::cin >> N >> K;
	for (int i = 0; i < N; i++)
		std::cin >> topBelt[i];
	for (int i = N - 1; i >= 0; i--)
		std::cin >> lowBelt[i];

	return;
}

int main() {
	input();
	std::cout << sol();
	return 0;
}