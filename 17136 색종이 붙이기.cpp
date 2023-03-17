#include <iostream>
#include <algorithm>

int arr[10][10];	// arr[i][j]: 색종이를 붙힐 종이
int confetti[6];	// confetti[i]: i x i 색종이의 남은 수 -> 최대 각각 5개
int cnt;	// cnt: 색종이를 붙혀야 하는 남은 칸 수
int ans = 100;	// ans: 모든 칸을 붙이는데 필요한 색종이의 최소 개수

void DFS(int num, int left){	// num: 붙힌 색종이 수, left: 색종이를 붙여야하는 남은 칸 수

	if(left == 0){	// 남은 칸 없이 모두 색종이를 붙혔다면
		ans = std::min(ans, num);	// 사용한 색종이 개수 비교하여 최소 개수 갱신

		return;
	}

	for(int j=0; j<10; j++){
		for(int i=0; i<10; i++){
			if(arr[j][i] != 1) continue;	// j행 i열에 색종이를 붙힐 필요 없으면 continue

			for(int s=5; s>=1; s--){	// 큰 색종이부터 붙혀봄
				if(left < s*s) continue;	// 남은 칸이 색종이 칸보다 작다면 continue
				if(confetti[s] == 0) continue;	// 붙히고 싶은 색종이가 남아 있지 않다면 continue
				if(j+s > 10 || i+s > 10) continue;	// 색종이가 범위를 벗어나면 continue

				int flag = 0;	// flag: 생종이를 붙힐 수 있으면 0, 없으면 1
				for(int l=0; l<s; l++){
					for(int k=0; k<s; k++){
						if(arr[j+l][i+k] != 1){	// 색종이를 붙힐 수 없는 칸이라면
							flag = 1;	// flag = 1
							break;
						}
					}
					if(flag == 1)
						break;
				}
				if(flag == 0){	// 색종이를 붙힐 수 있다고 판단
					for(int l=0; l<s; l++){
						for(int k=0; k<s; k++){
							arr[j+l][i+k] = 2;	// 색종이 붙힘
						}
					}
					confetti[s]--;	// 사용한 색종이 종류 감소
					DFS(num+1, left - (s*s));	// 사용한 색종이 수 증가, 남은 색종이 수 감소
					confetti[s]++;	// 사용했던 색종이 종류 증가
					for(int l=0; l<s; l++){
						for(int k=0; k<s; k++){
							arr[j+l][i+k] = 1;	// 색종이 빈칸 복구
						}
					}
				} 
			}
			return;	// 5가지 색종이를 붙일 수 없으면 이미 색종이를 잘못 붙혔으니 return
		}
	}


}

void sol(){
	DFS(0, cnt);
	if(ans == 100)	// 빈 칸을 색종이로 채우는 것이 불가능 하면 -1
		ans = -1;

	return;
}

void input(){
	for(int j=0; j<10; j++){
		for(int i=0; i<10; i++){
			std::cin >> arr[j][i];
			if(arr[j][i] == 1)
				cnt++;
		}
	}

	return;
}

void reset(){
	for(int i=1; i<=5; i++){	// 색종이 초기 개수 설정
		confetti[i] = 5;
	}

	return;
}

int main(){
	reset();
	input();
	sol();
	std::cout << ans;
	return 0;
}