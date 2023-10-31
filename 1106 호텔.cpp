#include <iostream>
#include <vector>
#include <algorithm>

int C, N;	// C: 늘리고 싶은 고객의 수, N: 도시의 개수
std::vector<std::pair<int, int>> v;	// v[i]: i 번째 도시의 홍보할 때 대는 비용과 그 비용으로 얻을 수 있는 고객의 수

int answer;	// answer: 고객을 적어도 C명 늘리기 위해 형택이가 투자해야하는 돈의 최솟값

void Solution() {

	std::vector<int> dp;	// dp[i]: i 돈을 투자하여 늘릴 수 있는 고객의 수
	dp.assign(1'000 * 100 + 1, 0);

	for (int i = 0; i < N; ++i) {	// 도시에 대하여
		for (int j = v[i].first; j <= 100'000; ++j) {	// 최대 100'000 까지 고객을 늘림
			dp[j] = std::max(dp[j], dp[j - v[i].first] + v[i].second);			
		}
	}

	for (int i = 1; i <= 100'000; ++i) {
		if (dp[i] >= C) {	// C명이상 고객이 늘었다면
			answer = i;
			break;
		}
	}

	return;
}

void Input() {

	std::cin >> C >> N;

	v.assign(N, { 0, 0 });

	for (int i = 0; i < N; ++i) {
		std::cin >> v[i].first >> v[i].second;
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