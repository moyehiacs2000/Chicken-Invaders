#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
using namespace std;
using namespace sf;
class Score_Time{
public:
	void Score(int score, Text &mscore, Font &font);
	void TIME(Time elapsed1, Text &ttime, Font &font);
	void LIFE(int life, Text &l_life, Font &font);
	void Score_Time::Finsh(Text &finsh, Font &font);
};
class Animation
{
public:
	float Frame, speed;
	Sprite sprite;
	vector<IntRect> frames;

	Animation(){}
	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed, string s);
    void update();
	bool isEnd();
	
};
class Entity
{
public:
	float x, y, dx, dy, R, angle;
	bool life; int number;
	string name;
	Animation anim;
	Entity();
	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1, int n = -1);
	virtual void update(){};
	void draw(RenderWindow &app);
	virtual ~Entity(){};
};
class chicken_enenmy : public Entity
{
public:
	chicken_enenmy();
	void update();
};
class bullet : public Entity
{
public:
	bullet();
	void  update();
};
class player : public Entity
{
public:
	bool up, down, right, left;
	player();
	void update();

};
class chicken_f : public Entity
{
public:
	chicken_f();
	void  update();

};
class chicken_egg : public Entity
{
public:
	chicken_egg();
	void  update();
};
class asteroid : public Entity
{
public:
	asteroid();
	void update();
};
class bigenemy :public Entity{
public:
	bigenemy();
	void update();
};
class chickenenemy_egg : public Entity
{
public:
	chickenenemy_egg();
	void  update();
};
class time_score{
	int score;
	int time;
public:
	time_score();
	void Score(Font &font, Text &text_score);
	void calculate_time(Font &font, Text &text_time);
	void gameover(Font &font, Text &game_over);
	void updete(string n);
	void update_time(Time m);
};
class mohmed{
public:
	void mohmed_yehia();
};
class enter{
public:
	string name; int mx, my;
	enter(string x);
	void ent_name(Text &fr_name, Font &font);
	void all_image(Texture &texture, Texture &ch_inva);
	void enter_form(RectangleShape &shape1, Text &frist, Font &font, RectangleShape &shape2, Text &secand,
		RectangleShape &shape3, Text &third, RectangleShape &shape4, Text &four, RectangleShape &shape5, Text &five);
	void mouse_moves(RenderWindow &window, Event &event, RectangleShape &shape1, RectangleShape &shape2, RectangleShape &shape3,
		RectangleShape &shape4, RectangleShape &shape5);
	void frist_enter(RenderWindow &window, Text frist, Text secand, Text third, Text four, Text five, Text fr_name,
		RectangleShape shape1, RectangleShape shape2, RectangleShape shape3, RectangleShape shape4, RectangleShape shape5, Sprite f_image);
};
class start{
public:
	void start_game();
};
bool isCollide(Entity *a, Entity *b); 
class LevelFour
{
private:

	int RedHpPoints = 40, BlueHpPoints = 40, EggGapTime = 0, Lag = 0;
	bool BlueDied = false, RedDied = false;
	list<Entity*> Objects;
	bigenemy *BlueChicken = NULL, *RedChicken = NULL;
public:

	void directions();
	void Progress();

};
class levels{
public:
	bool level1();
	bool start_game1();
	bool levelAmr(); 
	bool levelAhmed();
};
class ch_move_level : public Entity{
public:
	ch_move_level();
	void update();
};
class ahmed{
public:
	void Gemy();
};

