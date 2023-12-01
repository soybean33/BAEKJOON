#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 아이들의 수
std::vector<int> V;	// V[i]: i 번째 아이의 번호

int answer;	// answer: 번호 순서대로 줄을 세우는데 옮겨지는 아이들의 최소 수

void Solution() {

	std::vector<int> dp;	// dp[i]; 옮겨지는 아이의 수

	dp.assign(N + 1, 1);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= i; ++j) {
			if (V[j] < V[i]) { dp[i] = std::max(dp[i], dp[j] + 1); }
		}
		answer = std::max(answer, dp[i]);
	}

	answer = N - answer;

	return;
}

void Input() {

	std::cin >> N;

	V.assign(N + 1, 0);

	for (int i = 1; i <= N; ++i) { std::cin >> V[i]; }


	return;
}

int main() {

	Input();

	Solution();

	std::cout << answer;

	return 0;
}