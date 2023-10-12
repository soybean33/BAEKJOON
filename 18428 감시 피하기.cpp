#include <iostream>
#include <vector>

struct Coordinate{	// 좌표
	int y, x;
};

// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

int N;	// N: 한 변의 크기
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 정보 -> -1: 벽, 0: 빈 곳, 1: 선생님, 2: 학생

std::vector<Coordinate> teachers;	// teachers: 선생님의 좌표
bool flag = false;	// flag: 모든 학생이 감시로 피할 수 있는지

void Dfs(int depth, int idx){	// depth: 장애물 설치 개수, idx: 탐색 시작 위치

	if(flag == true) {return;}	// 모든 학생들이 감시로부터 피할 수 있는 경우가 있음

	if(depth == 3){	// 모든 장애물 설치

		bool tmpFlag = true;	// tmpFlag: 현재 설치한 장애물로 모든 학생들이 감시로부터 피할 수 있는지

		for(const Coordinate& teacher : teachers) {	// teacher: 선생님의 위치
			
			for(int dir=0; dir<4; ++dir){
				Coordinate curr = teacher;	// curr: 이번에 탐색할 선생님의 위치

				while(true){
					curr = {curr.y + dirY[dir], curr.x + dirX[dir]};	// 4가지 방향 중 한 방향으로 탐색

					if(curr.y < 0 || curr.x < 0 || curr.y >= N || curr.x >= N) {break;}	// 범위 벗어나면 continue

					if(MAP[curr.y][curr.x] == 2) {	// 학생을 만남
						tmpFlag = false;	// 모든 학생이 감시로부터 피할 수 없음
						break;
					}
					if(MAP[curr.y][curr.x] == -1) {break;}	// 장애물을 만났다면 탐색 중지
				}
				if(tmpFlag == false) {break;}
			}
			if(tmpFlag == false) {break;}
		}

		flag = tmpFlag;

		return;
	}

	for(int i=idx; i<N*N; ++i){
		if(MAP[i/N][i%N] != 0) {continue;}	// 빈 공간이 아니면 continue

		MAP[i/N][i%N] = -1;	// 장애물 설치
		Dfs(depth + 1, i + 1);
		MAP[i/N][i%N] = 0;	// 장애물 제거

	}

	return;
}

void Solution(){

	Dfs(0, 0);

	return;
}

void Input(){

	std::cin >> N;

	MAP.assign(N, std::vector<int>(N, 0));

	for(int y=0; y<N; ++y){
		for(int x=0; x<N; ++x){
			char c;	// c: 정보 -> S: 학생, T: 선생님, X: 아무것도 없음
			std::cin >> c;
			if(c == 'X') {MAP[y][x] = 0;}
			else if(c == 'T') {
				MAP[y][x] = 1;
				teachers.push_back({y, x});	// 선생님의 좌표 저장
			}
			else if(c == 'S') {MAP[y][x] = 2;}
		}
	}

	return;
}

int main(){

	Input();

	Solution();

	if(flag == true) {std::cout << "YES";}	// 모든 학생들이 감시로부터 피할수 있음
	else {std::cout << "NO";}	// 모든 학생들이 감시로부터 피할수 없음

	return 0;
}