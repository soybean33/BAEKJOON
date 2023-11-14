#include <iostream>

int N;
char t[3072][6144];
 
void Dfs(int n, int x, int y){
    if (n == 3) {
        t[y][x] = '*';
        
        t[y + 1][x - 1] = '*';
        t[y + 1][x + 1] = '*';
 
        t[y + 2][x - 2] = '*';
        t[y + 2][x - 1] = '*';
        t[y + 2][x] = '*';
        t[y + 2][x + 1] = '*';
        t[y + 2][x + 2] = '*';
    }
	else {
        Dfs(n / 2, x, y);
        Dfs(n / 2, x-n/2, y+n/2);
        Dfs(n / 2, x-n/2+n, y+n/2);
    }

	return;
}

void Input(){

	std::cin >> N;

	for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2*N-1; j++) {
                t[i][j] = ' ';
        }
    }

	return;
}

int main(){
    
	Input();   
 
    Dfs(N, N-1, 0);
 
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 2 * N -1; j++){
            std::cout << t[i][j];
        }
        std::cout << "\n";
    }

	return 0;
}
