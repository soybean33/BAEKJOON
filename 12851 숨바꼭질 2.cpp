#include <iostream>
#include <queue>

int N, K;	// N: 수빈이의 위치, K: 동생의 위치
bool visited[100'001];	// visited[i]: i 위치 방문 여부
std::pair<int, int> ans;	// ans: {수빈이가 동생을 찾는 가장 빠른 시간, 가장 빠른 시간으로 수빈이가 동생을 찾는 방법의 수}

void solution(){

	std::queue<std::pair<int, int>> q;	// q[i]: {수빈이의 현재 위치, 흐른 시간}

	q.push({N, 0});
	visited[N] = true;

	while(!q.empty()){
		std::pair<int, int> cur = q.front();	// cur: {수빈이의 현재 위치, 흐른 시간}
		q.pop();

		visited[cur.first] = true;

		if(ans.second){	// 이미 동생을 찾은 적 있음
			if(cur.first == K && cur.second == ans.first) ans.second++;	// 같은 위치, 같은 시간이면 수빈이가 동생을 찾는 방법의 수 ++
		}

		if(!ans.second){	// 동생을 찾은 적 없음
			if(cur.first == K){	// 수빈이가 동생의 위치에 도착
				ans.first = cur.second;	// 가장 빠른 시간 저장
				ans.second++;	// 가장 빠른 시간으로 동생을 찾는 방법 ++
			}
		}

		if(cur.first * 2 <= 100'000){	// 2 * X 의 위치로 이동
			if(!visited[cur.first * 2]) q.push({cur.first * 2, cur.second + 1});
		}
		if(cur.first + 1 <= 100'000){	// X + 1 의 위치로 이동
			if(!visited[cur.first + 1]) q.push({cur.first + 1, cur.second + 1});
		}
		if(cur.first - 1 >= 0){	// X - 1 의 위치로 이동
			if(!visited[cur.first - 1]) q.push({cur.first - 1, cur.second + 1});
		}
	}

	return;
}

void input(){

	std::cin >> N >> K;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans.first << '\n' << ans.second;

	return 0;
}