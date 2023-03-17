#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int N;	// N: 수식의 길이
int num[20];	// num[i]: 수식의 숫자 -> N / 2 + 1 개
char oper[20];	// oper[i]: 수식의 연산자 -> N / 2 개
int chk[20];	// chk[i]: 괄호 여부 체크 -> i 위치에 괄호가 생기려면 i - 1에는 괄호가 있으면 안됨
int ans = -21e8;

int calNum(int a, char c, int b) {	// 괄호 연산
	if (c == '+')
		return a + b;
	if (c == '-')
		return a - b;
	if (c == '*')
		return a * b;
}

void cal() {
	
	std::vector<int> tmpNum;	// tmpNum: 괄호 처리 후 수식의 숫자
	std::vector<char> tmpOper;	// oper: 괄호 처리 후 수식의 연산자

	for (int i = 0; i < N / 2 + 1; i++) {
		if (chk[i] != 1) {	// 괄호가 없다면
			tmpNum.push_back(num[i]);
			tmpOper.push_back(oper[i]);
		}
		if (chk[i] == 1) {	// 괄호가 있다면
			int a = num[i], b = num[i + 1];
			char c = oper[i];
			tmpNum.push_back(calNum(a, c, b));
			tmpOper.push_back(oper[i + 1]);
			i++;	// 그 다음은 연산자만 있으므로 i++
		}
	}
	int ret = 0;	// ret: 연산 결과
	for (int i = 0; i < tmpNum.size(); i++) {
		if (i == 0)
			ret = tmpNum[i];
		else {
			if (tmpOper[i - 1] == '+')
				ret = ret + tmpNum[i];
			if (tmpOper[i - 1] == '-')
				ret = ret - tmpNum[i];
			if (tmpOper[i - 1] == '*')
				ret = ret * tmpNum[i];
		}
	}

	ans = std::max(ans, ret);	// 최대값 갱신
}

void DFS(int now) {

	cal();

	for (int i = now + 1; i < N / 2; i++) {
		if (i == 0) {
			
		}
		else if (chk[i - 1] == 1) {	// 이전에 괄호가 있으면 괄호를 만들 수 없으므로 continue
			continue; 
		}

		chk[i] = 1;	// chk가 1이면 괄호
		DFS(i);
		chk[i] = 0;
	}

	return;
}

void sol() {
	DFS(-1);
	return;
}

void input() {
	std::cin >> N;
	std::string S;
	std::cin >> S;
	for (int i = 0; i < N; i++) {	// 수식의 숫자와 연산자를 따로 저장
		if (i % 2 == 0) {
			num[i / 2] = (S[i] - '0');
		}
		else {
			oper[i / 2] = S[i];
		}	
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << ans;
	return 0;
}