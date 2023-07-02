#include <iostream>
#include <string>
#include <vector>

std::string S;	// S[i]: 압축되지 않은 문자열의 i 번째 문자
std::vector<std::pair<char, int>> v;	// v[i]: i 번째 문자의 문자와 반복 횟수
int ans;	// ans: 압축되지 않은 문자열의 길이

void solution(){

	int strSize = 0;	// strSize: 반복되는 문자열 길이

	for(int i=0; i<S.length(); ++i){	// 문자열을 앞에서 부터 탐색
		if(S[i] == ')'){	// 닫는 괄호
			while(true){
				if(v.back().first == '('){	// 앞 문자열 중 여는 괄호를 발견
					v.pop_back();
					int rptCnt = v.back().first - '0';	// rptCnt: 문자열 반복 횟수
					v.back().second = rptCnt * strSize;	// 반복
					strSize = 0;	// 반복 횟수 초기화
					break;
				}
				strSize += v.back().second;	// 반복되는 문자열 길이 증가
				v.pop_back();
			}
		}
		else v.push_back({S[i], 1});	// 여는 괄호
	}

	while(!v.empty()){
		ans += v.back().second;
		v.pop_back();
	}

	return;
}

void input(){

	std::cin >> S;

	return;
}

int main(){

	input();

	solution();

	std::cout << ans;

	return 0;
}