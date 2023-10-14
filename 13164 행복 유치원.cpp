#include <iostream>
#include <vector>
#include <algorithm>

int N, K;	// N: 유치원에 있는 원생의 수 1<=N<=300'000, K: 나누려고 하는 조의 개수 1<=K<=N
std::vector<int> H;	// H[i]: i 번째 원생의 키

long long answer;	// answer: 티셔츠 만드는 비용이 최소가 되도록 K개의 조로 나누었을 때, 티셔츠 만드는 비용

void Solution(){

	std::vector<int> differ;	// differ[i]: i-1번째 원생과 i 원생과의 키 차이(티셔츠를 맞추는 비용)
	differ.assign(N-1, 0);

	for(int i=1; i<N; ++i) {differ[i-1] = H[i] - H[i-1];}

	std::sort(differ.begin(), differ.end());	// 오름차순 정렬

	for(int i=0; i<N-K; ++i) {answer += differ[i];}

	return;
}

void Input(){

	std::cin >> N >> K;
	H.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> H[i];}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}