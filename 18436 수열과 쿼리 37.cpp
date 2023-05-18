#include <iostream>
#include <vector>
#include <cmath>

struct Query {
	int a, b, c;	// a: 1인 경우 b 번째 수열을 c로 변경, 2인 경우 b에서 c에 속하는 수의 짝수의 개수, 3인 경우 b에서 c에 속하는 수의 홀수의 개수
};

struct Node {
	int oddCnt, evenCnt;	// oddCnt: 홀수의 개수, evenCnt: 짝수의 개수
};

int N, M;	// N: 수열의 길이, M: 쿼리의 개수
std::vector<int> element;	// element[i]: 수열의 i 번째 원소
std::vector<Query> query;	// query[i]: i 번째 쿼리
std::vector<Node> segmentTree;	// segmentTree[i]: 세그먼트 트리의 i 노드의 값

Node printSegmentTreeNode(int nodeNum, int start, int end, int left, int right) {	// nodeNum: 노드 번호, start, end: 노드가 포함하는 범위, left, right: 탐색할 수열의 범위

	if (start > right || end < left) return { 0, 0 };	// 수열의 범위에 포함되지 않는 경우 영향을 미치지 않는 값 return

	if (start >= left && end <= right) return segmentTree[nodeNum];	// 수열의 범위에 모두 포함되는 경우 자식 노드로 내려가지 않고 현재 노드의 값 return

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드의 범위를 나누는 기준
	Node leftNode = printSegmentTreeNode(nodeNum * 2, start, middle, left, right);	// leftNode: 왼쪽 자식 노드의 값
	Node rightNode = printSegmentTreeNode(nodeNum * 2 + 1, middle + 1, end, left, right);	// rightNode: 오른쪽 자식 노드의 값

	return { leftNode.oddCnt + rightNode.oddCnt, leftNode.evenCnt + rightNode.evenCnt };	// 왼쪽 자식 노드와 오른쪽 자식 노드로 부터 얻은 값
}

Node updateSegmentTree(int nodeNum, int start, int end, int idx, int num) {	// nodeNum: 노드 번호, start, end: 노드가 포함하는 범위, idx: 변경할 수열의 인덱스, num: 변경할 수

	if (start > idx || end < idx) return segmentTree[nodeNum];	// 변경되는 노드에 영향을 미치지 않는 노드의 경우 그대로 return

	if (start == end) {	// 변경되는 노드

		int oddCnt = 0;	// oddCnt: 홀수의 개수
		int evenCnt = 0;	// evenCnt: 짝수의 개수

		if (num % 2)  oddCnt++;	// 홀수++
		else evenCnt++;	// 짝수++

		element[start] = num;	// 수열 갱신

		return segmentTree[nodeNum] = { oddCnt, evenCnt };	// 노드 갱신
	}

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드의 범위를 나누는 기준
	Node leftNode = updateSegmentTree(nodeNum * 2, start, middle, idx, num);	// leftNode: 왼쪽 자식 노드의 값
	Node rightNode = updateSegmentTree(nodeNum * 2 + 1, middle + 1, end, idx, num);	// rightNode: 오른쪽 자식 노드의 값

	return segmentTree[nodeNum] = { leftNode.oddCnt + rightNode.oddCnt, leftNode.evenCnt + rightNode.evenCnt };	// 왼쪽 자식 노드와 오른쪽 자식 노드로 부터 얻은 값
}

Node makeSegmentTree(int nodeNum, int start, int end) {	// nodeNum: 노드 번호, start, end: 노드가 포함하는 범위 start ~ end

	if (start == end) {	// 리프 노드

		int oddCnt = 0;	// oddCnt: 홀수의 개수
		int evenCnt = 0;	// evenCnt: 짝수의 개수

		if (element[start] % 2) oddCnt++;	// 홀수++
		else evenCnt++;	// 짝수 ++

		return segmentTree[nodeNum] = { oddCnt, evenCnt};	// node에 값 넣음
	}

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드의 범위를 나누는 기준
	Node leftNode = makeSegmentTree(nodeNum * 2, start, middle);	// leftNode: 왼쪽 자식 노드의 값
	Node rightNode = makeSegmentTree(nodeNum * 2 + 1, middle + 1, end);	// rightNode: 오른쪽 자식 노드의 값
	
	return segmentTree[nodeNum] = {leftNode.oddCnt + rightNode.oddCnt, leftNode.evenCnt + rightNode.evenCnt};	// 왼쪽 자식 노드와 오른쪽 자식 노드로 부터 얻은 값
}

void sol() {

	int treeDepth = std::ceil(std::log2(N));	// treeDepth: 트리의 깊이
	int treeSize = 1 << (treeDepth + 1);	// treeSize: 트리의 크기
	segmentTree.resize(treeSize);	// 세그먼트 트리 공간 할당

	makeSegmentTree(1, 0, N - 1);	// 세그먼트 트리 생성

	for (int i = 0; i < M; i++) {
		Query cur = query[i];	// cur: 실행할 쿼리

		if (cur.a == 1) {	// a: 1인 경우 b 번째 수열을 c로 변경
			updateSegmentTree(1, 0, N - 1, cur.b - 1, cur.c);
		}
		else{	// 2인 경우 b에서 c에 속하는 수의 짝수의 개수, 3인 경우 b에서 c에 속하는 수의 홀수의 개수
			Node res = printSegmentTreeNode(1, 0, N - 1, cur.b - 1, cur.c - 1);	// res: 결과
			if (cur.a == 2) std::cout << res.evenCnt << '\n';
			else std::cout << res.oddCnt << '\n';
		}
	}

	return;
}

void input() {

	std::cin >> N;

	for (int i = 0; i < N; i++) {	
		int n;	// n: 수
		std::cin >> n;
		element.push_back(n);
	}

	std::cin >> M;

	for (int i = 0; i < M; i++) {
		int a, b, c;	// a: 1인 경우 b 번째 수열을 c로 변경, 2인 경우 b에서 c에 속하는 수의 짝수의 개수, 3인 경우 b에서 c에 속하는 수의 홀수의 개수
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