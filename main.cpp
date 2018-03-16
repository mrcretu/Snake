#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>

using namespace sf;
int score=0;
int rows=30,columns=25;
int length=25;
int width = length*rows;
int height = length*columns;
int ok=0;
int dir=0,num=3;
bool gameover=false;
bool imput=false;
bool valid=false;
bool pausegame = false;

float delay=0.1;

struct Snake
{
    int x,y;
}  snake[1400];

struct Fruct
{
    int x,y;
} fruit;


void Logic()
{
    for (int i=num; i>0; --i)
    {
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }

    if (dir==0) snake[0].y+=1;
    if (dir==1) snake[0].x-=1;
    if (dir==2) snake[0].x+=1;
    if (dir==3) snake[0].y-=1;

    if ((snake[0].x==fruit.x) && (snake[0].y==fruit.y))
    {
        num++;
        do
        {
            valid=true;
            fruit.x=rand() % rows;
            fruit.y=rand() % columns;

            for(int i=1; i<num; i++)
                if((snake[i].x==fruit.x)&&(snake[i].y)==(fruit.y))
                    valid=false;
        }
        while(valid==false);


        score++;
    }
    if (snake[0].x>=rows) gameover=true;
    if (snake[0].x<0) gameover=true;
    if (snake[0].y>columns-1) gameover=true;
    if (snake[0].y<0) gameover=true;

    for (int i=1;i<num;i++)
     if (snake[0].x==snake[i].x && snake[0].y==snake[i].y) gameover=true;
imput=false;
 }

 void Play()
{
    srand(time(0));
    RenderWindow window(VideoMode(width, height), "Snake Game!");

	Texture t1,t2,t3;
	t1.loadFromFile("images/fundal2.jpg");
	t2.loadFromFile("images/sarpe.png");
	t3.loadFromFile("images/bal.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);

        Clock clock;

    float timer=0;


	fruit.x=10;
    fruit.y=10;

    Event e;
    while (window.isOpen())
    {
        if (gameover==true)
            {
                window.close();
            }
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;


        while (window.pollEvent(e))
        {
            if (gameover==true)
                window.close();
            if (e.type == Event::Closed)
                window.close();
            if (gameover==true)
                window.close();
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left) and dir!=2)and imput==false) {dir=1;imput=true;}
	    if ((Keyboard::isKeyPressed(Keyboard::Right) and dir!=1)and imput==false)  {dir=2;imput=true;}
	    if ((Keyboard::isKeyPressed(Keyboard::Up) and dir!=0)and imput==false) {dir=3;imput=true;}
		if ((Keyboard::isKeyPressed(Keyboard::Down) and dir!=3)and imput==false) {dir=0;imput=true;}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) gameover=true;
		if (Keyboard::isKeyPressed(Keyboard::P))  pausegame=true;
		if (Keyboard::isKeyPressed(Keyboard::Return)) pausegame=false;
		if ((timer>delay)&&(!pausegame)) {timer=0; Logic();}

   ////// draw  ///////
    window.clear();
    window.draw(sprite1);


    //set snake

        for (int i=0; i<num; i++)
            {sprite2.setPosition(snake[i].x*length, snake[i].y*length);
            window.draw(sprite2);
        }
         //set food

        if(ok==0)
        {
            sprite3.setPosition(fruit.x*length, fruit.y*length);
            window.draw(sprite3);

        }

        window.display();
    }

    //return 0;
}
void Meniu()
{

    start:
    sf::RenderWindow window(sf::VideoMode(340, 250), "Snake | Menu");
	Texture t;
    t.loadFromFile("images/menu.jpg");

    Sprite sprite1(t);

	Menu menu(170, 125);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
					    window.close();
                        Play();
                        goto start;
						break;
					case 1:
						//eroare
						break;
					case 2:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();
        window.draw(sprite1);
		menu.draw(window);

		window.display();
	}
}
int main()
{
	Meniu();
}
