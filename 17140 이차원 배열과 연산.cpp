#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

struct List {
	int n;
	int cnt;

	bool operator < (List next) const {
		// 수의 등장 횟수가 커지는 순으로
		if (cnt < next.cnt) return false;
		if (cnt > next.cnt) return true;

		// 수가 커지는 순으로
		if (n < next.n) return false;
		if (n > next.n) return true;

		return false;
	}
};


int r, c, k;	// r: 목표 행, c: 목표 열, k: 목표 숫자
int A[100][100];	// A[i][j]: i행 j열의 수
int T;	// T: 시간

int jLen = 3;	// jLen: 행의 수
int iLen = 3;	// iLen: 열의 수

int maxJLen = 0;	// maxJLen: 최대 행의 수
int maxILen = 0;	// maxILen: 최대 열의 수

void newLine(int line[], int flag) {
	
	int DAT[101] = { 0, };	// DAT[i]: i 수의 개수
	int idx = 0;	// idx: 배열 인덱스
	std::priority_queue<List> pq;	// pq: 수의 등장 횟수가 커지는 순으로, 그러한 것이 여러가지면 수가 커지는 순으로

	for (int i = 0; i < iLen; i++) {	// 수의 개수 조사
		DAT[line[i]]++;
	}

	for (int i = 0; i < 100; i++)	// line 초기화
		line[i] = 0;

	for (int i = 1; i <= 100; i++) {
		if (DAT[i] == 0) continue;	// 수가 등장한 적이 없다면 continue

		pq.push({ i, DAT[i] });	// 우선 순위 큐에 넣기
	}

	while (!pq.empty()) {
		line[idx] = pq.top().n;	// 수
		line[idx+1] = pq.top().cnt;	// 수의 개수
		pq.pop();

		idx += 2;	// 수와 수의 개수의 쌍으로 들어가므로 idx++
		if (idx > 100)	// 100개 이상이면 무시
			break;
	}

	if (flag == 0) {	// 행이 열보다 길거나 같은 경우
		maxILen = std::max(maxILen, idx);	// 더 길다면 최대값 갱신
	}
	else {	// 열이 더 긴 경우
		maxJLen = std::max(maxJLen, idx);	// 더 길다면 최대값 갱신
	}

	return;
}

void sol() {
	while (true) {
		if (A[r - 1][c - 1] == k)	// 값을 찾음
			return;
		if (T == 100) {	// 100초가 지나도 찾지 못함
			T = -1;
			return;
		}
		
		maxJLen = 0;
		maxILen = 0;

		if (jLen >= iLen) {
			for (int j = 0; j < jLen; j++) {
				int line[100];	// line[i]: 변경할 라인
				memcpy(line, A[j], sizeof(line));	// 라인 복사
				newLine(line, 0);
				for (int i = 0; i < 100; i++)
					A[j][i] = line[i];
			}
			iLen = maxILen;	// 열의 값 갱신
		}
		else {
			for (int i = 0; i < iLen; i++) {
				int line[100] = { 0, };	// line[i]: 변경할 라인
				for (int j = 0; j < jLen; j++)
					line[j] = A[j][i];
				newLine(line, 1);
				for (int j = 0; j < 100; j++) {
					A[j][i] = line[j];
				}
			}
			jLen = maxJLen;	// 행의 값 갱신
		}
		T++;	// 시간 증가
	}

	return;
}

void input() {
	std::cin >> r >> c >> k;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++)
			std::cin >> A[j][i];
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << T;

	return 0;
}