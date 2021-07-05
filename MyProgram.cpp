#include <stdio.h>
#include <stdlib.h>

int menu();
void rules();
void game();
void initial_B(char[3][3]);
void display(char [3][3]);
int is_empty(char[3][3],int);
void moves(char[3][3],char,int*);
void get_row_col(int,int*,int*);
int is_win(char[3][3],char,int);

int main(){
	while(menu()){
		rules();
		game();
	}
	printf("\n=========== Goodbye  ===========\n");

	return 0;
}

int menu(){
	int trigger;
	printf("================================\n");
	printf("=========== 1. Start ===========\n");
	printf("=========== 0. Exit  ===========\n");
	printf("================================\n");
	printf("Please Enter Your Choice : ");
	scanf("%d",&trigger);
	while(trigger != 1 && trigger != 0){
		printf("Please Enter Valid Index : ");
		scanf("%d",&trigger);
	}
	return trigger;
}

void rules(){
	printf("\n X go First    O Second\n\n");
	int index;
	for(int i=0;i<3;i++){
		index = 7 - i * 3;
		for(int j=0;j<3;j++){
			switch(index){
				case 1:
				case 4:
				case 7:
				case 2:
				case 5:
				case 8:
					printf(" %d |",index);
					break;
				case 3:
				case 6:
				case 9:
					printf(" %d\n",index);
					break;
			}index++;
		}
		if(i != 2) printf("------------\n");
	}printf("\n");
}

void game(){
	char board[3][3],stamp[2] = {'X','O'};
	initial_B(board);
    int index,draw = 1;
	for(int count=0;count<9;count++){
		moves(board,stamp[count%2],&index);
		display(board);
		if(is_win(board,stamp[count%2],index)){
			printf("Player %d Win !!\n\n",count%2+1);
			draw = 0;
			break;
		}
	}
	if(draw == 1){
		printf("Draw\n\n");
	}
}

void initial_B(char board[3][3]){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			board[i][j] = ' ';
		}
	}
}

void display(char board[3][3]){
	int i, j;
	printf("\n");
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			printf(" %c |",board[i][j]);
		}
		printf(" %c\n",board[i][j]);
		if(i != 2)
		    printf("------------\n");
	}
	printf("\n");
}

void moves(char board[3][3],char stamp,int* index){
	int row,col,player = (stamp == 'X')?1:2;;
	printf("Player %d's Turn\nPlease Enter the Index \
to Place %c : ",player,stamp);
	scanf("%d",index);
	while((*index) < 1 || (*index) > 9 || !is_empty(board,*index)){
		printf("Please Enter Valid Index : \n");
		scanf("%d",index);
	}
	get_row_col(*index,&row,&col);
	board[row][col] = stamp;
}

void get_row_col(int index,int *row,int *col){
	*row = (9 - index) / 3;
	switch((*row)){
		case 0:
			*col = index - 7;
			break;
		case 1:
			*col = index - 4;
			break;
		case 2:
			*col = index - 1;
			break;
	}
}

int is_empty(char board[3][3],int index){
	int row,col;
	get_row_col(index,&row,&col);
	if(board[row][col] == ' ')
	    return 1;
	return 0;
}

int is_win(char board[3][3],char stamp,int index){
	int row,col,line = 0;
	get_row_col(index,&row,&col);
	switch(index){
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
			if(board[0][0] == board[1][1] && board[1][1] \
			== board[2][2] && board[2][2] == stamp)
			    return 1;
			if(board[2][0] == board[1][1] && board[1][1] \
			== board[0][2] && board[0][2] == stamp)
			    return 1;
		case 2:
		case 4:
		case 6:
		case 8:
			if(board[row][0] == board[row][1] && board[row][1] \
			== board[row][2] && board[row][2] == stamp)
			    return 1;
			if(board[0][col] == board[1][col] && board[1][col] \
			== board[2][col] && board[2][col] == stamp)
			    return 1;
	}
	return 0;
}
