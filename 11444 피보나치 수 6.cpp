#include <iostream>
#include <unordered_map>

constexpr int MODULAR = 1'000'000'007;	// MODULAR: 모듈러 값

long long N;	// N: 피보나치 수를 구할 순서
std::unordered_map<long long, long long> um;	// um[i]: N 번째 피보나치 수 저장

long long Fibonacci(long long n) {
	if(um[n]) {return um[n];}	// 이미 n 번째 피보나치 수를 구했다면 그 수를 return

	long long result;	// result: 피보나치수
	
	if(n % 2 == 0) {	// 짝수인 경우
		result = Fibonacci(n/2) * (Fibonacci(n/2 + 1) + Fibonacci(n/2 - 1)) % MODULAR;
	}
	else{	// 홀수인 경우
		result = ((Fibonacci((n+1)/2) * Fibonacci((n+1)/2))%MODULAR) + ((Fibonacci((n-1)/2)*Fibonacci((n-1)/2)) % MODULAR);
	}

	return um[n] = result % MODULAR;
}

void Solution(){

	um[0] = 0;
	um[1] = 1;
	um[2] = 1;

	std::cout << Fibonacci(N);

	return;
}

void Input(){

	std::cin >> N;

	return;
}

int main(){

	Input();

	Solution();

	return 0;
}