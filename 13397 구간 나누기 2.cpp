#include <iostream>
#include <algorithm>

int N, M;	// N: 배열의 크기, M: 나눌 수 있는 구간의 개수
int arr[5'001];	// arr[i]: i 번째 수
int MAX;	// MAX: 배열에서 가장 큰 수

bool possible(int middle) {	// middle: 한 구간의 점수

	int cnt = 1;	// cnt: 구간의 개수
	int min, max;	// min: 구간 점수의 최소솟값, max: 구간 점수의 최댓값

	// 초기값 설정
	min = arr[0];
	max = arr[0];

	for (int i = 1; i < N; i++) {
		
		min = std::min(arr[i], min);	// 최솟값 갱신
		max = std::max(arr[i], max);	// 최댓값 갱신
		
		if ((max - min) > middle) {	// 최댓값과 최솟값의 차가 탐색할 구간의 점수보다 크다면
			cnt++;	// 구간 다시 나눔
			min = arr[i];
			max = arr[i];
		}
	}

	return cnt <= M;	// 최대 구간의 개수를 넘어가면 false, 넘지 않으면 true

}

int sol() {

	int left = 0;	// left: 왼쪽 값 -> 최댓값과 최소값의 차이는 최소가 0
	int right = MAX;	// right: 오른쪽 값 -> 최댓값과 최소값의 차이는 최대가 MAX
	int ans = MAX;	// ans: 구간의 점수의 최댓값의 최소값

	while (left <= right) {
		int middle = (left + right) / 2;	// middle: 적용해 볼 수

		if (possible(middle)) {	// middle로 M개 이하의 구간을 나눌 수 있으면
			ans = std::min(ans, middle);	// ans 값 갱신
			right = middle - 1;	// 더 작은 값으로 시도
		}
		else {
			left = middle + 1;	// 더 큰 값으로 시도
		}
	}

	return ans;
}

void input() {

	std::cin >> N >> M;

	for (int i = 0; i < N; i++) {
		std::cin >> arr[i];
		MAX = std::max(MAX, arr[i]);	// 최댓값 찾음 -> 최대 구간 점수
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	std::cout << sol();

	return 0;
}