#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 크레인의 수
std::vector<int> C;	// C[i]: i 번째 크레인의 무게 제한
int M;	// M: 박스의 수
std::vector<int> B;	// B[i]: i 번째 박스의 무게

int answer = 0;	// answer: 박스를 배로 옮기는데 드는 시간의 최솟값

void Solution(){

	// 오름차순 정렬
	std::sort(C.begin(), C.end(), std::less<int>());
	std::sort(B.begin(), B.end(), std::less<int>());

	if(C[N-1] < B[M-1]) {	// 크레인의 무게제한 보다 무거운 박스가 있다면 모든 박스를 배로 옮길 수 없으므로 -1
		answer = -1;
		return;
	}

	int idx = 0;	// idx: 박스의 번호
	while(idx != M) {	// 모든 박스를 옮길 때 까지 반복
		++answer;	// 시간 증가
		int cIdx = N-1;	// cIdx: 크레인의 인덱스 -> 가장 무게 제한이 큰 크레인에 가장 무거운 박스를 할당
		for(int i=M-1; i>=0; --i){
			if(B[i] == 0) {continue;}	// 이미 박스를 옮겼다면 continue
			if(cIdx == -1) {break;}	// 모든 크레인에 박스가 할당 되었다면 break
			if(B[i] <= C[cIdx]){	// i 크레인으로 박스를 옮길 수 있다면
				--cIdx;	// 다음 크레인에 박스를 할당할 수 있도록 
				++idx;	// 다음 박스를 크레인에 할당할 수 있도록
				B[i] = 0;	// 옮긴 박스는 0으로 표시하여 중복되지 않도록
			}
		}
	}

	return;
}

void Input(){

	std::cin >> N;

	C.assign(N, 0);

	for(int i=0; i<N; ++i){
		std::cin >> C[i];	// 크레인의 무게 제한 입력
	}

	std::cin >> M;

	B.assign(M, 0);

	for(int i=0; i<M; ++i){
		std::cin >> B[i];	// 박스의 무게 입력
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}