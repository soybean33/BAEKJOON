#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>

struct Coordinate {
	int y, x;	// y, x: 좌표
};

int N, Q;	// N: 파이어스톰의 크기 2^N, Q: 파이어스톰 시전 횟수
int A[64][64];	// A[i][j]: i행 j열의 얼음의 양
int L[1001];	// L[i]: i 번째 단계

int len;	// len: 격자의 한 변의 길이
int divide;	// divide: 부분 격자의 한 변의 길이

// 방향 벡터
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

int sum;	// sum: 남아있는 얼음의 합
int large;	// large: 남이있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수
int visited[64][64];	// visited[i][j]: i행 j열 덩어리 체크 여부

void func(int j, int i) {
	int tmpA[64][64] = { 0, };	// tmpA[i][j]: i행 j열의 부분 격자

	// 부분 격자 시계 방향으로 90도 회전
	for (int k = 0; k < divide; k++) {
		for (int l = 0; l < divide; l++) {
			tmpA[k][l] = A[j + divide - 1 - l][i + k];
		}
	}

	// 원본에 적용
	for (int l = 0; l < divide; l++) {
		for (int k = 0; k < divide; k++) {
			A[l + j][k + i] = tmpA[l][k];
		}
	}

	return;
}

void sol() {
	for (int q = 0; q < Q; q++) {
		int l = L[q];	// l: 파이어스톰 단계
		divide = std::pow(2, l);	// 2^l로 부분 격자의 한 변의 길이 구함


		if (l != 0) {	// 부분 격자의 크기가 1인 경우 즉, l = 0인 경우는 회전할 필요 없음
			// 부분 격자로 나누고 시계 바향으로 90도 회전
			for (int j = 0; j < len; j += divide) {
				for (int i = 0; i < len; i += divide) {
					func(j, i);
				}
			}
		}

		// 얼음 감소
		int tmpA[64][64];	// tmpA[i][j]: 원본 A 복사
		for (int j = 0; j < len; j++) {
			for (int i = 0; i < len; i++) {
				tmpA[j][i] = A[j][i];
			}
		}

		for (int j = 0; j < len; j++) {
			for (int i = 0; i < len; i++) {
				int cnt = 0;	// cnt: 인접한 칸 중 얼음이 있는 칸의 수
				for (int dir = 0; dir < 4; dir++) {
					int newY = j + dirY[dir];
					int newX = i + dirX[dir];

					if (newY < 0 || newX < 0 || newY >= len || newX >= len) continue;	// 범위 벗어나면 continue

					if (tmpA[newY][newX] == 0) continue;	// 얼음이 없으면 continue

					cnt++;	// 얼음이 있으면 cnt++
				}
				if (cnt < 3) {	// 인접한 칸에 3개 미만의 얼음이 있다면
					if(A[j][i] != 0)	// 현재 칸이 0이 아닌 경우
						A[j][i]--;	// 얼음의 양 1 감소
				}
			}
		}
	}

	for (int j = 0; j < len; j++) {
		for (int i = 0; i < len; i++) {
			if (A[j][i] == 0) continue;	// 얼음이 없는 칸 continue

			sum += A[j][i];	// 남아있는 얼음의 합
				
			if (visited[j][i] == 1) continue;	// 이미 덩어리 검사를 했다면 continue

			int size = 0;	// size: 덩어리 크기
			std::queue<Coordinate> q;	// q: 연결되어 있는 칸
			q.push({ j, i });
			visited[j][i] = 1;	// 덩어리 검사 하였음

			while (!q.empty()) {
				Coordinate now = q.front();
				q.pop();

				size++;	// 사이즈 증가

				for (int dir = 0; dir < 4; dir++) {
					// newY, newX: 다음 덩어리 검사 위치
					int newY = now.y + dirY[dir];
					int newX = now.x + dirX[dir];

					if (newY < 0 || newX < 0 || newY >= len || newX >= len) continue;	// 범위 벗어나면 continue
					if (visited[newY][newX] == 1) continue;	// 이미 덩어리 검사 했으면 continue
					if (A[newY][newX] == 0) continue;	// 얼음이 없으면 continue

					visited[newY][newX] = 1;	// 덩어리 검사 하였음
					q.push({ newY, newX });
				}
			}
			large = std::max(large, size);	// 가장 큰 덩어리가 차지하는 칸의 개수 갱신
		}
	}
		
	return;
}

void input() {
	std::cin >> N >> Q;
	len = std::pow(2, N);	// 격자 한 변의 길이
	for (int j = 0; j < len; j++) {
		for (int i = 0; i < len; i++) {
			std::cin >> A[j][i];
		}
	}
	for (int i = 0; i < Q; i++)
		std::cin >> L[i];

	return;
}

int main() {
	input();
	sol();
	std::cout << sum << '\n' << large;
	return 0;
}