#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int N, M;	// N: 노드의 개수, M: 쿼리의 개수
std::vector<int> element;	// element[i]: i 번째 수
std::vector<std::pair<int, int>> range;	// range[i]: i 번째 쿼리의 범위 -> first ~ second
std::vector<std::pair<int, int>> segmentTree;	// segmentTree[i]: i 번째 노드의 최소값과 최댓값

std::pair<int, int> doQuery(int nodeNum, int start, int end, int left, int right) {	// nodeNum: 노드 번호, start, end: 노드의 범위 strat ~ end, left, right: 최솟값과 최댓값을 구할 범위 left ~ right

	if (start > right || end < left) return { 21e8, 0 };	// 범위를 벗어나면 영향을 미치지 않도록 값을 return

	if (start >= left && end <= right) return segmentTree[nodeNum];	// 범위를 모두 포함하면 자식노드로 내려가지 않고 현재 노드의 값을 return

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드를 나누는 기준
	std::pair<int, int> leftValue = doQuery(nodeNum * 2, start, middle, left, right);	// leftValue: 왼쪽 자식 노드에서의 최솟값과 최댓값
	std::pair<int, int> rightValue = doQuery(nodeNum * 2 + 1, middle + 1, end, left, right);	// rightValue: 오론쪽 자식 노드에서의 최솟값과 최댓값

	return { std::min(leftValue.first, rightValue.first), std::max(leftValue.second, rightValue.second) };	// 두 자식 노드의 최솟값과 최댓값
}

std::pair<int, int> makeSegmentTree(int nodeNum, int start, int end) {	// nodeNum: 노드 번호, start, end: 노드의 범위

	if (start == end) return segmentTree[nodeNum] = { element[start], element[start]};	// 리프 노드는 원소의 값을 갖음

	int middle = (start + end) / 2;	// middle: 왼쪽 자식 노드와 오른쪽 자식 노드를 나누는 기준
	std::pair<int, int> leftValue = makeSegmentTree(nodeNum * 2, start, middle);	// leftValue: 왼쪽 자식 노드에서의 최솟값과 최댓값
	std::pair<int, int> rightValue = makeSegmentTree(nodeNum * 2 + 1, middle + 1, end);	// rightValue: 오른쪽 자식 노드에서의 최솟값과 최댓값

	return segmentTree[nodeNum] = { std::min(leftValue.first, rightValue.first), std::max(leftValue.second, rightValue.second) };	// 두 자식 노드의 최솟값과 최댓값
}

void sol() {

	int treeDepth = std::ceil(std::log2(N));	// treeDepth: 세그먼트 트리의 깊이
	int treeSize = 1 << (treeDepth + 1);	// treeSize: 세그먼트 트리의 사이즈
	segmentTree.assign(treeSize, { 0, 0 });	// 세그먼트 트리의 크기

	makeSegmentTree(1, 0, N - 1);

	for (int i = 0; i < M; i++) {
		std::pair<int, int> cur = range[i];	// cur: 실행할 쿼리

		std::pair<int, int> ans = doQuery(1, 0, N - 1, cur.first, cur.second);	// ans: 최소값과 최댓값 -> ans.first, ans.second

		std::cout << ans.first << ' ' << ans.second << '\n';
	}
	return;
}

void input() {

	std::cin >> N >> M;

	for (int i = 0; i < N; i++) {
		int n;	// n: 입력받은 수
		std::cin >> n;
		element.push_back(n);
	}

	for (int i = 0; i < M; i++) {
		int left, right;	// left, right: 최솟값과 최댓값을 구할 범위
		std::cin >> left >> right;
		left--;
		right--;
		range.push_back({ left, right });
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