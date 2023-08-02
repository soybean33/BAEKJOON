#include <iostream>
#include <string>
#include <stack>

std::string infix;	// infix: 중위 표현식

void solution() {

	std::stack<char> s;	// s: 스텍

	for(const char& curr : infix) {	// curr: 중위 표현식의 문자
		if(curr >= 'A' && curr <= 'Z') {	// 연산자가 아닌 경우
			std::cout << curr;	// 바로 출력
		}
		else {	// 괄호를 포함한 연산자의 경우
			if(curr == '(') {	// 왼쪽 괄호를 만나면 스택에 넣음
				s.push(curr);
			}
			else if(curr == '*' || curr == '/') {	// 우선 순위 연산자 (* , /) 인 경우
				while(!s.empty() && (s.top() == '*' || s.top() == '/')) {	// 스택이 비어 있지 않으면서, 우선 순위 연산자의 경우
					std::cout << s.top();
					s.pop();
				}
				s.push(curr);
			}
			else if(curr == '+' || curr == '-') {	// 우선 순위가 밀리는 연산자 (+, -) 인 경우
				while(!s.empty() && s.top() != '(') {	// 스택이 비어 있지 않거나 왼쪽 괄호가 있는 경우
					std::cout << s.top();
					s.pop();
				}
				s.push(curr);
			}
			else if(curr == ')') {	// 오른쪽 괄호가 있는 경우
				while(!s.empty() && s.top() != '(') {	// 스택이 비어있지 않거나, 왼쪽 괄호가 없는 경우
					std::cout << s.top();
					s.pop();
				}
				s.pop();
			}
		}		
	}

	while(!s.empty()) {	// 남은 모든 스택의 괄호를 포함한 연산자 출력
		std::cout << s.top();
		s.pop();
	}

	return;
}

void input() {

	std::cin >> infix;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	return 0;
}