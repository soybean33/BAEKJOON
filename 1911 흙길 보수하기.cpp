#include <iostream>
#include <vector>
#include <algorithm>

int N, L;	// N: 물웅덩이의 개수, L: 널빤지의 길이
std::vector<std::pair<int, int>> V;	// V[i]: 물 웅덩이의 시작점과 끝점

int answer;	// answer: 널빤지의 최소 개수

bool Cmp(const std::pair<int, int>& left, const std::pair<int, int>& right){	// 시작 위치를 기준으로 오름차순 정렬

	if(left.first != right.second) {return left.first < right.first;}

	return false;
}

void Solution(){

	std::sort(V.begin(), V.end(), Cmp);

	int idx = 0;	// idx: 인덱스

	for(const std::pair<int, int> v : V) {	// v: 현재 물 웅덩이

		if(idx >= v.second) {continue;}	// 이미 널빤지로 덮였다면 continue

		idx = std::max(idx, v.first);	// 최댓값 갱신

		int cnt = (v.second - (idx + 1)) / L + 1;	// cnt: 필요한 널빤지의 개수

		answer += cnt;	// 널빤지 개수 추가

		idx += L * cnt;	// 위치 추가
	}

	return;
}

void Input(){

	std::cin >> N >> L;

	V.assign(N, {0, 0});

	for(int i=0; i<N; ++i) {
		std::cin >> V[i].first >> V[i].second;
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}