#include <iostream>

int N, L;	// N: 지도의 한 변의 길이, L: 경사로의 길이
int MAP[101][101];	// MAP[i][j]: i행 j열의 높이
int ans;	// ans: 지나갈 수 있는 길의 개수

int validChk(int runway[]) {
	int height = runway[0];	// height: 기준 높이
	int cnt = 0;	// cnt: 현재 높이와 같은 높이가 현재까지 연속하여 나온 횟수
	int flag = 0;	// flag: 경사로 설치 가능성 -> 0: 가능, 1: 불가능

	for (int i = 0; i < N; i++) {
		if (height == runway[i]) {	// 연속된 같은 높이
			cnt++;
		}
		else if (height + 1 == runway[i]) {	// 1칸 높은 칸
			if (cnt >= L) {	// 현재까지 나온 같은 높이의 길이 경사로의 길이보다 크다면
				height++;	// 기준 높이 증가
				cnt = 1;
			}
			else {
				return -1;
			}
		}
		else if (height - 1 == runway[i]) {	// 1칸 낮은 칸
			int tmp = 0;
			for (int j = 0; j < L; j++) {	// 앞으로 나올 경사로 길이만큼 조사
				if (height - 1 == runway[i + j])
					tmp++;
				else {	// 다른 높이
					break;
				}
			}
			if (tmp < L)	// 길이가 모자름
				return -1;
			else {	// 경사로 설치 가능
				i += L - 1;
				height--;	// 기준 높이 감소
				cnt = 0;
			}
		}
		else {
			return -1;
			
		}
	}
	if (flag == 0)	// 경사로 설치 가능
		return 1;

	return 0;
}


void sol() {
	for (int j = 0; j < N; j++) {	// 가로
		int runway[101] = { 0, };	// runway[i]: 한 줄의 길 높이 정보

		for (int i = 0; i < N; i++) {
			runway[i] = MAP[j][i];
		}
		if (validChk(runway) == 1) {	// 지나다닐 수 있으면 1
			ans += 1;
		}
	}

	for (int i = 0; i < N; i++) {	// 세로
		int runway[101] = { 0, };	// runway[i]: 한 줄의 길 높이 정보
		for (int j = 0; j < N; j++) {
			runway[j] = MAP[j][i];
		}
		if (validChk(runway) == 1)	// 지나다닐 수 있으면 1
			ans += 1;
	}

	return;
}


void input() {
	std::cin >> N >> L;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			std::cin >> MAP[j][i];
		}
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << ans;

	return 0;
}