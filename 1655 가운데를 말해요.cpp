#include <iostream>
#include <vector>
#include <queue>

struct MinPQ{
	int n;	// n: 정수

	bool operator < (MinPQ next) const{	// 오름차순
		if(n != next.n) return n > next.n;

		return false;
	}
};

int N;	// N: 정수의 개수
std::vector<int> v;	// v[i]: i 번째 정수

void sol(){

	std::priority_queue<int> maxPQ;	// maxPQ: 큰 값을 top으로 갖는 PQ
	std::priority_queue<MinPQ> minPQ;	// minPQ: 작은 값을 top으로 갖는 PQ

	for(int i=0; i<N; i++){
		int cur = v[i];	// cur: 추가될 정수의 값

		// 1. maxPQ의 크기는 항상 minPQ의 크기보다 작거나 1만큼 더 큼
		// 2. minPQ의 모든 원소는 maxPQ의 모든 원소보다 항상 같거나 큼

		// 우선 1 번의 조건을 만족하도록 PQ에 값 넣음
		if(maxPQ.size() > minPQ.size()) minPQ.push({cur});
		else maxPQ.push(cur);

		if(!maxPQ.empty() && !minPQ.empty()){	// 두 PQ에 모두 값이 있을 경우
			if(maxPQ.top() > minPQ.top().n){	// maxPQ에서 가장 큰 값이 minPQ의 가장 작은 값보다 큰 경우 -> 두 값 바꿔야 함
				int a = maxPQ.top();	// a: maxPQ에서 가장 큰 값
				int b = minPQ.top().n;	// b: minPQ에서 가장 작은 값

				// 두 값 바꿈
				maxPQ.pop();
				minPQ.pop();

				maxPQ.push(b);
				minPQ.push({a});
			}
		}

		std::cout << maxPQ.top() << '\n';	// 정수의 개수가 짝수인 경우 두 수 중에 작은 수
	}

}

void input(){

	std::cin >> N;

	v.resize(N);	// 정수를 저장할 벡터

	for(int i=0; i<N; i++) std::cin >> v[i];

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	return 0;
}