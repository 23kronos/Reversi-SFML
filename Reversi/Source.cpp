
/*
** ==========================================
** Reversi, The Game of WAR!!!
** Authors: Jared Sanders, David Paller
** Revision Date: Aprill 11th, 2017
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
** Wave the flag of victory and parade your troops through the
** enemy captial to show complete and utter dominance
** @params: Window, player
** @return: none
** ============================================================
*/

void draw_win_scene(sf::RenderWindow &window, int player)
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
** Count the cities you've conquered and lost
** @params: board, player
** @return: integer representing number of pieces (soldiers)
** ============================================================
*/

int score(std::vector<std::vector<int>> &board, int player) {
	int sum = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == player)
			{
				sum++;
			}
		}
	}
	return sum;
}

/*
** ============================================================
** Check if you've defeated the enemy, if you should retreat
** or if the two sides are evenly matched in battle.
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
** Initialize the battlefield, and setup our main cities
** @params: Window for drawing
** @return: none
** ============================================================
*/

void draw_board(sf::RenderWindow &window)
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
** Display the number of cities we've conquered and lost
** @params: board, window, player
** @return: none
** ============================================================
*/

void draw_score(std::vector<std::vector<int>> &board, 
	sf::RenderWindow &window, int player)
{
	// Display which side is which, followed by the scores of each
	sf::Text text;
	sf::Font font;
	font.loadFromFile("Cut the crap.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(40);
	text.setPosition(450, 50);
	text.setString("White: ");
	window.draw(text);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(40);
	text.setPosition(450, 200);
	text.setString("Black: ");
	window.draw(text);

	if (player == 1)
	{
		// This is straight from sfml's forum.
		// Don't know why we need a stringstream
		// but it works. 
		int whiteScore = score(board, 1);
		std::stringstream ss;
		ss << whiteScore;
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(50);
		text.setPosition(500, 100);
		text.setString(ss.str().c_str());
		window.draw(text);
	}
	else if (player == 2)
	{
		int blackScore = score(board, 2);
		std::stringstream ss;
		ss << blackScore;
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(50);
		text.setPosition(500, 250);
		text.setString(ss.str().c_str());
		window.draw(text);
	}
}

/*
** ============================================================
** Draw our cities, making sure to keep
** the allegiance flags waving
** @params: Window, player, x position, y position, board
** @return: none
** ============================================================
*/

void draw_slot(sf::RenderWindow &window, int player, int row, int col, 
	std::vector<std::vector<int>> &board)
{
	// We're either this player
	if (player == 1) //White
	{
			sf::CircleShape shape(20); //radius of 20
			shape.setFillColor(sf::Color::White);   //fill white
			shape.setOutlineThickness(1);
			shape.setOutlineColor(sf::Color::White);
			shape.setPosition(5 + (50 * row), 5 + (50 * col));
			window.draw(shape);
	}
	// Else we are the other player
	else if (player == 2) //Black piece
	{
		
			sf::CircleShape shape(20); //radius of 20
			shape.setFillColor(sf::Color::Black);   //fill black
			shape.setOutlineThickness(1);
			shape.setOutlineColor(sf::Color::Black);
			shape.setPosition(5 + (50 * row), 5 + (50 * col));
			window.draw(shape);
	}

	// Call draw score to see how the war is going
	draw_score(board, window, player);
}

/*
** ============================================================
** Is your proposed move follow standard war ethics? 
** Let's check
** @params: Board, row, col, player
** @return: Number of citie captured by move, if
**	    it was ethical (legal)
** ============================================================
*/

int checkLegal(std::vector<std::vector<int>> &board, int row, int col, int player)
{
	int num_flipped = 0;

	if (board[row][col] != 0)
		return 0;

	// Declare enemy cities
	int opponent;
	if (player == 1)
		opponent = 2;
	else
		opponent = 1;

	//Prepare for battle!
	// Check surroundings to the East
	int disc_pos = -1;
	for (int c = col + 1; c < 8 && board[row][c] != 0 && disc_pos == -1; c++)
	{
		if (board[row][c] == player)
			disc_pos = c;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos > col + 1)
	{
		for (int c = col + 1; c < disc_pos; c++)
		{
			// Conquer those cities!
			board[row][c] = player;
			num_flipped++;
		}
	}

	//Check surroundings to the West
	disc_pos = -1;
	for (int c = col - 1; c >= 0 && board[row][c] != 0 && disc_pos == -1; c--)
	{
		if (board[row][c] == player)
			disc_pos = c;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos < col - 1)
	{
		// Conquer those cities!
		for (int c = col - 1; c > disc_pos; c--)
		{
			board[row][c] = player;
			num_flipped++;
		}
	}

	// Check surroundings to the North
	disc_pos = -1;
	for (int r = row - 1; r >= 0 && board[r][col] != 0 && disc_pos == -1; r--)
	{
		if (board[r][col] == player)
			disc_pos = r;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos < row - 1)
	{
		// Conquer those cities!
		for (int r = row - 1; r > disc_pos; r--)
		{
			board[r][col] = player;
			num_flipped++;
		}
	}

	// Check surroundings to the South
	disc_pos = -1;
	for (int r = row + 1; r < 8 && board[r][col] != 0 && disc_pos == -1; r++)
	{
		if (board[r][col] == player)
			disc_pos = r;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos > row + 1)
	{
		// Conquer those cities!
		for (int r = row + 1; r < disc_pos; r++)
		{
			board[r][col] = player;
			num_flipped++;
		}
	}

	// Check surroundings to the North West
	disc_pos = -1;
	int c = col - 1;
	for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != 0 && disc_pos == -1; r--)
	{
		if (board[r][c] == player)
			disc_pos = r;
		c--;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos < row - 1)
	{
		c = col - 1;
		for (int r = row - 1; r > disc_pos; r--)
		{
			// Conquer those cities!
			board[r][c] = player;
			num_flipped++;
			c--;
		}
	}

	// Check surroundings to the North East
	disc_pos = -1;
	c = col + 1;
	for (int r = row - 1; c < 8 && r >= 0 && board[r][c] != 0 && disc_pos == -1; r--)
	{
		if (board[r][c] == player)
			disc_pos = r;
		c++;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos < row - 1)
	{
		c = col + 1;
		for (int r = row - 1; r > disc_pos; r--)
		{
			// Conquer those cities!
			board[r][c] = player;
			num_flipped++;
			c++;
		}
	}

	// Check surroundings to the South East
	disc_pos = -1;
	c = col - 1;
	for (int r = row + 1; c >= 0 && r < 8 && board[r][c] != 0 && disc_pos == -1; r++)
	{
		if (board[r][c] == player)
			disc_pos = r;
		c--;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos > row + 1)
	{
		c = col - 1;
		for (int r = row + 1; r < disc_pos; r++)
		{
			// Conquer those cities!
			board[r][c] = player;
			num_flipped++;
			c--;
		}
	}

	// Check surroundings to the South West
	disc_pos = -1;
	c = col + 1;
	for (int r = row + 1; c < 8 && r < 8 && board[r][c] != 0 && disc_pos == -1; r++)
	{
		if (board[r][c] == player)
			disc_pos = r;
		c++;
	}

	// Found a city, must be 2 spots away
	if (disc_pos != -1 && disc_pos > row + 1)
	{
		c = col + 1;
		for (int r = row + 1; r < disc_pos; r++)
		{
			// Conquer those cities!
			board[r][c] = player;
			num_flipped++;
			c++;
		}
	}

	// No enemy's found. You're dead.
	// Or you're move is invalid. Your choice.
	if (num_flipped == 0)
		board[row][col] = 0;

	return num_flipped;
}

/*
** ============================================================
** Make your selection, and prepare to move the troops
** @params: board, player, row, col
** @return: true if the mouse is clicked, false otherwise
** ============================================================
*/

bool handle_click(std::vector<std::vector<int>> &board, int player, int row, int col)
{
	// Where clicked?
	// Set row and col to that to move soliders to
	int i, j;

	if (row < 50)
	{
		i = 0;
	}
	else if (row < 100)
	{
		i = 1;
	}

	else if (row < 150)
	{
		i = 2;
	}
	else if (row < 200)
	{
		i = 3;
	}
	else if (row < 250)
	{
		i = 4;
	}
	else if (row < 300)
	{
		i = 5;
	}
	else if (row < 350)
	{
		i = 6;
	}
	else
	{
		i = 7;
	}


	if (col < 50)
	{
		j = 0;
	}
	else if (col < 100)
	{
		j = 1;
	}
	else if (col < 150)
	{
		j = 2;
	}

	else if (col < 200)
	{
		j = 3;
	}
	else if (col < 250)
	{
		j = 4;
	}

	else if (col < 300)
	{
		j = 5;
	}
	else if (col < 350)
	{
		j = 6;
	}

	else
	{
		j = 7;
	}

	// Check if your tactics are ethical
	int legal = checkLegal(board, i, j, player);
	if (board[i][j] == 0)   // Emtpy location
	{			
		// If your tactics are ethical, proceed
		if (legal > 0)
		{
			board[i][j] = player;
			return true;
		}
		else
		{
			return false;
		}
	}
	// Default state
	return false;
}

/*
** ============================================================
** Main driving function behind our war. The enemy 
** stole your sweet roll, shot you in the knee with
** an arrow, or is oppressing your nation, this is what
** has driven you to war.
** 
** @params: none
** 
** @return: none
** ============================================================
*/

int main()
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
		draw_board(window);
		// Loops below draw our soldiers as the 
		// battle rages on. 
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				draw_slot(window, board[i][j], i, j, board);

		// If we win, call the draw scene to announce
		// our victory
		if (win == 1)
		{
			draw_win_scene(window, 1);
		}
		else if (win == 2)
		{
			draw_win_scene(window, 2);
		}
		else if(win == 3)
			draw_win_scene(window, 3);
		
		// Make sure we actuall show the battlfield so we aren't
		// fighting blind. 
		window.display();
	}

	return 0;
}
