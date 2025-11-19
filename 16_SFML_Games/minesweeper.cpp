#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int tileSize=32;
    int dataBoard[12][12];
    int displayBoard[12][12]; //for showing

    Texture tileTexture;
    tileTexture.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite tileSprite(tileTexture);

    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        displayBoard[i][j]=10;
        if (rand()%5==0)  dataBoard[i][j]=9;
        else dataBoard[i][j]=0;
      }

    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        int n=0;
        if (dataBoard[i][j]==9) continue;
        if (dataBoard[i+1][j]==9) n++;
        if (dataBoard[i][j+1]==9) n++;
        if (dataBoard[i-1][j]==9) n++;
        if (dataBoard[i][j-1]==9) n++;
        if (dataBoard[i+1][j+1]==9) n++;
        if (dataBoard[i-1][j-1]==9) n++;
        if (dataBoard[i-1][j+1]==9) n++;
        if (dataBoard[i+1][j-1]==9) n++;
        dataBoard[i][j]=n;
      }

    while (app.isOpen())
    {
        Vector2i mousePos = Mouse::getPosition(app);
        int tileX = mousePos.x/tileSize;
        int tileY = mousePos.y/tileSize;

        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::MouseButtonPressed)
              if (event.key.code == Mouse::Left) displayBoard[tileX][tileY]=dataBoard[tileX][tileY];
              else if (event.key.code == Mouse::Right) displayBoard[tileX][tileY]=11;
        }

        app.clear(Color::White);

        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
           if (displayBoard[tileX][tileY]==9) displayBoard[i][j]=dataBoard[i][j];
           tileSprite.setTextureRect(IntRect(displayBoard[i][j]*tileSize,0,tileSize,tileSize));
           tileSprite.setPosition(i*tileSize, j*tileSize);
           app.draw(tileSprite);
          }

        app.display();
    }

    return 0;
}
