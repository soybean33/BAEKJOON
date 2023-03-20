#include <iostream>
#include <cstring>
#include <algorithm>

int N, M, H;	// N: 세로선의 개수, M: 가로선의 개수, H: 가로선을 놓을 수 있는 위치의 개수
int MAP[40][20];	// MAP[i][j]: i 번째 가로선과 j번째 세로선의 사디리 정보, 1: 오른쪽으로 이동, 2: 왼쪽으로 이동
int ans = 21e8; // i번 세로선의 결과가 i번이 나오도록 추가해야 하는 가로선 수의 최소값, 만약 정답이 3보다 큰 값이거나 불가능한 경우면 -1 출력

void DFS(int y, int x, int depth) {   // depth: 추가된 가로선의 수

	if (depth <= 3) {   // 추가된 가로선의 개수가 3개 이하일 경우만 진행
		int flag = 0;   // flag: 모든 i번 세로선의 결과가 i번이 나온다면 0
		for (int i = 1; i <= N; i++) {  // N개의 i선에 대하여
			int loc = i;    // loc: j번째 가로선에서의 위치
			for (int j = 1; j <= H; j++) {  // H개의 j선에 대하여
				if (MAP[j][loc] == 1) { // 1이면 오른쪽으로
					loc++;
				}
				else if (MAP[j][loc] == 2) {    // 2면 왼쪽으로
					loc--;
				}
			}
			if (loc != i) { // 같지 않다면
				flag = 1;
				break;
			}
		}
		if (flag == 0) {    // 조건을 만족하면 최소값 갱신
			ans = std::min(ans, depth);
		}
	
		if (depth == 3) // 추가된 가로선의 개수가 3개면 return
			return;
	}
	
	for (int j = y; j <= H; j++) {
		for (int i = x; i <= N; i++) {
            if(i >= N){ // i가 끝까지 다 돌았다면
                x = 1;  // x = 1부터 다시
            }
			if (MAP[j][i] != 0 || MAP[j][i+1] != 0) continue;   // 조사하는 칸과 연결할 오른쪽 칸이 불가능한 칸(-1)이거나 이미 연결되어 있는칸 (1, 2)라면 continue

			MAP[j][i] = 1;
			MAP[j][i + 1] = 2;

			DFS(j, i+1, depth + 1); // (ㅓ, ㅑ+1) 칸 부터 탐색

			MAP[j][i] = 0;
			MAP[j][i + 1] = 0;
		}
	}

	return;
}

void sol() {
	DFS(1, 1, 0);
	if (ans > 3)
		ans = -1;

	return;
}

void input() {
	memset(MAP, -1, sizeof(MAP));   // 전체 -1로 초기화
	std::cin >> N >> M >> H;
	for (int j = 1; j <= H; j++) {
		for (int i = 1; i <= N; i++) {
			MAP[j][i] = 0;  // 가로선의 후보가 될 수 있는 구역 0으로 표시
		}
	}
	for (int m = 0; m < M; m++) {   // M개의 가로선 정보 입력
		int a, b;   // a: 가로선 위치, b: b번 세로선과 b+1번 세로선 연결
		std::cin >> a >> b;
		MAP[a][b] = 1;  // 가로선의 왼쪽은 1
		MAP[a][b + 1] = 2;  // 가로선의 오른쪽은 2
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << ans;

	return 0;
}