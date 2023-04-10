#include <iostream>
#include <string>
#include <algorithm>

int R, C;	// R: 세로 크기, C: 가로 크기
char MAP[21][21];	// MAP[i][j]: 보드의 i행 j열에 있는 대문자 알파벳

int DAT[26];	// DAT[i]: i + 'A' 문자 사용 여부
int ans;	// ans: 말이 최대한 지나간 칸 수

// 방향 백터
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

void DFS(int y, int x, int depth) {	// y, x: 좌표, depth: 지나간 칸의 수

	ans = std::max(ans, depth);	// 최대 지나간 칸의 수 갱신

	for (int d = 0; d < 4; d++) {	// 4 방향
		// nextY, nextX: 다음 칸
		int nextY = y + dirY[d];
		int nextX = x + dirX[d];

		if (nextY < 0 || nextX < 0 || nextY >= R || nextX >= C) continue;	// 범위 벗어나면 continue
		char nextChar = MAP[nextY][nextX];	// 다음 칸에 있는 대문자 알파벳
		if (DAT[nextChar - 'A'] != 0) continue;	// 이미 사용된 알파벳이면 continue

		DAT[nextChar - 'A'] = 1;	// 알파벳 사용
		DFS(nextY, nextX, depth + 1);
		DAT[nextChar - 'A'] = 0;	// 알파벳 복구

	}

	return;
}

void sol() {
	char start = MAP[0][0];	// start: 시작 알파벳

	DAT[start - 'A'] = 1;
	DFS(0, 0, 1);


	return;
}

void input() {
	std::cin >> R >> C;
	for (int j = 0; j < R; j++) {
		std::string s;	// s: 한 행 알파벳
		std::cin >> s;
		for (int i = 0; i < C; i++) {
			MAP[j][i] = s[i];
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