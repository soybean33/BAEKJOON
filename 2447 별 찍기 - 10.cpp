#include <iostream>

int N;	// N: 한 변의 크기

void star(int i, int j, int N){
    if((i / N) % 3 == 1 && (j / N) % 3 == 1) {
        std::cout << ' ';
    }
    else {
        if(N / 3 == 0) {std::cout <<'*';}
        else {star(i,j,N/3);}
    }

	return;
}

void Solution(){

	for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            star(i, j, N);
		}
        std::cout << '\n';
    }

	return;
}

void Input(){

	std::cin >> N;

	return;
}

int main() {
    
	Input();

    Solution();

    
}