#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

// N is the size of the 2D matrix   N*N
#define N 9
 
/* A utility function to print grid */
void print_sudoku(int grid[N][N]){ //print the sudoku grid after solve
   for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
		 if(grid[row][col]==0) cout<<"_ ";
         else cout << grid[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N-1; i++)
            cout << "---";
      }
      cout << endl;
   }
}
bool is_valid_choice(int grid[N][N],int row, int col, int num){
	for(int i{};i<9;i++){
		if(grid[i][col]==num) return false;
	}
	for(int i{};i<9;i++){
		if(grid[row][i]==num) return false;
	}
	int r=row-row%3;
	int c=col-col%3;
	for(int i{};i<3;i++){
		for(int j{};j<3;j++){
			if(grid[r+i][c+j]==num) return false;
		}
	}
	return true;
}
bool solve_sudoku(int grid[N][N], int row, int col){
	if(row==N-1 && col==N) return true;
	if(col==N){
		col=0;
		row++;
	}
	if(grid[row][col]>0) return solve_sudoku(grid,row, col+1);
	else{
		for(int i{1};i<=N;i++){
			if(is_valid_choice(grid,row,col,i)){
				grid[row][col]=i;
				if(solve_sudoku(grid,row,col+1)) return true;
			}
			grid[row][col]=0;
		}
	}
	return false;
}


int main() {
	// your code goes here
	int n{};
//	int c{};
	ifstream puzzle;
	puzzle.open("Valid_sudoku.txt");
	if(puzzle.is_open()){
		cout<<"Generating random puzzle..."<<endl;
		cout<<"---------------------------------------"<<endl;
		int a[9][9];
		srand(time(0));
		int k=rand()%10;
		string line;
		const int c=k*9+(k);
		int i{};
		while(i<=c && getline(puzzle,line)){
			if(i==c){
				for(int l{};l<9;l++){
					for(int m{};m<9;m++){
						puzzle>>a[l][m];
					}
				}
			}
			i++;
		}
		print_sudoku(a);
		cout<<"---------------------------------------"<<endl;
		if (solve_sudoku(a,0,0)){
			cout<<"Solution..."<<endl;
			print_sudoku(a);
		}
		else
			cout << "no solution  exists " << endl;
	}
		
	else{
		cout<<"File could not be opened\n";
	}
	puzzle.close();
	return 0;
}
