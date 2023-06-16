#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

int N, M, X;	// N: 학생의 수, M: 대회 본부에 찾아간 수, X: 등수를 알고 싶은 학생의 번호
std::vector<int> v[100'001], reverse_v[100'001];	// v[i][j]: i 학생보다 못한 j 번째 학생 번호, reverse_v[i][j]: i 학생보다 잘한 j 번째 학생 번호
int visited[100'001];	// visited[i]: 방문 체크
int back, front;	// back: X 학생보다 못한 학생의 수, front: X 학생보다 잘한 학생의 수

void DFS(int now, int type){	// now: 현재 학생 번호, type: 0이면 못한학생 탐색, 1 이면 잘한 학생 탐색

	if(type == 0){
		for(int i=0; i<v[now].size(); i++){
			if(visited[v[now][i]]) continue;	// 이미 방문한 학생 continue
			back++;	// 못한 학생 ++
			visited[v[now][i]] = 1;	// 방문 체크
			DFS(v[now][i], type);	// 계속 탐색
		}
	}
	else if(type == 1){
		for(int i=0; i<reverse_v[now].size(); i++){
			if(visited[reverse_v[now][i]]) continue;	// 이미 방문한 학생 continue
			front++;	// 잘한 학생 ++
			visited[reverse_v[now][i]] = 1;	// 방문 체크
			DFS(reverse_v[now][i], type);	// 계속 탐색
		}
	}

	return;
}

void sol(){

	memset(visited, 0, sizeof(visited));	// 방문 초기화
	visited[X] = 1;	// X 학생 방문 체크

	DFS(X, 0);	// X 학생보다 못한 학생 탐색

	memset(visited, 0, sizeof(visited));	// 방문 초기화
	visited[X] = 1;	// X 학생 방문 체크

	DFS(X, 1);	// X 학생보다 잘한 학생 탐색

	return;
}

void input(){

	std::cin >> N >> M >> X;

	for(int i=0; i<M; i++){
		int a, b;	// a, b: 두 학생 a, b가 본부에 찾아갔고, a 학생이 더 잘함
		std::cin >> a >> b;
		v[a].push_back(b);	// 정방향
		reverse_v[b].push_back(a);	// 역방향
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << front + 1 << ' ' << N - back;

	return 0;
}