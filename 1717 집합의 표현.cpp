#include <iostream>

int parent[1000001];	// parent[i]: i의 소속 정보

int Find(int now) {	// now: 소속을 찾을 수
	if (parent[now] == now) return now;	// 소속을 찾음
	return parent[now] = Find(parent[now]);
}

void Union(int a, int b) {	// a, b: 소속을 찾을 원소
	int pa = Find(a);	// 원소 a의 소속 찾기
	int pb = Find(b);	// 원소 b의 소속 찾기

	if (pa == pb) return;	// 같은 소속이면 return;

	parent[pa] = pb;	// 원소 pa는 pb의 소속에 포함

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N, M;	// N: 집합에 포함되는 수의 수(n+1). M: 연산의 개수
	
	std::cin >> N >> M;

	for (int i = 0; i <= N; i++) {	// 소속 정보 초기화
		parent[i] = i;	// 소속이 없는 수는 자기 자신이 부모
	}

	for (int i = 0; i < M; i++) {
		int o, a, b;	// o: 명령어 -> 0: 합집합, 1: 두 원소가 같은 집합인지 확인, a, b: 원소
		std::cin >> o >> a >> b;

		if (o == 0) {	// 합집합
			Union(a, b);
		}
		else if (o == 1) {	// 확인
			if (Find(a) == Find(b))	// 같은 소속
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
	}

	return 0;
}