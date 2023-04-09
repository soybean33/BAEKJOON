#include <iostream>
#include <string>
#include <queue>

struct Coordinate{
	int y, x;	// y, x: 좌표
	int category;	// category: 지훈 1, 불 -1
};

int R, C;	// R: 미로의 행의 개수, C: 미로의 열의 개수
int MAP[1001][1001];	// MAP[i][j]: i행 j열의 정보
Coordinate J, F;	// J: 지훈, F: 불
int ans;	// ans: 지훈이가 미로를 탈출할 수 있는 가장 빠른 탈출 시간

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

std::queue<Coordinate> tmpFQ;	// tmpFQ: 불이 난 공간은 여러개 일 수 있으므로 tmpFQ에 저장

int sol(){

	std::queue<Coordinate> q;	// q: 경로를 탐색할 것 저장

	q.push(J);	// 지훈 먼저 이동

	while(!tmpFQ.empty()){	// 불 이동
		q.push(tmpFQ.front());
		tmpFQ.pop();
	}
	
	while(!q.empty()){
		Coordinate cur = q.front();	// cur: 현재 이동할 것
		q.pop();

		if(cur.category == 1 && MAP[cur.y][cur.x] == -1) continue;	// 지훈이 있던 곳에 불이 생겼다면 continue

		for(int dir = 0; dir < 4; dir++){
			Coordinate next = {cur.y + dirY[dir], cur.x + dirX[dir], cur.category};	// next: 다음으로 이동할 공간

			if(next.category == 1){	// 지훈
				if(next.y < 0 || next.x < 0 || next.y >= R || next.x >= C)
					return MAP[cur.y][cur.x];	// 미로 밖으로 나가면 지훈이가 탈출
				if(MAP[next.y][next.x] != 0) continue;	// 불이 있거나 이미 방문했던 곳이면 continue
				MAP[next.y][next.x] = MAP[cur.y][cur.x] + 1;	// 거리 증가
				q.push(next);
			}

			if(next.category == -1){	// 불
				if(next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) continue;	// 범위 밖으로 나가면 continue
				if(MAP[next.y][next.x] == -1) continue;	// 이미 불이 있다면 continue
				MAP[next.y][next.x] = -1;
				q.push(next);
			}
		}
	}

	return -1;	// 지훈이가 미로를 탈출할 수 없음
}

void input(){
	std::cin >> R >> C;
	for(int j=0; j<R; j++){
		std::string s;	// s: 미로의 한 행의 정보
		std::cin >> s;
		for(int i=0; i<C; i++){
			if(s[i] == '#') MAP[j][i] = -1;	// 벽
			else if(s[i] == 'J'){	// 지훈
				J = {j, i, 1};
				MAP[j][i] = 1;
			}
			else if(s[i] == 'F'){	// 불
				F = {j, i, -1};
				MAP[j][i] = -1;
				tmpFQ.push(F);
			}
		}
	}

	return;
}

int main(){
	input();
	ans = sol();

	if(ans == -1)	// 지훈이가 미로를 탈출하지 못함
		std::cout << "IMPOSSIBLE";
	else
		std::cout << ans;

	return 0;
}