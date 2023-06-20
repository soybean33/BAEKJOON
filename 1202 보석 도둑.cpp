#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

int N, K;	// N: 보석의 개수, K: 상덕이의 가방의 개수
std::vector<std::pair<int, int>> jewel;	// jewel[i]: i 번째 보석의 무게와 가격
std::vector<int> bag;	// bag[i]: i 번째 가방에 담을 수 있는 최대 무게
long long ans;	// ans: 상덕이가 훔칠 수 있는 보석 가격의 합의 최댓값

bool cmp(std::pair<int, int> left, std::pair<int, int> right){	// 보석의 무게를 기준으로 오름차순 정렬

	if(left.first != right.first) return left.first < right.first;

	return false;
}

void sol(){

	std::sort(jewel.begin(), jewel.end(), cmp);	// 보석의 무게를 기준으로 오름차순 정렬

	std::sort(bag.begin(), bag.end());	// 가방에 담을 수 있는 최대 무게를 기준으로 오름차순 정렬

	std::priority_queue<int> pq;	// pq: 현재 가방에 담을 수 있는 보석의 가격을 기준으로 내림차순 정렬한 우선 순위 큐
	
	int idx = 0;	// idx: 가방에 넣을 수 있는 보석의 인덱스

	for(int i=0; i<K; i++){
		int curBag = bag[i];	// curBag: 현재 가방에 담을 수 있는 최대 무게

		while(idx < N && jewel[idx].first <= curBag){
			pq.push(jewel[idx].second);	// 현재 가방에 넣을 수 있는 보석은 우선 순위 큐에 넣음
			idx++;
		}

		if(!pq.empty()){
			ans += pq.top();	// 가장 가격이 높은 보석 부터 가방에 넣음
			pq.pop();
		}
	}

	return;
}

void input(){

	std::cin >> N >> K;

	jewel.resize(N);	// 보석 공간 할당
	bag.resize(K);	// 가방 공간 할당
	
	for(int i=0; i<N; i++){
		int M, V;	// M: 보석의 무게, V: 보석의 가격
		std::cin >> M >> V;
		jewel[i] = {M, V};
	}

	for(int i=0; i<K; i++){
		int C;	// C: 가방에 담을 수 있는 최대 무게
		std::cin >> C;
		bag[i] = C;
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