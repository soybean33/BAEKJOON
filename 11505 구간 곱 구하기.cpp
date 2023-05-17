#include <iostream>
#include <vector>
#include <cmath>

struct Query {
	int a, b, c;	// a: a가 1인 경우 b 번째 수를 c로 바꾸고 a가 2인 경우 b부터 c까지의 곱을 구함
};

int N, M, K;	// N: 수의 개수, M: 수의 변경이 일어나는 횟수, K: 구간의 곱을 구하는 횟수
std::vector<int> element;	// element[i]: i 번째로 입력된 수
std::vector<Query> query;	// query[i]: i 번째로 수행되는 쿼리
std::vector<int> segmentTree;	// segmentTree[i]: i 노드의 값

int calMulSegmentTree(int nodeNum, int start, int end, int left, int right) {	// nodeNum: 노드 번호, start, end: 현재 노드에 영향을 미치는 노드의 범위 start ~ end, left, right: 구간의 곱을 구할 범위 left ~ right

	if (left > end || right < start) return 1;	// 곱을 구하는 범위에 포함되지 않음 -> 곱에 영향을 미치지 않는 1의 값 return
	if (left <= start && right >= end) return segmentTree[nodeNum];	// 곱을 구하는 범위가 모두 포함됨 -> 자식 노드에 방문하지 않아도 되므로 해당 노드의 값 return

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드의 범위를 나누는 기준
	int leftValue = calMulSegmentTree(nodeNum * 2, start, middle, left, right);	// leftValue: 왼쪽 자식 노드의 값
	int rightValue = calMulSegmentTree(nodeNum * 2 + 1, middle + 1, end, left, right);	// rightValue: 오른쪽 자식 노드의 값

	return ((long long)leftValue * (long long)rightValue) % 1'000'000'007;	// 두 자식 노드의 곱 % 1,000,000,007
}

int updateSegmentTree(int nodeNum, int start, int end, int idx, int num) {	// nodeNum: 노드 번호, start, end: 현재 노드에 영향을 미치는 노드의 범위 start ~ end, idx: 변경할 노드의 번호, num: 변경할 값

	if (start > idx || end < idx) return segmentTree[nodeNum];	// 탐색할 노드가 범위에 포함되지 않으면 원래의 값을 가짐

	if (start == end) return segmentTree[nodeNum] = element[start] = num;	// 현재 노드가 변경하는 노드인 경우 값을 변경

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드의 범위를 나누는 기준
	int leftValue = updateSegmentTree(nodeNum * 2, start, middle, idx, num);	// leftValue: 왼쪽 자식 노드의 값
	int rightValue = updateSegmentTree(nodeNum * 2 + 1, middle + 1, end, idx, num);	// rightValue: 오른쪽 자식 노드의 값
	
	return segmentTree[nodeNum] = ((long long)leftValue * (long long)rightValue) % 1'000'000'007;	// 두 자식 노드의 곱 % 1,000,000,007
}

int makeSegmentTree(int nodeNum, int start, int end) {	// nodeNum: 노드 번호, start, end: 현재 노드에 영향을 미치는 노드의 범위 start ~ end
	
	if (start == end) return segmentTree[nodeNum] = element[start];	// 리프 노드의 경우 값을 넣음

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드의 범위를 나누는 기준
	int leftValue = makeSegmentTree(nodeNum * 2, start, middle);	// leftValue: 왼쪽 자식 노드의 값
	int rightValue = makeSegmentTree(nodeNum * 2 + 1, middle + 1, end);	// rightValue: 오른쪽 자식 노드의 값

	return segmentTree[nodeNum] = ((long long)leftValue * (long long)rightValue) % 1'000'000'007;	// 두 자식 노드의 곱 % 1,000,000,007
}

void sol() {

	int treeHeight = std::ceil(std::log2(N));	// treeHeight: 세그먼트 트리의 높이
	int treeSize = 1 << (treeHeight + 1);	// treeSize: 세그먼트 트리의 크기
	segmentTree.assign(treeSize, 0);	// 세그먼트 트리 크기 할당

	makeSegmentTree(1, 0, N - 1);

	for (int i = 0; i < M + K; i++) {
		Query cur = query[i];	// cur: 실행할 쿼리

		if (cur.a == 1) {	// a가 1인 경우 b 번째 수를 c로 바꿈
			updateSegmentTree(1, 0, N - 1, cur.b - 1, cur.c);
		}
		else {	// a가 2인 경우 b부터 c까지의 곱을 구하여 출력
			std::cout << calMulSegmentTree(1, 0, N - 1, cur.b - 1, cur.c - 1) << '\n';
		}
	}

	return;
}

void input() {

	std::cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		int n;	// n: 입력 받은 수
		std::cin >> n;
		element.push_back(n);
	}

	for (int i = 0; i < M + K; i++) {
		int a, b, c;	// a: a가 1인 경우 b 번째 수를 c로 바꾸고 a가 2인 경우 b부터 c까지의 곱을 구함
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