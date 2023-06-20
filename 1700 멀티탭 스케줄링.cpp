#include <iostream>
#include <vector>

int N, K;	// N: 멀티탭 구멍의 개수, K: 전기 용품의 총 사용횟수
std::vector<int> multiTab;	// multiTab[i]: i 번째 멀티텝 구멍에 꼿혀있는 전기 용품
std::vector<int> appliance;	// applicane[i]: i 번째로 사용할 전기 용품의 번호
int ans;	// ans: 플러그를 빼는 최소의 횟수

void sol(){

	int remain = N;	// remain: 남아 있는 멀티탭 구멍의 갯수

	for(int i=0; i<K; i++){
		int curAppliance = appliance[i];	// curAppliance: 사용할 전기 용품

		bool flag = false;	// flag: 사용할 전기 용품이 꼿혀 있는지 판단

		for(int j=0; j<N; j++){
			if(multiTab[j] == curAppliance){	// 이미 꼿혀 있음
				flag = true;
				break;
			}
		}

		if(flag) continue;	// 이미 사용할 전기 용품이 꼿혀 있으므로 continue

		if(remain){	// 전기 용품이 꼿혀 있지 않은 상황에서 남은 멀티탭 자리가 있음
			for(int i=0; i<N; i++){
				if(multiTab[i]) continue;	// 이미 다른 전기 용품이 꼿혀 있으면 continue
				multiTab[i] = curAppliance;	// 비어 있는 멀티탭에 전기 용품 꼿음
				break;
			}			
			remain--;	// 빈 구멍 개수 줄임
			continue;
		}

		int changeAppliance = 0;	// changeAppliance: 뽑을 전기 용품
		int multiTabHoleNum = 0;	// multiTabHoleNum: 뽑을 멀티탭 구멍 번호
		int maxTime = 0;	// maxTime: 가장 늦게 다시 사용하는 전기 용품 시간

		for(int j=0; j<N; j++){
			int reAppliance = multiTab[j];	// reAppliance: 뽑을 전기 용품

			flag = false;	// 다시 사용하는지 판단

			for(int k = i; k < K; k++){
				if(appliance[k] == reAppliance){	// 다시 사용하는 경우가 있음

					flag = true;

					if(maxTime < k){	// 늦게 사용하는 전기 용품으로 갱신
						changeAppliance = reAppliance;
						maxTime = k;
						multiTabHoleNum = j;
					}
					break;
				}
			}

			if(!flag){	// 다시 사용하는 경우가 없으면 더 이상 탐색하지 않고 뽑음
				changeAppliance = reAppliance;
				multiTabHoleNum = j;
				break;
			}
		}

		multiTab[multiTabHoleNum] = curAppliance;	// 다른 전기 용품으로 갱신
		ans++;	// 플러그를 뺌
	}

}

void input(){

	std::cin >> N >> K;

	multiTab.resize(N);
	appliance.resize(K);

	for(int i=0; i<K; i++) std::cin >> appliance[i];

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