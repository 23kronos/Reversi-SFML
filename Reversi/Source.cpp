/*
** ==========================================
** Reversi, written in C++ and Assembly
** Authors: Jared Sanders, David Paller
** Revision Date: Aprill 17th, 2017
**===========================================
*/

#include <SFML/Graphics.hpp> // Render window for graphics
#include <sstream> // For displaying the score in the window
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector> // Used for default board state

/*
** ============================================================
** draw the appropriate banner for the winning player, 
** or a draw
** @params: Window, player
** @return: none
** ============================================================
*/

void drawWinScene(sf::RenderWindow &window, int player)
{
	// The below sets up our text variable
	// the font, size, and location, and then
	// acts accordingly

	sf::Text text;
	sf::Font font;
	font.loadFromFile("Cut the crap.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(40);
	text.setPosition(100, 100);

	if (player == 1)
	{
		text.setString("White wins");
	}
	else if (player == 2)
	{
		text.setString("Black wins");
	}
	else
		text.setString("It's a draw!");

	window.draw(text);
}

/*
** ============================================================
** Count the pieces for each player
** @params: board, player
** @return: integer representing number of pieces
** ============================================================
*/

int score(std::vector<std::vector<int>> &board, int player) {
	int sum = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == player)
			{
				_asm {
					inc sum // increment sum counter for each piece flipped
							// changes dynamically as the game goes on
				}
			}
		}
	}
	return sum;
}

/*
** ============================================================
** Check if game is over, and if it is, who won, or if it was
** a draw
** @params: board, player
** @return: integer representing winner, or draw
** ============================================================
*/

int check_win(std::vector<std::vector<int>> &board, int side)
{
	// Calculate our score
	// If the scores added together,
	// are greater than our boards max size, 
	// the game is over, and we return the victors number

	int blackScore = score(board, 2);
	int whiteScore = score(board, 1);
	if (blackScore + whiteScore == board.size() * board.size()) {
		if (blackScore > whiteScore)
		{
			return 2;
		}
		else if (whiteScore > blackScore)
		{
			return 1;
		}
		else
			return 3;
	}
	return 0;
}

/*
** ============================================================
** Initialize the board, and setup our initial pieces
** @params: Window for drawing
** @return: none
** ============================================================
*/

void drawBoard(sf::RenderWindow &window)
{
	//clear the window to black
	window.clear(sf::Color::Color(29, 90, 21, 0.6));

	//draw horizontal lines
	sf::RectangleShape line1(sf::Vector2f(400, 2));
	line1.setFillColor(sf::Color::Black);
	line1.setPosition(0, 50);

	//Set below lines to same as the previous line, making sure
	//to adjust the positions to the new position
	sf::RectangleShape line2 = line1;
	line2.setPosition(0, 100);

	sf::RectangleShape line3 = line2;
	line3.setPosition(0, 150);

	sf::RectangleShape line4 = line3;
	line4.setPosition(0, 200);

	sf::RectangleShape line5 = line4;
	line5.setPosition(0, 250);

	sf::RectangleShape line6 = line5;
	line6.setPosition(0, 300);

	sf::RectangleShape line7 = line6;
	line7.setPosition(0, 350);

	sf::RectangleShape line8 = line7;
	line7.setPosition(0, 400);
	

	//draw vertical lines;
	sf::RectangleShape line9(sf::Vector2f(2, 400));
	line9.setFillColor(sf::Color::Black);
	line9.setPosition(50, 0);

	//Set below lines to same as the previous line, making sure
	//to adjust the positions to the new position
	sf::RectangleShape line10 = line9;
	line10.setPosition(100, 0);

	sf::RectangleShape line11 = line10;
	line10.setPosition(150, 0);

	sf::RectangleShape line12 = line11;
	line12.setPosition(200, 0);

	sf::RectangleShape line13 = line12;
	line13.setPosition(250, 0);

	sf::RectangleShape line14 = line13;
	line14.setPosition(300, 0);

	sf::RectangleShape line15 = line14;
	line15.setPosition(350, 0);

	sf::RectangleShape line16 = line15;
	line16.setPosition(400, 0);

	// Actually draws the above lines
	window.draw(line1);
	window.draw(line2);
	window.draw(line3);
	window.draw(line4);
	window.draw(line5);
	window.draw(line6);
	window.draw(line7);
	window.draw(line8);
	window.draw(line9);
	window.draw(line10);
	window.draw(line11);
	window.draw(line12);
	window.draw(line13);
	window.draw(line14);
	window.draw(line15);
	window.draw(line16);
}

/*
** ============================================================
** Display the number of pieces for each player
** @params: board, window, player
** @return: none
** ============================================================
*/

void drawScore(std::vector<std::vector<int>> &board, 
	sf::RenderWindow &window, int player)
{
	// Display which side is which, followed by the scores of each dictated
	// by the for loops below this section
	sf::Text text;
	sf::Font font;
	font.loadFromFile("Cut the crap.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(30);
	text.setPosition(450, 100);
	text.setString("White: ");
	window.draw(text);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(30);
	text.setPosition(450, 250);
	text.setString("Black: ");
	window.draw(text);

	if (player == 1)
	{
		// This is straight from sfml's forum.
		// Don't know why we need a stringstream
		// but it was the only way to properly get a number to display
		int whiteScore = score(board, 1);
		std::stringstream ss;
		ss << whiteScore;
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(30);
		text.setPosition(500, 150);
		text.setString(ss.str().c_str());
		window.draw(text);
	}
	else if (player == 2)
	{
		//draw blacks score
		int blackScore = score(board, 2); // calculate blacks score
		std::stringstream ss;
		ss << blackScore;
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(30);
		text.setPosition(500, 300); // position on left side of board
		text.setString(ss.str().c_str());
		window.draw(text);
	}
}

/*
** ============================================================
** Draw our pieces, making sure to keep the pieces in the
** correct position
** @params: Window, player, x position, y position, board
** @return: none
** ============================================================
*/

void drawSlot(sf::RenderWindow &window, int player, int row, int col, 
	std::vector<std::vector<int>> &board)
{
	// We're either this player
	if (player == 1) //White
	{
			sf::CircleShape shape(20); //radius of 20
			shape.setFillColor(sf::Color::White);   //fill white
			shape.setOutlineThickness(1);
			shape.setOutlineColor(sf::Color::White); // white piece drawn white

			//center the piece based in each square
			//50 = width and height of each row, 5 helps center it
			shape.setPosition(5 + (50 * row), 5 + (50 * col));
			window.draw(shape);
	}
	// Else we are the other player
	else if (player == 2) //Black piece
	{
			sf::CircleShape shape(20); //radius of 20
			shape.setFillColor(sf::Color::Black);   //fill black
			shape.setOutlineThickness(1); 
			shape.setOutlineColor(sf::Color::Black); // black piece drawn black

			//center the piece based in each square
			//50 = width and height of each row, 5 helps center it
			shape.setPosition(5 + (50 * row), 5 + (50 * col));
			window.draw(shape);
	}

	// Call draw score to display score
	drawScore(board, window, player);
}

/*
** ============================================================
** Check if your move is legal, meaning you flip at least 1
** of your opponents pieces.
** @params: Board, row, col, player
** @return: Number of pieces flipped
** ============================================================
*/

int checkLegal(std::vector<std::vector<int>> &board, int row, int col, int player)
{
	// intialize variable of number of opp pieces flippd
	int flipped = 0;

	// if the space isn't empty, it's already illegal
	if (board[row][col] != 0)
		return 0;

	// Check surroundings to the East
	// default state to continue loop, break if changed
	int disc = -1; 
	for (int c = col + 1; c < 8 && board[row][c] != 0 && disc == -1; c++)
	{
		if (board[row][c] == player)
			disc = c; // found our piece, break the loop
	}

	// Found a city, so disc != -1, must be 2 spots away
	if (disc != -1 && disc > col + 1)
	{
		for (int c = col + 1; c < disc; c++)
		{
			// Flip all opp pieces found
			board[row][c] = player;
			__asm {
				inc flipped
			}
		}
	}

	// Check surroundings to the West
	// Reset default state, change to break
	disc = -1;
	for (int c = col - 1; c >= 0 && board[row][c] != 0 && disc == -1; c--)
	{
		if (board[row][c] == player)
			disc = c; // found our piece, break the loop
	}

	// Found opp piece, has to be 2 spaces away
	if (disc != -1 && disc < col - 1)
	{
		// Flip all opp pieces found
		for (int c = col - 1; c > disc; c--)
		{
			board[row][c] = player; // change to our piece
			__asm {
				inc flipped // increment number flipped
			}
		}
	}

	// Check pieces to the South
	// Reset default state, change to break loop
	disc = -1;
	for (int r = row - 1; r >= 0 && board[r][col] != 0 && disc == -1; r--)
	{
		if (board[r][col] == player)
			disc = r; // found our piece, stop this direction
	}

	// Found opp, must be 2 spots away
	if (disc != -1 && disc < row - 1)
	{
		// Flip all opp pieces found
		for (int r = row - 1; r > disc; r--)
		{
			board[r][col] = player; // set our piece
			__asm {
				inc flipped // increment number flipped
			}
		}
	}

	// Check pieces to the North
	// Reset default state, change to break loop
	disc = -1;
	for (int r = row + 1; r < 8 && board[r][col] != 0 && disc == -1; r++)
	{
		if (board[r][col] == player)
			disc = r; // found our piece, break
	}

	// Found opp, must be 2 spots away
	if (disc != -1 && disc > row + 1)
	{
		// Flip all opp pieces
		for (int r = row + 1; r < disc; r++)
		{
			board[r][col] = player; // place our piece
			__asm {
				inc flipped // increment number flipped
			}
		}
	}

	// Check pieces to the South West
	// Reset default state, change to break
	disc = -1;
	int c = col - 1; // col -1 = west, row -1 = south
	for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != 0 && disc == -1; r--)
	{
		
		if (board[r][c] == player)
			disc = r; // found our piece break this direction
		__asm {
			dec c // move west one more column if we haven't broken yet
		}
	}

	// Found opp, must be 2 spots away
	if (disc != -1 && disc < row - 1)
	{
		c = col - 1; // move west 1
		for (int r = row - 1; r > disc; r--)
		{
			// Flip all opp pieces found
			board[r][c] = player;
			__asm {
				inc flipped // num flipped +1
				dec c // keep moving west
			}
		}
	}

	// Check surroundings to the South East
	// Reset default state, change to break
	disc = -1;
	c = col + 1; //  1 column to right = east
	for (int r = row - 1; c < 8 && r >= 0 && board[r][c] != 0 && disc == -1; r--)
	{
		if (board[r][c] == player)
			disc = r; // found our piece. stop this direction
		__asm {
			inc c // if we haven't broken, keep going east
		}
	}

	// Found a city, must be 2 spots away
	if (disc != -1 && disc < row - 1) 
	{
		c = col + 1; // 1 col to right = east
		for (int r = row - 1; r > disc; r--)
		{
			// Flip all opp pieces found
			board[r][c] = player;
			__asm {
				inc flipped // number pieces flipped + 1
				inc c // inc column to keep checking this direction
			}
		}
	}

	// Check surroundings to the North West
	disc = -1; // default state to continue checking, or break if it's not -1
	c = col - 1; // move column left one = west
	for (int r = row + 1; c >= 0 && r < 8 && board[r][c] != 0 && disc == -1; r++)
	{
		if (board[r][c] == player)
			disc = r; // found our piece, break
		__asm{
			dec c
		}
	}

	// Found opp, must be 2 spots away
	if (disc != -1 && disc > row + 1)
	{
		c = col - 1; // move left one colum 
		for (int r = row + 1; r < disc; r++)
		{
			// Flip all opp pieces found
			board[r][c] = player;
			__asm {
				inc flipped // number pieces flipped + 1 for each piece
				dec c // keep going that direction
			}
		}
	}

	// Check surroundings to the North East
	// Reset default state, break if changed
	disc = -1;
	c = col + 1; // move one column right = east
	for (int r = row + 1; c < 8 && r < 8 && board[r][c] != 0 && disc == -1; r++)
	{
		// hit our piece. stop this direction
		if (board[r][c] == player)
			disc = r; // found our piece, break
		__asm {
			inc c // increment column to continue checking this direction, if we don't break
		}
	}

	// Found opp, must be 2 spots away
	if (disc != -1 && disc > row + 1)
	{
		c = col + 1; // still east
		for (int r = row + 1; r < disc; r++)
		{
			// Flip all opp pieces found
			board[r][c] = player;
			__asm {
				inc flipped // num flipped + 1
				inc c // move east 1 more
			}
		}
	}

	// No pieces flipped == invalid. 
	// Way to switch players if current player has no possible moves
	if (flipped == 0)
		board[row][col] = 0;

	return flipped;
}

/*
** ============================================================
** A lot of this can be written in ASM
** Make your selection, and prepare to move the troops
** @params: board, player, row, col
** @return: true if the mouse is clicked, false otherwise
** ============================================================
*/

bool handle_click(std::vector<std::vector<int>> &board, int &player, int row, int col)
{
	// Where clicked?
	// Set row and col to that to move soliders to
	int i, j, opponent;

	if (player == 1)
	{
		opponent = 2;
	}
	else
		opponent = 1;

	__asm {
		cmp row, 50 //if row < 50, i  = 0
		jl ifrow50
		jge elserow50
		ifrow50:
			mov dword ptr[i],0
			jmp endif
		elserow50: // else if row >= 50 && < 100 i =1
			cmp row, 100
			jl ifrow100
			jge elserow100
		ifrow100:
			mov dword ptr[i], 1
			jmp endif
		elserow100: // else if row >= 100 && row < 150 i = 2
			cmp row, 150
			jl ifrow150
			jge elserow150
		ifrow150: 
			mov dword ptr[i], 2
			jmp endif
		elserow150: // else if row >= 200 && row < 250 i = 3
			cmp row, 200
			jl ifrow200
			jge elserow200
		ifrow200:
			mov dword ptr[i], 3
			jmp endif
		elserow200: // else if row >= 250 && row < 300 i =4
			cmp row, 250
			jl ifrow250
			jge elserow250
		ifrow250:
			mov dword ptr[i], 4
			jmp endif
		elserow250: // else if row >=300 && < 350 i =5
			cmp row, 300
			jl ifrow300
			jge elserow300
		ifrow300:
			mov dword ptr[i], 5
			jmp endif
		elserow300: // else if row >=350 && < 400 i =5
			cmp row, 350
			jl ifrow350
			jge elserow350
		ifrow350:
			mov dword ptr [i], 6
			jmp endif
		elserow350: // else i = 7
			mov dword ptr[i], 7
			jmp endif
		endif : 
	}	

	__asm {
			cmp col, 50 // if col < 50 j = 0 
			jl col50
			jge else50

			col50:
				mov dword ptr[j],0
				jmp endcol
			else50: // else if col >= 50 && col < 100 j =1
				cmp col, 100
				jl col100
				jge else100
			col100:
				mov dword ptr[j],1
				jmp endcol
			else100: // else if col >= 100 && col < 150 j =2
				cmp col, 150
				jl col150
				jge else150
			col150:
				mov dword ptr[j],2
				jmp endcol
			else150: // else if col >= 150 && col < 200 j = 3
				cmp col, 200
				jl col200
				jmp else200
			col200:
				mov dword ptr[j],3
				jmp endcol
			else200: // else if col >= 200 && col < 250 j = 4
				cmp col, 250
				jl col250
				jge else250
			col250:
				mov dword ptr[j], 4
				jmp endcol
			else250: // else if col >= 250 && col < 300 j = 5
				cmp col, 300
				jl col300
				jge else300
			col300:
				mov dword ptr[j],5
				jmp endcol
			else300: // else if col >= 300 && col < 350 j = 6
				cmp col, 350
				jl col350
				jge else350
			col350:
				mov dword ptr[j],6
				jmp endcol
			else350: //else j =7
				mov dword ptr[j], 7
			endcol: // end asm
	}

	// Check if your move is valid
	// legal > 0 = valid, legal < 0 = invalid
	int legal = checkLegal(board, i, j, player);
	if (board[i][j] == 0)   // Emtpy location found
	{			
		// If your move is valid, proceed
		if (legal > 0)
		{
			// the call to legal flips all our pieces, then this
			// places our piece, and displays it
			board[i][j] = player;
			return true;
		}
		else
		{
			// move is invalid.
			// opponents turn
			player = opponent;
			return false;
		}
	}
	// Default state
	return false;
}

/*
** ============================================================
** Main driving function behind our game. This initializes
** our playing board, as well as the original four piece. It
** then handles our mouse clicks, placing pieces that are valid
** as well as handling if the game is over or not
** @params: none
** 
** @return: none
** ============================================================
*/

void initGame()
{
	int player = 1; //1 for White, 2 for Black
	int win = 0;  //default win state, 0 = still play, 1 = white, 2 = black

	// The initial board, with our base camps initialized
	// These can be changed as wished. 
	// Just change the values to the player values
	std::vector<std::vector<int>> board{
		{ { 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,2,0,0,0 },
		{ 0,0,0,2,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 } }
	};

	//the sf::Titlebar | sf::Style::Close prevents resizing of the window
	sf::RenderWindow
		window(sf::VideoMode(600, 400), "Reversi", sf::Style::Titlebar | sf::Style::Close);

	//main game loop
	while (window.isOpen())
	{
		//handle event
		sf::Event event;
		while (window.pollEvent(event))
		{
			//close window
			if (event.type == sf::Event::Closed)
				window.close();

			if (win == 0 && event.type == sf::Event::MouseButtonPressed)
			{
				// If mouse is clicked, handle it
				if (handle_click(board, player, event.mouseButton.x, event.mouseButton.y))
				{
					// Check for win or draw
					win = check_win(board, player);
					// If no win or draw yet, 
					// change to next player
					if (win == 0)
					{
						if (player == 1)
						{
							player = 2;
						}
						else
						{
							player = 1;
						}
					}
				}
			}
		}

		// Call to draw the battlefield
		drawBoard(window);
		// Loops below draw our pieces as the 
		// game plays on
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				drawSlot(window, board[i][j], i, j, board);

		// If a winner, or draw, call the draw scene to announce
		// our victory
		
		if (win == 1 || win ==2 || win ==3)
		{
			drawWinScene(window, win);
		}
			

		window.display(); // call to print the window to the screen
	}
}

int main() {
	__asm {
		// main assembly call to our initialize the game.
		call initGame
	// end asm
	}
	return 0;
}
