#include <iostream>
#include <string>
#include <cmath>

struct Order {
	int idx;	// idx: 회전하는 톱니바퀴
	int dir;	// dir: 방향 시계 1, 반시계 -1
};

int gear[4][8];	// gear[i][j]: i 톱니바퀴의 12시부터 시계 방향으로의 극성(N극 0, S극 1)
int gearIdx[4];	// gearIdx[i]: i 톱니바퀴의 12시 방향 index
int K;	// K: 회전 횟수
Order order[100];	// order[i]: i 번째 회전
int ans;	// 최종 토니바퀴 상태에 의한 점수

void sol() {
	for (int k = 0; k < K; k++) {
		Order now = order[k];	// now: 이번에 실행할 회전

		int roll[4] = { 0, };	// roll: 이번 실행에서 회전하는 톱니바퀴의 회전 정보
		roll[now.idx] = now.dir;

		// 왼쪽으로 가면서 확인
		int rollDir = now.dir;	// rollDir: 회전 방향, 시계 1 반시계 -1
		for (int i = now.idx - 1; i >= 0; i--) {
			rollDir *= -1;	// 회전이 가능하다면 반전
			int leftIdx = (gearIdx[i + 1] - 2 + 8) % 8;	// 오른쪽 톱니바퀴의 왼쪽 극성
			int rightIdx = (gearIdx[i] + 2) % 8;	// 현재 톱니바퀴의 오른쪽 극성

			if (gear[i + 1][leftIdx] == gear[i][rightIdx]) break;	// 두 극성이 같다면 break

			roll[i] = rollDir;	// 다음 톱니바퀴의 회전 방향
		}

		// 오른쪽으로 가면서 확인
		rollDir = now.dir;		
		for (int i = now.idx + 1; i < 4; i++) {
			rollDir *= -1;	// 회전이 가능하다면 반전
			int leftIdx = (gearIdx[i] - 2 + 8) % 8;	// 현재 톱니퀴의 왼쪽 극성
			int rightIdx = (gearIdx[i - 1] + 2) % 8;	// 왼쪽 톱니바퀴의 오른쪽 극성

			if (gear[i - 1][rightIdx] == gear[i][leftIdx]) break;	// 두 극성이 같다면 break

			roll[i] = rollDir;	// 다음 톱니바퀴의 회전 방향
		}

		for (int i = 0; i < 4; i++) {	// 회전 정보에 따라 톱니바퀴 회전
			if (roll[i] == 0) continue;	// 0이면 회전하지 않음

			gearIdx[i] = (gearIdx[i] + (roll[i] * -1) + 8) % 8;	// 톱니바퀴가 회전했으므로 12시 방향 index 갱신
		}
	}

	for (int i = 0; i < 4; i++) {
		if (gear[i][gearIdx[i]] == 0) continue;	// N극이면 점수 없음
		ans += std::pow(2, i * gear[i][gearIdx[i]]);	// S극이면 점수 더하기
	}

	return;
}

void input() {
	for (int j = 0; j < 4; j++) {
		std::string s;	// s: 12시 방향부터 시계 방향으로 들어오는 문자열 형태의 톱니바퀴 정보
		std::cin >> s;
		for (int i = 0; i < 8; i++)
			gear[j][i] = s[i] - '0';	// 문자형태로 들어오기 때문에 '0' 뺌
	}
	std::cin >> K;
	for (int i = 0; i < K; i++) {
		std::cin >> order[i].idx >> order[i].dir;
		order[i].idx--;	// 1 ~ 4로 들어오는 톱니바퀴 번호를 0 ~ 3으로 변경
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << ans;

	return 0;
}