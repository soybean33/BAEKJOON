#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

constexpr int INF = 21e8;

int N;
std::vector<std::vector<int>> MAP;

std::vector<int> visited;

int answer = INF;

void Dfs(int depth) {

	if (depth == N) {

		int team1 = 0;
		int team2 = 0;

		for (int i = 0; i < N - 1; ++i) {
			for (int j = i + 1; j < N; ++j) {
				if (visited[i] && visited[j]) { team1 += MAP[i][j] + MAP[j][i]; }
				else if (!visited[i] && !visited[j]) { team2 += MAP[i][j] + MAP[j][i]; }
			}
		}
	
		answer = std::min(answer, std::abs(team1 - team2));

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

	Input();

	Solution();

	std::cout << answer;

	return 0;
}
