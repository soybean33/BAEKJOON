#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

struct Coordinate{	// 좌표
	int y, x;
};

int T;	// T: 테스트 케이스의 개수
int N;	// N: 편의점의 개수
Coordinate Home;	// Home: 상근이네 집 좌표
std::vector<Coordinate> Stores;	// Stores[i]: i 번째 편의점 좌표
Coordinate Festival;	// Festival: 펜타포트 락 페스티벌 좌표

std::string answer;	// answer: 상근이와 친구들이 행복하게 페스티벌에 갈 수 있으면 "happy", 중간에 맥주가 바닥나서 더 이동할 수 없으면 "sad"

bool DistancePassible(Coordinate left, Coordinate right){	// left, right: 이동을 희망하는 두 좌표
	int distance = std::abs(left.y - right.y) + std::abs(left.x - right.x);	// distance: 맨해튼 거리 계산

	if(distance <= 1'000) {return true;}	// 50미터 * 20병 -> 1'000 미터 가능

	return false;
}

void Solution(){

	bool flag = false;	// flag: 페스티벌에 갈 수 있으면 true

	std::vector<bool> visited;	// visited[i]: i 번째 편의점에 들렸다면 true
	visited.assign(N, false);

	std::queue<Coordinate> q;	// q: 출발할 좌표
	q.push(Home);	// 집에서 출발

	while(!q.empty()){
		Coordinate curr = q.front();
		q.pop();

		if(DistancePassible(Festival, curr)) {	// 현재 위치에서 페스티벌에 갈 수 있다면
			flag = true;	// flag를 true로 변경
			break;
		}
		for(int i=0; i<N; ++i){
			if(visited[i] == true) {continue;}	// 이미 방문 했다면 continue

			if(DistancePassible(Stores[i], curr)) {	// 현재 위치에서 갈 수 있는 편의점이 있다면
				visited[i] = true;	// 방문 체크
				q.push(Stores[i]);	// 큐에 넣음
			}
		}
	}

	answer = flag ? "happy\n" : "sad\n";	// 페스티벌에 갈 수 있으면 Happy, 아니면 sad

	return;
}

void Input(){

	std::cin >> N;

	std::cin >> Home.y >> Home.x;

	Stores.assign(N, {0, 0});
	for(int i=0; i<N; ++i) {std::cin >> Stores[i].y >> Stores[i].x;}

	std::cin >> Festival.y >> Festival.x;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> T;

	while(T--){
		Input();
		Solution();
		std::cout << answer;
	}

	return 0;
}