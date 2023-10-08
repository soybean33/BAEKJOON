#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 하나가 가진 헤어에센스 용기의 수 1<=N<=1e5
long long X;	// X: 헤어에센스 용기의 총 용량 1<=X<=1e18
std::vector<long long> C;	// C[i]: i 번째 용기에 담겨 있는 헤어에센스 용량 0<=C[i]<=1e18

int answer = 0;	// answer: 헤어에센스를 교환해서 만들수 있는 용량이 꽉 찬 헤어에센스 용기의 수

void Solution(){

	std::sort(C.begin(), C.end());	// 오름차순 정렬

	int left = 0, right = C.size() - 1;	// left, right: 투포인터
	int pass = 0;	// pass: 두 용기로 꽉찬 용기를 만들 수 없는 경우의 수

	while(left <= right){

		if(C[left] + C[right] >= (X + 1) / 2 && left != right) {	// 두 용기로 꽉찬 용기를 만들 수 있는 경우 -> 중복에 주의
			++answer;	// 꽉찬 용기 만듦
			++left;
			--right;
		}
		else{	// 두 개로 꽉찬 용기를 만들 수 없는 경우
			++pass;
			++left;
		}
	}

	answer += pass / 3;

	return;
}

void Input(){

	std::cin >> N >> X;

	for(int i=0; i<N; ++i){
		long long c;	// c: 헤어에센스의 용량
		std::cin >> c;
		if(c == X) {	// 이미 꽉찬 경우
			++answer;
		}
		else{	// 덜 찬 경우
			C.push_back(c);
		}
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