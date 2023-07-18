#include <iostream>
#include <vector>
#include <string>
#include <queue>

// 방향 백터
int dirY[4] = {0, 1, 0, -1};
int dirX[4] = {1, 0, -1, 0};

struct Coordinate{	// 좌표
	int y, x;	// y, x: 좌표

	static Coordinate nextCoordi(Coordinate curr, int dir) {	// curr: 현재 좌표, dir: 이동할 방향
		return {curr.y + dirY[dir], curr.x + dirX[dir]};	// 다음 위치 return
	}
};

int N;	// N: 그림의 한 변의 길이
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 그림의 색
std::vector<std::vector<bool>> visited;	// visited[i][j]: i 행 j 열의 방문 여부
int ansA, ansB;	// ansA: 적록색약이 아닌 사람이 봤을 때의 구역의 개수, ansB: 적록색약인 사람이 봤을 때의 구역의 수

void funcA(){

	visited.assign(N, std::vector<bool>(N, false));

	std::queue<Coordinate> q;	// q: 다음 방문할 그림의 위치

	for(int y=0; y<N; ++y){
		for(int x=0; x<N; ++x){
			if(visited[y][x]) continue;	// 이미 방문한 위치면 continue

			q.push({y, x});
			visited[y][x] = true;
			ansA += 1;	// 구역 증가

			while(!q.empty()){
				Coordinate curr = q.front();	// curr: 현재 위치
				q.pop();

				int currColor = MAP[curr.y][curr.x];	// currColor: 현재 위치의 색				

				for(int dir=0; dir<4; ++dir){
					Coordinate next = Coordinate::nextCoordi(curr, dir);	// next: 다음 위치

					if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) continue;	// 범위 벗어나면 continue
					if(MAP[next.y][next.x] != currColor) continue;	// 색 다르면 continue
					if(visited[next.y][next.x]) continue;	// 이미 방문했다면 continue

					q.push(next);
					visited[next.y][next.x] = true;	// 방문 체크
				}
			}
		}
	}

	return;
}

void funcB(){

	visited.assign(N, std::vector<bool>(N, false));

	std::queue<Coordinate> q;	// q: 다음 방문할 그림의 위치

	for(int y=0; y<N; ++y){
		for(int x=0; x<N; ++x){
			if(visited[y][x]) continue;	// 이미 방문한 위치면 continue

			q.push({y, x});
			visited[y][x] = true;
			ansB += 1;	// 구역 증가

			while(!q.empty()){
				Coordinate curr = q.front();	// curr: 현재 위치
				q.pop();

				int currColor = MAP[curr.y][curr.x];	// currColor: 현재 위치의 색			

				for(int dir=0; dir<4; ++dir){
					Coordinate next = Coordinate::nextCoordi(curr, dir);	// next: 다음 위치

					if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) continue;	// 범위 벗어나면 continue
					if(currColor == 0){	// 파랑일 경우
						if(MAP[next.y][next.x] == 1 || MAP[next.y][next.x] == 2) continue;	// 빨강과 초록이면 continue
					}
					else{	// 파랑이 아닌 경우 -> 빨강이거나 파랑인 경우
						if(MAP[next.y][next.x] == 0) continue;	// 파랑이면 continue
					}
					if(visited[next.y][next.x]) continue;	// 이미 방문한 위치면 continue

					q.push(next);
					visited[next.y][next.x] = true;	// 방문 체크
				}
			}
		}
	}

	return;
}

void solution(){

	funcA();	// 적록색약인 사람

	funcB();	// 적록색약이 아닌 사람

	return;
}

void input(){

	std::cin >> N;

	MAP.assign(N, std::vector<int>(N, 0));

	for(int y=0; y<N; ++y){
		std::string s;	// s: 그림의 한 행의 색 정보
		std::cin >> s;
		for(int x=0; x<N; ++x){
			if(s[x] == 'R')	// 빨강
				MAP[y][x] = 1;
			else if(s[x] == 'G')	// 초록
				MAP[y][x] = 2;
			else MAP[y][x] = 0;	// 파랑
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

	std::cout << ansA << ' ' << ansB;

	return 0;
}