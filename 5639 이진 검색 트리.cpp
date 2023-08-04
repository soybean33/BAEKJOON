#include <iostream>
#include <vector>

std::vector<int> v;	// v[i]: i 번째 전위 순회

void dfs(int leftIdx, int rightIdx){	// leftIdx: 왼쪽 인덱스, rightIdx: 오른쪽 인덱스
	if(leftIdx >= rightIdx) return;	// 탐색 완료
	if(leftIdx == rightIdx - 1){	// 분할된 한쪽이 탐색 완효
		std::cout << v[leftIdx] << '\n';	// 값 반환 후 return
		return;
	}

	int currIdx = leftIdx + 1;	// currIdx: 기준 인덱스
	while(currIdx < rightIdx){	// 기준 인덱스가 오른쪽 인덱스 보다 작은 경우 -> 분할 된 한쪽의 탐색이 다 끝나지 않은 경우
		if(v[leftIdx] < v[currIdx]) break;	// 오른쪽의 값이 더 크다면 break
		currIdx++;	// 커질 때 까지 반복
	}
	dfs(leftIdx + 1, currIdx);	// 왼쪽 분할
	dfs(currIdx, rightIdx);	// 오른쪽 분할
	std::cout << v[leftIdx] << '\n';	// 값 출력

	return;
}

void solution(){

	int s = v.size();	// s: 입력받은 수의 개수

	dfs(0, s);

	return;
}

void input(){
	int n;	// n: 입력 값

	while(std::cin >> n){	// 마지막 까지 입력
		v.push_back(n);
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	return 0;
}