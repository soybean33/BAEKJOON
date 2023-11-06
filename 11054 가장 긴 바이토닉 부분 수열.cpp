#include <iostream>
#include <vector>

int N;	// N: 수열의 크기 1<=N<=1'000
std::vector<int> A;	// A[i]: 수열의 값 1<=A[i]<=1'000

int answer;	// answer: 수열 A의 부분 수열 중에서 가장 긴 바이토닉 수열의 길이

void Solution(){

	std::vector<int> dp, rdp;	// dp[i]: 증가하는 가장 긴 수열의 길이, rdp[i]: 감소하는 가장 긴 수열의 길이
	dp.assign(N, 0);
	rdp.assign(N, 0);

	for(int i=0; i<N; ++i){
		dp[i] = 1;	// 자기 지신은 1
		for(int j=0; j<i; ++j){
			if(A[j] < A[i] && dp[i] < dp[j] + 1) {	// 직전 값 보다 값이 증가하거나, 더 긴 수열의 길이를 갖고 있다면
				dp[i] = dp[j] + 1;	// 수열의 값 저장
			}
		}
	}

	// 위의 과정을 역 과정으로 진행
	for(int i=N-1; i>=0; --i){
		rdp[i] = 1;
		for(int j=N-1; j>=i; --j){
			if(A[i] > A[j] && rdp[j] + 1 > rdp[i]) {
				rdp[i] = rdp[j] + 1;
			}
		}
	}

	for(int i=0; i<N; ++i){
		if(answer < dp[i] + rdp[i] - 1) {
			answer = dp[i] + rdp[i] - 1;
		}
	}

	return;
}

void Input(){

	std::cin >> N;

	A.assign(N, 0);
	
	for(int i=0; i<N; ++i) {std::cin >> A[i];}

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}