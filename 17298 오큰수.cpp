#include <iostream>
#include <vector>

int N;	// N:L 수열의 길이
std::vector<int> v;	// v[i]: 수열
std::vector<int> stack;	// stack[i]: 스택

std::vector<int> answer;	// answer[i]: i 보다 오른쪽에 있으면서 v[i]보다 큰 수 중에서 가장 왼쪽에 있는 수

void Solution() {

	answer.assign(N, 0);

	for (int i = N - 1; i >= 0; --i) {
		while (!stack.empty() && stack.back() <= v[i]) { stack.pop_back(); }	// 다른 오큰수가 있음

		if (stack.empty()) answer[i] = -1;	// 오큰수가 없다면 -1
		else answer[i] = stack.back();	// 오큰수 출력

		stack.push_back(v[i]);
	}

	return;
}

void Input() {

	std::cin >> N;
	v.assign(N, 0);

	for (int i = 0; i < N; ++i) { std::cin >> v[i]; }

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	for (int i = 0; i < N; ++i) { std::cout << answer[i] << ' '; }

	return 0;
}