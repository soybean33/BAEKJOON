#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

constexpr int INF = 21e8;

int N;	// N: 사람의 수
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 번 사람과 j 번 사람이 같은 팀에 속했을 때, 팀에 더해지는 능력치

std::vector<int> visited;	// visited[i]: i 사람의 소속 팀 정보

int answer = INF;	// answer: 스타트 팀과 링크 팀의 능력치의 차이의 최솟값

void Dfs(int depth) {	// depth: 팀을 정할 사람의 번호

	if (depth == N) {	// 모든 사람의 팀이 정해진 경우

		// 스타트 팀과 링크 팀의 능력치
		int team1 = 0;
		int team2 = 0;

		for (int i = 0; i < N - 1; ++i) {
			for (int j = i + 1; j < N; ++j) {
				if (visited[i] && visited[j]) { team1 += MAP[i][j] + MAP[j][i]; }	// true 팀인 경우
				else if (!visited[i] && !visited[j]) { team2 += MAP[i][j] + MAP[j][i]; }	// false 팀인 경우
			}
		}
	
		answer = std::min(answer, std::abs(team1 - team2));	// 팀의 능력치의 최솟값

		return;
	}

	visited[depth] = true;
	Dfs(depth + 1);

	visited[depth] = false;
	Dfs(depth + 1);

	return;
}

void Solution() {

	visited.assign(N, 0);

	Dfs(0);

	return;
}

void Input() {

	std::cin >> N;

	MAP.assign(N, std::vector<int>(N, 0));

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			std::cin >> MAP[y][x];
		}
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}
