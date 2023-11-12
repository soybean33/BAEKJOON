#include <iostream>
#include <vector>
#include <string>
#include <queue>

/** 방향 벡터 */
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

/** 좌표 */
struct Coordinate{
	int y, x;
};

int R, C; // R: 지도의 행의 크기, C: 지도의 열의 크기
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 비어있는곳(0), 돌(-1), 고슴도치의 방문 시간
std::vector<std::vector<bool>> WATER;	// WATER[i][j]: i 행 j 열의 물이 차있는 여부(true)

std::queue<Coordinate> waterQueue;	// waterQueue: 물이 찰 좌표
std::queue<Coordinate> hedgehogQueue;	// hedgehogQueue: 고슴도치가 움직일 좌표
Coordinate BEAVER;	// BEAVER: 비버의 소굴 좌표 -> 도착 지점

int answer;	// answer: 고슴도치가 비버의 굴로 이동할 수 있는 가장 빠른 시간 -> 이동할 수 없다면 0

void Solution(){

	while(!hedgehogQueue.empty()){	// 고슴도치가 더 이상 움직일 수 없을 때 까지 반복

		int waterSize = waterQueue.size();	// waterSize: 이번 시간에 퍼지는 물의 수

		for(int i=0; i<waterSize; ++i){
			Coordinate curr = waterQueue.front();	// curr: 물의 현재 좌표
			waterQueue.pop();

			for(int dir=0; dir<4; ++dir){	// 4 방향으로 탐색
				Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]};	// next: 다음 물의 좌표

				if(next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) {continue;}	// 범위 벗어나면 continue

				if(MAP[next.y][next.x] == -1) {continue;}	// 물은 돌이 있는 곳으로 갈 수 없음
				if(WATER[next.y][next.x] == true) {continue;}	// 이미 물이 찬 곳
				if(next.y == BEAVER.y && next.x == BEAVER.x) {continue;}	// 물은 비버의 소굴로 이동할 수 없음		

				waterQueue.push(next);
				WATER[next.y][next.x] = true;
			}
		}

		int hedgehogSize = hedgehogQueue.size();	// hedgehogSize: 이번 시간에 움직일 수 있는 고슴도치의 위치 수

		for(int i=0; i<hedgehogSize; ++i){
			Coordinate curr = hedgehogQueue.front();	// curr: 고슴도치의 현재 위치
			hedgehogQueue.pop();

			for(int dir=0; dir<4; ++dir){
				Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]};	// next: 고슴도치의 다음 위치

				if(next.y < 0 || next.x < 0 || next.y >= R || next.x >= C) {continue;}	// 범위 밖으로 나가면 continue

				if(MAP[next.y][next.x] != 0) {continue;}	// 이미 갔던 곳이거나, 돌이 있다면 갈 수 없음
				if(WATER[next.y][next.x] == true) {continue;}	// 물이 차 있는 곳으로 갈 수 없음
				
				hedgehogQueue.push(next);
				MAP[next.y][next.x] = MAP[curr.y][curr.x] + 1;	// 다음 위치의 시간 계산

				if(BEAVER.y == next.y && BEAVER.x == next.x) {	// 고슴도치가 비버의 소굴이 도착한 경우
					answer = MAP[next.y][next.x];
					return;
				}
			}
		}

	}


	return;
}

void Input(){

	std::cin >> R >> C;

	MAP.assign(R, std::vector<int>(C, 0));
	WATER.assign(R, std::vector<bool>(C, 0));

	for(int y=0; y<R; ++y){
		std::string S;	// S: 한 행 정보
		std::cin >> S;
		for(int x=0; x<C; ++x){
			if(S[x] == '.') {continue;}	// 비어 있는 곳
			else if(S[x] == '*') {	// 물이 차있는 지역
				WATER[y][x] = true;
				waterQueue.push({y, x});
			}
			else if(S[x] == 'X') {MAP[y][x] = -1;}	// 돌
			else if(S[x] == 'D') {BEAVER = {y, x};}	// 비버의 굴
			else if(S[x] == 'S') {	// 고슴도치의 위치
				MAP[y][x] = 1;
				hedgehogQueue.push({y, x});
			}
		}
	}

	return;
}

int main(){

	Input();

	Solution();

	if(answer == 0) {std::cout << "KAKTUS";}
	else {std::cout << answer - 1;}	// 시작 지점을 1의 시간을 주고 시작하였으므로 -1

	return 0;
}