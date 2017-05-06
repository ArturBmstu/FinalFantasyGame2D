#include <SFML\Graphics.hpp>
#include <iostream>
#include "map.h"



class Base{

protected:
	float x, y;
	float dx, dy,  w, h;
	String File;
	Image image;
	Texture texture;

public :
	bool dead = false;
	Sprite sprite;
	float speed;
	float CurrentFrame = 0;

	Base(String F, float X, float Y, int spritex, int spritey, int height, int width, int colorx, int colory, int colorz){
		dx = 0; dy = 0; speed = 0;
		File = F;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(colorx, colory, colorz));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		w = width;
		h = height;
		sprite.setTextureRect(IntRect(spritex, spritey, h, w));
	}

	float getplayercoordinateX(){	//���� ������� ����� �������� ���������� �	
		return x;
	}
	float getplayercoordinateY(){	//���� ������� ����� �������� ���������� Y 	
		return y;
	}

	float getwidth(){
		return w ;
	}

	float getheight(){
		return h ;
	}
	virtual void update(float){}
};

class Weapon : public Base{

public:

	Weapon(String F, float X, float Y, int spritex, int spritey, int height, int width, int colorx, int colory, int colorz)
		: Base(F, X, Y, spritex, spritey, height, width, colorx, colory, colorz){
		sprite.setPosition(x, y);
	}


	void update(float time)
	{
		x += speed*time;
		sprite.setPosition(x, y);

		CurrentFrame += 0.005*time;
		if (CurrentFrame > 4){
			CurrentFrame -= 4;
		}

		sprite.setTextureRect(IntRect(9 + int(CurrentFrame) * 33, 138, w, h));
	}

	FloatRect getWepRect()
	{
		return FloatRect(x, y, w, h);
	}

	void setx(int f){
		x = f;
	}

	void sety(int l){
		y = l;
	}
};

 class Player;

class Enemy : public Base {
public:
	Rect<float> rect;
	friend Weapon;
	Weapon axe;
		
	Enemy(String F, float X, float Y, int spritex, int spritey, int height, int width, int colorx, int colory, int colorz,
		String wF, int wspritex, int wspritey, int wheight, int wwidth, int wcolorx, int wcolory, int wcolorz)
		: Base(F, X, Y, spritex, spritey, height, width, colorx, colory, colorz)
		, axe(wF, X + 33, Y, wspritex, wspritey, wheight, wwidth, wcolorx, wcolory, wcolorz){

		rect = FloatRect(x, y, w, h);
		sprite.setPosition(x, y);
		axe.speed = 0.5;
	}

	bool isDead(Player* Celes);


	void atack(float& dt){
		if (axe.getplayercoordinateX() > x + 350 ){
			axe.setx (x );
			axe.sety ( y);
			axe.sprite.setPosition(x , y);
		}
	}

	void update(float time)
	{
		axe.update(time);

		CurrentFrame += 0.005*time;
		if (CurrentFrame > 7)
			CurrentFrame -= 7;

		if (!dead)
			sprite.setTextureRect(IntRect(5 + int(CurrentFrame) * 33, 55, h, w));
	}
};



class Player : public Base {
private:
public:
	int dir = 0;
	int deadX = -1, deadY = -1;
	bool isFight = false;
	Sprite HP[3];
	Sprite MP[3];
	int playerScore = 0;
	Sprite face;

	Player (String F, float X, float Y, int spritex, int spritey, int height, int width, int colorx, int colory, int colorz, int facex, int facey,
		int faceheight, int facewidth, int hpx, int hpy, int hpwidth, int hpheight, int mpx, int mpy, int mpwidth, int mpheight)
		: Base(F, X, Y, spritex, spritey, height, width, colorx, colory, colorz){
		face.setTexture(texture);
		for (int i = 0; i < 3; i++){
			HP[i].setTexture(texture);
			MP[i].setTexture(texture);
		}
		face.setTextureRect(IntRect(facex, facey, facewidth, faceheight));
		for (int i = 0; i < 3; i++){
			HP[i].setTextureRect(IntRect(hpx, hpy, hpwidth, hpheight));
			MP[i].setTextureRect(IntRect(mpx, mpy, mpwidth, mpheight));
		}
	}

	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx*time;
		y += dy*time;
		speed = 0;
		if (dead ){
			sprite.setPosition(deadX, deadY);
			if (Keyboard::isKeyPressed(Keyboard::R)){
				dead = false;
				deadX = -1;
				deadY = -1;
				sprite.setTextureRect(IntRect(176, 0, 17, 26));
				sprite.setPosition(50.0, 50.0);
				x = 50.0;
				y = 50.0;
			}
		}
		else sprite.setPosition(x, y);

		CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������

	}

	void interactionWithMap(Map &map)//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������,, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = x / 32; j < (x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{

			if (map.TileMap[i][j] == 'm')
			{
				playerScore++;
				map.TileMap[i][j] = ' ';
			}
			if (map.TileMap[i][j] == 't' || map.TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
			{
				if (dy > 0)//���� �� ��� ����,
				{
					y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.

				}
				if (dy < 0)
				{
					y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
				}
				if (dx > 0)
				{
					x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
				}
				if (dx < 0)
				{
					x = j * 32 + 32;//���������� ���� �����
				}
			}
		}
	}

	FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}

	void isDead(float time, Enemy** e, int len){

		for (int i = 0; i < len; i++)
		if (!e[i]->dead && ( (getRect().intersects(e[i]->rect) && !isFight) || getRect().intersects(e[i]->axe.getWepRect()) ))

		{	
			if (deadX == -1 && deadY == -1){
				deadX = x;
				deadY = y;
			}
			dead = true;
			sprite.setTextureRect(IntRect(44, 151, 29, 21));
		}
	}

	void Restart(int X, int Y){
		sprite.setPosition(X, Y);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(176, 0, 17, 26));

	}
};

bool Enemy::isDead(Player* Celes){
	if (rect.intersects(Celes->getRect()) && Celes->isFight)
		dead = true;
	return dead;
}
