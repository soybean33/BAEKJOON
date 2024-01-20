#include <iostream>
#include <vector>
#include <algorithm>

int T;	// A의 부 배열의 합과 B의 부 배열의 합을 더해서 T
int N;	// N: A 배열의 원소의 개수
std::vector<int> A;	// A[i]: A 배열
int M;	// M: B 배열의 원소의 개수
std::vector<int> B;	// B[i]: B 배열

long long answer;	// answer: 가능한 경우의 가지 수

void Solution(){

	std::vector<int> sumA, sumB;	// sumA: A 배열의 부 배열에서 나올 수 있는 값, sumB: B 배열의 부 배열에서 나올 수 있는 값

	for(int i=0; i<N; ++i) {
		int sum = A[i];	// sum: A 배열의 부 배열 값
		sumA.push_back(sum);
		for(int j=i+1; j<N; ++j) {
			sum += A[j];
			sumA.push_back(sum);
		}
	}

	for(int i=0; i<M; ++i) {
		int sum = B[i];	// sum: B 배열의 부 배열의 값
		sumB.push_back(sum);
		for(int j=i+1; j<M; ++j) {
			sum += B[j];
			sumB.push_back(sum);
		}
	}

	std::sort(sumB.begin(), sumB.end());	// B 배열에서 나올 수 있는 부 배열의 값 오름차순 정렬

	for(const int a : sumA) {
		int differ = T - a;	// differ: T와의 차이
		std::vector<int>::iterator upperB = std::upper_bound(sumB.begin(), sumB.end(), differ);
		std::vector<int>::iterator lowerB = std::lower_bound(sumB.begin(), sumB.end(), differ);
		answer += (upperB - lowerB);
	}

	return;
}

void Input(){

	std::cin >> T;

	std::cin >> N;
	A.assign(N, 0);
	for(int i=0; i<N; ++i) {std::cin >> A[i];}

	std::cin >> M;
	B.assign(M, 0);
	for(int i=0; i<M; ++i) {std::cin >> B[i];}

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