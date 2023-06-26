#include <iostream>
#include <string>
#include <queue>

struct Coordinate{	// Coordinate: 좌표
	int y, x;	// y, x: 좌표
};

int M, N;	// M: 가로 크기, N: 세로 크기
int MAP[100][100];	// MAP[i][j]: i 행 j 열의 상태 -> 0: 빈 방, 1: 벽
int breakWallCnt[100][100];	// breakWallCnt[i][j]: i 행 j 열에 도착할 때 부순 최소 벽의 갯수
int ans;	// ans: (N, M)으로 이동하며 부순 최소 벽의 개수

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

void solution(){

	for(int j=0; j<M; j++){
		for(int i=0; i<N; i++)
			breakWallCnt[j][i] = 21e8;	// 초기화
	}

	std::queue<Coordinate> q;	// q[i]: 탐색할 좌표

	// 시작 지점 넣기
	q.push({0, 0});
	breakWallCnt[0][0] = 0;

	while(!q.empty()){

		Coordinate cur = q.front();	// cur: 현재 위치
		q.pop();

		for(int dir=0; dir<4; dir++){
			Coordinate next = {cur.y + dirY[dir], cur.x + dirX[dir]};	// next: 현재 위치에서 이동할 위치

			if(next.y < 0 || next.x < 0 || next.y >= M || next.x >= N) continue;	// 범위 벗어나면 continue

			if(MAP[next.y][next.x]){	// 이동한 위치에 벽이 있는 경우
				if(breakWallCnt[next.y][next.x] > breakWallCnt[cur.y][cur.x] + 1){	// 이전 이동보다 더 적은 벽을 부수고 이동할 수 있다면
					breakWallCnt[next.y][next.x] = breakWallCnt[cur.y][cur.x] + 1;	// 값 갱신
					q.push(next);	// 탐색할 수 있도록 넣기
				}
			}
			else{	// 이동한 위치가 빈 방인 경우
				if(breakWallCnt[next.y][next.x] > breakWallCnt[cur.y][cur.x]){	// 이전 이동보다 더 적은 벽을 부수고 이동할 수 있다면
					breakWallCnt[next.y][next.x] = breakWallCnt[cur.y][cur.x];	// 값 갱신
					q.push(next);	// 탐색할 수 있도록 넣기
				}
			}
		}
	}

	ans = breakWallCnt[M-1][N-1];	// 도착지점의 값

	return;
}

void input(){

	std::cin >> N >> M;

	for(int j=0; j<M; j++){
		std::string s;	// s[i]: j 행의 i 열에 해당하는 방의 정보
		std::cin >> s;
		for(int i=0; i<N; i++){
			MAP[j][i] = s[i] - '0';
		}
	}

	return;
}


int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}