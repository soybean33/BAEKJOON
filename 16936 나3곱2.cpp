#include <iostream>
#include <vector>
#include <algorithm>

struct D3M2{
	long long n;	// n: 원소
	int D3, M2;	// D3: 3의 소인수 개수, M2: 2의 소인수 개수
};

int N;	// N: 수열의 크기
std::vector<D3M2> A;	// A[i]: 정렬된 i 번째 수와 소인수 정보 -> 3의 소인수 개수 내림차순, 2의 소인수 개수 오름차순 정렬

bool cmp(D3M2 left, D3M2 right){	// 정렬
	if(left.D3 != right.D3) return left.D3 > right.D3;	// 3의 소인수 개수 내림차순
	if(left.M2 != right.M2) return left.M2 < right.M2;	// 2의 소인수 개수 오름차순

	return false;
}

void sol(){

	for(int i=0; i<N; i++){
		long long num = A[i].n;	// num: 소인수의 개수를 구할 수

		while(num % 3 == 0){	// 3의 개수
			A[i].D3 ++;
			num = num / 3;
		}
		while(num % 2 == 0){	// 2의 개수
			A[i].M2 ++;
			num = num / 2;
		}
	}

	std::sort(A.begin(), A.end(), cmp);	// 정렬

	for(int i=0; i<N; i++) std::cout << A[i].n << ' ';

	return;
}

void input(){

	std::cin >> N;

	A.resize(N);

	for(int i=0; i<N; i++) {
		long long n;	// n: 원소
		std::cin >> n;
		A[i] = {n, 0, 0};
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	return 0;
}