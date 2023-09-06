#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int INF = 21e8;	// INF: 나올 수 없는 초기 값

std::vector<int> Solution(const int& N, const int& K) {

	std::vector<int> answer;	// answer[i]: 동생이 수빈이가 있는 위치 까지 가는 경로 정보

	std::vector<int> path;	// path[i]: 경로 정보
	std::queue<int> q;	// q: 이동을 시작할 위치

	int max = std::max(N, K);	// max: 벡터의 크기를 정하기 위해 큰 값을 도출

	path.assign(2 * max + 1, INF);

	path[N] = -1;
	q.push(N);

	while (!q.empty()) {
		int currLoc = q.front();	// currLoc: 현재 위치
		q.pop();

		if (path[K] != INF) { break; }	// 도착지점에 도착했다면 break

		if (currLoc > 0) {	// X - 1로 이동할 수 있는 경우
			int nextLoc = currLoc - 1;	// nextLoc: 다음 위치

			if (path[nextLoc] == INF) {	// 다음위치에 방문한 적이 없다면
				path[nextLoc] = currLoc;
				q.push(nextLoc);
			}
		}
		if (currLoc < 2 * max) {	// X + 1로 이동할 수 있는 경우
			int nextLoc = currLoc + 1;

			if (path[nextLoc] == INF) {	// 다음위치에 방문한 적이 없다면
				path[nextLoc] = currLoc;
				q.push(nextLoc);
			}
		}
		if (currLoc <= max) {	// 2 * X로 이동할 수 있는 경우
			int nextLoc = currLoc * 2;

			if (path[nextLoc] == INF) {	// 다음위치에 방문한 적이 없다면
				path[nextLoc] = currLoc;
				q.push(nextLoc);
			}
		}
	}

	int currPath = K;	// currPath: 현재 경로 위치

	while (currPath != -1) {	// 수빈이의 위치에 도착할 때 까지 반복
		answer.push_back(currPath);
		currPath = path[currPath];
	}	

	return answer;
}

void Input(int& N, int& K) {

	std::cin >> N >> K;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;	// N: 수빈이가 있는 위치, K: 동생이 있는 위치
	std::vector<int> answer;	// answer[i]: 동생이 수빈이가 있는 위치 까지 가는 경로 정보

	Input(N, K);

	answer = Solution(N, K);

	int answerSize = answer.size();	// answerSize: 경로의 길이

	std::cout << answerSize - 1 << '\n';
	for (int i = answerSize - 1; i >= 0; --i) {
		std::cout << answer[i] << ' ';
	}
	
	return 0;
}