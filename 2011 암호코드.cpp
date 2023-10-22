#include <iostream>
#include <string>
#include <vector>

constexpr int Moduler = 1'000'000;	// Moduler: 해석의 가짓수를 나눌 값

std::string S;	// S: 암호문

int answer;	// answer: 해석의 가짓수

void Solution(){

	int len = S.length();	// len: 암호문의 길이

	if(len == 1 && S[0] == '0') {	// 암호를 해석할 수 없는 경우
		return;
	}

	std::vector<int> v;	// v[i]: i 번째 암호문을 int 형으로 변경
	v.assign(len + 1, 0);

	for(int i=1; i<=len; ++i){v[i] = S[i-1] - '0';}

	std::vector<int> dp;	// dp[i]: i 번째 암호문까지의 해석의 가짓수
	dp.assign(len + 1, 0);
	dp[0] = 1;

	for(int i=1; i<=len; ++i){
		if(v[i] >= 1 && v[i] <= 9) {dp[i] = (dp[i-1] + dp[i]) % Moduler;}	// 한 자릿수 암호문이 될 수 있으면 -> 1 ~ 9 사이의 값

		if(i==1) {continue;}

		int tmp = v[i] + v[i-1] * 10;	// tmp: 두 자릿수 암호문이라고 가정
		if(tmp >= 10 && tmp <= 26) {dp[i] = (dp[i-2] + dp[i]) % Moduler;}	// 두 자릿수 암호문이 될 수 있다면 -> 10 ~ 26 사이의 값
	}

	answer = dp[len];	// answer: 마지막 암호문 까지 봤을 때 해석할 수 있는 가짓 수

	return;
}

void Input(){

	std::cin >> S;

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}