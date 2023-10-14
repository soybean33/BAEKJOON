#include <iostream>
#include <vector>

constexpr int INF = 21e8;	// INF: 나올 수 없는 값

int N, H;	// N: 동굴의 길이 2<=N<=200'000, H: 동굴의 높이 2<=H<=500'000
std::vector<std::pair<int, int>> pillar;	// pillar[i]: i 번때 장애물 누적합 -> (종유석, 석순)

int answer = INF;	// answer: 파괴해야 하는 장애물의 최솟값
int cnt;	// cnt: 구간의 수

void Solution(){

	// 누적합 계산
	for(int i=1; i<=H; ++i){
		pillar[i].first += pillar[i-1].first;	// 종유석은 아래에서 부터
		pillar[H - i].second += pillar[H - i + 1].second;	// 석순은 위에서 부터
	}

	// 모든 동굴의 높이를 탐색하며 파괴해야하는 장애물의 수 계산
	for(int i=1; i<=H; ++i){
		if(pillar[i].first + pillar[i].second < answer) {	// 더욱 적게 파괴해도 되는 경우 발견
			cnt = 1;	// 첫 번째
			answer = pillar[i].first + pillar[i].second;
		}
		else if(pillar[i].first + pillar[i].second == answer) {++cnt;}	// 같은 개수 발견
	}

	return;
}

void Input(){

	std::cin >> N >> H;

	pillar.assign(H + 1, std::pair<int, int>(0, 0));

	for(int i=0; i<N; ++i){
		int height;	// height: 장애물의 크기
		std::cin >> height;
		if(i%2 != 0) ++pillar[H - height + 1].first;	// 종유석 -> 위에서 부터 시작되므로 높이에서 값을 뺌
		else ++pillar[height].second;	// 석순
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer << ' ' << cnt;

	return 0;
}