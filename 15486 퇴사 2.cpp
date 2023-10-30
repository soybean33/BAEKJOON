#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: N + 1 번째 날에 퇴사
std::vector<std::pair<int, int>> V;	// V[i]: i 번째의 걸리는 기간과 상담을 했을 때 받을 수 있는 금액

int answer;	// answer: 상담을 적절히 했을 때, 백준이가 얻을 수 있는 최대 수익

void Solution() {

	std::vector<int> dp;	// dp[i]: i 번째 날의 최대 수익

	dp.assign(N + 3, 0);

	for (int i = 1; i <= N + 1; ++i) {
		answer = std::max(answer, dp[i]);	// 최대값 갱신
		if (i + V[i].first > N + 1) { continue; }

		dp[i + V[i].first] = std::max(dp[i + V[i].first], answer + V[i].second);
	}

	return;
}

void Input() {

	std::cin >> N;

	V.assign(N + 2, { 0, 0 });

	for (int i = 1; i <= N; ++i) { std::cin >> V[i].first >> V[i].second; }

	return;
}

int main() {

	Input();

	Solution();

	std::cout << answer;

	return 0;
}