#include <iostream>
#include <vector>

using namespace std;

#define INFINITY 1000

int check_end(vector<vector<char> > board);
void draw_board(vector<vector<char> > board);

class Node
{
public:


	int turn;
	int value;

	char piece;

	int bestX, bestY;

	vector<vector<char> > board;

	Node(vector<vector<char> > board, int turn)
	{
		bestX = 0;
		bestY = 0;

		if(turn%2 == 0)
		{
			value = -INFINITY;
			piece = 'X';
		}
		else
		{
			value = INFINITY;
			piece = 'O';
		}

		this->board = board;
		this->turn = turn;

		int boardValue = check_end(this->board);

		if(boardValue != 0 || turn == 9)
		{
			value = boardValue;
		}
		else
		{
			for(int i = 0; i < 3; ++i)
			{
				for(int j = 0; j < 3; ++j)
				{
					if(board[i][j] == ' ')
					{
						vector<vector<char> > newBoard = this->board;
						newBoard[i][j] = piece;

						Node child(newBoard,turn+1);

						if(turn%2 == 0)
						{
							if(child.value > this->value)
							{
								this->value = child.value;
								bestX = j+1;
								bestY = i+1;
							}
						}
						else
						{
							if(child.value < this->value)
							{
								this->value = child.value;
								bestX = j+1;
								bestY = i+1;
							}
						}	
					}
				}
			}
		}
	}
};

void draw_board(vector<vector<char> > board)
{
	
	cout << "1 2 3" << endl << endl;

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			cout << board[i][j];
			if(j < 2)
				cout << '|';
		}

		cout << " " << i + 1 << endl;

		if(i < 2)
			cout  << "-----";
		cout << endl;

	}

	for(int i = 0; i < 4; ++i)
	{
		cout << endl;
	}
}

int check_end(vector<vector<char> > board)
{
	for(int i = 0; i < 3; ++i)
	{
		if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
		{
			return ((float)board[i][2] - 83.5f)/4.5f;
		}
		if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] != ' ')
		{
			return ((float)board[2][i] - 83.5f)/4.5f;
		}
	}

	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
	{
		return  ((float)board[2][2] - 83.5f)/4.5f;
	}
	if(board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[0][2] != ' ')
	{
		return  ((float)board[0][2] - 83.5f)/4.5f;
	}
	return 0;
}

int main()
{

	vector<char> line(3,' ');
	vector<vector<char> > board(3,line);

	int turn = 0;

	int gameValue = 3;
	while(gameValue > 2)
	{	
		draw_board(board);

		int x = 0;
		int y = 0;

		char piece = 'X';

		if(turn%2 == 0)
		{
			bool validInput = false;

			while(!validInput)
			{
				cin >> x;
				cin >> y;

				if(x < 1 || x > 3 || y < 1 || y > 3 || board[y-1][x-1] != ' ')
				{
					cout << "Invalid input.\n";
				}
				else
				{
					validInput = true;
				}


			}
		}	
		else
		{
			piece = 'O';
			Node root(board,turn);
			x = root.bestX;
			y = root.bestY;
		}

		cout << endl << endl;

		board[y-1][x-1] = piece;

		turn++;
		
		gameValue = check_end(board);
		if(gameValue == 0 && turn < 9)
			gameValue = 5;
	}

	draw_board(board);

	switch(gameValue)
	{
		case -1: cout << "O wins!\n"; break;
		case 0: cout << "Cat's game!\n"; break;
		case 1: cout << "X wins\n"; break;
	}

	return 0;
}
