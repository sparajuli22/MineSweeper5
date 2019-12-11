//Program - Final Project (Building the Minesweeper game)
//CS - 171 - 3
//Author - Mradul Mourya and Satish Parajuli
//Modfication Date - 12/11/2019
//Description - Construction of the program using class (Minesweeper) under which there are nine methods. The system will prompt user to
//enter the row number and column number which user wants to reveal, And if there is no empty tile remains, user wins the game.

#include <iostream> //needed for console input and output
#include <iomanip> //need for set pricision
#include <cstdlib> //needed for generating random numbers



using namespace std; //using namespace standard

//Maximum number of sides in the game would be 9
const int MAXSIDES = 9; 

class Minesweeper
{
private:
    int sides;                          //number of tiles in a side.
    int difficulty;                     //user defined difficulty level
    int mines;                          //number of mines in a game
    bool nextmove;                      //bool that checks if the user proceeds to next move or not.
    bool gamewon;                       //check if the user wins the game
    char realBoard[MAXSIDES][MAXSIDES]; //minesweeper board has the mines placed.
    char userBoard[MAXSIDES][MAXSIDES]; //minesweeper board that the user can see without mines.
    bool isRevealed[MAXSIDES][MAXSIDES];//this array checks if each tiles are revealed or not.

public:
    //empty constructor creates a board that has (9X9) tiles and 10 mines
    Minesweeper()
    {
        nextmove = true;//Initializing next move as true
        gamewon = false;//Initializing gamewon as false
        difficulty = 1; //By default difficulty level is on beginner mode
        sides = 9;  //9 rows and columns (According to standard beginner minesweeper game)
        mines = 10; //By default, the game is on beginner mode with 10 mines in it.
    }

    //function for choosing level as beginner, intermediate, and advance
    //input: level as integer from user (1,2,3)
    void chooseLevel(int level)
    {
        if (level == 1)
        {               //condition for beginner
            mines = 10; //mines would be 10
        }
        else if (level == 2)
        {               //condition for intermediate
            mines = 15; //mines would be 15
        }
        else if (level == 3)
        {               //condition for advance
            mines = 20; //mines would be 20
        }
    }

    //Function for filling the board with dashes
    void fillBoard()
    {
        //loop for iteration through row
        for (int i = 0; i < sides; i++) //iterating till maximum no. of sides
        {
            //loop for iteration through column
            for (int j = 0; j < sides; j++) //iterating till maximum no. of sides
            {
                //the all tiles initially have no mines i.e. all values are '-'
                realBoard[i][j] = '-';
                userBoard[i][j] = '-';
                isRevealed[i][j] = false;
            }
        }
    }

    //Function for checking whether the given input for row and column by user is the board sides range
    //Return: Boolean true if entered row and column are from 0 to less than sides
    //Return: Boolean False if input is outside the range
    bool isValidTile(int row, int column) //Passing row and column as parameters
    {
        if (row >= 0 && column >= 0 && row < sides && column < sides)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //Function for randomly placing mines in board
    void placeMines()
    {
        //initating count from 0
        int count = 0;
        while (count < mines) //using do-while loop
        {
            int randomRow = rand() % MAXSIDES;             //random row numbers from 0 to max sides
            int randomColumn = rand() % MAXSIDES;          //random column numbers from 0 to max sides
            if (realBoard[randomRow][randomColumn] != 'X') //condition for checking mines in the board
            {
                realBoard[randomRow][randomColumn] = 'X'; //placing the mines in the board
                count++;                                  //increasing the count
            }

        } //stop the loop when count reaches number of mines
        cout << endl;
    }

    //Function for checking mines (Passing arguments userRow and userColumn)
    //Return: count 
    //Algorithm for checking all the adjacent sides (same followed in the function: checkNeighbourMines):
    //Ajacent sides would be eight in the nine till except the selected tile from the user
    //For checking left tile = userRow, userColumn - 1
    //For checking right tile = userRow, userColumn + 1
    //For checking above (up) tile = userRow - 1, userColumn
    //For checking below or (down) tile = userRow + 1, userColumn
    //For checking above left tile = userRow - 1, userColumn - 1
    //For checking above right tile = userRow - 1, userColumn + 1
    //For checking below left tile = userRow + 1, userColumn - 1
    //For checking below right tile = userRow + 1, userColumn + 1
    int checkMines(int userRow, int userColumn)
    {
        int count = 0; //variable for keeping track of count
        if (realBoard[userRow][userColumn] == 'X') //if program finds the mine, returns 9
        {
            return 9; 
        }
        else
        {
            //We've put everthing under two "for" loop for making program efficient
            for (int i = userRow - 1; i <= userRow + 1; i++) //iterate loop from userRow -1 to userRow + 1 (for rows)
            {
                for (int j = userColumn - 1; j <= userColumn + 1; j++) //iterate loop from userRow -1 to userRow + 1 (for column)
                    //Condition for checking the valid tile numbers
                    if (i >= 0 && j >= 0 && i < sides && j < sides && !(i == userRow && j == userColumn))
                    {
                        if (realBoard[i][j] == 'X') //Condition if there is mine in the tile, increment the count
                        {
                            count++;
                        }
                    }
            }
        }
        return count;
    }

    //Function for revealing the tile after user lose the game 
    //Passing arguments userRow and userColumn
    void reveal(int userRow, int userColumn)
    {
        int nearMines = checkMines(userRow, userColumn); //calling function checkMines and assing it to integer variable nearMines
        if (nearMines > 0 && nearMines < 9) //condition for checked mines are between 0 to 9
        {
            userBoard[userRow][userColumn] = checkMines(userRow, userColumn) + 48; //
            isRevealed[userRow][userColumn] = true; //isRevealed variable would be true
        }
        else if (nearMines == 9) //Condition if nearmine is 9
        {
            userBoard[userRow][userColumn] = 'X'; //userBoard will display the mine and where it is placed
            nextmove = false;                     //nextmove would be false as game will be over
        }
        else //condition is near mines is neither between 0 and 9 or 9
        {
            userBoard[userRow][userColumn] = ' '; //userBoard will display space
            isRevealed[userRow][userColumn] = true;//isRevealed variable would be true
        }
    }

    //Function for checking all the neighbouring mines at 8 adjacent sides
    //Using the same algorithm as used in checkMines
    //We've used 5 loops as we want to do this without recursion
    //Passsing parameters as userRow and userColumn
    void checkNeighbourMines(int userRow, int userColumn)
    {
        int nearMines = checkMines(userRow, userColumn); //re-using the variable nearMines assign it to checkMines
        //userBoard[userRow][userColumn] = static_cast<char>(nearMines + 48);
        reveal(userRow, userColumn); //calling the function reveal and passing the same parameters
        bool loopAgain = false;      //loopAgain variable initialized to false
        do                           //First, using do - while loop
        {
            loopAgain = false;       //Inside of do-while initially it will check loopAgain for re-iteritating
            for (int row = 0; row < sides; row++) //iterating till maximum no. of sides
            {
                //loop for iteration through column
                for (int column = 0; column < sides; column++)
                {
                    //condition if there is no mines in the adjacent sides filled the userBoard with space
                    if (isRevealed[row][column] && userBoard[row][column] == ' ')
                    {
                        //Again will go inside another loop and iterates from row -1 to row + 1 for checing adjacent sides
                        for (int i = row - 1; i <= row + 1; i++)
                        { 
                            //Again will go inside another loop iterates from column -1 to column + 1 for checing adjacent sides
                            for (int j = column - 1; j <= column + 1; j++)
                            {
                                //Condition if valid tile 
                                if (isValidTile(i, j) && !(isRevealed[i][j]))
                                {
                                    reveal(i, j);
                                    loopAgain = true; //if condition is true, loop will run again(all the loops)
                                }
                            }
                        }
                    }
                }
            }
        } while (loopAgain == true); //condtion for running the loop again
    }

    //Function for printing Minesweeper board
    //User interaction is done through this board
    void printBoard()
    {
        cout << "  |_";
        for (int i = 0; i < sides; i++) //iterate through number of sides
        {
            cout << "_" << i << "_"; //print 0 to 10 in first row
        }
        cout << "|" << endl;

        for (int i = 0; i < sides; i++) //iterate through number of sides for row
        {
            cout << i << " | "; //print number 0 to 10 after each row
            for (int j = 0; j < sides; j++) //iterate through number of sides for column
            {
                cout << setw(2) << userBoard[i][j] << " "; 
            }
            cout << "|";
            cout << endl; //ending line after each row
        }
        cout << "  |____________________________|" << endl;
    }

    //Function for printing real board
    //Just for programming (to check if user wins the game)
    /*void printRealBoard()
    {
        cout << "  ";
        for (int i = 0; i < sides; i++)
        {
            cout << setw(2) << i << " ";
        }
        cout << endl;

        for (int i = 0; i < sides; i++)
        {
            cout << i << " ";
            for (int j = 0; j < sides; j++)
            {
                cout << setw(2) << realBoard[i][j] << " ";
            }
            cout << " |" << endl;
        }
    }*/

    //Takes input to reveal mines.
    //int row the row no. of tile revealed
    //int column: the column no. of tile to be revealed.
    void takeUserInput(int& row,int& column){
        
        do{
        cout << "Enter row number for revealing a tile (0-8):";
        cin >> row;
        cout << "Enter column number for reveling a tile (0-8):";
        cin >> column;
        } while (isValidTile(row, column) == false); //takes input only if the tile is valid and lies in the array.
        
    }

    //user chooses the difficulty Level
    void chooseDifficulty(){
        int userDifficulty; //integer variable for userDifficulty
        cout << "All level have 9x9 tiles.\nChoose the level of difficulty \nPress \"1\" for Beginner(10 mines), \"2\" for Intermediate(15 mines), \"3\" for Advanced(20 mines) " << endl;
        cin >> userDifficulty; //user chooses the Difficulty
        chooseLevel(userDifficulty); //calling the function chooselevel by passing userDifficulty variable for different levels of the game
    }

    //Function for playing Minesweeper
    //Method which iteracts with most of the other methods in the class
    bool playMinesweeper()
    {
        chooseDifficulty();
        int row, column; //integer variable for row and column
        fillBoard();     //calling function fillBoard for filling the board with dashes
        placeMines();    //calling function placeMines to randomly placing the mines in the board

        while (nextmove == true) //condition for checking the next move or lost
        {
            printBoard(); //calling function printBoard for displaying the main minesweeper board to the user
            //printRealBoard();
            takeUserInput(row, column);
            //calling function checkNeighbourMines for checking all the adjacent mines by passing row and column
            checkNeighbourMines(row, column); 
            int tileRemaining = 0; //taking variable for remaining tiles and initializing to 0
            for (int i = 0; i < sides; i++) //iterate through number of sides for row
            {
                for (int j = 0; j < sides; j++) //iterate through number of sides for column
                {
                    if (userBoard[i][j] == realBoard[i][j]) //condition for checking remaining tiles
                    {
                        tileRemaining++; //incrementing the tiles
                    }
                }
            }
            if (tileRemaining == 0) //condition for winning or losing the game
            {
                gamewon = true;   //user wins the game if there is no blank tile remains
                nextmove = false; //there is no next move
            }
        }

        for (int i = 0; i < sides; i++)         //iterate through number of sides for row
            {
                for (int j = 0; j < sides; j++) //iterate through number of sides for column
                {
                    
                    if (realBoard[i][j] == 'X') //condtion for checking if board has mines in it
                    {
                        userBoard[i][j] = realBoard[i][j]; //replacing userBoard array with all the mine spaces.
                    }
                }
            }
            printBoard();                       //calling function printBoard for displaying the board
            return gamewon;                     //returns gamewon

        
    }
};

//Main function 
int main()
{
    //set random for the whole application. Based on the current time of execution
    srand(time(NULL)); 
    bool gamewon;  //re-using variable gamewon
    cout << "Welcome to Minesweeper\n " << endl;
    //Initialize the object play!
    Minesweeper play; 
    //assign playMinesweeper function inside gamewon variable (calling the method from class)
    //took variable gamewon as to remove cout statements from the member function "playMinesweeper"
    gamewon = play.playMinesweeper();
    if (gamewon == false) //condtion for checking user win or lose
        {
            //priting the hints for beating the minesweeper
            //Reference for the hints: https://www.instructables.com/id/How-to-beat-Minesweeper/
            cout << "You Touched a mine.\nGame Over, Better Luck Next Time." << endl;
            cout << "\"X\" shows all mines position." << endl;
            cout << "\n\nHints for beating the minesweeper: \n1. Mark all the mines that are downright OBVIOUS. Such as eight 1's surrounding a unopened square, it's obviously a mine.\n2. Next start finding the mines around other numbers\n3. Finding the mines in 1 blocks helps a lot, because it opens many squares and good hints to 2's and 3's.\n4. Be careful. Only open blocks that you KNOW are safe.\n5. Be lucky. Don't blow the mine up in first turn.\nHave fun! " ;
            
            
        } //If user wins the game
        else
        {
            cout << "\n___________________________" << endl ;
            cout << "________YOU______WIN_______" <<endl ;                  ; 
        }

    
}
