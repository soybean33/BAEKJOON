#include <iostream>
#include <queue>
#include <algorithm>

struct Stats {	// Stats: 학급의 학생들의 능력치 내림차순 정렬
	int n;	// n: 학생 능력치

	bool operator < (Stats next) const {
		if (n != next.n) return n < next.n;

		return false;
	}
};

int N, M;	// N: 학급의 수, M: 각 학급의 학생의 수
std::priority_queue<Stats> pq[1'001];	// pq[i]: i 학급의 학생들의 능력치 내림차순 정렬
int classStats[1'001];	// classStats[i]: i 학급의 대표 학생의 능력치
int ans = 21e8;	// ans: 대표로 선발된 모든 학생들 능력치의 최댓값과 최솟값 차이가 최소가 되는 경우의 값

void sol() {

	int classRoom = 0;	// classRoom: 가장 큰 능력치를 갖고 있는 학생이 있는 학급 인덱스
	int max = -1;	// max: 가장 큰 능력치를 갖고 있는 학생의 능력치

	for (int j = 0; j < N; j++) {	// 능력치가 가장 높은 학생부터 순서대로 학급의 대표
		classStats[j] = pq[j].top().n;
		pq[j].pop();
	}

	while (true) {	

		int minV = 21e8, maxV = 0;	// minV: 대표 학생 중 가장 최소 능력치, maxV: 대표 학생 중 가장 최대 능력치

		for (int j = 0; j < N; j++) {

			minV = std::min(minV, classStats[j]);	// 최소 능력치 갱신

			if(classStats[j] > maxV){
				maxV = classStats[j];	// 최대 능력치 갱신
				classRoom = j;	// 최대 능력치를 갖고 있는 학생이 있는 학급 인덱스 갱신
			}
		}

		ans = std::min(ans, maxV - minV);	// 최댓값과 최솟값 비교 및 갱신

		if (!pq[classRoom].size()) break;	// 더 이상 대표 학생을 내보낼수 없는 학급이 대표 학생을 내야할 경우 break

		classStats[classRoom] = pq[classRoom].top().n;	// 최대 능력치를 갖고 있는 학생이 있는 학급에서 대표 학생을 냄
		pq[classRoom].pop();
	}	

	return;
}

void input() {

	std::cin >> N >> M;

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			int n;	// n: 학생의 능력치
			std::cin >> n;
			pq[j].push({ n });
		}
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}