#include <iostream>

int N;	// N: 첫 번째 장대에 쌓인 원판의 개수

void Dfs(int n, int from, int to, int tmp){
	if(n == 1) {std::cout << from << ' ' << to << '\n';}
	else{
		Dfs(n-1, from, tmp, to);	// from에 있는 것을 tmp로 이동
		std::cout << from << ' ' << to << '\n';
		Dfs(n-1, tmp, to, from);	// tmp에 있는 것을 to로 이동
	}
}

void Solution(){

	std::cout << (1 << N) - 1 << '\n';

	Dfs(N, 1, 3, 2);	// 1번 장대에서 3번 장대로 원판을 옮길 것, 2번을 통해서 

	return;
}

void Input(){

	std::cin >> N;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	return 0;
}