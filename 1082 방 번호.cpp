#include <iostream>
#include <vector>
#include <string>

constexpr int INF = 1e9;	// INF: 나올 수 없는 값

int N;	// N: 문방구에서 파는 숫자
std::vector<int> P;	// P[i]: 각 숫자 i의 가격
int M;	// M: 숫자를 구매하기 위해 준비한 금액

std::string answer;	// answer: M원을 사용해서 만들 수 있는 가장 큰 방 번호

void Solution(){

	int first = INF, second = INF;
	int firstIdx, secondIdx;

	for(int i=0; i<N; ++i) {
		if(P[i] < first) {	// 첫 번째로 가장 싼 방 번호
			first = P[i];
			firstIdx = i;
		}
	}

	for(int i=1; i<N; ++i) {
		if(P[i] < second) {	// 0을 제외한 가장 싼 방 번호
			second = P[i];
			secondIdx = i;
		}
	}

	if(M < second) {	// 0을 제외하고 살 수 있는 번호가 없는 경우
		answer = "0";	// 방 번호 0
		return;
	}

	// 첫 번째 가장 싼 방 번호
	M -= second;
	answer.push_back('0' + secondIdx);
	while(M >= first) {	// 가장 싼 번호로 최대한 숫자 키우기
		answer.push_back('0' + firstIdx);
		M -= first;
	}

	int idx;	// idx: 변경할 숫자의 인덱스

	for(int i=0; i<answer.length(); ++i){
		for(int j=N-1; j>=0; --j){
			idx = answer[i] - '0';	// 숫자로 변경

			if(M >= P[j] - P[idx]) {	// 가능한 가장 큰 수로 변경
				M -= (P[j] - P[idx]);
				answer[i] = '0' + j;
				break;
			}
		}
	}

	return;
}

void Input(){

	std::cin >> N;

	P.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> P[i];}

	std::cin >> M;

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}