#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int N;	// N: 전체 용액의 수
int arr[100'001];	// arr[i]: i 번째 오름차순 정렬된 용액의 특성값
int ansLeft, ansRight;	// ansLeft, ansRight: 특성값이 0에 가장 가까운 용액의 인덱스

void sol() {

	int left = 0, right = N - 1;	// left, right: 왼쪽과 오른쪽 포인터
	int diff = std::abs(arr[right] + arr[left]);	// diff: 혼합 용액의 특성값
	ansLeft = left;
	ansRight = right;

	while (left < right) {	// left가 right보다 작을 때
		if (arr[right] + arr[left] > 0) right--;	// 혼합 용액이 양수라면 특성값이 더 작은 용액 혼합
		else left++;	// 혼합 용액이 음수라면 특성값이 더 큰 용액 혼합

		if (left == right) return;	// 서로 다른 용액을 혼합해야 하기 때문에 return

		if (std::abs(arr[right] + arr[left]) < diff) {	// 특성값이 0에 더 까운 용액
			ansLeft = left;
			ansRight = right;
			diff = std::abs(arr[right] + arr[left]);					
		}
	}

	return;
}

void input() {

	std::cin >> N;

	for (int i = 0; i < N; i++) std::cin >> arr[i];

	std::sort(arr, arr + N);	// 오름차순 정렬

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << arr[ansLeft] << ' ' << arr[ansRight];

	return 0;
}