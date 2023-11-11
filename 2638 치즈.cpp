#include <iostream>
#include <vector>
#include <queue>

// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate{	// Coordinate: 좌표
	int y, x;	// y, x: 좌표
};

int N, M;	// N: 세로 격자의 수, M: 가로 격자의 수
std::vector<std::vector<bool>> MAP;	// MAP[i][j]: i 행 j 열에 치즈가 있다면 true

int leftCheeze;	// leftCheeze: 남은 치즈 격자 개수
int answer;	// answer: 주어진 치즈가 모두 녹아 없어지는데 걸리는 시간

void Solution(){

	while(true){

		if(leftCheeze == 0) {break;}	// 모든 치즈가 녹아 없어졌다면 break

		++answer;	// 시간 증가

		std::queue<Coordinate> q;	// q: 탐색할 좌표
		std::vector<std::vector<bool>> visited;	// visited[i][j]: i 행 j 열 방문 여부
		std::vector<std::vector<int>> airCnt;	// airCnt[i][j]: i 행 j 열에 공기 접촉 개수

		q.push({0, 0});	// 시작점
		visited.assign(N, std::vector<bool>(M, false));
		visited[0][0] = true;
		airCnt.assign(N, std::vector<int>(M, 0));

		while(!q.empty()){
			Coordinate curr = q.front();	// curr: 현재 좌표
			q.pop();

			for(int dir=0; dir<4; ++dir){
				Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]};	// next: 다음 좌표

				if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) {continue;}	// 범위 벗어나면 continue

				if(MAP[next.y][next.x] == true) {	// 치즈가 있는 칸이라면
					++airCnt[next.y][next.x];	// 공기 접촉 증가
				}
				else{	// 치즈가 없는 칸이라면
					if(visited[next.y][next.x] == true) {continue;}	// 이미 방문한 칸이면 continue
					q.push(next);	// 방문하지 않은 칸이면 탐색에 넣음
					visited[next.y][next.x] = true;	// 방문 체크
				}
			}
		}

		for(int y=0; y<N; ++y){
			for(int x=0; x<M; ++x){
				if(airCnt[y][x] > 1) {	// 2변 이상이 실내온도의 공기와 접촉했다면
					--leftCheeze;	// 치즈가 녹아 없어짐
					MAP[y][x] = false;	// 치즈가 녹아 없어짐
				}
			}
		}
	}

	return;
}

void Input(){

	std::cin >> N >> M;

	MAP.assign(N, std::vector<bool>(M, false));

	for(int y=0; y<N; ++y){
		for(int x=0; x<M; ++x){
			int n;	// n: 치즈 유무
			std::cin >> n;

			if(n == 1) {	// 치즈가 있는 격자라면
				++leftCheeze;	// 치즈 개수 ++
				MAP[y][x] = true;	// 치즈 표시
			}
			else{MAP[y][x] = false;}	// 치즈가 없는 격자라면
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}