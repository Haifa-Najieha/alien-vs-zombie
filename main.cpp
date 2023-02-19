// ******************************************************************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT5L
// Names:             AINA SOFEA         |          NURUL AIN            |        HAIFA NAJIEHA
// IDs:               1211103430         |          1211103237           |         1211103429
// Emails: 1211103430@student.mmu.edu.my | 1211103237@student.mmu.edu.my | 1211103429@student.mmu.edu.my
// Phones:            01157672007        |          0172007878           |         0196468597
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

char SEPARATOR = ',';

class Planet
{
private:
    // creates 2D vector named map_
    vector<vector<char>> map_;
    int _cols, _rows;
    int _noOfObjects = 16;

    // MORE CHANCE FOR EMPTY SPACE TO DROP
    char _objects[16] = {
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::EMPTY_SPACE,
        Planet::ARROW_UP,
        Planet::ARROW_DOWN,
        Planet::ARROW_RIGHT,
        Planet::ARROW_LEFT,
        Planet::HEALTH,
        Planet::POD,
        Planet::ROCK

    };

public:
    static const char EMPTY_SPACE = ' ';
    static const char TRAIL = '.';
    static const char ARROW_UP = '^';
    static const char ARROW_DOWN = 'V';
    static const char ARROW_LEFT = '<';
    static const char ARROW_RIGHT = '>';
    static const char ROCK = 'r';
    static const char POD = 'p';
    static const char HEALTH = 'h';
    static const char ALIEN = 'A';
    static const char ZOMBIE = 'Z';

    void init(int rows, int cols);
    void display();
    bool isInside(int row, int col);

    int getRows() const;
    int getCols() const;

    char getObject(int row, int col);
    void setObject(int row, int col, char ch);

    void randomiseObject();
    void replaceTrail();
};

class Sprite
{
private:
    int _attack;
    int _health;
    int _range;
    int _row;
    int _col;
    char _icon;
    char _trail;
    bool _isAlien = false;

    // ALIEN SPECIFICATION
    char _direction;
    bool _isEndingMoving;

public:
    static const char UP = '1';
    static const char RIGHT = '2';
    static const char DOWN = '3';
    static const char LEFT = '4';

    Sprite();
    void randomiseAttributes(int &attributes, int min_, int max_);
    void randomisePosition(const Planet &planet);

    bool isMovable(Planet &planet, int row, int col);
    bool isEnemy(Planet &planet, int row, int col);
    void move(Planet &planet, Sprite &alien, vector<Sprite> &zombies, char direction);
    void detectObject(Planet &planet, vector<Sprite> &zombies, int row, int col);
    void moveAlien(Planet &planet, Sprite &alien, vector<Sprite> &zombies, char direction);

    void receiveDamage(int damage);

    void setupAlien(const Planet &planet);
    void setupZombie(const Planet &planet);

    int getAttack() const;
    int getHealth() const;
    int getRange() const;
    int getRow() const;
    int getCol() const;
    char getIcon() const;
    char getTrail() const;
    int findZombie(vector<Sprite> &zombies, int row, int col);
    int calculateDistancePoint(Sprite &zombie, int row, int col);

    void setAttack(int attack);
    void setHealth(int health);
    void setRange(int range);
    void setRow(int row);
    void setCol(int col);
};

////////////////////////////////////////////////////////////////////////

void displayIntro()
{
    cout << "\n\n"
         << endl;
    cout << "    _____________________________________________________________________     " << endl;
    cout << "   /          *               *                   *                    * \\   " << endl;
    cout << "  /  *               *                       *                   *        \\  " << endl;
    cout << " /  WE PRESENT TO YOU.... *            *                *        _____     \\ " << endl;
    cout << " |      _        _  _       _   _   _       _     _          __ / ___ \\  *  | " << endl;
    cout << " |     |_| |  | |_ | |  | ||_    / | | |V| |_| | |_    *    /  | |___| |    | " << endl;
    cout << " |     | | |_ | |_ | |   V  _|  /_ |_| | | |_| | |_        |   |       |    | " << endl;
    cout << " |               *                                    *    |___|  __   |    | " << endl;
    cout << " \\       *               Mission : Save Our Planet            |__| |__| *  /  " << endl;
    cout << "  \\ *              *                       *                *             /   " << endl;
    cout << "   \\____________________________________________________________________ /  \n"
         << endl;
    cout << endl
         << endl;
}

void displayOption()
{
    cout << " \n    SELECT AN OPTION :";
    cout << " \n==========================";
    cout << " \n 1 => Start Game ";
    cout << " \n 2 => Instructions ";
    cout << " \n 3 => Credits ";
    cout << " \n 4 => Help ";
    cout << " \n 5 => Quit ";
    cout << " \n==========================";
    cout << " \n Where will you go => ";
}

void displayInstruction()
{
    cout << "                                     ====  INSTRUCTIONS  ====                                         " << endl;
    cout << "\n\nThe Zombies have conquered all the planets! You will need to liberate them!                       " << endl;
    cout << "\nLet's take back our planet! Your mission is to destroy that despicable Zombie!                      " << endl;
    cout << "\n\n====================================================================================================" << endl;
    cout << endl;
    cout << "Commands"                                                                                               << endl;
    cout << "-----------"                                                                                            << endl;
    cout << "1. direction - Move alien"                                                                              << endl;
    cout << "2. arrow - Change direction of an arrow."                                                               << endl;
    cout << "3. help  - Display this user commands."                                                                 << endl;
    cout << "4. save  - Save the game."                                                                              << endl;
    cout << "5. load  - Load a game."                                                                                << endl;
    cout << "6. quit  - Quit the game."                                                                              << endl
                                                                                                                     << endl;
    cout << "Commands for direction: "                                                                               << endl
         << "1. up    - Move up"                                                                                     << endl
         << "2. down  - Move down "                                                                                  << endl
         << "3. right - Move right"                                                                                  << endl
         << "4. left  - Move left"                                                                                   << endl
         << endl;
    cout << "\n\n====================================================================================================" << endl;
    cout << "\n--- HP, Range, Attacks ---                                                                          " << endl;
    cout << "\nHP (Hit points) = When the zombie attacked, it will decreases your HP.                              " << endl;
    cout << "                  = You will lose when your HP reaches 0.                                             " << endl;
    cout << "                  = You can see the Zombies' HP and attack range below the gameboard.                 " << endl;
    cout << "\nRange        = Distance between alien to the zombies.";
    cout << "\nAttacks      = Damage that will be given by alien to zombies and vice versa.                             " << endl;
    cout << "               = Alien attacks increased when alien encounter arrow.                                       " << endl;
    cout << "\n\n====================================================================================================" << endl;
    cout << "\n--- Pods ---                                                                                        " << endl;
    cout << "\nThe Pods on the gameboard can be used for range attacks.                                            " << endl;
    cout << "\nPods will shoot the nearest Zombie with certain amount of damage.                                   " << endl;
    cout << "\nThe Zombie will be weaker when you use the Pods.                                                    " << endl;
    cout << "\n\n====================================================================================================" << endl;
    cout << "\n--- Rocks ---                                                                                       " << endl;
    cout << "\nThe rocks will contain either the health or the pods.                                               " << endl;
    cout << "\nWhen Alien stumbles upon the rock, the rock will breaks and will provide either health or pods.     " << endl;
}

void displayProgrammer()
{
    cout << "\n\nIntroducing to you, our main programmer.....                                                                   " << endl;
    cout << "\nAssignment Trimester 1 22/23 \nLecture Class TC1V \nTutorial Class TT5L \n\n                                     " << endl;
    cout << "\nTeam Members: \n\tAina Sofea binti Amier Hamzah \n\tNurul Ain binti Kamarudin \n\tHaifa Najieha binti Hashim \n\n"
         << endl;
    cout << "\nThanks to \n\tMr Wong Ya Ping, \n\tMr Ban Kar Weng, \n\tMadam Pang Nyuk Khee Angeline Pang                       " << endl;
}

void displayContact()
{
    cout << "\n\nNeed help ? No worries, just contact us for any further requiries.             " << endl;
    cout << "\nOur programmers' details :-                                                      " << endl;
    cout << "\nAina Sofea    : \n\t011 - 5767 2007 | aina03sofea@gmail.com         | 1211103430 " << endl;
    cout << "\nNurul Ain     : \n\t017 - 200 3878  | nurulainkamarudin17@gmail.com | 1211103237 " << endl;
    cout << "\nHaifa Najieha : \n\t019 - 646 8597  | haifanajieha286@gmail.com     | 1211103429 " << endl;
}

void displayGameOption()
{
    cout << endl;
    cout << "Commands" << endl;
    cout << "-----------" << endl;
    cout << "1. direction - Move alien" << endl;
    cout << "2. arrow - Change direction of an arrow." << endl;
    cout << "3. help  - Display this user commands." << endl;
    cout << "4. save  - Save the game." << endl;
    cout << "5. load  - Load a game." << endl;
    cout << "6. quit  - Quit the game." << endl
         << endl;
    cout << "Commands for direction: " << endl
         << "1. up    - Move up" << endl
         << "2. down  - Move down " << endl
         << "3. right - Move right" << endl
         << "4. left  - Move left" << endl
         << endl;
}

void displayOptionResult(int inputOption)
{
    switch (inputOption)
    {
    case 1:
        cout << " Let's fight for our planet !" << endl
             << endl;
        break;
    case 2:
        displayInstruction();
        break;
    case 3:
        displayProgrammer();
        break;
    case 4:
        displayContact();
        break;
    case 5:
        cout << "\n\nThanks for playing our game! Come back for more exciting experiences." << endl;
        break;
    default:
        cout << "Invalid selection !";
    }
    cout << "\n";
}

void displayAttribute(Sprite alien, vector<Sprite> zombies)
{
    cout << "<< ALIEN >>" << endl
         << "\tHealth: " << alien.getHealth() << endl
         << "\tAttack: " << alien.getAttack() << endl;

    for (int i = 0; i < zombies.size(); i++)
    {
        cout << "<< ZOMBIE " << i << " >>" << endl
             << "\tHealth: " << zombies.at(i).getHealth() << endl
             << "\tAttack: " << zombies.at(i).getAttack() << endl
             << "\tRange: " << zombies.at(i).getRange() << endl;
    }
}

void displayFullGameMap(Planet &planet, Sprite alien, vector<Sprite> zombies)
{
    //displayGameOption();
    planet.display();
    displayAttribute(alien, zombies);
    system("pause");
    //system("cls");
}

////////////////////////////////////////////////////////////////////////

void Planet::init(int rows, int cols)
{
    _rows = rows;
    _cols = cols;

    map_.resize(_rows);
    for (int i = 0; i < _rows; ++i)
    {
        map_[i].resize(_cols);
        fill(map_[i].begin(), map_[i].end(), ' ');
    }
}

void Planet::display()
{
    for (int i = 0; i < _rows; i++)
    {
        // line

        cout << "  ";
        for (int j = 0; j < _cols; j++)
        {
            cout << "+---";
        }
        cout << "+" << endl;

        // row
        cout << setw(2) << i + 1;

        for (int j = 0; j < _cols; j++)
        {
            cout << "| " << getObject(i, j) << " ";
        }
        cout << "|" << endl;
    }

    // line

    cout << "  ";
    for (int j = 0; j < _cols; j++)
    {
        cout << "+---";
    }
    cout << "+" << endl;

    cout << " ";
    for (int j = 1; j < _cols + 1; j++)
    {
        cout << setw(4) << j;
    }
    cout << " " << endl;
}

int Planet::getRows() const
{
    return _rows;
}

int Planet::getCols() const
{
    return _cols;
}

char Planet::getObject(int row, int col)
{
    return map_[row][col];
}

void Planet::setObject(int row, int col, char ch)
{
    map_[row][col] = ch;
}

void Planet::randomiseObject()
{
    for (int i = 0; i < _rows; ++i)
    {
        for (int j = 0; j < _cols; ++j)
        {
            int objNo = rand() % _noOfObjects;
            setObject(i, j, _objects[objNo]);
        }
    }
}

void Planet::replaceTrail()
{
    for (int i = 0; i < _rows; ++i)
    {
        for (int j = 0; j < _cols; ++j)
        {
            if (getObject(i, j) == Planet::TRAIL)
            {
                int objNo = rand() % _noOfObjects;
                setObject(i, j, _objects[objNo]);
            }
        }
    }
}

bool Planet::isInside(int row, int col)
{
    bool checkRow = row >= 0 && row < _rows;
    bool checkCol = col >= 0 && col < _cols;
    return checkRow && checkCol;
}

////////////////////////////////////////////////////////////////////////

Sprite::Sprite()
{
}

void Sprite::setupAlien(const Planet &planet)
{
    randomiseAttributes(_health, 100, 300);
    _attack = 0;
    _range = 0;
    _row = planet.getRows() / 2;
    _col = planet.getCols() / 2;
    _icon = Planet::ALIEN;
    _trail = Planet::TRAIL;
    _isAlien = true;
}

void Sprite::setupZombie(const Planet &planet)
{
    randomiseAttributes(_health, 100, 300);
    randomiseAttributes(_attack, 10, 30);
    randomiseAttributes(_range, 1, min(planet.getRows(), planet.getCols()) / 2 - 1);
    _icon = Planet::ZOMBIE;
    _trail = Planet::EMPTY_SPACE;
}

void Sprite::randomiseAttributes(int &attributes, int min_, int max_)
{
    attributes = rand() % max_ + min_;
}

void Sprite::randomisePosition(const Planet &planet)
{
    _row = rand() % planet.getRows();
    _col = rand() % planet.getCols();
}

bool Sprite::isMovable(Planet &planet, int row, int col)
{
    bool checkIsNotRock = planet.getObject(row, col) != Planet::ROCK;
    bool checkIsNotAlien = planet.getObject(row, col) != Planet::ALIEN;
    bool checkIsNotZombie = planet.getObject(row, col) != Planet::ZOMBIE;

    return checkIsNotRock && checkIsNotAlien && checkIsNotZombie;
}

bool Sprite::isEnemy(Planet &planet, int row, int col)
{
    bool checkIsAlien = planet.getObject(row, col) == Planet::ALIEN;
    bool checkIsZombie = planet.getObject(row, col) == Planet::ZOMBIE;

    return (_isAlien && checkIsZombie) || (!_isAlien && checkIsAlien);
}

void Sprite::detectObject(Planet &planet, vector<Sprite> &zombies, int row, int col)
{
    if (planet.getObject(row, col) == Planet::ARROW_UP)
    {
        cout << endl
             << "\nAlien finds an arrow.\n Alien's attack increased by 20." << endl;
        _attack += 20;
        _direction = Sprite::UP;
    }
    else if (planet.getObject(row, col) == Planet::ARROW_DOWN)
    {
        cout << endl
             << "\nAlien finds an arrow.\n Alien's attack increased by 20." << endl;
        _attack += 20;
        _direction = Sprite::DOWN;
    }
    else if (planet.getObject(row, col) == Planet::ARROW_LEFT)
    {
        cout << endl
             << "\nAlien finds an arrow.\n Alien's attack increased by 20." << endl;
        _attack += 20;
        _direction = Sprite::LEFT;
    }
    else if (planet.getObject(row, col) == Planet::ARROW_RIGHT)
    {
        cout << endl
             << "\nAlien finds an arrow.\n Alien's attack increased by 20." << endl;
        _attack += 20;
        _direction = Sprite::RIGHT;
    }
    else if (planet.getObject(row, col) == Planet::HEALTH)
    {
        cout << endl
             << "\nAlien finds a health pack.\nAlien's health increased by 20." << endl;
        _health += 20;
    }
    else if (planet.getObject(row, col) == Planet::ROCK)
    {
        cout << endl
             << "\nAlien stumbles upon a rock." << endl;

        if (planet.getObject(row, col) == Planet::POD)
        {
            cout << "\nAlien found a pod underneath rock." << endl;
        }
        else if (planet.getObject(row, col) == Planet::HEALTH)
        {
            cout << "\nAlien found health pack underneath rock." << endl;
        }
    }

    else if (planet.getObject(row, col) == Planet::POD)
    {
        cout << "\nAlien finds a pod.\n";
        int startZombieCount = 1;
        int current = 0;
        int currentPoint = calculateDistancePoint(zombies.at(0), row, col);
        cout << "Zombie " << 0 + startZombieCount << " receives a damage of 20" << endl;

        for (int i = 1; i < zombies.size(); i++)
        {
            int newPoint = calculateDistancePoint(zombies.at(i), row, col);
            if (newPoint < currentPoint)
            {
                current = i;
                currentPoint = newPoint;
            }
        }
        int podDamage = 20;
        zombies.at(current).receiveDamage(podDamage);

        if (zombies.at(current).getHealth() <= 0)
        {
            cout << " Zombie " << current + startZombieCount << " is dead" << endl;
        }
        else
        {
            cout << " Zombie " << current + startZombieCount << " is still alive" << endl;
        }
    }
}

int Sprite::calculateDistancePoint(Sprite &zombie, int row, int col)
{
    return abs(zombie.getRow() - row) + abs(zombie.getCol() - col) + (zombie.getRow() == row) + (zombie.getCol() == col);
}

void Sprite::move(Planet &planet, Sprite &alien, vector<Sprite> &zombies, char direction)
{
    // FOR FUTURE CHECK
    int futureRow = _row;
    int futureCol = _col;

    if (direction == Sprite::UP)
    {
        futureRow--;
    }
    else if (direction == Sprite::DOWN)
    {
        futureRow++;
    }
    else if (direction == Sprite::RIGHT)
    {
        futureCol++;
    }
    else if (direction == Sprite::LEFT)
    {
        futureCol--;
    }

    if (planet.isInside(futureRow, futureCol) && isMovable(planet, futureRow, futureCol))
    {
        if (_isAlien)
            detectObject(planet, zombies, futureRow, futureCol);

        // UPDATE CURRENT POSITION
        planet.setObject(_row, _col, _trail);
        _row = futureRow;
        _col = futureCol;
        planet.setObject(_row, _col, _icon);
    }
    else if (planet.isInside(futureRow, futureCol) && planet.getObject(futureRow, futureCol) == Planet::ROCK)
    {
        //"Alien stumbles upon a rock.\n Alien discovers a pod beneath the rock.\n"
        char rockPod[] = {
            Planet::EMPTY_SPACE, Planet::HEALTH, Planet::POD};

        int item = 3;
        int random = rand() % item;
        planet.setObject(futureRow, futureCol, rockPod[random]);
        _isEndingMoving = true;
    }
    else if (planet.isInside(futureRow, futureCol) && isEnemy(planet, futureRow, futureCol))
    {
        if (_isAlien)
        {
            int zombieIndex = findZombie(zombies, futureRow, futureCol);
            cout << "Alien attacks zombie." << zombieIndex << " " << _attack << endl;
            zombies.at(zombieIndex).receiveDamage(_attack);
        }
        else
        {
            cout << "Zombie attacks Alien" << endl;
            alien.receiveDamage(_attack);
        }
        _isEndingMoving = true;
    }
    else
    {
        _isEndingMoving = true;
        cout << "Alien hits a border" << endl;
        system("pause");
    }
}

void Sprite::moveAlien(Planet &planet, Sprite &alien, vector<Sprite> &zombies, char direction)
{
    _isEndingMoving = false;
    _direction = direction;

    while (!_isEndingMoving)
    {
        move(planet, alien, zombies, _direction);
        // system("cls");
        planet.display();
        system("pause");
    }
}

void Sprite::receiveDamage(int damage)
{
    _health -= damage;
}

int Sprite::findZombie(vector<Sprite> &zombies, int row, int col)
{
    for (int i = 0; i < zombies.size(); i++)
    {
        if (zombies.at(i).getRow() == row && zombies.at(i).getCol() == col)
            return i;
    }
    return 0;
}

int Sprite::getAttack() const
{
    return _attack;
}

int Sprite::getHealth() const
{
    return _health;
}

int Sprite::getRange() const
{
    return _range;
}

int Sprite::getRow() const
{
    return _row;
}

int Sprite::getCol() const
{
    return _col;
}

char Sprite::getIcon() const
{
    return _icon;
}

char Sprite::getTrail() const
{
    return _trail;
}

void Sprite::setAttack(int attack)
{
    _attack = attack;
}
void Sprite::setHealth(int health)
{
    _health = health;
}
void Sprite::setRange(int range)
{
    _range = range;
}
void Sprite::setRow(int row)
{
    _row = row;
}
void Sprite::setCol(int col)
{
    _col = col;
}

////////////////////////////////////////////////////////////////////////

void randomiseZombiePosition(Planet &planet, Sprite &zombie)
{
    zombie.randomisePosition(planet);

    // MAKING SURE THAT ZOMBIE NOT OVERLAPPING THE ALIEN OR ANOTHER ZOMBIE
    while (
        planet.getObject(zombie.getRow(), zombie.getCol()) == Planet::ALIEN ||
        planet.getObject(zombie.getRow(), zombie.getCol()) == Planet::ZOMBIE)
    {
        zombie.randomisePosition(planet);
    }
}

void setupGame(Planet &planet, Sprite &alien, vector<Sprite> &zombies)
{
    // SETUP PLANET
    planet.randomiseObject();

    // SETUP ALIEN
    alien.setupAlien(planet);
    planet.setObject(alien.getRow(), alien.getCol(), alien.getIcon());

    // SETUP ZOMBIE
    // FOR DEBUGGING PURPOSES
    int numOfZombie = rand() % 9 + 1;
    zombies.clear();
    zombies.resize(numOfZombie);

    for (int i = 0; i < numOfZombie; i++)
    {
        zombies.at(i).setupZombie(planet);
        randomiseZombiePosition(planet, zombies.at(i));
        planet.setObject(
            zombies.at(i).getRow(),
            zombies.at(i).getCol(),
            zombies.at(i).getIcon());
    }
}

void changeArrowDirection(Planet &planet, int row, int col, string direction)
{
    if (
        planet.getObject(row, col) == Planet::ARROW_UP ||
        planet.getObject(row, col) == Planet::ARROW_DOWN ||
        planet.getObject(row, col) == Planet::ARROW_LEFT ||
        planet.getObject(row, col) == Planet::ARROW_RIGHT)
    {
        if (direction == "up")
            planet.setObject(row, col, Planet::ARROW_UP);
        else if (direction == "down")
            planet.setObject(row, col, Planet::ARROW_DOWN);
        else if (direction == "left")
            planet.setObject(row, col, Planet::ARROW_LEFT);
        else if (direction == "right")
            planet.setObject(row, col, Planet::ARROW_RIGHT);
    }
}

void moveAlien(Planet &planet, Sprite &alien, vector<Sprite> &zombies, string direction)
{
    if (direction == "up")
        alien.moveAlien(planet, alien, zombies, Sprite::UP);
    else if (direction == "down")
        alien.moveAlien(planet, alien, zombies, Sprite::DOWN);
    else if (direction == "left")
        alien.moveAlien(planet, alien, zombies, Sprite::LEFT);
    else if (direction == "right")
        alien.moveAlien(planet, alien, zombies, Sprite::RIGHT);
}

void save(string filename, Planet &planet, Sprite &alien, vector<Sprite> &zombies)
{
    ofstream file(filename);

    file << alien.getRow() << SEPARATOR
         << alien.getCol() << SEPARATOR
         << alien.getHealth() << SEPARATOR
         << alien.getAttack() << SEPARATOR;

    file << zombies.size() << SEPARATOR;

    for (int i = 0; i < zombies.size(); i++)
    {
        file << zombies.at(i).getRow() << SEPARATOR
             << zombies.at(i).getCol() << SEPARATOR
             << zombies.at(i).getHealth() << SEPARATOR
             << zombies.at(i).getAttack() << SEPARATOR
             << zombies.at(i).getRange() << SEPARATOR;
    }

    file << planet.getRows() << SEPARATOR
         << planet.getCols() << SEPARATOR;

    for (int row = 0; row < planet.getRows(); row++)
    {
        for (int col = 0; col < planet.getCols(); col++)
        {
            file << (int)planet.getObject(row, col) << SEPARATOR; // Casting - Convert char to int ASCII table
        }
    }
}

void load(string filename, Planet &planet, Sprite &alien, vector<Sprite> &zombies)
{
    ifstream file(filename);
    string data;

    // READ DATA LINE BY LINE
    getline(file, data, SEPARATOR);
    alien.setRow(stoi(data));
    getline(file, data, SEPARATOR);
    alien.setCol(stoi(data));
    getline(file, data, SEPARATOR);
    alien.setHealth(stoi(data));
    getline(file, data, SEPARATOR);
    alien.setAttack(stoi(data));

    getline(file, data, SEPARATOR);
    zombies.clear();
    zombies.resize(stoi(data));

    for (int i = 0; i < zombies.size(); i++)
    {
        getline(file, data, SEPARATOR);
        zombies.at(i).setRow(stoi(data));
        getline(file, data, SEPARATOR);
        zombies.at(i).setCol(stoi(data));
        getline(file, data, SEPARATOR);
        zombies.at(i).setHealth(stoi(data));
        getline(file, data, SEPARATOR);
        zombies.at(i).setAttack(stoi(data));
        getline(file, data, SEPARATOR);
        zombies.at(i).setRange(stoi(data));
    }

    getline(file, data, SEPARATOR);
    int rows = stoi(data);
    getline(file, data, SEPARATOR);
    int cols = stoi(data);

    planet.init(rows, cols);

    for (int row = 0; row < planet.getRows(); row++)
    {
        for (int col = 0; col < planet.getCols(); col++)
        {
            getline(file, data, SEPARATOR);
            planet.setObject(row, col, (char)stoi(data));
        }
    }
}

int main()
{
    srand(time(NULL));
    displayIntro();

    // INITIALIZE OUR OBJECT
    Planet planet;
    Sprite alien;
    vector<Sprite> zombies;

    // INITIALIZE FOR GAME
    int row, col;
    string command;

    int arrowRow, arrowCol;
    string arrowDirection;

    // FOR DEBUGGING PURPOSES
    // int ENDING_THE_GAME_COUNTER = 0;

    // PROGRAM LOOP
    bool isComplete = false;

    while (!isComplete)
    {

        // GETTING USER OPTION
        displayOption();
        int inputOption;
        cin >> inputOption;

        // REFER ASCII TABLE
        while (inputOption < 1 || inputOption > 5)
        {
            // ERROR CHECKING
            cout << "ERROR: Please input between 1-5 =>> ";
            cin >> inputOption;
        }
        displayOptionResult(inputOption);

        if (inputOption == 1)
        {
            // EXECUTE GAME
            cout << "PLEASE ENTER ODD NUMBER FOR NUMBER OF ROW AND COLUMN." << endl;
            cout << "ENTER ROW: " << endl;
            cin >> row;
            cout << "ENTER COL: " << endl;
            cin >> col;
            cout << endl;


            while ((row % 2 == 0) || (col % 2 == 0))
            {
                cout << "INVALID INPUT!" << endl;
                cout << "PLEASE ENTER ODD NUMBER ONLY." << endl;
                cout << "ENTER ROW: " << endl;
                cin >> row;
                cout << "ENTER COL: " << endl;
                cin >> col;
                cout << endl;
            }
            planet.init(row, col);
            setupGame(planet, alien, zombies);

            // GAME LOOP
            bool isGameComplete = false;
            while (!isGameComplete)
            {
                // DISPLAY MAP
                displayFullGameMap(planet, alien, zombies);

                // RECEIVE COMMAND
                cout << "Command > ";
                cin >> command;

                // DIFFERENT COMMAND EXECUTION

                if (command == "direction")
                {
                    cout << "Command > Direction > ";
                    cin >> command;
                    moveAlien(planet, alien, zombies, command);
                }
                else if (command == "arrow")
                {
                    cout << "ENTER ROW: ";
                    cin >> arrowRow;
                    while (arrowRow > planet.getRows())
                    {
                        cin >> arrowRow;
                    }

                    cout << "ENTER COL: ";
                    cin >> arrowCol;
                    while (arrowCol > planet.getCols())
                    {
                        cin >> arrowCol;
                    }

                    cout << "ENTER DIRECTION: ";
                    cin >> arrowDirection;
                    while (!(arrowDirection == "up" || arrowDirection == "down" || arrowDirection == "right" || arrowDirection == "left"))
                    {
                        cin >> arrowDirection;
                    }

                    changeArrowDirection(planet, arrowRow - 1, arrowCol - 1, arrowDirection);
                }
                else if (command == "help")
                {
                    displayGameOption();
                }
                else if (command == "save")
                {
                    string fileName;
                    cout << "Enter (filename).txt: ";
                    cin >> fileName;

                    save(fileName, planet, alien, zombies);
                }
                else if(command == "load")
                {
                    string filename;
                    cout << "Enter filename to load: ";
                    cin >> filename;

                    load(filename, planet, alien, zombies);
                }
                else if(command == "quit")
                {
                    isComplete = true;
                    isGameComplete = true;
                }

                planet.replaceTrail();
                for (int i = 0; i < zombies.size(); i++)
                {
                    char direction[] = {Sprite::UP, Sprite::DOWN, Sprite::RIGHT, Sprite::LEFT};
                    int dirSize = 4;
                    char zombieDirection = direction[rand() % dirSize];
                    zombies.at(i).move(planet, alien, zombies, zombieDirection);
                }

                system("pause");
                system("cls");
            }
        }
        else if (inputOption == 5)
        {
            // END THE PROGRAM
            isComplete = true;
        }
    }

}
