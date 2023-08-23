#include <iostream>
#include <algorithm>

constexpr int INF = 21e8;	// INF: 나올 수 없는 값

int Solution(int& N, int& M, std::vector<int>& A) {

	int ans = INF;	// ans: 큰 값으로 초기화

	std::sort(A.begin(), A.end());	// 오름차순 정렬

	int leftIdx = 0;	// leftIdx: 왼쪽 인덱스
	int rightIdx = 0;	// rightIdx: 오른쪽 인덱스

	while(leftIdx < N && rightIdx < N) {	// 두 인덱스 중 하나라도 더 이상 탐색할 수 없을 때 까지 반복
		int diff = A[rightIdx] - A[leftIdx];	// diff: 두 수의 차이

		if(diff < M) {++rightIdx;}	// 최소 차이보다 작은 경우 rightIdx 증가
		else {	// 최소 차이 조건을 만족
			ans = std::min(ans, diff);	// 차이가 M 이상이면서 가장 작은 차이로 갱신
			if(ans == 0) return ans;	// 차이가 0이라면 즉시 종료
			++leftIdx;	// 왼쪽 인덱스 증가
		}
	}

	return ans;
}

// 값 입력
void Input(int& N, int& M, std::vector<int>& A) {

	std::cin >> N >> M;

	A.assign(N, 0);

	for(int i=0; i<N; ++i) std::cin >> A[i];

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;	// N: 수열의 길이, M: 최소 차이 조건
	std::vector<int> A;	// A[i]: i 번째 수열의 값

	Input(N, M, A);	// 값 입력

	std::cout << Solution(N, M, A);

	return 0;
}