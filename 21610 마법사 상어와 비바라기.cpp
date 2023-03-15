#include <iostream>
#include <cstring>

struct Order{
	int d, s;	// d: 방향, s: 이동 칸 수
};

int N, M;	// N: 한 변의 길이, M: 구름 이동 명령 수
int A[50][50];	// A[i][j]: i행 j열에 있는 바구니에 저장되어 있는 물의 양
Order order[100];	// order[i]: i 번째 명령
int cloud[50][50];	// cloud[i][j]: i행 j열의 구름
int ans;	// ans: 바구니의 물의 양의 합

// 방향 벡터
int dirY[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dirX[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};

void sol(){
	// 초기 구름
	cloud[N-1][0] = 1;
	cloud[N-1][1] = 1;
	cloud[N-2][0] = 1;
	cloud[N-2][1] = 1;

	for(int o=0; o<M; o++){

		int newCloud[50][50] = {0,};	// newCloud[i][j]: 명령에 따라 움직이고 난 후의 구름의 위치

		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(cloud[j][i] == 0) continue;	// 구름이 없는 곳은 continue

				// 1. 모든 구름이 d 방향으로 s칸 이동
				// 1번 행과 N번 행이 연결되어 있고, 1번 열과 N번 열이 연결되어 있음
				// 이를 구현하기 위해 % 연산을 사용하였고 음수가 나오는 것을 방지하고자 N * 100을 더하고 나머지 연산 진행
				// s가 최대 50이고 N이 최소 2이기 때문에 N * 25 정도로도 충분함
				int newY = (j + (dirY[order[o].d] * order[o].s) + N * 100) % N;
				int newX = (i + (dirX[order[o].d] * order[o].s) + N * 100) % N;
				newCloud[newY][newX] = 1;	// 새로 움직인 구름 위치 표시

				// 2. 각 구름에서 비가 내려 구름이 있는 칸의 바구니에 저장된 물의 양이 1 증가
				A[newY][newX] += 1;
			}
		}

		// 3. 구름이 모두 사라짐 -> 구현할 필요 없음

		// 4. 2에서 물이 증가한 칸에 물복사 버그 마법 시전
		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(newCloud[j][i] == 0) continue;	// 물 복사 버그는 구름이 사라진 칸에서만 일어남

				int cnt = 0;	// cnt: 대각선으로 인접한 칸의 수
				for(int dir=1; dir<9; dir++){
					if(dir % 2 == 1) continue;	// 대각선 아닌 경우 continue
					
					// 확인 해볼 인접한 대각선 칸
					int newY = j + dirY[dir];
					int newX = i + dirX[dir];

					if(newY < 0 || newX < 0 || newY >= N || newX >= N) continue;	// 범위 벗어나면 continue

					if(A[newY][newX] != 0)	// 비어있지 않다면
						cnt++;
				}
				A[j][i] += cnt;	// 바구니의 물의 양 증가
			}
		}

		// 5. 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름 생김
		memset(cloud, 0, sizeof(cloud));	// 새로 생기는 구름 정보를 저장하기 위해 0으로 초기화
		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(newCloud[j][i] != 0) continue;	// 구름이 사라진 칸이 아니여야 함

				if(A[j][i] >= 2){	// 바구니에 저장된 물의 양이 2 이상인 칸에 대하여
					cloud[j][i] = 1;	// 구름이 생기고
					A[j][i] -= 2;	// 물의 양이 2 줄어듦
				}
			}
		}
	}

	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			ans += A[j][i];	// 바구니에 들어있는 물의 양의 합
		}
	}

	return;
}

void input(){
	std::cin >> N >> M;
	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			std::cin >> A[j][i];
		}
	}
	for(int i=0; i<M; i++){
		std::cin >> order[i].d >> order[i].s;
	}

	return;
}

int main(){
	input();
	sol();
	std::cout << ans;
	return 0;
}