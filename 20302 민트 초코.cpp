#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

void CalPrimeFactor(const std::string& stringNum, std::vector<int>& primeFactor, const bool divideChk) {

	int num = stoi(stringNum);	// num: 정수로 변환

	if (num < 0) num *= -1;	// 음수라면 양수로 변환

	for (int i = 2; i <= static_cast<int>(std::sqrt(num)) + 1; ++i) {
		while (num % i == 0) {
			if (divideChk) { --primeFactor[i]; }	// 나눗셈이라면 소인수 빼기
			else { ++primeFactor[i]; }	// 곱셈이라면 소인수 더하기
			num /= i;
		}
	}

	if (num > 1) {	// 소인수가 되지 않은 값에 대하여
		if (divideChk) { --primeFactor[num]; }	// 나눗셈이라면 빼기
		else { ++primeFactor[num]; }	// 곰셈이라면 더하기
	}

	return;
}

bool Solution(int& N, const std::vector<std::string>& formula, const int& maxNum) {

	std::vector<int> primeFactor;	// primeFactor[i]: i 소인수가 존재하는가?

	primeFactor.assign(maxNum + 1, 0);

	if (formula[0] == "0") { return true; }	// 숫자에 0이 있다면 무조건 0
	CalPrimeFactor(formula[0], primeFactor, false);	// 수식의 첫 번째 값은 무조건 곱하기 취급

	for (int i = 1; i < N; i += 2) {
		bool divideChk = false;	// divideChk: 나눗셈 연산 검사
		if (formula[i] == "*") { divideChk = false; }	// 곱셈
		else if (formula[i] == "/") { divideChk = true; }	// 나눗셈

		if (formula[i + 1] == "0") { return true; }	// 0 인지 확인
		CalPrimeFactor(formula[i + 1], primeFactor, divideChk);
	}

	for (int i = 2; i < maxNum + 1; ++i) {
		if (primeFactor[i] < 0) return false;	// 나눗셈 소인수가 있나 확인
	}

	return true;
}

int Input(int& N, std::vector<std::string>& formula) {

	int maxNum = 1;	// maxNum: 최대 값

	std::cin >> N;

	N = 2 * N - 1;	// 수식의 길이는 2 * N - 1

	formula.assign(N, "0");	// 수식 공간 할당

	for (int i = 0; i < N; ++i) {
		std::cin >> formula[i];
		if (i % 2 == 0) {	// 수식의 숫자 순서라면
			int num = std::stoi(formula[i]);	// num: string을 int로 변경

			if (num < 0) num *= -1;	// 음수라면 양수로 변경

			maxNum = std::max(maxNum, num);	// 최대 값 갱신
		}
	}

	return maxNum;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;	// N: 수의 개수
	std::vector<std::string> formula;	// formula[i]: i 번째 수(-100,000 ~ 100,000)나 수식(* or /)
	int maxNum;	// maxNum: 수식에 포함되는 숫자의 최대 값
	
	maxNum = Input(N, formula);	// 입력 및 최대값 갱신

	if (Solution(N, formula, maxNum)) { std::cout << "mint chocolate"; }
	else { std::cout << "toothpaste"; }

	return 0;
}