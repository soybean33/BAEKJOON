#include <iostream>
#include <vector>

int N;	// N: 숫자의 자릿 수
std::vector<int> answers;	// answer: 수빈이가 관심있는 소수의 모음

bool Chk(int n){	// n: 수수임을 판별할 수
	for(int i=2; i*i<=n; ++i){
		if(n % i == 0) {return false;}	// 소수가 아니라면 return false
	}
	return true;	// 소수라면 return true
}

void Dfs(int n, int depth){	// n: 숫자, depth: 숫자의 길이
	if(depth == N) {	// 만족하는 길이가 되었을 경우
		answers.push_back(n);	// 수빈이가 관심있는 수
		return;
	}

	for(int i=1; i<10; ++i){
		if(Chk(n * 10 + i)) {Dfs(n*10 + i, depth + 1);}	// 수빈이가 관심있는 수라면 계속해서 탐색
	}
}

void Solution(){

	// 2, 3, 5, 7 로 시작하는 수에 대해 탐색
	Dfs(2, 1);
	Dfs(3, 1);
	Dfs(5, 1);
	Dfs(7, 1);

	return;
}

void Input(){

	std::cin >> N;

	return;
}

int main(){

	Input();

	Solution();

	for(const int& answer : answers) {	// answer: 수빈이가 관심있어 하는 수
		std::cout << answer << '\n';
	}

	return 0;
}