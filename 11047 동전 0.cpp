#include <iostream>
#include <vector>
#include <algorithm>

bool Cmp(const int& left, const int& right) {
	if(left != right) {return left > right;}
	return false;
}

int Solution(const int& N, const int& K, std::vector<int>& coinType) {

	int answer = 0;	//	answer: K원을 만드는데 필요한 동전 개수의 최솟값

	std::sort(coinType.begin(), coinType.end(), Cmp);	// 동전의 가치 내림차순 중렬

	int remain = K;	// remain: 남아있는 가치
	for(const int& coin : coinType) {
		if(remain - coin >= 0) {	// 동전이 1개라도 포함된다면
			answer += remain / coin;	// 모두 현재 동전으로 변환
			remain %= coin;	// 남아있는 금액 갱신
		}
	}

	return answer;
}

void Input(int& N, int& K, std::vector<int>& coinType) {

	std::cin >> N >> K;

	coinType.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> coinType[i];}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;	// N: 동전의 종류 1<=N<=10, K: 가치의 합 1<=K<=100'000'000
	std::vector<int> coinType;	// coinType[i]: i 번째로 입력된 동전의 가치 1<=coinType[i]<=1'000'000

	Input(N, K, coinType);

	std::cout << Solution(N, K, coinType);

	return 0;
}