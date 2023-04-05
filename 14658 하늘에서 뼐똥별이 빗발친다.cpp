#include <iostream>
#include <algorithm>

struct Coordinate {
	int x, y;	// x, y: 위치
};

int main() {
	int N, M, L, K;	// N: 가로 길이, M: 세로 길이, L: 트램펄린의 한 변의 길이, K: 별똥별의 수
	int ans = 0;	// ans: 정답
	Coordinate arr[101];	// arr[i]: i 번째 별똥별의 위치


	std::cin >> N >> M >> L >> K;
	for (int i = 0; i < K; i++) {
		int x, y;	// x, y: 위치
		std::cin >> x >> y;
		arr[i] = { x, y };
	}

	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			int curX = arr[i].x;	// curX: i 번째 별똥별의 X 좌표
			int curY = arr[j].y;	// curY: j 번째 별똥별의 Y 좌표

			int cnt = 0;	// cnt: 트램펄린에 떨어지는 별똥별의 수
			for (int k = 0; k < K; k++) {
				if (arr[k].x >= curX && arr[k].y >= curY && arr[k].x <= curX + L && arr[k].y <= curY + L)	// 트램펄린 안쪽
					cnt++;
			}
			ans = std::max(ans, cnt);	// 트램펄린에 튕겨 나가는 별똥별의 최대 수
		}
	}

	std::cout << K - ans;	// 지우게 부딪히는 별똥별의 개수

	return 0;
}