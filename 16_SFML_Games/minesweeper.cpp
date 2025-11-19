#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

enum TileType
{
    Empty = 0,
    One = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Mine = 9,
    Unrevealed = 10,
    Flag = 11
};

const int BOARD_SIZE = 10;
const int GRID_SIZE = 12;
const int TILE_SIZE = 32;
const int MINE_CHANCE = 5;

void initBoards(int dataBoard[GRID_SIZE][GRID_SIZE], int displayBoard[GRID_SIZE][GRID_SIZE]);
void calculateAdjacentMines(int dataBoard[GRID_SIZE][GRID_SIZE]);
void setupGame(int dataBoard[GRID_SIZE][GRID_SIZE], int displayBoard[GRID_SIZE][GRID_SIZE]);
void loadAssets(Texture& tileTexture, Sprite& tileSprite);
void eventHandling(RenderWindow& app, int dataBoard[GRID_SIZE][GRID_SIZE], int displayBoard[GRID_SIZE][GRID_SIZE], bool& mineClicked);
void drawGame(RenderWindow& app, int displayBoard[GRID_SIZE][GRID_SIZE], int dataBoard[GRID_SIZE][GRID_SIZE], Sprite& tileSprite, bool& mineClicked);


int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int dataBoard[GRID_SIZE][GRID_SIZE];
    int displayBoard[GRID_SIZE][GRID_SIZE]; //for showing

    Texture tileTexture;
    Sprite tileSprite;

    loadAssets(tileTexture, tileSprite);
    setupGame(dataBoard, displayBoard);

    while (app.isOpen())
    {
        bool mineClicked = false;

        eventHandling(app, dataBoard, displayBoard, mineClicked);

        app.clear(Color::White);

        drawGame(app, displayBoard, dataBoard, tileSprite, mineClicked);
    }

    return 0;
}


void setupGame(int dataBoard[GRID_SIZE][GRID_SIZE], int displayBoard[GRID_SIZE][GRID_SIZE])
{
    initBoards(dataBoard, displayBoard);
    calculateAdjacentMines(dataBoard);
}


void loadAssets(Texture& tileTexture, Sprite& tileSprite)
{
    tileTexture.loadFromFile("images/minesweeper/tiles.jpg");
    tileSprite.setTexture(tileTexture);
}


void eventHandling(RenderWindow& app, int dataBoard[GRID_SIZE][GRID_SIZE], int displayBoard[GRID_SIZE][GRID_SIZE], bool& mineClicked)
{
    Vector2i mousePos = Mouse::getPosition(app);
    int tileX = mousePos.x / TILE_SIZE;
    int tileY = mousePos.y / TILE_SIZE;

    Event event;
    while (app.pollEvent(event))
    {
        if (event.type == Event::Closed)
            app.close();

        if (event.type == Event::MouseButtonPressed)
            if (event.key.code == Mouse::Left)
            {
                if (dataBoard[tileX][tileY] == TileType::Mine)
                    mineClicked = true;

                displayBoard[tileX][tileY] = dataBoard[tileX][tileY];
            }
            else if (event.key.code == Mouse::Right) displayBoard[tileX][tileY] = TileType::Flag;
    }
}


void drawGame(RenderWindow& app, int displayBoard[GRID_SIZE][GRID_SIZE], int dataBoard[GRID_SIZE][GRID_SIZE], Sprite& tileSprite, bool& mineClicked)
{
    for (int i = 1; i <= BOARD_SIZE; i++)
        for (int j = 1; j <= BOARD_SIZE; j++)
        {
            if (mineClicked == true) displayBoard[i][j] = dataBoard[i][j];
            tileSprite.setTextureRect(IntRect(displayBoard[i][j] * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
            tileSprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
            app.draw(tileSprite);
        }

    app.display();
}


void initBoards(int dataBoard[GRID_SIZE][GRID_SIZE], int displayBoard[GRID_SIZE][GRID_SIZE])
{
    for (int i = 1; i <= BOARD_SIZE; i++)
        for (int j = 1; j <= BOARD_SIZE; j++)
        {
            displayBoard[i][j] = TileType::Unrevealed;
            if (rand() % MINE_CHANCE == 0)  dataBoard[i][j] = TileType::Mine;
            else dataBoard[i][j] = TileType::Empty;
        }
}


void calculateAdjacentMines(int dataBoard[GRID_SIZE][GRID_SIZE])
{
    for (int i = 1; i <= BOARD_SIZE; i++)
        for (int j = 1; j <= BOARD_SIZE; j++)
        {
            int numAdjacentMines = 0;
            if (dataBoard[i][j] == TileType::Mine) continue;
            if (dataBoard[i + 1][j] == TileType::Mine) numAdjacentMines++;
            if (dataBoard[i][j + 1] == TileType::Mine) numAdjacentMines++;
            if (dataBoard[i - 1][j] == TileType::Mine) numAdjacentMines++;
            if (dataBoard[i][j - 1] == TileType::Mine) numAdjacentMines++;
            if (dataBoard[i + 1][j + 1] == TileType::Mine) numAdjacentMines++;
            if (dataBoard[i - 1][j - 1] == TileType::Mine) numAdjacentMines++;
            if (dataBoard[i - 1][j + 1] == TileType::Mine) numAdjacentMines++;
            if (dataBoard[i + 1][j - 1] == TileType::Mine) numAdjacentMines++;
            dataBoard[i][j] = numAdjacentMines;
        }
}

