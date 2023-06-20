#include <iostream>
#include <vector>
#include <queue>

struct Cmp{	// 오름차순 정렬 우선 순위 큐
	bool operator () (int left, int right) const{
		if (left != right) return left > right;

		return false;
	}
};

int N;	// N: 카드 묶음의 수
std::priority_queue<int, std::vector<int>, Cmp> pq;	// pq: 카드 묶음의 수 오름차순 정렬 우선 순위 큐
int ans;	// ans: 최소 비교 횟수

void sol(){

	while(pq.size() > 1){	// 한 묶음이 될 때 까지 반복
		int a = pq.top();	// a: 첫 번째로 작은 카드 묶음의 카드 수
		pq.pop();

		int b = pq.top();	// b: 두 번째로 작은 카드 묶음의 카드 수
		pq.pop();

		ans += a + b;	// ans: 최소 비교 횟수
		pq.push(a + b);	// 두 묶음을 하나의 묶음으로 만들어 다시 우선 순위 큐에 삽입
	}

	return;
}

void input(){

	std::cin >> N;

	for(int i=0; i<N; i++){
		int n;	// n: 한 묶음의 숫자 카드 수
		std::cin >> n;
		pq.push(n);
	}

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