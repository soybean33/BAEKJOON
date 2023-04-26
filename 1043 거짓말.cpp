#include <iostream>
#include <vector>

int N, M;	// N: 사람의 수, M: 파티의 수
int parent[51];	// parent[i]: i의 소속 정보 -> 0번 소속이면 진실을 아는 사람
std::vector<int> party[51];	// party[i]: i 번째 파티에 참여한 사람의 번호

int Find(int now) {
	if (parent[now] == now) return now;
	return parent[now] = Find(parent[now]);
}

void Union(int A, int B) {
	int pa = Find(A);
	int pb = Find(B);

	if (pa == pb) return;

	parent[pa] = pb;	// A의 소속을 B의 소속으로 바꾸어 줌으로써 두 소속을 합침

	return;
}

int sol() {
	
	int cnt = 0;	// cnt: 과장된 이야기를 할 수 있는 파티 개수

	for (int i = 0; i < M; i++) {
		int flag = 0;	// flag: 파티에 진실을 아는 사람이 있다면 1
		for (int j = 0; j < party[i].size(); j++) {
			if (Find(party[i][j]) == 0) {	// 파티에 진실을 아는 사람이 있다면
				flag = 1;
				break;
			}
		}
		if (flag == 0) cnt++;	// i 번째 파티에서 과장된 이야기를 할 수 있음
	}

	return cnt;
}

void input() {
	std::cin >> N >> M;

	for (int i = 0; i <= N; i++)	// 소속 정보 초기화
		parent[i] = i;

	int T;	// T: 진실을 아는 사람의 수
	std::cin >> T;
	for (int i = 0; i < T; i++) {
		int n;	// n: 진실을 아는 사람의 번호
		std::cin >> n;
		Union(Find(n), 0);	// 진실을 아는 사람은 0번 소속을 갖도록 함
	}
	for (int i = 0; i < M; i++) {
		int n;	// n: i 번째 파티에 참여한 사람의 수
		std::cin >> n;
		for (int j = 0; j < n; j++) {
			int m;	// m: i 번째 파티에 참여한 사람의 번호 
			std::cin >> m;
			party[i].push_back(m);	// 과장된 이야기를 할 수 있는 파티 개수를 구하기 위하여 저장
		}
		for (int j = 1; j < n; j++) {
			int a = party[i][0];	// a: i 번째 파티의 기준 사람
			int b = party[i][j];	// b: i 번째 파티에 참여한 사람

			if (Find(a) == 0)	// a가 진실을 아는 사람이라면
				Union(Find(b), Find(a));	// b도 진실을 알게 됨
			else Union(Find(a), Find(b));	// b의 소속을 갖도록 함
		}
	}

	return;
}

int main() {

	input();
	std::cout << sol();

	return 0;
}