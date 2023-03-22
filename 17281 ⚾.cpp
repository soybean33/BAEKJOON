#include <iostream>
#include <algorithm>

int N;  // N: 이닝 수
int A[51][10];  // A[i][j]: i번 이닝의 j번 선수의 결과 -> 1: 안타, 2: 2루타, 3: 3루타, 4: 홈런, 0: 아웃
int order[9];   // order[i]: i번 타자의 선수 번호
bool visited[10];   // visited[i]: i번 타자가 뽑혔는지
int score = -21e8;  // score: 가장 많은 득점
// 0: 아무도 없음, 1: 1루, 2: 2루, 3: 1,2루, 4: 3루, 5: 1,3루, 6: 2,3루, 7: 1,2,3루
int base[3][8] = {  // base[i][j]: i루타를 쳤을 경우 j번 주자 상태에서의 결과 상태
    {1, 3, 5, 7, 1, 3, 5, 7},
    {2, 6, 2, 6, 2, 6, 2, 6},
    {4, 4, 4, 4, 4, 4, 4, 4}
};
int addScore[3][8] = {  // addScore[i][j]: i루타를 쳤을 경우 j번 주자 상태에서의 득점
    {0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 1, 2, 2},
    {0, 1, 1, 2, 1, 2, 2, 3}
};

void DFS(int depth) {   // depth: 선수 번호 - 1

	if (depth == 9) {
		int hitIdx = 0; // hitIdx: 타순
		int tmpScore = 0;   // tmpScore: 이번 타순으로 얻을 수 있는 점수
		for (int inning = 0; inning < N; inning++) {    // 모든 이닝에 대하여 반복
            int state = 0;  // state: 현재 주자 상태
			int outCnt = 0; // outcnt: 아웃 카운트 -> 3개 이상이면 이닝 종료
			while (outCnt < 3) {
				int hitMan = order[hitIdx]; // hitMan: 타자 번호
				if (A[inning][hitMan] == 0) {	// 아웃
					outCnt++;
				}
				else if (A[inning][hitMan] == 1) {	// 1루타
                    tmpScore += addScore[0][state]; // 득점
                    state = base[0][state]; // 상태 변화    		
				}
				else if (A[inning][hitMan] == 2) {	// 2루타
					tmpScore += addScore[1][state]; // 득점
                    state = base[1][state]; // 상태 변화
				}
				else if (A[inning][hitMan] == 3) {	// 3루타
					tmpScore += addScore[2][state]; // 득점
                    state = base[2][state]; // 상태 변화
				}
				else if (A[inning][hitMan] == 4) {	// 홈런
					tmpScore += addScore[2][state] + 1; // 득점 -> 3루타의 득점 결과에 + 1과 같음
                    state = 0;  // 상태 변화
				}
				hitIdx = (hitIdx + 1) % 9;  // 다음 타순
			}
		}
		score = std::max(score, tmpScore);  // 이번 타순에서의 점수로 최대 득점 갱신 시도

		return;
	}

	for (int i = 0; i < 9; i++) {
		if (visited[i] == true) continue;   // i번 타자가 정해졌으면 continue
		
		visited[i] = true;  // i번 타자 정해짐
		order[i] = depth + 1;   // i번 타자는 depth + 1번 선수
		DFS(depth + 1); // depth + 2번 선수 정하러 가기
		visited[i] = false; // i번 타자 안정해짐
	}

	return;
}

void sol() {
	order[3] = 1;   // 4번 타자는 1번 선수
	visited[3] = true;  // 4번 타자는 이미 정해짐
	DFS(1);

	return;
}

void input() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	std::cin >> N;
	for (int j = 0; j < N; j++) {
		for (int i = 1; i <= 9; i++) {
			std::cin >> A[j][i];    // j 이닝의 i번 선수의 결과
		}
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << score;

	return 0;
}