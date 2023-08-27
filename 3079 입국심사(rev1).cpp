#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 21e8;	// INF: 나올 수 없는 최대 값

long long Solution(const int& n, const int& m, const std::vector<int>& t, const int& minT) {

	long long answer = 0;	// answer: 심사를 마치는데 걸리는 시간의 최솟값

	long long leftTime = 1, rightTime = static_cast<long long>(minT) * static_cast<long long>(m);	// leftTime: 최소 심사시간, rightTime: 최대 심사 시간

	while(leftTime <= rightTime) {
		long long middleTime = (leftTime + rightTime) / 2;	// middleTime: 심사를 하는데 걸리는 예상 시간

		long long tmpPeopleNum = 0;	// tmpPeopleNum: middleTime 안에 심사 받을 수 있는 사람의 수
		for(const int& time : t) {tmpPeopleNum += middleTime / time;}	// 심사대의 인원 더하기

		if(tmpPeopleNum >= m) {	// 더 많은 인원을 심사할 수 있다면
			rightTime = middleTime - 1;	// 예상 시간 감소
			answer = middleTime;	// 갱신
		}
		else {leftTime = middleTime + 1;}	// 예상 시간을 조금 더 잡음
	}

	return answer;
}

void Input(int& n, int& m, std::vector<int>& t, int& minT) {

	std::cin >> n >> m;

	t.assign(n, 0);

	for(int i=0; i<n; ++i) {
		std::cin >> t[i];
		minT = std::min(minT, t[i]);	// 최소 입국대 심사시간 갱신
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;	// n: 입국심사대의 개수, m: 상근이와 친구들의 수
	std::vector<int> t;	// t[i]: i 번 심사대에 앉아있는 심사관이 한 명을 심사 하는데 드는 시간
	int minT = INF;	// minT: 가장 적은 시간이 소요되는 심사 시간

	Input(n, m, t, minT);

	std::cout << Solution(n, m, t, minT);

	return 0;
}