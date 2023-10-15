#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 배열의 크기
std::vector<int> v;	// v[i]: i 번째 값
int S;	// S: 교환의 횟수

void Solution() {

	for (int i = 0; i < N; ++i) {
		int max = v[i];	// max: 최대 값
		int maxIdx = i;	// maxIdx: 최대 값의 인덱스
		for (int j = i + 1; j < N; ++j) {
			if (S - (j - i) >= 0) {	// 교환 횟수가 남아 있다면
				if (max < v[j]) {	// 큰 값 갱신
					max = v[j];
					maxIdx = j;
				}
			}
		}
		for (int j = maxIdx; j > i; --j) {
			std::swap(v[j], v[j - 1]);	// 가장 큰 값이랑 교환
		}
		S -= (maxIdx - i);
		if (S <= 0) { break; }
	}
	for (int i = 0; i < N; ++i) { std::cout << v[i] << ' '; }

	return;
}

void Input() {

	std::cin >> N;
	v.assign(N, 0);

	for (int i = 0; i < N; ++i) { std::cin >> v[i]; }

	std::cin >> S;

	return;
}

int main() {

	Input();

	Solution();

	return 0;
}