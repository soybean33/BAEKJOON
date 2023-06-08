#include <iostream>
#include <cmath>

int N;	// N: 체스판의 한 변의 크기
int row[15];	// row[i]: i 번째 행의 퀸의 좌표
int ans;	// 문: 퀸 N개를 서로 공격할 수 없게 놓는 경우

void DFS(int depth){	// depth: 퀸을 놓을 행 번호

	if(depth == N) {	// 모든 퀸을 놓음
		ans++;	// +1
		return;
	}

	for(int i=0; i<N; i++){	// 	i: 퀸을 놓을 열 좌표

		bool flag = true;	// flag: 퀸을 놓을 수 있으면 true

		for(int j = 0; j < depth; j++){	// 지금까지 놓은 퀸의 j열 까지 조사
			if(i == row[j]) {	// 같은 열에 둘 수 없음
				flag = false;
				break;
			}
			if(std::abs(i - row[j]) == depth - j){	// 대각선에 둘 수 없음
				flag = false;
				break;
			}
		}

		if(!flag) continue;	// 퀸을 둘 수 없는 경우 continue

		row[depth] = i;	// 퀸 놓기
		DFS(depth+1);	// 다음 퀸 놓기
	}

}

void sol(){

	DFS(0);	// 0 번째 행부터 DFS

	return;
}

void input(){

	std::cin >> N;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}