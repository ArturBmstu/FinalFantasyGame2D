#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
const int HEIGHT_MAP = 32;//������ ����� ������
const int WIDTH_MAP = 57;//������ ����� ������ 

using namespace sf;
using namespace std;
vector<string> m = {
	"000000000000000000000000000000000000000000000000000000000",
	"0       m               t tt  t                         0",
	"0   t     m           tttttt         ttttttt            0",
	"0                     t  tt            tttttttt         0",
	"0       t    m                                          0",
	"0                                    tttttttt           0",
	"0         m                                             0",
	"0     m m  m                                            0",
	"0                  m                                    0",
	"0    m        m                 tttttttttt              0",
	"0        m                ttttt                 tttt    0",
	"0          m                  tt    tttttttttt          0",
	"0           m      m       ttttttttttttttt              0",
	"0                                                       0",
	"0                                                       0",
	"0                                ttttttt                0",
	"0                              ttttt                    0",
	"0             t tt  t                                   0",
	"0   t                 tttttt                            0",
	"0                     t  tt                             0",
	"0       t                                  m            0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"0                                                       0",
	"000000000000000000000000000000000000000000000000000000000",
};

class Tile{
private:
	Image I;
	Texture T;
public:
	Sprite S;

	Tile(String F, int colorx, int colory, int colorz) {

		I.loadFromFile(F);
		I.createMaskFromColor(Color(colorx, colory, colorz));
		T.loadFromImage(I);//�������� �������� ���������
		S.setTexture(T);//�������� �������� ��������
	}
};

class Map : public Tile{
public:
	vector<string> TileMap;

	Map(String F, int colorx, int colory, int colorz, vector<string> &t):
		Tile(F, colorx, colory, colorz){
		TileMap = t;
	}

	void update(RenderWindow &w){
		for (int i = 0; i < TileMap.size(); i++){
			for (int j = 0; j < TileMap[0].size(); j++)
			{
				if (TileMap[i][j] == '0')
					S.setTextureRect(IntRect(0, 64, 32, 32));
				if (TileMap[i][j] == ' ')
					S.setTextureRect(IntRect(0, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
				if (TileMap[i][j] == 't')
					S.setTextureRect(IntRect(32, 32, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
				if (TileMap[i][j] == 'm')
					S.setTextureRect(IntRect(256, 64, 32, 32));

				S.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������
				//������ ���������� �� �����
				w.draw(S);
			}
		}
	}
};
