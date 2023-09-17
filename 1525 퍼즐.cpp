#include <iostream>
#include <string>
#include <queue>
#include <set>

// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

int Solution(std::string& MAP) {

	int answer = -1;	// answer: 최소 이동 횟수 -> 이동이 불가능한 경우 -1
	
	std::queue<std::pair<std::string, int>> q;	// q: 퍼즐의 값과 이동 횟수를 담고 있는 큐
	std::set<std::string> visited;	// visited: 방문 검사를 위한 집합 -> 집합에 있는 문자열이라면 이미 방문한 문자열

	q.push({MAP, 0});	// 현재 위치에서 시작
	visited.insert(MAP);

	while(!q.empty()){
		std::pair<std::string, int> curr = q.front();	// curr: 최종 상태 확인 및 이동할 퍼즐
		q.pop();

		if(curr.first == "123456780") {	// 정리된 상태라면
			answer = curr.second;	// 이동 횟수로 정답 갱신
			break;
		}

		int zeroIdx = curr.first.find('0');	// zeroIdx: 문자열에서 빈 공간의 위치
		int currY = zeroIdx / 3;	// currY: 빈 공간의 Y 위치
		int currX = zeroIdx % 3;	// currX: 빈 공간의 X 위치

		for(int dir=0; dir<4; ++dir) {
			int nextY = currY + dirY[dir];	// nextY: 이동할 Y 위치
			int nextX = currX + dirX[dir];	// nextX: 이동할 X 위치

			if(nextY < 0 || nextX < 0 || nextY >= 3 || nextX >= 3) {continue;}	// 범위 벗어나면 continue

			std::pair<std::string, int> next = {curr.first, curr.second + 1};	// next: 다음 상태

			std::swap(next.first[currY * 3 + currX], next.first[nextY * 3 + nextX]);	// 퍼즐 이동

			if(visited.find(next.first) != visited.end()) {continue;}	// 이미 확인한 퍼즐이면 continue

			visited.insert(next.first);
			q.push(next);
		}
	}

	return answer;
}

void Input(std::string& MAP) {

	for(int y=0; y<3; ++y) {
		for(int x=0; x<3; ++x) {
			int n;
			std::cin >> n;
			MAP += n + '0';
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string MAP;	// MAP[i * 3 + j]: i 행 j 열의 수 -> 빈 칸은 0

	Input(MAP);

	std::cout << Solution(MAP);

	return 0;
}