#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

struct Coordinate{
	int y, x;	// y, x: 좌표
};

int N, M;	// N: 이차원 배열의 행의 개수, M: 이차원 배열의 열의 개수
int MAP[300][300];	// MAP[i][j]: i 행 j 열의 빙산의 부분별 높이
int iceNum;	// iceNum: 빙산이 있는 칸의 개수
int ans;	// ans: 빙산이 분리되는 최초의 시간, 빙산이 다 녹을 때까지 분리되지 않으면 0 출력

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

int calIcebergCnt(){

	int visited[300][300];	// viisted[i][j]: i 행 j 열 방문
	int ret = 0;	// ret: 빙산의 개수

	memset(visited, 0, sizeof(visited));

	for(int j=1; j<N; j++){
		for(int i=0; i<M; i++){
			if(!MAP[j][i]) continue;	// 빙산이 없는 칸 continue
			if(visited[j][i]) continue;	// 이미 확인한 칸 continue

			ret++;	// 새로운 빙산 발견

			std::queue<Coordinate> q;	// q[i]: 탐색할 i 번째 좌표

			q.push({j, i});

			while(!q.empty()){
				Coordinate cur = q.front();	// cur: 현재 좌표
				q.pop();

				for(int dir = 0; dir<4; dir++){
					Coordinate next = {cur.y + dirY[dir], cur.x + dirX[dir]};	// next: 탐색할 좌표

					if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) continue;	// 범위 벗어나면 continue
					if(!MAP[next.y][next.x]) continue;	// 빙산이 없으면 continue
					if(visited[next.y][next.x]) continue;	// 이미 탐색하였으면 continue

					visited[next.y][next.x] = 1;	// 탐색 완료
					q.push({next.y, next.x});	// 다음에 해당 지점 부터 탐색
				}
			}			
		}
	}

	return ret;
}

void sol(){

	while(true){
		
		if(iceNum == 0) return;	// 빙산이 없는 경우 -> 0 출력

		int icebergCnt = calIcebergCnt();	// icebergCnt: 빙산의 개수
		if(icebergCnt > 1) return;

		ans++;	// 시간 증가

		int water[300][300];	// water[i][j]: i 행 j 열의 상 하 좌 우 에 인접한 바닷물 칸의 수

		memset(water, 0, sizeof(water));

		for(int j=0; j<N; j++){
			for(int i=0; i<M; i++){
				Coordinate cur = {j, i};	// cur: 인접한 바닷물 칸의 수를 구할 칸의 좌표

				for(int dir=0; dir<4; dir++){
					Coordinate next = {cur.y + dirY[dir], cur.x + dirX[dir]};	// next: 바닷물 여부 확인

					if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) continue;	// 범위 벗어나면 continue

					if(!MAP[next.y][next.x]) water[cur.y][cur.x]++;	// 바닷물이면 증가
				}
			}
		}

		for(int j=0; j<N; j++){
			for(int i=0; i<M; i++){
				if(!MAP[j][i]) continue;	// 빙산 없으면 continue

				MAP[j][i] = std::max(MAP[j][i]-water[j][i], 0);	// 0 보다 작은 값은 없음 -> 0 이면 빙산 모두 녹음

				if(!MAP[j][i]) iceNum--;	// 현재 칸의 빙산이 모두 녹았다면 빙산이 있는 칸의 개수 감소
			}
		}

		if(!iceNum){	// 빙산이 다 녹을 때까지 분리되지 않음
			ans = 0;	// 0을 출력
			return;
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	for(int j=0; j<N; j++){
		for(int i=0; i<M; i++){
			std::cin >> MAP[j][i];
			if(MAP[j][i] != 0) iceNum++;	// 방산이 있는 칸의 갯수 증가 -> 빙산이 다 녹을 때 까지 분리되지 않는 경우 때문
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}