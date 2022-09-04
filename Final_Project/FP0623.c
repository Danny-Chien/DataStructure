#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <string.h>
#include <time.h>

#define checkerboardLength  9
#define checkerboardWidth  9
#define MaxshapeLength 5
#define MaxshapeWidth 5
#define ScoreBoardLength 5
#define ScoreBoardWidth 4
#define ShapeNumber 3
#define ScoreNumber 4
#define BlockNumber 9

void Initialization();//temp初始化
void Boardinitialization();//棋盤初始化
void Display();//顯示棋盤
void PlayerSelectArea();//顯示方塊選擇區
void ShapeKind(int number);//選擇方塊種類
void Copy();//將temp的資料複製到選擇區
bool DetermineIfExist(int choosenumber);  //判斷所選的方塊是否還存在 
bool DetermineIfCorrect(int choosenumber, char *where); //判斷是否能放入 
void PutIn(int choosenumber, char *where); //將選擇的方塊放入board且消除選擇的方塊
bool IfEliminate();    //判斷是否可消除
void ExecuteEliminate();  //執行消除行為 
void Generate();    /* Generate the random shape */
void Scoreboard(int Score);    //input the score and show it
void ScoreCopy(int number,int ScoreCount);
bool CheckInsert(int choosenumber);
bool Checklose();    /* check whether lose or not */

//有在想要不要2合1，但覺得分開比較好懂
struct Content{
    bool isOccupied;
    wchar_t *FillUpSign; 
};
struct ChooseShape{
    bool isChoose;
    wchar_t *chooseshape;
};
struct Block9Eliminate{
	bool ifeliminate;
	int row,column;
};

struct Content checkerboard[checkerboardLength][checkerboardWidth];
struct ChooseShape playshape[ShapeNumber][MaxshapeLength][MaxshapeWidth];
struct ChooseShape temp[MaxshapeLength][MaxshapeWidth];    //用temp陣列暫時記載選擇的形狀
struct ChooseShape scoreboard[ScoreNumber][ScoreBoardLength][ScoreBoardWidth];
struct ChooseShape scoretemp[ScoreBoardLength][ScoreBoardWidth];    //用scoretemp陣列暫時記著該number的形狀 
struct Block9Eliminate BlockEliminate[BlockNumber];   //判斷每個3*3是否需消除
bool IfRowEliminate[9], IfColumnEliminate[9];    //判斷每個Row或Column是否需消除 
char boardLength[checkerboardLength] = { 'a','b','c','d','e','f','g','h','i'};//棋盤下標
int Count = 0;
int GameScore = 0;    //遊戲總分的變數 
int Combo = 0;     //遊戲的combo 


int main(void)
{
    int choosenumber,flag = 0;
    char where[3];
    Boardinitialization();//棋盤初始化
    Initialization();
    while(1)
    {    
        Generate(); /* Generate the three random shape and show them */
	    int PutBlockCount = 0;
	    while(PutBlockCount < 3)
		{
            if(flag == 0){
                Scoreboard(GameScore);  // input score and show it
                Display();   // show the board
                PlayerSelectArea();  // show the block
            }
			printf("please choose number of block: ");
			scanf("%d", &choosenumber);
			if( choosenumber > 3 || choosenumber < 1 )    //判斷選擇是否在1~3 
			{
				printf("please input 1~3 .\n");
                flag = 1;
				continue;
			}
			
			if( !(DetermineIfExist(choosenumber)) )    //如果所選不存在則重選 
			{
				printf("Block %d don't exist. please choose other block.\n",choosenumber);
                flag = 1;
				continue;
			}
			
			printf("please choose where you want to input: ");
			scanf("%s", where);
			if( !( ('a'<=(*(where+0)) && (*(where+0))<='i' ) && ( '0'<=(*(where+1)) && (*(where+1))<='8' ) ) )   //判斷where格式是否有誤 
			{
				printf("please input a1 or d8.......\n");
                flag = 1;
				continue;
			}
			
			if( DetermineIfCorrect(choosenumber,where) )  //如果能放入則放入 
			{
				PutIn(choosenumber,where);   //放入方塊至棋盤上 
				PutBlockCount++;
				if( IfEliminate() )   //先判斷是否有消除的部分 
					ExecuteEliminate();  //執行消除行為
				else
					Combo = 0;   //若無消除行為則combo歸零 
				system("clear");
				if( Combo )
				{
					printf("!!!!!!!!!!!!!!!!!!!  Combo*%d  !!!!!!!!!!!!!!!!!!!\n\n",Combo);
				} 
					
				if(Checklose(choosenumber))
                {
                    Scoreboard(GameScore);  // input score and show it
                    Display();   // show the board
                    PlayerSelectArea();  // show the block
                    printf("You lose!!!\n");
                    return 0;
                } 
                flag = 0;
			}
			else
			{
				printf("Block can't put in. Please choose again.\n");
                flag = 1;
			}
		}   /* End of while(PutBlockCount < 3) */
		system("clear");
		PutBlockCount=0;
	}    /* End of while(1) */
    return 0;  
}

void Boardinitialization()    //棋盤初始化 -->three playshape and checkerboark 清空 
{
	int i, j, x, y;
    for(i = 0; i < checkerboardLength; i++)//棋盤初始化
    {
        for(j = 0; j < checkerboardWidth; j++)
        {
            checkerboard[i][j].isOccupied = false; 
            checkerboard[i][j].FillUpSign = L"  ";
        }
    }

    for(x = 0; x < MaxshapeLength; x++)//三個方塊陣列初始化
    {
        for(y = 0; y < MaxshapeWidth; y++)
        {
            playshape[0][x][y].chooseshape = L"  "; 
            playshape[1][x][y].chooseshape = L"  ";
            playshape[2][x][y].chooseshape = L"  ";
            playshape[0][x][y].isChoose = false; 
            playshape[1][x][y].isChoose = false;
            playshape[2][x][y].isChoose = false;
        }
    }
}

void Initialization()    //temp初始化 -->temp清空 
{    
	int x, y;
    for(x = 0; x < MaxshapeLength; x++)
    {
        for(y = 0; y < MaxshapeWidth; y++)
        {
            temp[x][y].chooseshape = L"  "; 
            temp[x][y].isChoose = false; 
        }
    }

    for(int i = 0; i < ScoreBoardLength;i++)
    {
        int scorenumber = 0;
        while(scorenumber < 4)
        {
            for(int j = 0; j < ScoreBoardWidth; j++)
            {
                scoreboard[scorenumber][i][j].chooseshape = L"  ";
                scoreboard[scorenumber][i][j].isChoose = false;
            }
            scorenumber++;
        }
    }

}

void Display()   //顯示棋盤 
{
    int i, j, k;
    for( k = 0; k < checkerboardLength; k++)
    {
	    printf("    ");
	    for (i = 0; i < 45; i++)
        {
            printf("-");//上邊框
        } 
        printf("\n");
		printf("  %d", k);
	    
	    for (j = 0; j < checkerboardWidth; j++)
        {
            //if內為棋盤變色部分
            if(checkerboard[k][j].isOccupied)
            	printf("| \033[44m%ls\033[0m ",checkerboard[k][j].FillUpSign);      //Bule
            else if((k > 2 && k < 6 && j < 3) || (j > 2 && j < 6 && k < 3) || (k > 2 && k < 6 && j > 5) || (j > 2 && j < 6 && k > 5))
                printf("| \033[43m%ls\033[0m ",checkerboard[k][j].FillUpSign);      //Yellow
            else
                printf("| \033[47m%ls\033[0m ",checkerboard[k][j].FillUpSign);      //White 
        }
	    printf("|\n");
    }
    printf("    ");
    for (i = 0; i < 45; i++){
		printf("-");
	}	    //下邊框
	printf(("\n"));
    printf("  ");
    for( i = 0; i < checkerboardWidth; i++){
    	printf("   %c ", boardLength[i]);
	}
	printf("\n\n"); //下標
} 

void PlayerSelectArea()   //顯示方塊選擇區
{
    int x, y, z;
    for (z = 0; z < 75; z++)//上邊框
    {
        if(z%25 == 0) printf("     ");  //一個*的陣列要用25個-，故每25個多一個空格
        else printf("-");
    } 
    printf(("\n"));
    for( x = 0; x < MaxshapeLength; x++)
    {	   
        int shapeNumber = 0;
        while(shapeNumber < 3)
        {
            if(x == 0 && shapeNumber == 0) printf(" 1.");
            else if(x == 0 && shapeNumber == 1) printf(" 2.");
            else if(x == 0 && shapeNumber == 2) printf(" 3.");
            else printf("   ");
            for (y = 0; y < MaxshapeWidth; y++)//編號1的5*5形狀選擇區
            {
                if(playshape[shapeNumber][x][y].isChoose == true)   //被選中的陣列位置旗標為true，則呈現不同顏色
                    {printf("| \033[44;30m%ls\033[0m ", playshape[shapeNumber][x][y].chooseshape);}    //藍色 
                else
                    {printf("| \033[40;34m%ls\033[0m ", playshape[shapeNumber][x][y].chooseshape);}    //黑色 
            }
            printf("|");
            shapeNumber++;            
        }
            printf("\n");
            printf("    -------------------------    -------------------------    -------------------------    \n");

    }
    printf(("\n"));   
}

void ShapeKind(int number)    //選擇方塊種類
{    
    temp[2][2].chooseshape = L"C ";    
    switch (number)//每個號碼代表一種方塊形式，陣列位置根據被選到的形狀立起旗標，表示此陣列位置被使用
    {
        case 1:
            temp[2][2].isChoose = true;
            break;
        case 2:
            temp[2][2].isChoose = true;
            temp[2][3].isChoose = true;
            break;
        case 3:
            temp[2][2].isChoose = true;
            temp[3][2].isChoose = true;
            break;
        case 4:
            temp[2][2].isChoose = true;
            temp[1][3].isChoose = true;
            break;
        case 5:
            temp[2][2].isChoose = true;
            temp[1][1].isChoose = true;
            break;
        case 6:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[3][2].isChoose = true;
            break;
        case 7:
            temp[2][2].isChoose = true;
            temp[2][1].isChoose = true;
            temp[2][3].isChoose = true;
            break;
        case 8:
            temp[2][2].isChoose = true;
            temp[1][1].isChoose = true;
            temp[3][3].isChoose = true;
            break;
        case 9:
            temp[2][2].isChoose = true;
            temp[1][3].isChoose = true;
            temp[3][1].isChoose = true;
            break;
        case 10:
            temp[2][2].isChoose = true;
            temp[2][1].isChoose = true;
            temp[3][2].isChoose = true;
            break;
        case 11:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[2][3].isChoose = true;
            break;
        case 12:
            temp[2][2].isChoose = true;
            temp[3][2].isChoose = true;
            temp[2][3].isChoose = true;
            break;
        case 13:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[2][1].isChoose = true;
            break;
        case 14:
            temp[2][2].isChoose = true;
            temp[3][2].isChoose = true;
            temp[4][2].isChoose = true;
            temp[2][3].isChoose = true;
            break;
        case 15:
            temp[2][2].isChoose = true;
            temp[3][2].isChoose = true;
            temp[4][2].isChoose = true;
            temp[2][1].isChoose = true;
            break;
        case 16:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[0][2].isChoose = true;
            temp[2][1].isChoose = true;
            break;
        case 17:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[0][2].isChoose = true;
            temp[2][3].isChoose = true;
            break;
        case 18:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[0][2].isChoose = true;
            temp[3][2].isChoose = true;
            break;
        case 19:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[2][1].isChoose = true;
            temp[3][2].isChoose = true;
            break;
        case 20:
            temp[2][2].isChoose = true;
            temp[1][2].isChoose = true;
            temp[2][3].isChoose = true;
            temp[3][2].isChoose = true;
            break;
        case 21:
            temp[2][2].isChoose = true;
            temp[2][1].isChoose = true;
            temp[2][3].isChoose = true;
            temp[2][4].isChoose = true;
            break;
        case 22:
            temp[2][2].isChoose = true;
            temp[1][1].isChoose = true;
            temp[0][0].isChoose = true;
            temp[3][3].isChoose = true;
            break;
        case 23:
            temp[2][2].isChoose = true;
            temp[3][1].isChoose = true;
            temp[0][4].isChoose = true;
            temp[1][3].isChoose = true;
            break;
        case 24:
            temp[2][2].isChoose = true;
            temp[2][1].isChoose = true;
            temp[2][4].isChoose = true;
            temp[2][3].isChoose = true;
            temp[2][0].isChoose = true;
            break;
        case 25:
            temp[2][2].isChoose = true;
            temp[0][2].isChoose = true;        
            temp[1][2].isChoose = true;
            temp[3][2].isChoose = true;
            temp[4][2].isChoose = true;
            break;
        case 26:
            temp[2][2].isChoose = true;                
            temp[1][2].isChoose = true;
            temp[3][2].isChoose = true;
            temp[2][3].isChoose = true;
            temp[2][4].isChoose = true;
            break;
        case 27:
            temp[2][2].isChoose = true;                
            temp[1][2].isChoose = true;
            temp[3][2].isChoose = true;
            temp[2][0].isChoose = true;
            temp[2][1].isChoose = true;
            break;
        case 28:
            temp[2][2].isChoose = true;                
            temp[1][2].isChoose = true;
            temp[3][2].isChoose = true;
            temp[2][3].isChoose = true;
            temp[2][1].isChoose = true;
            break;
        default:
            break;
    }          
}

void Copy()  //將temp的資料複製到選擇區
{
	int x, y;
    for(x = 0; x < MaxshapeLength; x++)
    {
        for(y = 0; y < MaxshapeWidth; y++)
        {
            playshape[Count % 3][x][y].chooseshape = temp[x][y].chooseshape;     //Count %3取餘數設定資料 
            playshape[Count % 3][x][y].isChoose = temp[x][y].isChoose;
        }
    }
    Initialization();//再將temp初始化
    Count++;
}

bool DetermineIfExist(int choosenumber)  //判斷所選的方塊是否還存在 -->true為存在 
{
	int x, y;
    for(x = 0; x < MaxshapeLength; x++)
    {
        for(y = 0; y < MaxshapeWidth; y++)
        {
        	if(playshape[choosenumber-1][x][y].isChoose) return true;
        }
    }
    return false;
}

bool DetermineIfCorrect(int choosenumber, char *where) //判斷是否能放入 -->true為能放入 
{
	int x, y;
	int row, column;
    // column = where[0] - 97;
	// row = where[1] - 48;
	column = ( (*(where+0))-97 );
	row = ( (*(where+1))-48 );
    for(x = 0; x < MaxshapeLength; x++)
    {
        for(y = 0; y < MaxshapeWidth; y++)
        {
        	if(playshape[choosenumber-1][x][y].isChoose)
        	{
        		if( (row-2+x)<0 || 8<(row-2+x) || (column-2+y)<0 || 8<(column-2+y) )   
                    return false;  //放入的位置不再棋盤內 
        		if(checkerboard[row-2+x][column-2+y].isOccupied) return false;    //放入的位置已經有方塊 
			}
        } 
    }
	return true;
} 

void PutIn(int choosenumber, char *where) //將選擇的方塊放入board且消除選擇的方塊 
{
	int x, y;
	int row, column;
	int blockscore = 0; //計算此方塊的分數 
	column = ( (*(where+0))-97 );
	row = ( (*(where+1))-48 );
    for(x = 0; x < MaxshapeLength; x++)
    {
        for(y = 0; y < MaxshapeWidth; y++)
        {
        	if(playshape[choosenumber-1][x][y].isChoose)
        	{
        		checkerboard[row-2+x][column-2+y].isOccupied = true;    //放入棋盤  
        		playshape[choosenumber-1][x][y].isChoose = false;    //放入後消除選定方塊  
        		blockscore++;
			}
        }
    }
    GameScore += blockscore;
}

bool IfEliminate()    //判斷是否可消除
{
	int x, y,i ,j;
	bool eliminate;
	int BlockCount = 0;
	bool returnvalue = false;
	
	/* 處理9塊3*3方塊是否消除 */
	for(x = 0; x < checkerboardLength; x+=3 )
    {
        for(y = 0; y < checkerboardWidth; y+=3 )
        {
        	eliminate = false;
        	if ( checkerboard[x][y].isOccupied )  //分成9塊3*3的區域，先檢查是否該區塊的左上角被Occupy 
        	{
        		eliminate = true;
        		for(i = 0; i < 3; i++)
			    {
			        for(j = 0; j < 3; j++)
			        {
			        	if ( !(checkerboard[x+i][y+j].isOccupied) ) eliminate = false;  //該3*3方塊若不能消除則 --> eliminate=false
			        }
			    }
			}
			if (eliminate) returnvalue = true;
			BlockEliminate[BlockCount].ifeliminate = eliminate;
			BlockEliminate[BlockCount].row = x;
			BlockEliminate[BlockCount].column = y;
			BlockCount++;
        }
    }
    /* 處理9塊3*3方塊是否消除 */
    
    /* 處理每個row是否消除 */ 
    for( x = 0; x < checkerboardLength; x++)
	{
		eliminate = false;
    	if( checkerboard[x][0].isOccupied )   //判斷是否row的第一個被Occupy 
    	{
    		eliminate = true;
    		for(y = 0; y < checkerboardWidth; y++ )
    		{
    			if( !(checkerboard[x][y].isOccupied) ) eliminate = false;   //該row若不能消除則 --> eliminate=false 
			}
		}
		if (eliminate) returnvalue = true;
		IfRowEliminate[x] = eliminate;
	}
    /* 處理每個row是否消除 */
    
	/* 處理每個column是否消除 */ 
    for( y = 0; y < checkerboardWidth; y++)
	{
		eliminate = false;
    	if( checkerboard[0][y].isOccupied )   //判斷是否column的第一個被Occupy 
    	{
    		eliminate = true;
    		for(x = 0; x < checkerboardLength; x++ )
    		{
    			if( !(checkerboard[x][y].isOccupied) ) eliminate = false;   //該column若不能消除則 --> eliminate=false 
			}
		}
		if (eliminate) returnvalue = true;
		IfColumnEliminate[y] = eliminate;
	}
    /* 處理每個column是否消除 */
    
    return returnvalue;
}

void ExecuteEliminate()  //執行消除行為 
{
	int i, x, y;
	for( i = 0; i < 9; i++)
	{
		/* 處理3*3方塊的消除 */ 
		if( BlockEliminate[i].ifeliminate )
		{
			for(x = 0; x < 3; x++ )
		    {
		        for(y = 0; y < 3; y++ )
		        {
		        	checkerboard[ (BlockEliminate[i].row) + x ][ (BlockEliminate[i].column) + y ].isOccupied = false;  //消除該3*3方塊 
		        }
		    }
		    Combo++;
		    GameScore += (9 * Combo);
		}
		/* 處理3*3方塊的消除 */ 
		
		/* 處理每個row是否消除 */
		if( IfRowEliminate[i] )
		{
			for(y = 0; y < checkerboardWidth; y++ )
			{
				checkerboard[i][y].isOccupied = false;    //消除該row的方塊 
			}
			Combo++;
		    GameScore += (9 * Combo);
		} 
		/* 處理每個row是否消除 */
		
		/* 處理每個column是否消除 */
		if( IfColumnEliminate[i] )
		{
			for(x = 0; x < checkerboardLength; x++ )
			{
				checkerboard[x][i].isOccupied = false;    //消除該column的方塊 
			}
			Combo++;
		    GameScore += (9 * Combo);
		}
		/* 處理每個column是否消除 */
	}
} 

void Generate() /* Generate the random shape */
{
    int num[3];
    time_t t;
    srand((unsigned) time(&t));
    num[0] = rand() % 28 + 1;
    num[1] = rand() % 28 + 1;
    num[2] = rand() % 28 + 1;
    
    ShapeKind(num[0]);
    Copy();
    
    while( !CheckInsert(1))
        num[0] = rand() % 28 + 1;

    for(int i = 0; i < 3; i++){
        ShapeKind(num[i]);
        Copy();
    }
}

bool Checklose(int choosenumber)    /* check whether lose or not */
{
    int num[2];
    if(choosenumber == 1){
        num[0] = 2;
        num[1] = 3;
    } 
    else if(choosenumber == 2){
        num[0] = 1;
        num[1] = 3;
    }
    else{
        num[0] = 1;
        num[1] = 2;
    }
	
    if( DetermineIfExist(num[0]) && DetermineIfExist(num[1]) )
    {
        if( !CheckInsert(num[0]) && !CheckInsert(num[1]) )
            return true; 
    }    
    else if( DetermineIfExist(num[0]) && !DetermineIfExist(num[1]) )
    {
        if( !CheckInsert(num[0]) )
            return true;
    }
    else if( !DetermineIfExist(num[0]) && DetermineIfExist(num[1]) )
    {
        if( !CheckInsert(num[1]) )
            return true;
    }
    return false;  
}

bool CheckInsert(int choosenumber)
{
    int i,j;
    i = 0;
    j = 0;
    char from[3];
    from[0] = 'a';
    from[1] = '0';
    /* char array to string  */
    char* string;
    string = malloc(sizeof(from)+1);
    memset(&string[0], 0x00, sizeof(from)+1);
    memcpy(&string[0], &from[0], sizeof(from));

    while(!DetermineIfCorrect(choosenumber, string) && DetermineIfExist(choosenumber) ){
        if(j < checkerboardWidth)
            j++;
        else{
            i++;
            j = 0;
        }
        if(i == checkerboardLength){
            return false;   /* can't insert */
        }
        from[0] = 'a' + i;
        from[1] = '0' + j;
        memset(&string[0], 0x00, sizeof(from)+1);
        memcpy(&string[0], &from[0], sizeof(from));
    } 
    return true;
}

void  Scoreboard(int Score)  //input the score and show it
{
    int thousand = 0,hundred = 0,tens = 0,digits = 0,remainder = 0;

    thousand = Score/1000; 
    remainder = Score%1000;
    hundred = remainder/100;
    remainder = remainder%100;
    tens = remainder/10;
    digits = remainder%10;

    ScoreCopy(thousand,0);ScoreCopy(hundred,1);ScoreCopy(tens,2);ScoreCopy(digits,3);

    for(int i = 0; i < ScoreBoardLength;i++)
    {
        int scorenumber = 0;
        while(scorenumber < 4)
        {
            for(int j = 0; j < ScoreBoardWidth; j++)
            {
                if(scoreboard[scorenumber][i][j].isChoose == true)   //被選中的陣列位置旗標為true，則呈現不同顏色
                    {printf("\033[41;30m%ls\033[0m ", scoreboard[scorenumber][i][j].chooseshape);}    //紅色 
                else
                    {printf("\033[40;34m%ls\033[0m ", scoreboard[scorenumber][i][j].chooseshape);}    //黑色
            }
            scorenumber++;
        }
        printf("\n");
    }
    printf("\n");
    
}

void ScoreCopy(int number,int ScoreCount) //ScoreCount為數字對應的旗標
{
    switch(number)
    {
        case 0:
            scoretemp[0][0].isChoose = true;
            scoretemp[1][0].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[3][0].isChoose = true;
            scoretemp[4][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[4][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[1][2].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            break;
        case 1:
            scoretemp[0][1].isChoose = true;
            scoretemp[1][1].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[3][1].isChoose = true;
            scoretemp[4][1].isChoose = true;
            break;
        case 2:
            scoretemp[0][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[1][2].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[3][0].isChoose = true;
            scoretemp[4][0].isChoose = true;
            scoretemp[4][1].isChoose = true;
            scoretemp[4][2].isChoose = true;
            break;
        case 3:            
            scoretemp[0][0].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[4][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[1][2].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            break;
        case 4:
            scoretemp[0][0].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[1][0].isChoose = true;
            scoretemp[1][2].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            break;
        case 5:
            scoretemp[0][0].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[4][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[1][0].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            break;
        case 6:
            scoretemp[0][0].isChoose = true;
            scoretemp[1][0].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[3][0].isChoose = true;
            scoretemp[4][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[4][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            break;
        case 7:
            scoretemp[0][0].isChoose = true;
            scoretemp[1][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[1][2].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            break;
        case 8:
            scoretemp[0][0].isChoose = true;
            scoretemp[1][0].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[3][0].isChoose = true;
            scoretemp[4][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[4][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            scoretemp[1][2].isChoose = true;
            break;
        case 9:
            scoretemp[0][0].isChoose = true;
            scoretemp[1][0].isChoose = true;
            scoretemp[2][0].isChoose = true;
            scoretemp[4][0].isChoose = true;
            scoretemp[0][1].isChoose = true;
            scoretemp[4][1].isChoose = true;
            scoretemp[0][2].isChoose = true;
            scoretemp[2][1].isChoose = true;
            scoretemp[2][2].isChoose = true;
            scoretemp[3][2].isChoose = true;
            scoretemp[4][2].isChoose = true;
            scoretemp[1][2].isChoose = true;
            break;
    }

    for(int i = 0; i < ScoreBoardLength; i++) //將數字旗標複製到計分板陣列上
    {
        for(int j = 0 ;j < ScoreBoardWidth; j++)
        {
            scoreboard[ScoreCount][i][j].isChoose = scoretemp[i][j].isChoose;
            scoretemp[i][j].isChoose = false;
        }
    }
}
