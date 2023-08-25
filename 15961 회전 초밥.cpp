#include <iostream>
#include <vector>

int Solution(const int& N, const int& d, const int& k, const int& c, const std::vector<int>& sushiNum) {

	int maxDiff = 0;	// maxDiff: 먹을 수 있는 초밥의 가짓수의 최댓값

	std::vector<int> sushiDAT;	// sushiDAT[i]: i 번호 초밥의 갯수

	sushiDAT.assign(d + 1, 0);

	// 쿠폰 사용
	int sushiDiff = 1;	// sushiDiff: 현재 시작 위치에서 먹을 수 있는 초밥의 가짓수
	sushiDAT[c] = 1;

	for (int i = 0; i < k - 1; ++i) {
		int currSushiNum = sushiNum[i];	// currSushiNum: 현재 위치 초밥 번호
		sushiDiff += sushiDAT[currSushiNum] == 0 ? 1 : 0;	// 현재 초밥을 고른적이 없다면 +1, 고른적 있다면 +0
		sushiDAT[currSushiNum] += 1;	// 초밥 갯수 증가
	}

	int leftIdx = 0, rightIdx = k - 1;	// leftIdx: 시작 위치 인덱스, rightIdx: 끝 위치 인덱스

	while (true) {
		int currSushiNum = sushiNum[rightIdx];	// currSushiNum: 현재 위치 초밥 번호
		sushiDiff += sushiDAT[currSushiNum] == 0 ? 1 : 0;	// 현재 초밥을 고른적이 없다면 +1, 고른적 있다면 +0
		sushiDAT[currSushiNum] += 1;	// 초밥 갯수 증가

		maxDiff = std::max(maxDiff, sushiDiff);	// 먹을 수 있는 초밥의 가짓수의 최댓값 갱신
		if (maxDiff == k + 1) { return k + 1; }	// 최대 k + 1개의 다른 초밥을 먹을 수 있으므로 최댓값이라면 return

		currSushiNum = sushiNum[leftIdx];	// currSushiNum: 현재 위치 초밥 번호
		sushiDiff -= sushiDAT[currSushiNum] == 1 ? 1 : 0;	// 현재 초밥을 먹지 못하는 경우 먹을 수 없다면 -1, 먹을 수 있다면 -0
		sushiDAT[currSushiNum] -= 1;	// 초밥 갯수 감소

		// 원형으로 인덱스 증가
		leftIdx = (leftIdx + 1) % N;
		rightIdx = (rightIdx + 1) % N;
				
		if (leftIdx == 0) { break; }	// 다시 시작 지점으로 돌아왔다면 break
	}	

	return maxDiff;
}

void Input(int& N, int& d, int& k, int& c, std::vector<int>& sushiNum) {

	std::cin >> N >> d >> k >> c;

	sushiNum.assign(N, 0);

	for (int i = 0; i < N; ++i) { std::cin >> sushiNum[i]; }

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, d, k, c;	// N: 회전 초밥 벨트에 놓인 접시의 수, d: 초밥의 가짓수, k: 연속해서 먹는 접시의 수, c: 쿠폰 번호
	std::vector<int> sushiNum;	// sushiNum[i]: 회전 초밥의 i번째 초밥 번호

	Input(N, d, k, c, sushiNum);

	std::cout << Solution(N, d, k, c, sushiNum);

	return 0;
}