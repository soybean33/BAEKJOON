#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

// 방향벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate{	// 좌표
	int y, x;
};

int N, K;	// N: 시험관의 한 변의 길이 1<=N<=200, K: 바이러스의 종류 1<=K<=1'000 
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 바이러스 종류
int S;	// S: 경과 시간
Coordinate answerCoordi;	// answerCoordi: 확인할 바이러스 위치

std::vector<std::pair<int, Coordinate>> viruses;	// viruses[i]: i 번째 바이러스의 종류와 좌표

int answer;	// answer: 바이러스 종류

bool Cmp(const std::pair<int, Coordinate>& left, std::pair<int, Coordinate>& right){	// 바이러스 종류를 기준으로 오름차순 정렬
	if(left.first != right.first) return left.first < right.first;

	return false;
}

void Solution(){

	std::sort(viruses.begin(), viruses.end(), Cmp);	// 바이러스 종류를 기준으로 오름차순 정렬
	int virusCnt = viruses.size();

	std::queue<std::pair<int, Coordinate>> q;	// q: 바이러스 종류와 좌표를 저장할 큐
	for(const std::pair<int, Coordinate> virus : viruses) {
		q.push(virus);	// 바이러스 저장
	}

	while(S--){	// S초 동안 S번 반복
		int qSize = q.size();	// qSize: 큐의 크기 -> 이번 턴에 퍼질 바이러스의 개수
		int cnt = 0;	// cnt: 퍼진 바이러스 수
		while(cnt < qSize){	// 이번 턴에 퍼질 바이러스 만큼만 반복
			++cnt;	// 퍼진 바이러스 증가
			
			int viruesNum = q.front().first;	// virusesNum: 바이러스 종류
			Coordinate curr = q.front().second;	// curr: 바이러스 좌표
			q.pop();		

			for(int dir=0; dir<4; ++dir){
				Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]};	// next: 바이러스가 퍼진 좌표

				if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) {continue;}	// 범위 벗어나면 continue

				if(MAP[next.y][next.x] != 0) {continue;}	// 이미 다른 바이러스가 퍼졌다면 continue

				MAP[next.y][next.x] = viruesNum;	// 바이러스 퍼짐
				q.push({viruesNum, next});

				if(answerCoordi.y == next.y && answerCoordi.x == next.x) {return;}	// 찾고자 하는 칸에 바이러스가ㅏ 퍼졌다면 return
			}			
		}	
	}

	return;
}

void Input(){

	std::cin >> N >> K;
	MAP.assign(N, std::vector<int>(N, 0));

	for(int y=0; y<N; ++y){
		for(int x=0; x<N; ++x){
			std::cin >> MAP[y][x];

			if(MAP[y][x] == 0) {continue;}	// 바이러스가 없는 빈 칸 continue		
			viruses.push_back({MAP[y][x], {y, x}});	// 바이러스 입력
		}
	}

	std::cin >> S >> answerCoordi.y >> answerCoordi.x;
	--answerCoordi.y;
	--answerCoordi.x;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << MAP[answerCoordi.y][answerCoordi.x];

	return 0;
}