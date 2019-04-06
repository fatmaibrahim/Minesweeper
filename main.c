#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
int numRow=31;
int numCol=31;
int myboard[31][31];
char gameboard[31][31];
int num_move=0;
int num_flag=0;
int num_question=0;
int time_move=0;

void welcome(){
    printf("                                WELCOME TO\n                                MINESWEEPER\n");
    system("pause");
    system("cls");
}/**checking if the user enters an integer number**/
int intCheckSize(int num){
    char term;
    int x=scanf(" %d%c", &num, &term);/**scanf returns the number of input successfully read**/
while( x !=2 || term != '\n' || num<2 || num>30 ){
        printf("Enter a valid number followed by the ENTER key: ");
        scanf("%*s");/**allows to clean scanf()**/
        x=scanf(" %d%c", &num, &term);}

return num;
}
int intCheckXs(int num){
    char term;
    int x=scanf(" %d%c", &num, &term);
while( x !=2 || term != '\n' || num<1 || num>numRow ){
        printf("Enter a valid number followed by the ENTER key: ");
        scanf("%*s");
        x=scanf(" %d%c", &num, &term);}

return num;
}
int intCheckYs(int num){
    char term;
    int x=scanf(" %d%c", &num, &term);
while( x !=2 || term != '\n' || num<1 || num>numCol ){
        printf("Enter a valid number followed by the ENTER key: ");
        scanf("%*s");
        x=scanf(" %d%c", &num, &term);}

return num;
}

typedef struct
{
    char*name[30];
    int score;
} player;

int main()
{
    welcome();
  main_menu();

    return 0;
}

void main_menu()
{
  printf("ENTER (N)to start a new game ENTER (L)to load game ENTER (R)to view ranks \n");
   char mark; mark=getch();
    printf("%c\n",mark);
  switch(mark){
  case 'N':startGame();
  break;
  case 'L':loadGame();
  break;
  case 'R':save_player();
  break;
  default:printf("Enter a valid character: \n");
   main_menu();
  }
}
int  isEmpty(FILE *file)
{
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0)
    {
        return 0;
    }

    fseek(file, savedOffset, SEEK_SET);
    return 1;
}
void loadGame(){
load_gameboard();
load_myboard();
load_detail();
  print_gameborad();
  play();
}

void save_player(){
int i;
    player List[50];
    for(i=0; i<50; i++)
    {
        List[i].score=0;
    }
    FILE*users;
  users=fopen("users.txt","r");
    if (users == NULL)
    {
        printf("File does not exists \n");
        main_menu();
        return;
    }

        if(!feof(users))
    {
        for(i=0; i<50; i++)
        {
          fscanf(users,"%s %d\n",List[i].name,&List[i].score);
        }
    }
   int k=0;
   while(List[k].score!=0){
    k++;
   }
    fclose(users);
char string1[50];
int index_list=k; int j=0;
for(i=0;i<index_list;i++){
  strcpy(string1,List[i].name);
   for(j=0;string1[j]!='\0';j++){
    if(string1[j]=='_'){
     string1[j]=' ';
    }
  }
strcpy(List[i].name,string1);
}

for(i=0; i<index_list; i++)
        {
 printf("%s %d\n",List[i].name,List[i].score);
        }
   main_menu();
}


void startGame(){
    printf("Enter Number Of Rows: ");
    numRow=intCheckSize(numRow);
    printf("Enter Number Of Columns: ");
    numCol=intCheckSize(numCol);
    clock_t start,End;
    start=clock();

    int firstRow,firstCol;
    printf("Enter your first Row: ");
    firstRow=intCheckXs(firstRow);
    printf("Enter your first Col: ");
    firstCol=intCheckYs(firstCol);

    End=clock();
   time_move=(double)(End-start)/CLOCKS_PER_SEC;
   num_move++;
    my_board(firstRow,firstCol);
    game_board(firstRow,firstCol);
    play();
}

    void my_board(int firstRow, int firstCol){
    int i=0,j=0,k=0;/**initializing my board**/
    for(i=0;i<=numRow;i++){
        for(j=0;j<=numCol;j++){
            myboard[i][j]=0;
        }
    }
    int numMine=1+(numRow*numCol)/10;
    int indexes[numMine][2];
    mine(indexes,numMine,firstRow,firstCol);
    /**placing mines inside the board,-1 represents a mine**/
    for(i=0;i<numMine;i++){
        myboard[indexes[i][0]][indexes[i][1]]=-1;
    }
    /**adding numbers around the mines starting from the left upper corner**/
    for(i=0;i<numMine;i++){
        for(j=-1;j<=1;j++){
            for(k=-1;k<=1;k++){
                if(myboard[indexes[i][0]+j][indexes[i][1]+k]!=-1 && indexes[i][0]+j >0 && indexes[i][0]+j <=numRow
                    && indexes[i][1]+k >0 && indexes[i][1]+k <= numCol ){/**checking if nearby cells contain mines
                        so not accessing the cell of the mine itself and checking for borders **/
                    myboard[indexes[i][0]+j][indexes[i][1]+k]++;
                }
            }
        }
    }


    }

    void mine(int arr1[][2], int size,int firstRow, int firstCol ){
        int n=50,arr2[size+n][2],i=0,j=0,k=0;
        srand(time(NULL));
        for(i=0;i<size+n;i++){ /**generating random indexes of the mines**/
            arr2[i][0]=1+rand()%numRow;
            arr2[i][1]=1+rand()%numCol;
        }
        for(i=0;i<size+n;i++){ /**removing repeated indexes**/
            for(j=i+1;j<size+n;j++){
                if(arr2[i][0]==arr2[j][0] && arr2[i][1]==arr2[j][1]){
                    for(k=j;k<size+n;k++){
                        arr2[k][0]=arr2[k+1][0]; arr2[k][1]=arr2[k+1][1];
                    } n--;j--;
                }
            }
        }
        for(i=0;i<size+n;i++){ /**if the first move of the player contains a mine, remove it**/
            if(arr2[i][0]==firstRow && arr2[i][1]==firstCol){
                for(j=i;j<size+n;j++){
                    arr2[j][0]=arr2[j+1][0]; arr2[j][1]=arr2[j+1][1];
                } n--;j--;
            }
        } /**the final array of indexes**/
        for(i=0;i<size;i++){
            for(j=0;j<2;j++){
                arr1[i][j]=arr2[i][j];
            }
        }

     }/**initialize the game board**/
     void game_board(int firstRow,int firstCol){
         int i=0,j=0;
         for(j=0;j<=numCol;j++){
            gameboard[0][j]=j+48;
         }
         for(i=0;i<=numRow;i++){
            gameboard[i][0]=i+48;
         }
         for(i=1;i<=numRow;i++){
            for(j=1;j<=numCol;j++){
                gameboard[i][j]='X';
            }
         }
         if(myboard[firstRow][firstCol]>0 ){
            gameboard[firstRow][firstCol]=myboard[firstRow][firstCol]+48;
             }
    else {if(myboard[firstRow][firstCol]==0){open(firstRow,firstCol);}}
         print_gameborad();

     }

void save_myboard(){
int i,j;
FILE*save1;
save1=fopen("save1.txt","w");
fprintf(save1,"%d %d\n",numRow,numCol);
for(i=0; i<numRow+1; i++)
    {
        for(j=0; j<numCol+1; j++)
        {
    fprintf(save1,"%d ",myboard[i][j]);
        }
    fprintf(save1,"\n");
    }

fclose(save1);
}
void save_gameboard(){
int i,j;
char  game_file[32][32];
for(i=0;i<numRow+1;i++){
  for(j=0;j<numCol+1;j++){
    if(gameboard[i][j]==' '){
      game_file[i][j]=0+48;
    }
    else {
       game_file[i][j]=gameboard[i][j];
    }
  }
}
FILE*save2;
save2=fopen("save2.txt","w");
fprintf(save2,"%d %d\n",numRow,numCol);
for(i=0; i<numRow+1; i++)
    {
        for(j=0; j<numCol+1; j++)
        {
    fprintf(save2,"%c ",game_file[i][j]);
        }
    fprintf(save2,"\n");
    }

fclose(save2);
}

void save_detail(){
  FILE*save3;
save3=fopen("save3.txt","w");
fprintf(save3,"%d\n",num_move);
fprintf(save3,"%d\n",num_flag);
fprintf(save3,"%d\n",num_question);
fprintf(save3,"%d\n",time_move);
fclose(save3);
}




 void saveGame(){
save_myboard();
 save_gameboard();
save_detail();
}

/**in case of winning or losing, remove what has been saved**/
void remove_file(){
remove_file1();
remove_file2();
remove_file3();
}

void print_detail()
{
    int  time_minutes=time_move/60;
    int  time_seconds=time_move%60;
    printf("moves=%d\n",num_move);
    printf("flags=%d\n",num_flag);
    printf("question marks=%d\n",num_question);
    printf("Time passed: %.2d:%.2d\n",time_minutes,time_seconds);
}




     void play(){
     clock_t start,End;
     start=clock();
     printf("Press F to put flag,? to put a question mark, O to open a cell:\n");
     char c; c=getch();
     printf("%c\n",c);
     int x,y;
     switch(c){
       case 'F':
         num_move++;
        num_flag++;
        printf("Enter Row Number: ");
        x=intCheckXs(x);
        printf("Enter Column Number: ");
        y=intCheckYs(y);
        gameboard[x][y]='F';
       End=clock();
      time_move+=(double)(End-start)/CLOCKS_PER_SEC;
        print_gameborad();
        break;

       case '?':
          num_move++;
        num_question++;
        printf("Enter Row Number: ");
        x=intCheckXs(x);
        printf("Enter Column Number: ");
        y=intCheckYs(y);
        gameboard[x][y]='?';
        End=clock();
       time_move+=(double)(End-start)/CLOCKS_PER_SEC;
        print_gameborad();
        break;

      case 'O':
         num_move++;
        printf("Enter Row Number: ");
        x=intCheckXs(x);
        printf("Enter Column Number: ");
        y=intCheckYs(y);
        if(myboard[x][y]>0 && (gameboard[x][y]=='X' || gameboard[x][y]=='?') ){
            gameboard[x][y]=myboard[x][y]+48;
            End=clock();
            time_move+=(double)(End-start)/CLOCKS_PER_SEC;
             print_gameborad();}
        else if (myboard[x][y]+48==gameboard[x][y]){
        openedCell(x,y);
        End=clock();
      time_move+=(double)(End-start)/CLOCKS_PER_SEC;
        print_gameborad();
        }
        else if(myboard[x][y]==-1 && gameboard[x][y]!='F'){
            End=clock();
            time_move+=(double)(End-start)/CLOCKS_PER_SEC;
            losing(x,y);}/**cell contains a mine**/
        else {if(myboard[x][y]==0 && gameboard[x][y]!='F'){open(x,y);
        End=clock();
       time_move+=(double)(End-start)/CLOCKS_PER_SEC;
        print_gameborad();}}/**empty cell**/
        break;
     default: printf("Enter a valid operation\n");
     }
     win();
     play();
     }


     void print_gameborad(){
         int i=0,j=0;
         system("cls");
         /**printing number of columns**/
         for(j=0;j<numCol+1;j++){
            if(j==0){printf("  \t");}
            else{printf("%C \t",j+48);}
            }printf("\n\n");
            /**printing the game board and the number of rows**/
         for(i=1;i<numRow+1;i++){
            for(j=0;j<numCol+1;j++){
                if(j==0){printf("%C \t",i+48);}
                else{printf("%c \t",gameboard[i][j]);}
                }
                printf("\n\n");}
        print_detail();
          saveGame();
     }
     /**if an empty cell is opened, all empty cells around it should be opened
     until it reaches a number or the borders of the board**/
     void open(int x ,int y){
   if(x<1 || x>numRow || y<1 || y>numCol){/**stop when a border is reached**/
   return ;
   }
   else{ /**checking if the cell is closed and empty otherwise it's already visited**/
    if(gameboard[x][y]=='X' && myboard[x][y]==0){
     gameboard[x][y]=' ';
    open(x-1,y);
    open(x,y-1);
    open(x+1,y);
    open(x,y+1);
    open(x+1,y+1);
    open(x-1,y-1);
    open(x-1,y+1);
    open(x+1,y-1);
   }
   if(gameboard[x][y]=='X'  && myboard[x][y]>0){ /**once you reach a number open the cell and stop the recursion**/
    gameboard[x][y]=myboard[x][y]+48;
    return;
   }

   }

}
    /**checking win**/
    void win(){
        int i,j,flag; i=j=flag=0;
        for(i=1;i<=numRow;i++){
            for(j=1;j<=numCol;j++){
                if(myboard[i][j]>0 ){
                    if(gameboard[i][j]!=myboard[i][j]+48){flag=1;}
                }
               else { if(myboard[i][j]==0 &&gameboard[i][j]!=' ' ){flag=1;}}
            }
        }
        if(flag==0){
                for(i=1;i<=numRow;i++){
                    for(j=1;j<=numCol;j++){
                        if(myboard[i][j]==-1){gameboard[i][j]='F';}
                    }
                }
                print_gameborad();
                remove_file();   ///remove the saved game
                printf("you Win\n");
                List_players();
               printf("if you want to play again Enter (Y) or press any key to exit:\n");
                char c; c=getch();
                printf("%c",c);
               if(c=='Y'){
                num_move=0;num_flag=0;num_question=0;
                system("cls");
                main_menu();
               }
               else exit(0);
                }

    }
    void losing(int x,int y){
        int i,j; i=j=0;
        for(i=1;i<numRow+1;i++){
            for(j=1;j<numCol+1;j++){
                if(myboard[i][j]>0){
            gameboard[i][j]=myboard[i][j]+48;
            }
           else if(myboard[i][j]==0){gameboard[i][j]=' ';}
           else if(myboard[i][j]==-1 && gameboard[i][j]=='F'){gameboard[i][j]='*';}
           else if(myboard[i][j]==-1 && gameboard[i][j]!='F'){gameboard[i][j]='M';}

            }
        }
        gameboard[x][y]='!';
        print_gameborad();
        printf("you Lose\n");
       remove_file();       ///remove the game that was saved in the file
        printf("if you want to play again Enter (Y) or press any key to exit:\n");
         char c; c=getch(); printf("%c",c);
               if(c=='Y'){
                num_move=0;num_flag=0;num_question=0;
                system("cls");
                main_menu();
               }
               else exit(0);
    }
    void openedCell(int x, int y){
        int i,j,count; i=j=count=0;
        for(i=x-1;i<=x+1;i++){
            for(j=y-1;j<=y+1;j++){
                if(gameboard[i][j]=='F'){count=count+1;}
            }
        }
        if(myboard[x][y]==count){
            for(i=x-1;i<=x+1;i++){
            for(j=y-1;j<=y+1;j++){
                    if(gameboard[i][j]!='F'){
                        if( myboard[i][j]>0 ){
                            gameboard[i][j]=myboard[i][j]+48;
                        }
                        else if(myboard[i][j]==0){open(i,j);}
                        else {if(myboard[i][j]==-1){losing(i,j);}}
                    }
                }
            }
        }
    }

int player_detail()
{
    int score=((pow(numRow,4))*(pow(numCol,4)))/(num_move*time_move);
    return score;
}

void List_players()
{
    int i;
   char name[30],temp1[30];
    player List[50];
   int score=player_detail();
    int j,index=-1,temp,num_name;  ///index is the number of array list that has the same name
    printf("Enter your name\n");
    scanf("%[^\n]s",name);
    for(i=0; name[i]!='\0'; i++)
    {
        if((name[i]>='A')&&(name[i]<='Z'))
        {
            char k=name[i];
            name[i]='a'+(k-'A');
        }
      num_name=i+2;
    }
    for(i=0;name[i]!='\0';i++){
    if(name[i]==' '){
      name[i]='_';
    }
  }

    FILE*users;
 users=fopen("users.txt","r");
 if (users == NULL)
    {
  users=fopen("users.txt","w");
   fprintf(users,"%s %d\n",name,score);
    return ;
    }

 for(i=0; i<50; i++)
    {
        List[i].score=0;
    }


        if(!feof(users))
    {
        for(i=0; i<50; i++)
        {
          fscanf(users,"%s %d\n",&List[i].name,&List[i].score);
        }
    }
   int k=0;
   while(List[k].score!=0){
    k++;
   }
 int index_list=k;
    fclose(users);
    for(j=0; j<index_list; j++)
    {
    if(strcmp(name,List[j].name)==0){
           index=j;
         break;
    }
    }///if the player is found add the new score to the previous one
if(index!=-1){
 List[index].score=List[index].score+score;
 /**arrange scores and names**/
for(i=0;i<index_list;i++){
    for(j=i+1;j<index_list;j++){
       if(List[i].score<List[j].score){
        temp=List[i].score;
        List[i].score=List[j].score;
        List[j].score=temp;
       strcpy(temp1,List[i].name);
       strcpy(List[i].name,List[j].name);
       strcpy(List[j].name,temp1);
       }
    }
 }
users=fopen("users.txt","w");
 for(i=0;i<index_list;i++){
   fprintf(users,"%s %d\n",List[i].name,List[i].score);
 }
 fclose(users);
}
 else
 {
  List[index_list].score=score;
  strcpy(List[index_list].name,name);
/**arrange scores and names**/
for(i=0;i<index_list+1;i++){
    for(j=i+1;j<index_list+1;j++){
       if(List[i].score<List[j].score){
        temp=List[i].score;
        List[i].score=List[j].score;
        List[j].score=temp;
       strcpy(temp1,List[i].name);
       strcpy(List[i].name,List[j].name);
       strcpy(List[j].name,temp1);
       }
    }
 }
 users=fopen("users.txt","w");
 for(i=0;i<index_list+1;i++){
   fprintf(users,"%s %d\n",List[i].name,List[i].score);
 }
 fclose(users);


 }
}

void load_myboard()
{
   int i,j;
    FILE*save1;
    save1=fopen("save1.txt","r");
   if(save1 == NULL){
     return ;
    }

    fscanf(save1,"%d %d\n",&numRow,&numCol);
    while(!feof(save1))
    {
        for(i=0; i<numRow+1; i++)
        {
            for(j=0; j<numCol+1; j++)
            {
                if((i==0)&&(j==0))
                {
                    fscanf(save1,"   \n%d ",&myboard[i][j]);
                }
                else
                {
                    fscanf(save1,"%d ",&myboard[i][j]);
                }
            }
          fscanf(save1,"\n");
        }
    }
    fclose(save1);

}
void load_gameboard()
{
    int i,j;
  char game_file[32][32];
    FILE*save2;
    save2=fopen("save2.txt","r");
    if(save2==NULL){
     return ;
    }
    fscanf(save2,"%d %d\n",&numRow,&numCol);
    while(!feof(save2))
    {
        for(i=0; i<numRow+1; i++)
        {
            for(j=0; j<numCol+1; j++)
            {
                if((i==0)&&(j==0))
                {
                    fscanf(save2,"   \n%c ",&game_file[i][j]);
                }
                else
                {
                    fscanf(save2,"%c ",&game_file[i][j]);
                }
            }
          fscanf(save2,"\n");
        }
    }

    fclose(save2);
   for(i=0;i<numRow+1;i++){
  for(j=0;j<numCol+1;j++){
    if(game_file[i][j]==0+48){
      gameboard[i][j]=' ';
    }
   else {
    gameboard[i][j]=game_file[i][j];
   }
  }
}


}

void load_detail(){
FILE*save3;
save3=fopen("save3.txt","r");
if(save3==NULL){
    printf("the file does not Exist\n");
    main_menu();
    }
else{
if(isEmpty(save3)==0){
   printf("there is no saved game \n");
 main_menu();
}
else {
if(!feof(save3)){
   fscanf(save3,"%d\n",&num_move);
   fscanf(save3,"%d\n",&num_flag);
   fscanf(save3,"%d\n",&num_question);
   fscanf(save3,"%d\n",&time_move);
}
fclose(save3);
}
}
}

void remove_file1()
{
    FILE *save1;
  save1=fopen("save1.txt","w");
   int remove(const char *save1);
}
void remove_file2()
{
    FILE *save2;
  save2=fopen("save2.txt","w");
   int remove(const char *save2);
}
void remove_file3()
{
    FILE *save3;
  save3=fopen("save3.txt","w");
   int remove(const char *save3);
}

