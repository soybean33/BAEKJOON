#include <iostream>
#include <vector>

// 뱡향 -> 동, 서, 남, 북
constexpr int dirY[4] = {0, 0, 1, -1};
constexpr int dirX[4] = {1, -1, 0, 0};

struct Coordinate{
	int y, x;	// y, x: 좌표

	static Coordinate nextCoordi(const Coordinate& curr, const int& dir) {
		return {curr.y + dirY[dir], curr.x + dirX[dir]};	// 다음 좌표
	}
};

double Dfs(const int& N, const std::vector<double>& percentage, std::vector<std::vector<bool>>& visited, Coordinate curr, int cnt) {

	if(cnt == N) {return 1.0;}	// N 번을 모두 움직였다면 단순한 움직임

	visited[curr.y][curr.x] = true;	// 로봇의 현재 위치 방문 체크
	double ret = 0.0;	// ret: 로봇의 이동이 단순할 확률

	for(int dir=0; dir<4; ++dir) {
		Coordinate next = Coordinate::nextCoordi(curr, dir);	// next: 로봇의 다음 위치

		if(visited[next.y][next.x]) {continue;}	// 이미 방문했다면 continue

		ret += percentage[dir] * Dfs(N, percentage, visited, next, cnt + 1);	// 확률 계산 -> 현재 까지의 확률 + 다음 방향 확률 * 그 후 단순하게 움직일 확률
	}
	visited[curr.y][curr.x] = false;	// 방문 해제

	return ret;
}

double Solution(const int& N, const std::vector<double>& percentage) {
	
	double answer = 0;	// answer: 로봇의 이동거리가 단순할 확률

	std::vector<std::vector<bool>> visited;	// visited[i][j]: i 행 j 열의 로봇 방문 체크
	visited.assign(2 * N + 1, std::vector<bool>(2 * N + 1, false));	// 로봇을 중앙에서 출발 시키기 위해 2 * N + 1 크기를 잡음

	answer = Dfs(N, percentage, visited, {N, N}, 0);	// {N, N}에서 출발하여 N번 움직일 때 까지 반복

	return answer;
}

void Input(int& N, std::vector<double>& percentage) {

	std::cin >> N;

	for(int i=0; i<4; ++i) {
		std::cin >> percentage[i];	// 0 <= percntage[i] <= 100
		percentage[i] /= 100;	// 확률로 표시하기 위해 100으로 나눔
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::cout.precision(10);	// 절대/상대 오차는 10^-9 까지 허용

	int N;	// N: 로봇의 행동 횟수
	std::vector<double> percentage(4);	// percentage[i]: 로봇이 i 방향을 선택할 확률 -> 동,서,남,북 순서

	Input(N, percentage);

	std::cout << Solution(N, percentage);

	return 0;
}