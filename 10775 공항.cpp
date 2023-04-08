#include <iostream>

int parent[100001];	// parent[i]: i의 소속 정보
int G, P;	// G: 게이트의 수, P: 비행기의 수

int Find(int now){	// now: 소속을 찾을 비행기
	if(now == parent[now]) return now;
	return parent[now] = Find(parent[now]);
}

void Union(int A, int B){	// A, B: 비행기를 도킹할 수 있는지
	int pa = Find(A);
	int pb = Find(B);

	if(pa == pb) return;

	parent[pb] = pa;

	return;
}

int main(){
	int ans = 0;	// ans: 되킹한 비행기의 수

	std::cin >> G >> P;	

	for(int i=1; i<=G; i++)
		parent[i] = i;	// 소속 정보 초기화
	
	for(int i=0; i<P; i++){
		int num;	// num: 비행기 번호
		std::cin >> num;
		int p = Find(num);	// p: num 비행기의 소속 정보
		
		if(p != 0){	// 비행기를 도킹할 수 있는 경우
			Union(p-1, p);	// 더 작은 번호의 게이트와 소속 합침
			ans++;
		}
		else break;	// 비행기를 더 이상 도킹할 수 없으면 공항 폐쇄
	}

	std::cout << ans;

	return 0;
}