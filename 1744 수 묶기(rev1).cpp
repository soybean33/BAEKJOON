#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int Solution(const int& N, const std::vector<int>& v) {

	int answer = 0;	// answer: 수열의 각 수를 적절히 묶었을 때의 합

	std::priority_queue<int, std::vector<int>, std::less<int>> positive;	// positive: 양수 내림차순 정렬 pq
	std::priority_queue<int, std::vector<int>, std::greater<int>> negative;	// negative: 음수 오름차순 정렬 pq
	int zeroCnt = 0;	// zeroCnt: 0의 개수 -> 홀수로 남은 음수를 지울 때 사용
	int oneCnt = 0;	// oneCnt: 1의 개수 -> 1은 묶지 않고 더하는 것이 좋음

	for(const int& n : v) {
		if(n == 0) {	// n이 0인 경우
			++zeroCnt;
			continue;
		}
		if(n == 1) {	// n이 1인 경우
			++oneCnt;
			continue;
		}
		if(n > 0) {positive.push(n);}	// n이 양수인 경우
		else if(n < 0) {negative.push(n);}	// n이 음수인 경우
	}

	while(positive.size() > 1) {	// 양수의 개수가 1개 보다 많이 남았을 경우
		int a = positive.top();	// a: 양수
		positive.pop();

		int b = positive.top();	// b: 양수
		positive.pop();

		answer += a * b;	// 두 수 a, b 를 묶음
	}

	while(negative.size() > 1) {	// 음수의 개수가 1개 보다 많이 남았을 경우
		int a = negative.top();	// a: 음수
		negative.pop();

		int b = negative.top();	// b: 음수
		negative.pop();

		answer += a * b;	// 두 수 a, b 를 묶음
	}

	if(!positive.empty()) {answer += positive.top();}	// 1개 남은 양수가 있을 경우 더 함
	if(!negative.empty()) {answer += zeroCnt ? 0 : negative.top();}	// 1개 남은 음수가 있을 경우 0이 있다면 0과 묶고, 없다면 더함

	answer += oneCnt;	// 1의 개수를 더함

	return answer;
}

void Input(int& N, std::vector<int>& v) {

	std::cin >> N;

	v.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> v[i];}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;	// N: 수열의 크기 1<=N<50
	std::vector<int> v;	// v[i]: 수열의 i 번째 수 -1'000<=v[i]<=1'000

	Input(N, v);

	std::cout << Solution(N, v);

	return 0;
}