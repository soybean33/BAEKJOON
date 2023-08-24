#include <iostream>
#include <string>
#include <algorithm>

// 문제 해결
bool Solution(std::string& S, std::string& T) {

	while(S.length() <= T.length()) {	// S의 길이가 T의 길이보다 작을 때

		if(S == T) {return true;}	// 두 문자열이 같다면 return true

		if(T[T.length() - 1] == 'A') {	// 문자열 뒤에 A를 추가했던 경우
			T.pop_back();	// A를 뺌
		}
		else {	// 문자열을 뒤집고 뒤에 B를 추가했던 경우
			T.pop_back();	// B를 빼고
			std::reverse(T.begin(), T.end());	// 뒤집음
		}
	}

	return false;
}

// 입력
void Input(std::string& S, std::string& T) {

	std::cin >> S;
	std::cin >> T;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string S, T;	// S: 변경할 문자열, T: 변경될 문자열

	Input(S, T);

	if(Solution(S, T)) {std::cout << "1";}	// S를 T로 바꿀 수 있으면 1
	else {std::cout << "0";}	// S를 T로 바꿀 수 없으면 0

	return 0;
}