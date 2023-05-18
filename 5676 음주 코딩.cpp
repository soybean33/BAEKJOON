#include <iostream>
#include <vector>
#include <cmath>

struct Query {
	char a;	// a: 선영이가 내린 명령 -> C: 변경 명령, P: 곱셈 명령
	int b, c;	// b, c: a가 C인 경우 b 번째 수를 c로 변경, a가 P인 경우 수열의 b 번째에서 c 번째 수 곱
};

int printSegmentTreeNode(std::vector<int>& segmentTree, int nodeNum, int start, int end, int left, int right) {	// segmentTree[i]: 세그먼트 트리의 i 번째 노드의 값, nodeNum: 노드 번호, start, end: 현재 노드가 포함하는 범위 start ~ end, left, right: 곱을 구할 범위 left ~ right

	if (start > right || end < left) return 1;	// 곱을 구할 범위가 아니라면, 영향을 미치지 않는 값인 1 return

	if (start >= left && end <= right) return segmentTree[nodeNum];	// 곱을 구할 범위를 모두 포함하는 노드라면 더 이상 내려가보지 않고 해당 노드 값 return

	int middle = (start + end) / 2;	// middle: 자식 노드의 범위를 나누는 기준
	int leftValue = printSegmentTreeNode(segmentTree, nodeNum * 2, start, middle, left, right);	// leftValue: 왼쪽 자식 노드의 값
	int rightValue = printSegmentTreeNode(segmentTree, nodeNum * 2 + 1, middle + 1, end, left, right);	// rightValue: 오른쪽 자식 노드이 값

	return leftValue * rightValue;	// 현재 노드의 값 업데이트 및 return
}

int updateSegmentTree(std::vector<int>& element, std::vector<int>& segmentTree, int nodeNum, int start, int end, int idx, int num) {	// element[i]: 수열의 i 번째 수, segmentTree[i]: 세그먼트 트리의 i 번째 노드의 값, nodeNum: 노드 번호, start, end: 현재 노드가 포함하는 범위 start ~ end, idx: 변경할 수열의 인덱스, num: 변경할 수

	if (start > idx || end < idx) return segmentTree[nodeNum];	// 업데이트되는 노드를 포함하는 범위가 아니면 그대로 return

	if (start == end) {	// 변경하는 리프 노드
		element[start] = num;	// 수열 갱신
		return segmentTree[nodeNum] = element[start];	// 갱신된 값 세그먼트 트리에 적용하고 return
	}

	int middle = (start + end) / 2;	// middle: 자식 노드의 범위를 나누는 기준
	int leftValue = updateSegmentTree(element, segmentTree, nodeNum * 2, start, middle, idx, num);	// leftValue: 왼쪽 자식 노드의 값
	int rightValue = updateSegmentTree(element, segmentTree, nodeNum * 2 + 1, middle + 1, end, idx, num);	// rightValue: 오른쪽 자식 노드이 값

	return segmentTree[nodeNum] = leftValue * rightValue;	// 현재 노드의 값 업데이트 및 return
}

int makeSegmentTree(std::vector<int> &element, std::vector<int> &segmentTree, int nodeNum, int start, int end) {	// element[i]: 수열의 i 번째 수, segmentTree[i]: 세그먼트 트리의 i 번째 노드의 값, nodeNum: 노드 번호, start, end: 현재 노드가 포함하는 범위 start ~ end
	
	if (start == end) return segmentTree[nodeNum] = element[start];	// 리프 노드

	int middle = (start + end) / 2;	// middle: 자식 노드의 범위를 나누는 기준
	int leftValue = makeSegmentTree(element, segmentTree, nodeNum * 2, start, middle);	// leftValue: 왼쪽 자식 노드의 값
	int rightValue = makeSegmentTree(element, segmentTree, nodeNum * 2 + 1, middle + 1, end);	// rightValue: 오른쪽 자식 노드이 값

	return segmentTree[nodeNum] = leftValue * rightValue;	// 현재 노드의 값 업데이트 및 return
}

void sol(std::vector<int>& element, std::vector<Query>& query, int* N, int* K) {	// element[i]: 수열의 i 번째 수, query[i]: i 번째 쿼리, N: 수열의 크기, K: 게임 라운드 수

	std::vector<int> segmentTree;	// segmentTree: 세그먼트 트리의 i 번째 노드의 값 -> -1 음수, 0 , 1 양수

	int treeDepth = std::ceil(std::log2(*N));	// treeDepth: 세그먼트 트리의 깊이
	int treeSize = 1 << (treeDepth + 1);	// treeSize: 세그먼트 트리의 크기
	segmentTree.resize(treeSize);	// 세그먼트 트리 공간 할당

	makeSegmentTree(element, segmentTree, 1, 0, *N - 1);	// 세그먼트 트리 생성

	for (int i = 0; i < *K; i++) {
		Query cur = query[i];	// cur: 실행할 쿼리

		if (cur.a == 'C') {	// 변경 명령

			if (cur.c > 0) cur.c = 1;	// 양수
			else if (cur.c == 0) cur.c = 0;	// 0
			else cur.c = -1;	// 음수

			updateSegmentTree(element, segmentTree, 1, 0, *N - 1, cur.b - 1, cur.c);	// 세그먼트 트리 업데이트
		}
		else {	// 곱셈 명령
			int ans = printSegmentTreeNode(segmentTree, 1, 0, *N - 1, cur.b - 1, cur.c - 1);	// ans: 곱셈의 결과 -> -1 음수, 0, 1 양수
			if (ans > 0) std::cout << '+';	// 양수인 경우
			else if (ans == 0) std::cout << '0';	// 0인 경우
			else std::cout << '-';	// 음수인 경우
		}
	}

	return;
}

void input(std::vector<int> &element, std::vector<Query> &query, int* N, int* K) {	// element[i]: 수열의 i 번째 수, query[i]: i 번째 쿼리, N: 수열의 크기, K: 게임 라운드 수

	for (int i = 0; i < *N; i++) {
		int n;	// n: 수
		std::cin >> n;
		if (n > 0) element.push_back(1);	// 수열의 수가 양수면 1
		else if (n == 0) element.push_back(0);	// 수열의 수가 0이면 0
		else element.push_back(-1);	// 수열의 수가 음수면 -1
	}

	for (int i = 0; i < *K; i++) {
		char a;	// a: 선영이가 내린 명령
		int b, c;
		std::cin >> a >> b >> c;
		query.push_back({ a, b, c });
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N, K;	// N: 수열의 크기, K: 게임의 라운드 수

	while (std::cin >> N >> K) {	// 더 이상 입력이 들어오지 않는다면 종료

		std::vector<int> element;	// element[i]: 수열의 i 번째 수
		std::vector<Query> query;	// query[i]: i 번째 쿼리

		input(element, query, &N, &K);

		sol(element, query, &N, &K);
		std::cout << '\n';
	}
	
	return 0;
}