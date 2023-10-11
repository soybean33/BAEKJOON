#include <iostream>
#include <string>
#include <vector>

std::string S;	// S: 괄호열

int answer = 0;	// answer: 괄호열의 값을 나타내는 정수

void Solution(){

	int tmp = 1;	// tmp: 임시 값

	std::vector<char> v;	// v[i]: 저장되어 있는 i 번째 괄효
	for(int i=0; i<S.length(); ++i) {
		if(S[i] == '(') {	// '(' 괄호의 사작
			tmp *= 2;	// 임시 값에 2를 곱함
			v.push_back('(');	// 벡터에 저장
		}
		else if(S[i] == '[') {	// '[' 괄호의 시작
			tmp *= 3;	// 임시 값에 3을 곱함
			v.push_back('[');	// 벡터에 저장
		}
		else if(S[i] == ')') {	// ')' 괄호의 끝
			if(v.empty() || v.back() != '(') {	// 올바르지 않은 경우
				answer = 0;
				return;
			}

			if(S[i-1] == '(') {	// () 괄효열의 값은 2
				answer += tmp;
				tmp /= 2;
				v.pop_back();
			}
			else {	// (X)의 괄호열의 값은 2 * X
				tmp /= 2;
				v.pop_back();
			}
		}
		else if(S[i] == ']') {	// ']' 괄호의 끝
			if(v.empty() || v.back() != '[') {	// 올바르지 않은 경우
				answer = 0;
				return;
			}
			if(S[i-1] == '[') {	// [] 괄호열의 값은 3
				answer += tmp;
				tmp /= 3;
				v.pop_back();
			}
			else {	// [X]의 괄호열의 값은 3 * X
				tmp /= 3;
				v.pop_back();
			}
		}
	}

	if(!v.empty()) {answer = 0;}	// 올바르지 않은 경우

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