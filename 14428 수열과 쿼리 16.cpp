#include <iostream>
#include <vector>
#include <cmath>

struct Query {
	int a, b, c;	// a: 1인 경우 b 번째 수를 c로 변경, 2인 경우 b 에서 c 사이의 값 중 크기가 가장 작은 값의 인덱스를 출력
};

struct Node {
	int idx, minNum;	// idx: 수열의 인덱스, minNum: 최솟값
};

int N, M;	// N: 수열의 크기, M: 쿼리의 개수
std::vector<int> element;	// element[i]: i 번째 수
std::vector<Query> query;	// query[i]: i 번째 쿼리
std::vector<Node> segmentTree;	// segmenmtTree[i]: i 노드의 값

Node printSegmentTreeNode(int nodeNum, int start, int end, int left, int right) {	// nodeNum: 노드 번호, start, end: 세그먼트 트리의 범위 start ~ end, left, right: 탐색할 범위

	if (start > right || end < left) return { 0, static_cast<int>(21e8) };	// 범위 밖은 탐색할 필요 없음, 결과에 영향을 미치지 않은 큰 값 return
	if (left <= start && right >= end) return segmentTree[nodeNum];	// 해당 노드가 범위에 모두 포함되는 경우 해당 노드 return

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드를 나누는 기준
	Node leftValue = printSegmentTreeNode(nodeNum * 2, start, middle, left, right);	// leftValue: 왼쪽 자식 노드의 값
	Node rightValue = printSegmentTreeNode(nodeNum * 2 + 1, middle + 1, end, left, right);	// rightValue: 오른쪽 자식 노드의 값

	return (leftValue.minNum <= rightValue.minNum) ? leftValue : rightValue;	// 왼쪽 노드의 크기가 더 작거나 같은 경우 왼쪽 노드 return, 아니면 오른쪽 노드 return
}

Node updateSegmentTree(int nodeNum, int start, int end, int idx, int num) {	// nodeNum: 노드 번호, start, end: 세그먼트 트리의 범위 start ~ end, idx: 변경할 수의 인덱스, num: 변경할 수

	if (start > idx || end < idx) return segmentTree[nodeNum];	// 범위 밖은 업데이트할 필요 없으므로 값 그대로 return

	if (start == end) {
		element[start] = num;	// 수열의 값 갱신
		return segmentTree[nodeNum] = { idx, element[start]};	// 세그먼트 값 갱신
	}

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드를 나누는 기준
	Node leftValue = updateSegmentTree(nodeNum * 2, start, middle, idx, num);	// leftValue: 왼쪽 자식 노드의 값
	Node rightValue = updateSegmentTree(nodeNum * 2 + 1, middle + 1, end, idx, num);	// rightValue: 오른쪽 자식 노드의 값

	return segmentTree[nodeNum] = (leftValue.minNum <= rightValue.minNum) ? leftValue : rightValue;	// 왼쪽 노드의 크기가 더 작거나 같은 경우 왼쪽 노드 return, 아니면 오른쪽 노드 return
}

Node makeSegmentTree(int nodeNum, int start, int end) {	// nodeNum: 노드 번호, start, end: 세그먼트 트리의 범위 start ~ end

	if (start == end) return segmentTree[nodeNum] = { start, element[start] };	// 리프 노드인 경우 노드 번호와 값을 넣음

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드를 나누는 기준
	Node leftValue = makeSegmentTree(nodeNum * 2, start, middle);	// leftValue: 왼쪽 자식 노드의 값
	Node rightValue = makeSegmentTree(nodeNum * 2 + 1, middle + 1, end);	// rightValue: 오른쪽 자식 노드의 값

	return segmentTree[nodeNum] = (leftValue.minNum <= rightValue.minNum) ? leftValue : rightValue;	// 왼쪽 노드의 크기가 더 작거나 같은 경우 왼쪽 노드 return, 아니면 오른쪽 노드 return
}

void sol() {

	int treeDepth = std::ceil(std::log2(N));	// 세그먼트 트리의 깊이
	int treeSize = 1 << (treeDepth + 1);	// 세그먼트 트리의 크기
	segmentTree.resize(treeSize);	// 세그먼트 트리 공간 할당

	makeSegmentTree(1, 0, N - 1);	// 세그먼트 트리 생성

	for (int i = 0; i < M; i++) {
		Query cur = query[i];	// cur: 실행할 쿼리

		if (cur.a == 1) {	// a가 1인 경우 b 번째 수를 c로 변경
			updateSegmentTree(1, 0, N - 1, cur.b - 1, cur.c);
		}
		else {	// a가 2인 경우 b 에서 c 사이의 값 중 크기가 가장 작은 값의 인덱스를 출력
			Node ans = printSegmentTreeNode(1, 0, N - 1, cur.b - 1, cur.c - 1);
			std::cout << ans.idx + 1 << '\n';
		}
	}

	return;
}

void input() {

	std::cin >> N;

	for (int i = 0; i < N; i++) {
		int n;	// n: 수열의 수
		std::cin >> n;
		element.push_back(n);
	}

	std::cin >> M;

	for (int i = 0; i < M; i++) {
		int a, b, c;	// a: 1인 경우 b 번째 수를 c로 변경, 2인 경우 b 에서 c 사이의 값 중 크기가 가장 작은 값의 인덱스를 출력
		std::cin >> a >> b >> c;
		query.push_back({ a, b, c });
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	return 0;
}