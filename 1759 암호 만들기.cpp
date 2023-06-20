#include <iostream>
#include <vector>
#include <algorithm>

int L, C;	// L: 암호의 길이, C: 암호로 사용했을 법한 문자의 개수
std::vector<char> v;	// v[i]: 암호로 사용했을 법한 문자 오름차순 정렬
bool visited[15];	// visited[i]: i 번째 문자 사용 여부
char path[15];	// path[i]: i 번째 암호

void DFS(int idx, int depth, int vowel, int consonant){	// idx: 사용한 문자의 인덱스, depth: 암호의 길이, vowel: 모음의 개수, consonant: 자음의 개수

	if(depth == L){	// L 길이의 암호를 만듦
		if(vowel >= 1 && consonant >= 2){	// 암호의 조건 확인 -> 최소 한 개의 모음, 최소 두개의 자음
			for(int i=0; i<L; i++) std::cout << path[i];
			std::cout << '\n';
		}

		return;
	}

	for(int i=idx; i<C; i++){	// 암호 조함
		if(visited[i]) continue;	// 이미 사용한 문자 continue

		visited[i] = true;	// 문자 사용 체크

		if(v[i] == 'a' || v[i] == 'e' || v[i] == 'i' || v[i] == 'o' || v[i] == 'u'){	// 모음의 경우
			path[depth] = v[i];
			DFS(i + 1, depth + 1, vowel + 1, consonant);
		}
		else{	// 자음의 경우
			path[depth] = v[i];
			DFS(i + 1, depth + 1, vowel, consonant + 1);
		}
		visited[i] = false;	// 문자 사용 해제
	}
}

void sol(){

	std::sort(v.begin(), v.end());	// 오름차순 정렬

	DFS(0, 0, 0, 0);

	return;
}

void input(){

	std::cin >> L >> C;

	v.resize(C);

	for(int i=0; i<C; i++){
		char c;	// c: 암호에 사용했을 법한 문자
		std::cin >> c;
		v[i] = c;
	}

	return;
}

int main(){

	input();

	sol();

	return 0;
}