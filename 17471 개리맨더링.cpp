#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

int N;	// N: 구역의 개수
int population[11];	// population[i]: i구역의 인구 수
std::vector<int> v[11];	// i 구역과 연결된 구역
int visited[11];	// visited[i]: i 구역이 0이면 A 선거구, 1이면 B 선거구
int ans = 21e8;	// ans: 두 선거구의 최소값
int parent[11];	// parent[i]: i의 부모

int Find(int now){
	if(now==parent[now]) return now;	// 자기 자신이 소속이면 return
	return parent[now] = Find(parent[now]);	// 계속해서 최상위 소속 찾아서 재귀
}

void Union(int a, int b){
	int pa = Find(a);	// pa: a 구역의 소속
	int pb = Find(b);	// pb: b 구역의 소속

	if(pa == pb) return;	// 두 구역의 소속이 같다면 return

	parent[pa] = pb;	// pa의 소속 pb

	return;
}

void differ(){
	int A = -1, B = -1;	// A, B: 각 선거구의 시작 위치
	for(int i=1; i<=N; i++){
		if(visited[i] == 0 && A == -1)
			A = i;
		if(visited[i] == 1 && B == -1)
			B = i;
	}

	if(A==-1 || B == -1) return;	// A나 B 선거구가 없다면 return

	for(int i=0; i<=N; i++){	// parent 초기화
		parent[i] = i;
	}

	std::queue<int> q;	// q: A 선거구에 연결된 구역
	q.push(A);
	while(!q.empty()){
		int now = q.front();	// now: 연결을 시작할 구역
		q.pop();

		for(int i=0; i<v[now].size(); i++){
			int next = v[now][i];	// next: 연결할 구역

			if(visited[now] != visited[next]) continue;	// 두 구역이 다른 선거구에 속한다면 continue

			if(parent[now] != parent[next]){	// 두 구역이 같은 선거구임에도 소속 정보가 다르다면
				q.push(next);	// next와 연결되어 있는 다른 구역도 탐색하기 위해 넣음
				Union(now, next);	// now 구역과 next 구역 연결
			}
			
		}
	}

	q.push(B);
	while(!q.empty()){
		int now = q.front();
		q.pop();

		for(int i=0; i<v[now].size(); i++){
			int next = v[now][i];

			if(visited[now] != visited[next]) continue;

			if(parent[now] != parent[next]){
				q.push(next);
				Union(now, next);
			}
		}
	}

	int cnt = 0;	// cnt: 소속의 개수
	int sumA = 0, sumB = 0;	// sumA: A 지역구의 인구수 합, sumB: B 지역구의 인구수 합
	for(int i=1; i<=N; i++){
		if(parent[i] == i) cnt++;
		if(visited[i] == 0)
			sumA += population[i];
		else
			sumB += population[i];
	}
	
	if(cnt != 2) return;	// 소속이 2개 이상이면 return

	ans = std::min(ans, std::abs(sumA-sumB));	// 두 선거구의 인구수 차이의 최소값 갱신

	return;
}

void DFS(int now){

	differ();	// 두 선거구의 인구수 차이 계산

	for(int i=now+1; i<=N; i++){	// 조합
		
		visited[i] = 1;
		DFS(i);
		visited[i] = 0;
	}
}

void sol(){
	DFS(0);
	return;
}

void input(){
	std::cin >> N;
	for(int i=1; i<=N; i++)
		std::cin >> population[i];	// 각 선거구 인구수 입력
	for(int j=1; j<=N; j++){
		int n;
		std::cin >> n;
		for(int i=0; i<n; i++){
			int b;
			std::cin >> b;
			v[j].push_back(b);
		}
	}

	return;
}

int main(){
	input();
	sol();
	if(ans == 21e8)
		std::cout << -1;
	else
		std::cout << ans;

	return 0;
}