#include <iostream>
#include <algorithm>
#include <vector>

int N, C;	// N: 집의 개수, C: 공유기의 개수
std::vector<int> v;	// v[i]: i 번째 집의 좌표
int minDis = 21e8;	// minDis: 두 집 사이의 최소 거리
int ans = 0;	// ans: 가장 인접한 두 공유기 사이의 최대 거리

void bs() {
	int left = minDis;	// left: 이분 탐색의 왼쪽 -> 가장 가까운 두 집 사이의 거리
	int right = v[v.size()-1] - v[0];	// right: 이분 탐색의 오른쪽 -> 가장 먼 두 집 사이의 거리

	while (left <= right) {
		int mid = (left + right) / 2;	// mid: 공유기를 설치해볼 거리

		int cnt = C - 1;	// cnt: 설치할 수 있는 공유기의 개수 -> 첫 번째 집에 공유기를 설치하고 시작
		int pre = v[0];	// pre: 직전에 설치된 공유
		int distance = 21e8;	// distance: 두 공유기 사이의 최대 거리
		for (int i = 1; i < N; i++) {
			int dis = v[i] - pre;	// dis: 두 집 사이의 거리
			if (dis >= mid) {
				distance = std::min(distance, dis);
				pre = v[i];
				cnt--;
			}
			if (cnt == 0) break;	// 모든 공유기를 설치
		}

		if (cnt != 0) {	// 모든 공유기를 설치하지 못한 경우
			right = mid - 1;	// 공유기 사이의 거리를 더 줄여서 다시 시도
		}
		else {	// 모든 공유기를 설치한 경우
			left = mid + 1;	// 공유기 사이의 거리를 더 늘려서 다시 시도
			ans = std::max(ans, distance);	// 가장 인접한 두 공유기 사이의 거리 갱신
		}
	}

	return;
}

void sol() {
	std::sort(v.begin(), v.end());

	for (int i = 1; i < N; i++) {
		int dis = v[i] - v[i - 1];	// dis: 두 집사이의 거리
		minDis = std::min(minDis, dis);
	}

	bs();

	return;
}

void input() {
	std::cin >> N >> C;
	for (int i = 0; i < N; i++) {
		int loc;	// loc: 집의 위치
		std::cin >> loc;
		v.push_back(loc);			
	}

	return;
}

int main() {
	input();
	sol();

	std::cout << ans;

	return 0;
}