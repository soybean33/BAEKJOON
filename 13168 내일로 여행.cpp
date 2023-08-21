#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

constexpr int INF = 10e8;	// INF: 나올 수 없는 값

int N, R;	// N: 도시의 수, R: 1인당 내일로 티켓의 가격
std::unordered_map<std::string, int> um;	// um: <도시의 이름, 인덱스>
int M;	// M: 여행할 도시의 수
std::vector<int> visiteCityIdx;	// visitedCityIdx[i]: i 번째로 여행할 도시의 인덱스
int K;	// K: 교통수단의 수
std::vector<std::vector<double>> cost, railCost;	// cost[i][j]: i 도시에서 j 도시까지의 최소 여행 비용, railCost[i][j]: 내일로를 사용하였을 때 i 도시에서 j 도시까지의 최소 여행 비용
double costSum, railCostSum;	// costSum: 내일로 티켓을 사지 않았을 경우의 여행 비용, railCostSum: 내일로 티켓을 샀을 경우의 여행 비용

void solution() {

	// 플로이드-워셜
	for(int t=0; t<N; ++t) {
		for(int s=0; s<N; ++s) {
			for(int e=0; e<N; ++e) {
				cost[s][e] = std::min(cost[s][e], cost[s][t] + cost[t][e]);	// 네일로를 사용하지 않았을 경우
				railCost[s][e] = std::min(railCost[s][e], railCost[s][t] + railCost[t][e]);	// 네일로를 사용하였을 경우
			}
		}
	}

	for(int i=0; i<M-1; ++i) {
		int startIdx = visiteCityIdx[i];	// startIdx: 출발 도시 인덱스
		int endIdx = visiteCityIdx[i+1];	// endIdx: 도착 도시 인덱스

		costSum += cost[startIdx][endIdx];
		railCostSum += railCost[startIdx][endIdx];
	}

	railCostSum += R;	// 네일로 티켓의 가격 더하기

	return;
}

void input(){

	std::cin >> N >> R;

	for(int i=0; i<N; ++i){
		std::string s;	// s: 도시의 이름
		std::cin >> s;

		um.insert({s, i});	// 인덱스로 호출할 수 있도록 맵에 넣음
	}

	std::cin >> M;

	visiteCityIdx.assign(M, -1);

	for(int i=0; i<M; ++i){
		std::string s;	// s: 도시의 이름
		std::cin >> s;

		visiteCityIdx[i] = um[s];	// 방문해야 하는 도시 인덱스 저장
	}

	std::cin >> K;

	cost.assign(N, std::vector<double>(N, INF));
	railCost.assign(N, std::vector<double>(N, INF));

	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j) {
			if(i==j) {	// 출발 도시와 도착 도시가 같은 경우
				cost[i][j] = 0;
				railCost[i][j] = 0;
			}
		}
	}

	for(int i=0; i<K; ++i){
		std::string Type, S, E;	// Type: 교통수단의 종류 -> 'Subway’, ‘Bus’, ‘Taxi’, ‘Airplane’, ‘KTX’, ‘S-Train’, ‘V-Train’, ‘ITX-Saemaeul’, ‘ITX-Cheongchun’, ‘Mugunghwa’, S, E: 양 끝 도시
		double Cost;	// Cost: 1인당 비용

		std::cin >> Type >> S >> E >> Cost;

		int startIdx = um[S], endIdx = um[E];	// startIdx, endIdx: 양 끝 도시의 인덱스

		cost[startIdx][endIdx] = std::min(cost[startIdx][endIdx], Cost);
		cost[endIdx][startIdx] = std::min(cost[endIdx][startIdx], Cost);

		if(Type == "Mugunghwa" || Type == "ITX-Saemaeul" || Type == "ITX-Cheongchun") {	// 무궁화호, ITX-새마을, ITX-청춘은 무료로 이용
			railCost[startIdx][endIdx] = 0;
			railCost[endIdx][startIdx] = 0;	// 양방향
		}
		else if(Type == "S-Train" || Type == "V-Train") {	// S-Train, V-Train은 50% 할인된 가격으로 이용
			railCost[startIdx][endIdx] = std::min(railCost[startIdx][endIdx], Cost / 2);
			railCost[endIdx][startIdx] = std::min(railCost[endIdx][startIdx], Cost / 2);	// 양방향
		}
		else {	// KTX, 지하철, 다른 교통수단에 대해서는 할인이 적용되지 않음
			railCost[startIdx][endIdx] = std::min(railCost[startIdx][endIdx], Cost);
			railCost[endIdx][startIdx] = std::min(railCost[endIdx][startIdx], Cost);	// 양방향
		}		
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	(costSum > railCostSum)? (std::cout << "Yes") : (std::cout << "No");

	return 0;
}