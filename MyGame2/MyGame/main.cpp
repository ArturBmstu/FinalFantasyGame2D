#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include "Player.h"
#include <iostream>
#include <sstream>
#define WINWIDTH 1368
#define WINHEIGHT 768
#define NUMRABBITS 3

using namespace sf;


int main()
{
	RenderWindow window(sf::VideoMode(WINWIDTH, WINHEIGHT), "Final Fantasy");
	view.reset(sf::FloatRect(0, 0, WINWIDTH, WINHEIGHT));

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	//text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(Text::Bold);

	Text textwin("", font, 40);
	textwin.setStyle(Text::Bold);

	Text textRepeat("Repeat", font, 20);
	//textwin.setColor(Color::Red);

	Map map("images/map.png", 255, 255, 255, m);
	Tile level("images/levelComplete.png", 255, 255, 255);
	Tile button("images/кнопушка.png", 0, 0, 0);

	std::ostringstream levelComplete;
	levelComplete << "Уровень пройден!!!";
	std::ostringstream Repeat;
	levelComplete << "Repeat";


	Player Celes("CelesChere_sprite.png", 50, 75, 176, 0, 17, 26, 0, 128, 128, 75, 150, 43, 43, 124, 156, 42, 10, 124, 174, 42, 10);

	Enemy* rabbits[3] = {
		new Enemy("rabbit.png", 100, 100, 9, 5, 33, 50, 255, 0, 255, "rabbit.png", 9, 138, 33, 33, 255, 0, 255),
		new Enemy("rabbit.png", 250, 300, 9, 5, 33, 50, 255, 0, 255, "rabbit.png", 9, 138, 33, 33, 255, 0, 255),
		new Enemy("rabbit.png", 400, 400, 9, 5, 33, 50, 255, 0, 255, "rabbit.png", 9, 138, 33, 33, 255, 0, 255)
	};

	int toMoveFrame = 0;
	float CurrentFrame = 0;//хранит текущий кадр
	float CurrentEnemyFrame = 0;
	float CurrentWeaponFrame = 0;
	Clock clock;
	bool rightPress = true;
	int check = 0;
	int pressX;
	int pressY;
	int count = 0;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		static float dt[NUMRABBITS] = {0};
		time = time / 800;

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed){//если нажата клавиша мыши
				if (button.S.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
				{
					std::cout << "restart" << std::endl;
					for (int i = 0; i < NUMRABBITS; i++)
						rabbits[i]->dead = false;
					Celes.Restart(50, 75);
					map.TileMap = m;
				}
			}
		}
		
		
		


		
		for (int i = 0; i < NUMRABBITS; i++){
			rabbits[i]->atack(time);
		}
		
		Celes.isFight = false;
		getplayercoordinateforview(Celes.getplayercoordinateX(), Celes.getplayercoordinateY());
		if (!Celes.dead) {

			if (((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))))) { //если нажата клавиша стрелка влево или англ буква
				Celes.dir = 1; Celes.speed = 0.1;
				Celes.CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
				if (Celes.CurrentFrame > 3) Celes.CurrentFrame -= 3;
				Celes.sprite.setTextureRect(IntRect(36 + int(Celes.CurrentFrame) * 17, 63, 17, 26)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
				getplayercoordinateforview(Celes.getplayercoordinateX(), Celes.getplayercoordinateY());
			}

			if (((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))) {
				Celes.dir = 0; Celes.speed = 0.1;
				Celes.CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
				if (Celes.CurrentFrame > 3) Celes.CurrentFrame -= 3;
				Celes.sprite.setTextureRect(IntRect(459 + int(Celes.CurrentFrame) * 17, 63, 17, 26)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
				getplayercoordinateforview(Celes.getplayercoordinateX(), Celes.getplayercoordinateY());
			}

			if (((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))))) { //если нажата клавиша стрелка влево или англ буква
				Celes.dir = 3; Celes.speed = 0.1;
				Celes.CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
				if (Celes.CurrentFrame > 3) Celes.CurrentFrame -= 3;
				Celes.sprite.setTextureRect(IntRect(33 + int(Celes.CurrentFrame) * 17, 0, 17, 26)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
				getplayercoordinateforview(Celes.getplayercoordinateX(), Celes.getplayercoordinateY());
			}

			if (((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))))) { //если нажата клавиша стрелка влево или англ буква
				Celes.dir = 2; Celes.speed = 0.1;
				Celes.CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
				if (Celes.CurrentFrame > 3) Celes.CurrentFrame -= 3;
				Celes.sprite.setTextureRect(IntRect(34 + int(Celes.CurrentFrame) * 17, 32, 17, 26)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
				getplayercoordinateforview(Celes.getplayercoordinateX(), Celes.getplayercoordinateY());
			}

			if (((Keyboard::isKeyPressed(Keyboard::Space)))) { //если нажата клавиша стрелка влево или англ буква
				Celes.isFight = true;
				Celes.CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
				if (Celes.dir == 1)
					Celes.sprite.setTextureRect(IntRect(99, 91, 34, 26)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
				if (Celes.dir == 0){
					Celes.sprite.setTextureRect(IntRect(411, 91, 34, 26));
				}
				getplayercoordinateforview(Celes.getplayercoordinateX(), Celes.getplayercoordinateY());
			}

			
		}

		Celes.isDead(time, rabbits, NUMRABBITS);
		Celes.update(time);

		Celes.interactionWithMap(map);

		
		for (int i = 0; i < NUMRABBITS; i++)
			rabbits[i]->isDead(&Celes);


		for (int i = 0; i < NUMRABBITS; i++){
			rabbits[i]->update(time);
	
		}

		viewmap(time);//функция скроллинга карты, передаем ей время sfml
		changeview();
		window.setView(view);//"оживляем" камеру в окне sfml
		window.clear();
		map.update(window);
		std::ostringstream playerScore;    // объявили переменную
		playerScore << Celes.playerScore;		//занесли в нее число очков, то есть формируем строку
		text.setString("Собрано монет:" + playerScore.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(view.getCenter().x - 600, view.getCenter().y - 300);//задаем позицию текста, отступая от центра камеры
		Celes.face.setPosition(view.getCenter().x - 600, view.getCenter().y - 350);
		if (!Celes.dead){
			for (int i = 0, diff = 0; i < 3; i++, diff += 41){
				Celes.HP[i].setPosition(view.getCenter().x - 550 + diff, view.getCenter().y - 330);
				Celes.MP[i].setPosition(view.getCenter().x - 550 + diff, view.getCenter().y - 320);

					window.draw(Celes.HP[i]);
					window.draw(Celes.MP[i]);
			}
		}
		
		window.draw(text);
		window.draw(Celes.sprite);//выводим спрайт на экран
		window.draw(Celes.face);
		for (int i = 0; i < NUMRABBITS; i++)
			if (!rabbits[i]->dead){
				window.draw(rabbits[i]->sprite);
				window.draw(rabbits[i]->axe.sprite);
			}

		for (int i = 0, count = 0; i < NUMRABBITS; i++){
			if (rabbits[i]->dead)
				count++;
			if (count == NUMRABBITS){
				level.S.setPosition(view.getCenter().x - 250, view.getCenter().y - 100);
				window.draw(level.S);
				textwin.setString(levelComplete.str());
				textwin.setPosition(view.getCenter().x - 150, view.getCenter().y);
				window.draw(textwin);
				button.S.setPosition(view.getCenter().x - 60, view.getCenter().y + 75);
				textRepeat.setString(Repeat.str());
				textRepeat.setPosition(view.getCenter().x - 60, view.getCenter().y + 75);
				window.draw(textRepeat);
				window.draw(button.S);
			}
		}
		window.display();
	}
	return 0;
}
