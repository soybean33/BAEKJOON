#include <iostream>
#include <vector>

int N;	// N: 자연수

int answer = 0;	// answer: 연속된 소수의 합으로 나타낼 수 있는 경우의 수

void Solution(){

	std::vector<bool> primeChk;	// primeChk[i]: i 번째 수가 소수이면 true
	primeChk.assign(N + 1, true);	// 우선 모든 수가 소수라고 가정

	primeChk[0] = false;	// 0은 소수가 될 수 없음
	primeChk[1] = false;	// 1은 소수가 될 수 없음

	for(int i=2; i*i<=N; ++i) {	// 2부터 root N 까지 탐색
		for(int j = i+i; j<=N; j+=i) {
			  primeChk[j] = false;	// 에라토스테네스의 체를 이용
		}
	}

	std::vector<int> prime;	// prime[i]: N보다 작은 소수 모음

	for(int i=0; i<=N; ++i){
		if(primeChk[i] == true) {	// 에라토스테네스의 체에서 소수라면
			prime.push_back(i);	// 소수 모음에 넣음
		}
	}

	int left = 0, right = 0;	// left, right: 투 포인터
	int primeSize = prime.size();	// primeSize: N 보다 작은 소수의 개수
	int sum = 0;	// sum: 연속된 소수의 합
	while(true) {
		if(sum < N) {	// 더 큰 수를 더해야 함
			if(right >= primeSize) {break;}	
			sum += prime[right];
			++right;			
		}
		else if(sum > N){	// 너무 많은 수를 더함
			sum -= prime[left];
			++left;			
		}
		else{	// 소수의 합으로 표현함
			++answer;	// 경우의 수 증가
			if(right >= primeSize) {break;}	
			sum += prime[right];
			++right;
		}
	}

	return;
}

void Input(){

	std::cin >> N;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}