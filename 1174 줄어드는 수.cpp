#include <iostream>
#include <vector>
#include <queue>

int N;	// N: 구해야 하는 감소하는 수의 번호

long long answer = -1;	// answer: 감소하는 수 -> 없다면 -1

struct Cmp {	// 내림차순 정렬
	bool operator() (long long& left, long long& right) {
		if (left != right) return left > right;

		return false;
	}
};

void Solution() {

	std::priority_queue<long long, std::vector<long long>, Cmp> pq;	// pq: 내림차순 정렬한 우선 순위 큐

	// 한자리 수 초기 값 넣음
	for (long long i = 0; i < 10; ++i) {
		pq.push(i);
	}

	while (!pq.empty()) {
		long long curr = pq.top();	// curr: 현재 수
		pq.pop();
		
		--N;

		if (N == 0) {	// 원하는 번째의 수
			answer = curr;
			return;
		}		

		int lastNum = curr % 10;	// lastNum: 가장 마지막 수

		for (int i = 0; i < lastNum; ++i) {
			long long next = curr * 10 + i;	// next: 다음 후보 수
			pq.push(next);
		}
	}

	return;
}

void Input() {

	std::cin >> N;

	return;
}

int main() {
	
	Input();

	Solution();

	std::cout << answer;

	return 0;
}