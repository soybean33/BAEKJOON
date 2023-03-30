#include <iostream>
#include <queue>

int visited[100001];	// visited[i]: i 위치까지 가는데 걸린 시간

struct Node {
	int location;	// location: 위치
	int distance;	// distance: location까지 가는데 걸린 시간

	bool operator < (Node next) const {	// 시간 순서 오름차순 정렬
		if (distance < next.distance) return false;
		if (distance > next.distance) return true;

		return false;
	}
};

int main() {

	int N, K;	// N: 수빈의 위치, K: 동생의 위치

	std::cin >> N >> K;
	for (int i = 0; i <= 100000; i++)
		visited[i] = 21e8;	// 초기값 최대 값

	std::priority_queue<Node> pq;	// pq: 수빈이의 위치를 기준으로 걸리는 시간
	pq.push({ N, 0 });	// 수빈의 위치는 0초
	visited[N] = 1;

	while (!pq.empty()) {
		Node cur = pq.top();
		pq.pop();

		if (cur.location == K) {	// 동생의 위치에 도착
			std::cout << cur.distance;
			return 0;
		}

		if (cur.location + 1 <= 100000) {	// 앞으로 한 칸, 1초 소요
			if (visited[cur.location + 1] > cur.distance + 1) {	// 기록된 시간보다 작은 경우 갱신
				pq.push({ cur.location + 1, cur.distance + 1 });
				visited[cur.location + 1] = cur.distance + 1;
			}
		}

		if (cur.location * 2 <= 100000) {	// 순간 이동, 현재 위치의 2배 위치, 0초 소요
			if (visited[cur.location * 2] > cur.distance) {	// 기록된 시간보다 작은 경우 갱신
				pq.push({ cur.location * 2, cur.distance });
				visited[cur.location * 2] = cur.distance;
			}
		}

		if (cur.location - 1 >= 0) {	// 뒤로 한 칸, 1초 소요
			if (visited[cur.location - 1] > cur.distance + 1) {	// 기록된 시간보다 작은 경우 갱신
				pq.push({ cur.location - 1, cur.distance + 1 });
				visited[cur.location - 1] = cur.distance + 1;
			}
		}
	}	 

	return 0;
}