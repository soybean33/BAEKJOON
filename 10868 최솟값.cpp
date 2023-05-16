#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int N, M;	// N: 노드의 개수, M: 쿼리의 개수
std::vector<int> element;	// element[i]: i 번째 원소 값
std::vector<std::pair<int, int>> query;	// query[i]: i 번째 쿼리의 범위 a ~ b
std::vector<int> segmentTree;	// segmentTree[i]: 세그먼트 트리의 i 노드의 값

int doQuery(int nodeNum, int start, int end, int left, int right) {

	if (right < start || left > end) return static_cast<int> (21e8);	// 범위를 벗어나면 최소값에 영향을 미치지 않도록 큰 값 return
	if (left <= start && end <= right) return segmentTree[nodeNum];	// 범위 내의 값이라면 값 return

	int middle = (start + end) / 2;	// middle: 범위 start ~ end의 중앙값
	int leftResult = doQuery(nodeNum * 2, start, middle, left, right);	// leftResult: 쿼리를 수행하였을 때 왼쪽에서 얻을 수 있는 최쇠 값
	int rightResult = doQuery(nodeNum * 2 + 1, middle + 1, end, left, right);	// rightResult: 쿼리를 수행하였을 때 오른쪽에서 얻을 수 있는 최대 값
	
	return std::min(leftResult, rightResult);	// 왼쪽 노드와 오른쪽 노드 중 최소값 return
}

int makeSegmentTree(int nodeNum, int start, int end) {	// nodeNum: 노드 번호, start: 세그먼트 트리의 왼쪽, end: 세그먼트 트리의 오른쪽

	if (start == end) {	// 세그먼트 트리의 왼쪽과 오른쪽 번호가 같다면 -> 더 이상 탐색할 노드가 없음
		segmentTree[nodeNum] = element[start];	// 원소의 값 넣기
		return segmentTree[nodeNum];	// 세그먼트 트리의 원소 값 return
	}

	int middle = (start + end) / 2;	// middle: 범위 start ~ end의 중앙값
	int left = makeSegmentTree(nodeNum * 2, start, middle);	// left: 왼쪽 start ~ middle
	int right = makeSegmentTree(nodeNum * 2 + 1, middle + 1, end);	// right: 오른쪽 middle + 1 ~ end
	segmentTree[nodeNum] = std::min(left, right);	// 왼쪽에서의 값과 오른쪽에서의 값 중 작은 값이 노드의 값으로 설정

	return segmentTree[nodeNum];
}


void sol() {

	int treeHeight = std::ceil(std::log2(N));	// treeHeight: 세그먼트 트리의 높이
	int treeSize = (1 << (treeHeight + 1));	// treeSize: 세그먼트 트리의 크기	
	segmentTree.assign(treeSize, NULL);	// 세그먼트 트리 공간 할당

	makeSegmentTree(1, 0, N-1);	// 세그먼트 트리 생성

	for (int i = 0; i < M; i++) {

		int leftIdx = query[i].first - 1;	// leftIdx: 쿼리의 시작 범위
		int rightIdx = query[i].second - 1;	// rightIdx: 쿼리의 끝 범위

		std::cout << doQuery(1, 0, N - 1, leftIdx, rightIdx) << '\n';	// 루트 노드부터 탐색 시작
	}

	return;
}

void input() {

	std::cin >> N >> M;

	for (int i = 0; i < N; i++) {
		int n;	// n: 원소의 값
		std::cin >> n;
		element.push_back(n);
	}

	for (int i = 0; i < M; i++) {
		int a, b;	// a, b: 쿼리의 범위 a ~ b
		std::cin >> a >> b;
		query.push_back({ a,b });
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