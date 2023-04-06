#include <iostream>
#include <vector>
#include <queue>

struct Edge {
	int to;	// to: 다음 헛간
	int cowNum;	// cowNum: 길에 있는 소의 수

	bool operator < (Edge next) const {	// 소의 수에 따른 오름차순
		if (cowNum < next.cowNum) return false;
		if (cowNum > next.cowNum) return true;

		return false;
	}
};

int N, M;	// N: 헛간의 수, M: 길의 수
std::vector<Edge> v[50001];	// v: 길 정보
int cows[50001];	// cows[i]: i 헛간까지 가는데 만나는 최소 소의 수

void sol() {

	for (int i = 1; i <= N; i++)
		cows[i] = 21e8;	// 최대값으로 초기화

	std::priority_queue<Edge> pq;	// pq: 길 정보 오름차순
	pq.push({ 1, 0 });	// 시작위치
	cows[1] = 0;	// 시작위치에서 만날 수 있는 소의 수는 0

	while (!pq.empty()) {
		Edge now = pq.top();	// 현재 헛간에 연결되어 있는 길 정보
		pq.pop();
		
		if (cows[now.to] < now.cowNum) continue;	// 다른 길을 통해 다음 헛간까지 갔을 때의 소의 수가 지금 이 길을 통해 갔을 때 보다 적다면 continue

		for (int i = 0; i < v[now.to].size(); i++) {
			Edge next = v[now.to][i];	// next: 다음 헛간에 연결되어 있는 길 정보
			int nextCowNum = cows[now.to] + next.cowNum;	// nextCowNum: 다음 헛간까지의 소의 수와 그 다음 헛간까지 가는데 만나는 소의 수

			if (cows[next.to] <= nextCowNum) continue;	// 다다음 헛간까지의 소의 수보다 더 많은 소를 만나면 continue

			cows[next.to] = nextCowNum;	// 다다음 헛간의 소의 수 갱신

			pq.push({ next.to, nextCowNum });
		}
	}

	return;
}

void input() {
	std::cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to, cowNum;	// from: 현재 헛간, to: 다음 헛간, cowNum: 길에 있는 소의 수
		std::cin >> from >> to >> cowNum;
		v[from].push_back({ to, cowNum });
		v[to].push_back({ from, cowNum });	// 양방향
	}

	return;
}

int main() {
	input();
	sol();

	std::cout << cows[N];

	return 0;
}