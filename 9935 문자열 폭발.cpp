#include <iostream>
#include <string>

std::string s;	// s: 문자열
std::string boom;	// boom: 폭발 문자열
std::string tmp;	// tmp: 폭발 검사를 위한 임시 문자열

void solution() {

	int sLen = s.length();	// sLen: 문자열의 길이
	int bLen = boom.length();	// bLen: 폭발 문자열의 길이

	for(int i=0; i<sLen; ++i) {	// 모든 문자열에 대하여 반복
		tmp += s[i];	// 폭발 검사를 위한 문자열에 추가

		if(tmp.length() < bLen) continue;	// 폭발 검사를 위한 문자열이 폭발 문자열 보다 작은 경우는 폭발이 발생할 수 없으므로 continue

		bool flag = true;	// flag: 폭발 여부 -> false면 폭발 안함

		for(int j=0; j<bLen; ++j){	// 폭발 문자열의 길이만큼 뒤에서 부터 검사
			if(tmp[tmp.length() - bLen + j] != boom[j]) {	// 폭발 문자열과 다르다면
				flag = !flag;	// 폭발하지 않음
				break;
			}
		}

		if(flag) {	// 폭발
			tmp.erase(tmp.end() - bLen, tmp.end());	// 뒤에서 부터 폭발 문자열 만큼 폭발
		}
	}

	return;
}

void input() {

	std::cin >> s;
	std::cin >> boom;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	if(!tmp.length()) std::cout << "FRULA";	// 남아있는 문자가 없는 경우
	else std::cout << tmp;

	return 0;
}