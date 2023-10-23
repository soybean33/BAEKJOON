#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 장소의 개수
std::vector<int> sum, honey;	// sum[i]: i 번째 위치까지의 꿀의 합, honey[i]: i 번째 위치의 꿀의 양

int answer;	// answer: 가능한 최대 꿀의 양

void Solution() {

	// 벌 - 꿀통 - 벌
	for (int i = 2; i < N; ++i) {
		int curr = (sum[i] - sum[1]) + (sum[N - 1] - sum[i - 1]);
		answer = std::max(answer, curr);
	}

	// 벌 - 벌 - 꿀통
	for (int i = 2; i < N; ++i) {
		int curr = (sum[N] - sum[1] - honey[i]) + (sum[N] - sum[i]);
		answer = std::max(answer, curr);
	}

	// 꿀통 - 벌 - 벌
	for (int i = 2; i < N; ++i) {
		int curr = (sum[N-1] - honey[i]) + sum[i - 1];
		answer = std::max(answer, curr);
	}

	return;
}

void Input() {

	std::cin >> N;

	honey.assign(N + 1, 0);
	sum.assign(N + 1, 0);	

	for (int i = 1; i <= N; ++i) {
		std::cin >> honey[i];
		sum[i] = sum[i - 1] + honey[i];
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