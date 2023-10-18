#include <iostream>
#include <vector>

int N, K;	// N: 정수의 범위, K: 정수의 개수

int answer;	// answer: 답을 1'000'000'000 으로 나눈 나머지

void Solution(){

	std::vector<std::vector<int>> arr;	// arr[i][j]: 정수 i 를 j 개의 정수로 나타낼 수 있는 개수

	arr.assign(N+1, std::vector<int>(K+1, 0));

	for(int i=1; i<=K; ++i) {arr[1][i] = i;}	// 1을 i 개 사용하여 수를 만들 수 있음

	for(int i=2; i<=N; ++i) {
		for(int j=1; j<=K; ++j) {
			arr[i][j] = (arr[i-1][j] + arr[i][j-1]) % 1'000'000'000;
		}
	}

	answer = arr[N][K];

}

void Input(){

	std::cin >> N >> K;

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}