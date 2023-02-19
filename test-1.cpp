// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT5L
// Names: AINA SOFEA | NURUL AIN | HAIFA NAJIEHA
// IDs: 1211103430 | 1211103237 | 1211103429
// Emails: 1211103430@student.mmu.edu.my | 1211103237@student.mmu.edu.my | 1211103429@student.mmu.edu.my
// Phones: 01157672007 | 0172007878 | 0196468597
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int InputdimX;
int InputdimY;

class Planet
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_;

public:
    Planet(int dimX = InputdimX, int dimY = InputdimY);
    void init(int dimX, int dimY);
    void display() const;

    int getDimX() const;
    int getDimY() const;

    char getObject(int x, int y) const;

    void setObject(int x, int y, char ch);

    // void test1_1() const;
    void attributes() const;
    void zombiefunction() const;
};

void Menu()
{
    char selection;

    cout << " \n    SELECT AN OPTION :";
    cout << " \n==========================";
    cout << " \n 1 => Start Game ";
    cout << " \n 2 => Instructions ";
    cout << " \n 3 => Credits ";
    cout << " \n 4 => Help ";
    cout << " \n 5 => Quit ";
    cout << " \n==========================";
    cout << " \n Where will you go =>  ";
    cin >> selection;

    switch (selection)
    {
    case '1':
        cout << "Let's fight for our planet !";
        break;
    case '2':
        cout << "Here are steps on how to play this game.";
        break;
    case '3':
        cout << "Introducing to you, our main programmer.....";
        break;
    case '4':
        cout << "Need help ? No worries, our team can be contacted via our email.";
        break;
    case '5':
        cout << "Sorry to see you go, have a good day ! Thank you~";
        quit();
        break;

    default:
        cout << "Invalid selection !";
    }
    cout << "\n";
}

void Planet::setObject(int x, int y, char ch)
{
    map_[dimY_ - y][x - 1] = ch;
}

char Planet::getObject(int x, int y) const
{
    return map_[dimY_ - y][x - 1];
}

int Planet::getDimX() const
{
    return dimX_;
}

int Planet::getDimY() const
{
    return dimY_;
}

Planet::Planet(int dimX, int dimY)
{
    init(dimX, dimY);
}

void Planet::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;

    char objects[] = {' ', ' ', ' ', ' ', ' ', 'h', 'p', 'r', ' '}; // kena tanya berapa zombie and then masukkan dalm char object, and alien is a must just ada satu sahaja
    int noOfObjects = 9;

    map_.resize(dimY);
    for (int i = 0; i < dimY_; ++i)

    {
        map_[i].resize(dimX_);
    }

    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void Planet::display() const
{
    cout << "     __________________________________________________   " << endl;
    cout << "   /          *               *                   *    |  " << endl;
    cout << "  /  *               *                       *         |  " << endl;
    cout << " /  WE PRESENT TO YOU.... *            *           *   |  " << endl;
    cout << " |    _        _  _       _   _   _       _     _      |   " << endl;
    cout << " |   |_| |  | |_ | |  | ||_    / | | |V| |_| | |_      |  " << endl;
    cout << " |   | | |_ | |_ | |   V  _|  /_ |_| | | |_| | |_      |  " << endl;
    cout << " |             *                                       |  " << endl;
    cout << " |       *               Mission : Save Our Planet     /  " << endl;
    cout << " | *              *                                   /   " << endl;
    cout << " |___________________________________________________/    " << endl;

    for (int i = 0; i < dimY_; ++i)
    {
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+--";
        }
        cout << "+" << endl;

        cout << setw(2) << (dimY_ - i);

        for (int j = 0; j < dimX_; ++j)
        {
            cout << "| " << map_[i][j];
        }
        cout << "| " << endl;
    }

    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+--";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << "  ";
        if (digit == 0)
            cout << "  ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "  " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void test1_1()
{
    Planet planet;
    planet.display();
}

void Planet::attributes() const
{
    int alienLife = 100 + (rand() % 120);
    int alienAtt = 0;

    int zombie1Life = 100 + (rand() % 120);
    int zombie1Att = 100 + (rand() % 120);
    int zombie1Ran = 1 + rand() % dimX_ % dimY_;

    int zombie2Life = 100 + (rand() % 170);
    int zombie2Att = 100 + (rand() % 170);
    int zombie2Ran = 1 + rand() % dimX_ % dimY_;

    int zombie3Life = 100 + (rand() % 200);
    int zombie3Att = 100 + (rand() % 200);
    int zombie3Ran = 1 + rand() % dimX_ % dimY_;

    cout << "Alien     : Life  " << setw(4) << alienLife << "     Attack " << setw(4) << alienAtt << endl;
    cout << "Zombie 1  : Life  " << setw(4) << zombie1Life << "     Attack " << setw(4) << zombie1Att << "        Range" << setw(4) << zombie1Ran << endl;
    cout << "Zombie 2  : Life  " << setw(4) << zombie2Life << "     Attack " << setw(4) << zombie2Att << "        Range" << setw(4) << zombie2Ran << endl;
    cout << "Zombie 3  : Life  " << setw(4) << zombie3Life << "     Attack " << setw(4) << zombie3Att << "        Range" << setw(4) << zombie3Ran << endl;
}

void Planet::zombiefunction() const
{
    int defaultzombie = 3;
    char changezombie;
    int noofzombie;
    cout << "Zombie Settings" << endl;
    cout << "---------------" << endl;
    cout << " Default Zombie count: 3" << endl;
    cout << "Do you wish to change the zombie count? (y/n) :";
    cin >> changezombie;
    if (changezombie == 'y')
    {
        cout << "Enter number of zombies: ";
        cin >> noofzombie;
        for (int i = 1; i < noofzombie + 1; ++i)
        {
            int zombieLife[i] = {100 + (rand() % 170)};
            int zombieAtt[i] = {100 + (rand() % 170)};
            int zombieRange[i] = {1 + rand() % dimX_ % dimY_};

            cout << "Zombie " << i << ": Life " << setw(4) << zombieLife[i] << "       Attack " << setw(4) << zombieAtt[i] << "       Range" << zombieRange[i] << endl;
        } // mcm mana nak tambah zombie (1,2,3,4,..) in the array dim x and dim y map bla bla
    }

    else if (changezombie == 'n')
    {
        cout << "Okay" << endl;
        Planet planet;
        planet.attributes();
    }
}
void InsertValue()
{
    cout << " Please insert your preferred dimension. \n You can only choose odd numbers for your dimension. " << endl;
    cout << " Dimension X :";
    cin >> InputdimX;
    cout << " Dimension Y :";
    cin >> InputdimY;
    cout << endl
         << endl;

    if (InputdimX % 2 == 0 || InputdimY % 2 == 0)
    {
        cout << "You are required to use only odd numbers." << endl;
        InsertValue();
    }
}

// buat dimX and dimY jadi global
// int dimX = 15;
// int dimY = 5;
// declare a and b is global variable
// int a = (dimX + 1) / 2; // a = column alien
// int b = (dimY + 1) / 2; // b = rown alien
// char c = 'A'; // character alien
// int a = (InputdimX + 1) / 2;
// int b = (InputdimY + 1) / 2;
void alienPoint()
{
    Planet Planet;
    // int a = 0; // a = column
    // int b = 0; // b = row

    int a = (InputdimX + 1) / 2;
    int b = (InputdimY + 1) / 2;
    int x1 = a, y1 = b;
    char ch1 = 'A';
    Planet.setObject(x1, y1, ch1);
    Planet.display();
    cout << "The object " << ch1 << " should be at column "
         << x1 << " and row " << y1 << endl;
}

void move_right()
{
    Planet Planet;
    int a = (InputdimX + 1) / 2;
    int b = (InputdimY + 1) / 2;
    int x1 = a + 1, y1 = b;
    char ch1 = 'A';
    Planet.setObject(x1, y1, ch1);
    Planet.setObject(x1 - 1, y1, '.');
    Planet.display();
    cout << "The object " << ch1 << " should be at column "
         << x1 << " and row " << y1 << endl;
}

void move_left()
{
    Planet Planet;
    int a = (InputdimX + 1) / 2;
    int b = (InputdimY + 1) / 2;
    int x1 = a - 1, y1 = b;
    char ch1 = 'A';
    Planet.setObject(x1, y1, ch1);
    Planet.setObject(x1 + 1, y1, '.');
    Planet.display();
    cout << "The object " << ch1 << " should be at column "
         << x1 << " and row " << y1 << endl;
}

void move_up()
{
    Planet Planet;
    int a = (InputdimX + 1) / 2;
    int b = (InputdimY + 1) / 2;
    int x1 = a, y1 = b + 1;
    char ch1 = 'A';
    Planet.setObject(x1, y1, ch1);
    Planet.setObject(x1, y1 - 1, '.');
    Planet.display();
    cout << "The object " << ch1 << " should be at column "
         << x1 << " and row " << y1 << endl;
}

void move_down()
{
    Planet Planet;
    int a = (InputdimX + 1) / 2;
    int b = (InputdimY + 1) / 2;
    int x1 = a, y1 = b - 1;
    char ch1 = 'A';
    Planet.setObject(x1, y1, ch1);
    Planet.setObject(x1, y1 + 1, '.');
    Planet.display();
    cout << "The object " << ch1 << " should be at column "
         << x1 << " and row " << y1 << endl;
}

void direction()
{
    // while (thecommand == "direction"){
    string direct; // kalau nak jadikan dia selalu jalan, jadikan dia while loop
    cout << endl
         << "Enter direction: ";
    cin >> direct;
    while ((direct == "right") || (direct == "left") || (direct == "down") || (direct == "up"))
    {
        if (direct == "right")
        {
            move_right();
            break;
        }
        else if (direct == "left")
        {
            move_left();
            break;
        }
        else if (direct == "up")
        {
            move_up();
            break;
        }
        else if (direct == "down")
        {
            move_down();
            break;
        }
        else
        {
            break;
        }
    }
}

void help()
{
    cout << endl;
    cout << "Commands" << endl;
    cout << "-----------" << endl;
    cout << "1. up    - Move up." << endl;
    cout << "2. down  - Move down." << endl;
    cout << "3. left  - Move left." << endl;
    cout << "4. right - Move right." << endl;
    cout << "5. arrow - Change direction of an arrow." << endl;
    cout << "6. help  - Display this uder commands." << endl;
    cout << "7. save  - Save the game." << endl;
    cout << "8. load  - Load a game." << endl;
    cout << "9. quit  - Quit the game." << endl;
}

void save()
{
    cout << "Save the game" << endl;
}

void arrow()
{
    int row = 0;
    int column = 0;
    char direction;
    cout << "Enter row, column and direction: " << endl;
    cin >> row >> column >> direction;
}

void quit()
{
    char inputquit;
    cout << "Do you want to quit? (y/n) : ";
    cin >> inputquit;
    while ((inputquit == 'y') || inputquit == 'n')
    {
        if (inputquit == 'y')
        {
            break;
        }
        else if (inputquit == 'n')
        {
            continue;
        }
        else
        {
            cout << "Please enter yes or no (y/n): ";
            cin >> inputquit;
            continue;
        }
    }
}

void Command(string inputcommand)
{
    while ((inputcommand == "direction") || (inputcommand == "help") || (inputcommand == "save") || (inputcommand == "arrow") || (inputcommand == "quit"))
    {
        if (inputcommand == "direction")
        {
            direction();
            break;
        }
        else if (inputcommand == "help")
        {
            help();
            break;
        }
        else if (inputcommand == "save")
        {
            save();
            break;
        }
        else if (inputcommand == "arrow")
        {
            arrow();
            break;
        }
        else if (inputcommand == "quit")
        {
            quit();
            break;
        }
    }
}
int main()
{
    Menu();
    InsertValue();

    srand(time(NULL));
    Planet planet;
    // test1_1();
    alienPoint();
    planet.attributes();
    // planet.zombiefunction();

    string input;
    cout << "command> ";
    cin >> input;
    Command(input);
    if (input == "help")
    {
        cout << "command> ";
        cin >> input;
        Command(input);
    }
}
