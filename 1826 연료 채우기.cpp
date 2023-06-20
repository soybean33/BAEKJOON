#include <iostream>
#include <queue>

int N;	// N: 주유소의 개수
int gasStation[1'000'001];	// gasStation[i]: i 거리에 있는 주유소에서 채울 수 있는 연료의 양
int L, P;	// L: 성경이의 위치에서 마을까지의 거리, P: 트럭에 원래 있던 연료의 양
std::priority_queue<int> pq;	// pq: 주유소에서 채울 수 있는 연료의 양 내림차순 정렬
int ans;	// ans: 주유소에서 멈추는 횟수, 마을에 도착하지 못할경우 -1

void sol(){

	for(int i=0; i<L; i++){
		if(gasStation[i]) pq.push(gasStation[i]);	// 현재 위치에 주유소가 있다면 우선 순위 큐에 넣음

		if(P == 0){	// 연료가 다 소모됨
			if(pq.empty()){	// 오는 길에 주유소가 없었다면
				ans = -1;	// 마을에 도착하지 못함
				return;
			}
			P += pq.top();	// 연료 채움
			pq.pop();
			ans++;	// 주유소에서 멈추는 횟수 증가
		}
		P--;	// 연료 감소
	}

}

void input(){

	std::cin >> N;
	for(int i=0; i<N; i++){
		int a, b;	// a: 성경이의 시작 위치에서ㅓ 주유소 까지의 거리, b: 그 주유소에서 채울 수 있는 연료의 양
		std::cin >> a >> b;
		gasStation[a] = b;
	}

	std::cin >> L >> P;

	return;
}


int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();
	
	sol();

	std::cout << ans;

	return 0;
}