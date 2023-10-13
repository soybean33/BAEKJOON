#include <iostream>
#include <string>
#include <queue>

// 방향벡터 -> 동 서 남 북 상 하
constexpr int dirZ[6] = {0, 0, 0, 0, 1, -1};
constexpr int dirY[6] = {0, 0, -1, 1, 0, 0};
constexpr int dirX[6] = {1, -1, 0, 0, 0, 0};

struct Coordinate{	// 좌표
	int z, y, x;
};

int L, R, C;	// L: 층, R: 세로, C: 가로
std::vector<std::vector<std::vector<int>>> MAP;	// MAP[i][j][k]: i 층의 j 행 k 열의 정보 -> -1: 갈수 없는 칸, 0: 갈 수 있는 칸
Coordinate start, end;	// start, end: 시작 지점 끝 지점

void Solution(){

	bool flag = false;	// flag: 탈출 가능하면 true

	std::vector<std::vector<std::vector<int>>> visited;	// visited[i][j][k]: i 층의 j 행 k 열의 방문 여부 및 시간
	visited.assign(L, std::vector<std::vector<int>>(R, std::vector<int>(C, 0)));

	std::queue<Coordinate> q;	// q: 탐색할 좌표를 넣을 쿠
	q.push(start);
	visited[start.z][start.y][start.x] = 1;

	while(!q.empty()){
		Coordinate curr = q.front();	// curr: 현재 좌표
		q.pop();

		for(int dir=0; dir<6; ++dir) {
			Coordinate next = {curr.z + dirZ[dir], curr.y + dirY[dir], curr.x + dirX[dir]};	// next: 다음 좌표

			if(next.z < 0 || next.y < 0 || next.x < 0 || next.z >= L || next.y >= R || next.x >= C) {continue;}	// 범위 벗어나면 continue

			if(MAP[next.z][next.y][next.x] != 0) {continue;}	// 갈 수 없는 곳 continue
			if(visited[next.z][next.y][next.x] != 0) {continue;}	// 이미 방문한 곳 continue

			visited[next.z][next.y][next.x] = visited[curr.z][curr.y][curr.x] + 1;	// 시간 입력

			if(next.z == end.z && next.y == end.y && next.x == end.x) {	// 탈출할 수 있는 곳에 도착
				std::cout << "Escaped in " << visited[end.z][end.y][end.x] - 1 << " minute(s).\n";
				flag = true;
			}

			q.push(next);			
		}
	}

	if(flag == false) {std::cout << "Trapped!\n";}	// 탈출 못함

	return;
}

void Input(){

	std::cin >> L >> R >> C;

	MAP.assign(L, std::vector<std::vector<int>>(R, std::vector<int>(C, 0)));

	for(int z=0; z<L; ++z){
		for(int y=0; y<R; ++y){
			std::string s;
			std::cin >> s;
			for(int x=0; x<C; ++x){
				if(s[x] == 'S') {	// 시작 지점
					start = {z, y, x};
					MAP[z][y][x] = 0;
				}
				else if(s[x] == '#') {MAP[z][y][x] = -1;}	// 벽
				else if(s[x] == 'E') {	// 도착 지점
					end = {z, y, x};
					MAP[z][y][x] = 0;
				}
			}
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while(true){

		Input();

		if(L == 0 && R == 0 && C == 0) {break;}

		Solution();
	}

	return 0;
}