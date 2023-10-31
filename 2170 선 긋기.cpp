#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 21e8;

struct Line {
	int start, end;
};

int N;
std::vector<Line> lines;

int answer;

bool Cmp(const Line& left, const Line& right) {

	if (left.start != right.start) { return left.start < right.start; }

	return false;
}

void Solution() {

	std::sort(lines.begin(), lines.end(), Cmp);

	int left = -INF;
	int right = -INF;

	for (int i = 0; i < N; ++i) {
		if (lines[i].start <= right) { right = std::max(right, lines[i].end); }
		else {
			answer += right - left;
			left = lines[i].start;
			right = lines[i].end;
		}
	}
	answer += right - left;

	return;
}

void Input() {

	std::cin >> N;
	lines.assign(N, { 0, 0 });

	for (int i = 0; i < N; ++i) { std::cin >> lines[i].start >> lines[i].end; }

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