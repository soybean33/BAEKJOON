#include <iostream>
#include <string>
#include <unordered_map>

int sLen;	// sLen: 암호에 사용할 수 있는 문자의 개수
std::unordered_map<char, int> um;	// um[i]: 암호로 사용할 수 있는 문자의 위치
std::string cyperText;	// cyperText: 암호

int answer;	// answer: 주어진 암호를 풀기위한 시도 횟수

void Solution(){

	int cyperTextLen = cyperText.length();	// cyperTextLen: 암호의 길이

	int rotate = 1;	// rotate: 반복해야 하는 횟수

	for(int i=cyperTextLen - 1; i>=0; --i){	// 뒤의 암호문 부터 탐색
		answer = (answer + rotate * um[cyperText[i]]) % 900528;	// 문자 탐색
		rotate = rotate * sLen % 900528;	// 반복 횟수는 암호로 사용할 수 있는 문자의 개수 배로 증가
	}

	return;
}

void Input(){

	std::string S;	// S: 암호로 사용할 수 있는 문자
	std::cin >> S;

	sLen = S.length();	// 암호로 사용할 수 있는 문자의 개수
	for(int i=0; i<sLen; ++i){
		um[S[i]] = i + 1;	// 1번 인덱스를 시작하여 저장
	}

	std::cin >> cyperText;

	return;
}


int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}