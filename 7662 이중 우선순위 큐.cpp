#include <iostream>
#include <set>

std::multiset<int> ms;	// 멀티셋

void sol(int k) {	// k: 연산의 수

	while (k--) {	// 모든 연산을 수행할 때 까지 반복
		char c;	// c: 연산의 종류 -> I 삽입, D 제거
		int n;	// n: 삽입하는 원소나 제거에 사용되는 명령어

		std::cin >> c >> n;
		if (c == 'I') ms.insert(n);	// 원소 삽입
		else {
			if (!ms.size()) continue;	// 멀티셋이 비어있다면 continue

			if (n == 1) {	// 최댓값을 삭제
				std::multiset<int>::iterator it;	// it: 반복자
				it = ms.end();
				it--;
				ms.erase(it);
			}
			else {	// 최솟값을 삭제
				ms.erase(ms.begin());
			}
		}
	}

	return;
}

void reset() {

	while (!ms.empty()) {	// 멀티셋이 빌 때 까지 원소 제거
		ms.erase(ms.begin());
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T, k;	// T: 테스트 케이스 수, k: 입력데이터의 수

	std::cin >> T;

	for (int tc = 0; tc < T; tc++) {
		reset();	// 멀티셋 초기화

		std::cin >> k;

		sol(k);

		if (!ms.size()) std::cout << "EMPTY\n";	// 멀티셋이 비어 있다면 "EMPTY"
		else {
			std::multiset<int>::iterator it;	// it: 반복자
			it = ms.end();
			it--;
			std::cout << *it << ' ' << *ms.begin() << '\n';	// 최댓값과 최솟값 출력
		}
	}

	return 0;
}