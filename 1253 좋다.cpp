#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 수의 개수 1<= N <= 2,000
std::vector<int> v;	// v[i]: i 번째 수
int ans;	// ans: 좋은 수의 개수

bool bs(int leftIdx, int rightIdx, int sumIdx){	// leftIdx: 왼쪽 수 인덱스, rightIdx: 오른쪽 수 인덱스, sumIdx: 합 인덱스

	while(leftIdx < rightIdx){	// 투포인터
		int tmpSum = v[leftIdx] + v[rightIdx];	// tmpSum: 두 수의 합

		if(tmpSum == v[sumIdx]){	// 좋은 수열의 조건 중 값을 만족함
			// 같은 인덱스가 있는지 확인
			if(leftIdx == sumIdx) leftIdx++;
			else if(rightIdx == sumIdx) rightIdx--;
			else if(leftIdx == rightIdx) rightIdx--;
			else return true;
		}
		else if(tmpSum < v[sumIdx]) ++leftIdx;	// 값이 너무 작음
		else --rightIdx;	// 값이 너무 큼
	}

	return false;
}

void solution(){

	std::sort(v.begin(), v.end());	// 오름차순 정렬

	for(int i=0; i<N; ++i){
		int sumIdx = i;	// sumIdx: 합이 될 수의 인덱스
		int leftIdx = 0, rightIdx = N-1;	// leftIdx: 왼쪽 수 인덱스, rightIdx: 오른쪽 수 인덱스

		if(bs(leftIdx, rightIdx, sumIdx)) ++ans;
	}

	return;
}

void input(){	// 입력

	std::cin >> N;

	v.assign(N, 0);

	for(int i=0; i<N; ++i) std::cin >> v[i];

	return;
} 

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	std::cout << ans;

	return 0;
}