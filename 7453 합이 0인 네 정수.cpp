#include <iostream>
#include <algorithm>

int n;	// n: 배열의 크기
int A[4'000], B[4'000], C[4'000], D[4'000];	// A[i], B[i], C[i], D[i]: 정수로 이루어진 크기가 같은 배열 A, B, C, D
int sum1[4'000 * 4'000], sum2[4'000 * 4'000];	// sum1[i]: A 배열과 B 배열의 모든 조합의 합, sum2[i]: C 배열과 D 배열의 모든 조합의 합
long long ans;	// ans: 합이 0이 되는 쌍의 개수

void sol(){

	for(int j=0; j<n; j++){
		for(int i=0; i<n; i++){
			sum1[j*n + i] = A[i] + B[j];	// A 배열과 B 배열
			sum2[j*n + i] = C[i] + D[j];	// C 배열과 D 배열
		}
	}

	// 오름차순 정렬
	std::sort(sum1, sum1 + n*n);
	std::sort(sum2, sum2 + n*n);

	int left = 0, right = n*n-1;	// left: 왼쪽부터 시작하는 sum1 배열의 인덱스, right: 오른쪽부터 시작하는 sum2 배열의 인덱스

	while(left < n*n && right >= 0){	// 두 합 배열의 범위를 벗어나지 않을 때 까지
		if(sum1[left] + sum2[right] == 0){	// 0인 경우

			int leftValue = sum1[left], rightValue = sum2[right];	// leftValue: sum1 배열의 left 인덱스의 값, rightValue: sum2 배열의 right 인덱스의 값
			long long leftSame = 0, rightSame = 0;	// leftSame: leftValue와 같은 값의 수, rightSum: rightValue와 같은 값의 수

			while(leftValue == sum1[left]){	// 같은 값일 경우
				if(left >= n*n) break;	// 범위 벗어나면 break
				leftSame++;	// 갯수 증가
				left++;	// 인덱스 증가
			}
			while(rightValue == sum2[right]){	// 같은 값일 경우
				if(right < 0) break;	// 범위 벗어나면 break
				rightSame++;	// 갯수 증가
				right--;	// 인덱스 감소
			}
			ans += leftSame * rightSame;	// 조합의 개수를 더함
		}
		else if(sum1[left] + sum2[right] < 0) left++;	// 0 보다 작은 경우 -> 더 큰 값을 더하기
		else right--;	// 0 보다 큰 경우 -> 더 작은 값을 더하기
	}

	return;
}

void input(){

	std::cin >> n;

	for(int i=0; i<n; i++){
		std::cin >> A[i] >> B[i] >> C[i] >> D[i];
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}