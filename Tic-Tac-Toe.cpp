#include<iostream>
#include<random>
#include<algorithm>
#include<time.h>
#include<limits.h>
using namespace std;

#define Com 0
#define Hum 1
#define len 3

//Computer X
//Human O

vector<int> emptycells;


void printboard(char board[][len])
{
    cout<<"\n\n";
    cout<<"\t\t\t  "<< board[0][0] <<"|  "<< board[0][1] <<"  |   "<< board[0][2] <<"       \n";
    cout<<"\t\t\t--------------\n";
    cout<<"\t\t\t  "<< board[1][0] <<"|  "<< board[1][1] <<"  |   "<< board[1][2] <<"       \n";
    cout<<"\t\t\t--------------\n";
    cout<<"\t\t\t  "<< board[2][0] <<"|  "<< board[2][1] <<"  |   "<< board[2][2] <<"       \n";

    return;
}

void showInstructions()
{
    printf("\t\t\t  Tic-Tac-Toe Game\n\n");
    printf("Choose a cell numbered from 1 to 9 as below"
            " and play\n\n");
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");  
    printf("\t\t\t  1 | 2  | 3  \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t  4 | 5  | 6  \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t  7 | 8  | 9  \n\n");
      
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
  
    return;
}

vector<int>& init(char board[][len],vector<int> &emptycells)
{
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<len;j++)
        {
            board[i][j]=' ';
        }
    }

    for(int i=1;i<=len*len;i++)
    {
        emptycells.push_back(i);
    }
    return emptycells;
}

bool row_win(char board[][len])
{
    for(int i=0;i<len;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!=' ')
        {
            return true;
        }
    }
    return false;
}

bool col_win(char board[][len])
{
    for(int i=0;i<len;i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!=' ')
        {
            return true;
        }
    }
    return false;
}

bool diag_win(char board[][len])
{
    if((board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!=' ') || (board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!=' '))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool gameover(char board[][len])
{
    return (diag_win(board) || row_win(board) || col_win(board));
}

bool isMovesLeft(char board[][len])
{
    for (int i = 0; i<len; i++){
        for (int j = 0; j<len; j++){
            if (board[i][j]==' ')
                return true;
    	}
    }
    return false;
}
void winner(int turn)
{
	if(turn==0)
	{
		cout<<"\nComputer has Won....   :(  \n";
	}
	else
	{
		cout<<"\nYou have Won....   :D  \n";
	}
}

int checkwinner(char board[][len])
{
	for(int i=0;i<len;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
        {
        	if(board[i][0]=='X')
            return 10;
            else if(board[i][0]=='O')
            return -10;
        }
    }
    
    for(int i=0;i<len;i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i])
        {
        	if(board[0][i]=='X')
            return 10;
            else if(board[0][i]=='O')
            return -10;
        }
    }
    
    if((board[0][0]==board[1][1] && board[1][1]==board[2][2]))
    {
        if(board[0][0]=='X')
    	return 10;
    	else if(board[0][0]=='O')
    	return -10;
    }
    if((board[0][2]==board[1][1] && board[1][1]==board[2][0]))
    {
    	if(board[0][2]=='X')
    	return 10;
    	else if(board[0][2]=='O')
    	return -10;
	}
	
	return 0; //in case of draw
}

int minimax(char board[][len],int depth,bool ismaximize)
{
	//Base Case
	int score=checkwinner(board);
	if(score==10)
	return (score-depth);
	if(score==-10)
	return (score+depth);
	if(!isMovesLeft(board))
	return 0;
	
	if(ismaximize)
	{
		int bestscore=INT_MIN;
		
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
			{
				if(board[i][j]==' ')
				{
					board[i][j]='X';
					bestscore=max(bestscore,minimax(board,depth+1,!ismaximize));
					board[i][j]=' ';
				}
			}
		}
		return bestscore;
	}
	else{
		int bestscore=INT_MAX;
		
		for(int i=0;i<len;i++)
		{
			for(int j=0;j<len;j++)
			{
				if(board[i][j]==' ')
				{
					board[i][j]='O';
					bestscore=min(bestscore,minimax(board,depth+1,!ismaximize));
					board[i][j]=' ';
				}
			}
		}
		return bestscore;
	}
}
void playgame(int turn)
{
    char board[len][len];
    emptycells=init(board,emptycells);
    

    while(!gameover(board) && emptycells.size()!=0)
    {
        if(turn==Com)
    	{
    		cout<<"\nComputers turn......\n";
    		int best=INT_MIN;
    		int row=-1;
    		int col=-1;
    		for(int i=0;i<len;i++)
    		{
    			for(int j=0;j<len;j++)
    			{
    				if(board[i][j]==' ')  //if cell is empty
    				{
    					board[i][j]='X';
    					int curr=minimax(board,0,false);
    					board[i][j]=' ';
    					
    					if(curr>best)
    					{
    						best=curr;
    						row=i;
    						col=j;
						}
					}
				}
			}
        	int pos=(row*len)+col+1;
        	cout<<"\n Computer put X in cell "<<pos<<endl;
            

            board[row][col]='X';
            printboard(board);
            emptycells.erase(find(emptycells.begin(),emptycells.end(),pos));
			turn=Hum;
        }
        else if(turn==Hum)
        {
            bool flag=false;
            while(!flag){
            	cout<<"\nYour turn......\n";
            	
            	
	            cout<<"Available cells are :-\n";
	            for(int i=0;i<emptycells.size()-1;i++)
	            {
	                cout<<emptycells[i]<<" , ";
	            }
	            cout<<emptycells[emptycells.size()-1]<<endl;
	            cout<<"Enter the cell number :- \n";
	            int pos;
	            cin>>pos;
				
	            if(std::find(emptycells.begin(),emptycells.end(),pos)!=emptycells.end())
	            {
	                flag=true;
	                int x=pos/len;
	                int y=pos%len;
	
	                board[x][y-1]='O';
	                printboard(board);
	
	                emptycells.erase(find(emptycells.begin(),emptycells.end(),pos));
	            }
            }
			turn=Com;
        }
    }
    
    if(!gameover(board) && emptycells.size()==0){
    	cout<<"\nIts a draw....   -_-\n";
    	return;
	}
	else
	{
		if(turn==Com)
			turn=Hum;
		else if(turn==Hum)
			turn=Com;
		winner(turn);
		return;
	}
}

int main()
{
	showInstructions();
    playgame(Hum);
}
