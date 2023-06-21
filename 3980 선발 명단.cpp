#include <iostream>
#include <cstring>
#include <algorithm>

int s[11][11];	// s[i][j]: i 선수의 j 포지션에서 뛸 때의 능력
bool visited[11];	// visited[i]: i 포지션에 선수 여부
int ans;	// ans: 모든 포지션의 선수를 채웠을 때, 능력치의 합의 최댓값

void DFS(int stats, int depth){	// stats: 현재 까지 능력치, depth: 선수 번호

	if(depth == 11){	// 11명의 선수가 모두 포지션을 할당 받았다면
		ans = std::max(ans, stats);	// 최댓값 비교
		return;
	}

	for(int i=0; i<11; i++){
		if(!s[depth][i]) continue;	// 능력치가 0인 포지션은 할당 받을 수 없음
		if(visited[i]) continue;	// 이미 해당 포지션에 선수가 있음

		visited[i] = true;	// 포지션 채우기
		DFS(stats + s[depth][i], depth + 1);
		visited[i] = false;	// 포지션 비우기
	}
}

void reset(){	// 변수 초기화

	memset(visited, 0, sizeof(visited));
	ans = 0;

	return;
}

void sol(){

	reset();

	DFS(0, 0);

	return;
}

void input(){	// 입력

	for(int j=0; j<11; j++){
		for(int i=0; i<11; i++){
			std::cin >> s[j][i];
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int C;	// C: 테스트 케이스의 개수

	std::cin >> C;

	for(int tc=0; tc<C; tc++){

		input();

		sol();

		std::cout << ans << '\n';

	}

	return 0;
}