#include <iostream>
#include <vector>
#include <algorithm>

struct Line{	// 연결되어 있는 전깃줄
	int A, B;	// A, B: 연결되어 있는 전봇대 번호
};

int N;	// N: 전깃줄의 개수

std::vector<Line> v;	// v[i]: i 번째 전깃줄 연결 정보

int answer;	// answer: 모든 전깃줄이 서로 교차하지 않게 하기 위해 없애야 하는 전깃줄의 최소 개수

bool Cmp(const Line& left, const Line& right){	// A 전봇대 번호를 기준으로 오름차순 정렬
	if(left.A != right.A) {return left.A < right.A;}

	return false;
}

void Solution(){

	std::sort(v.begin(), v.end(), Cmp);	// A 전봇대 번호를 기준으로 오름차순 정렬
	
	std::vector<int> dp;	// dp[i]: A 전봇대 번호가 i 일 때 가장 긴 증가하는 부분 수열
	dp.assign(N, 1);

	for(int i=0; i<N; ++i){
		for(int j=0; j<i; ++j){
			if(v[i].B > v[j].B) {dp[i] = std::max(dp[i], dp[j] + 1);}	// 증가하는 경우 +1
		}
		answer = std::max(answer, dp[i]);	// 가장 긴 증가하는 부분수열 갱신
	}

	answer = N - answer;	// 전체의 개수에서 가장 긴 증가하는 부분수열의 길이를 빼주면 없애야 하는 전깃줄의 최소 개수를 구할 수 있음

	return;
}

void Input(){

	std::cin >> N;
	v.assign(N, {0, 0});

	for(int i=0; i<N; ++i){
		std::cin >> v[i].A >> v[i].B;
	}

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