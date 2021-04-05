#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <sstream>
#include <stack>

using namespace std;
using namespace sf;
#define pos 500
const int W = 1900, H = 1000;
class Amr
{
public:
	Amr();
	bool star(bool is){ return is; }

	class time_score{
		int score;
		int time;
	public:
	time_score(){
		score = 0; time = 0;
	}
	void calculate_time(Font &font, Text &text_time){
		text_time.setFont(font);  text_time.setCharacterSize(40);
		text_time.setScale(0.8, 0.8);  text_time.setFillColor(Color(113, 130, 130));
		text_time.setPosition(1100 + pos, 10);
		stringstream ss5;
		ss5 << " Time : " << time;  text_time.setString(ss5.str());
	}
	void Score(Font &font, Text &text_score){
		text_score.setFont(font);  text_score.setCharacterSize(40);
		text_score.setScale(0.8, 0.8);  text_score.setFillColor(Color(113, 130, 130));
		text_score.setPosition(  pos-500, 10);
		stringstream ss5;
		ss5 << " Score : " << score;  text_score.setString(ss5.str());
	}
	void gameover(Font &font, Text &game_over){
		game_over.setFont(font);  game_over.setCharacterSize(40);
		game_over.setScale(3, 3);  game_over.setFillColor(Color::Green);
		game_over.setPosition(600, 450);
		stringstream ss5;
		ss5 << " GAME OVER!! ";  game_over.setString(ss5.str());
	}
	void update_time(Time m){
		time = m.asSeconds();
	}
	void updete(string n){
		if (n == "c")
			score += 5;
		else
			score++;
	}
};
	void Run();



	class Animation
	{
	public:
		float Frame, speed;
		Sprite sprite;
		std::vector<IntRect> frames;

		Animation() {}

		Animation(Texture &t, int x, int y, int w, int h, int count, float Speed, string s="0")
		{
			Frame = 0;
			speed = Speed;

			for (int i = 0; i<count; i++)
				frames.push_back(IntRect(x + i*w, y, w, h));
			if (s == "heart"){
				sprite.setScale(0.4, 0.4);
			}
			sprite.setTexture(t);
			sprite.setOrigin(w / 2, h / 2);
			sprite.setTextureRect(frames[0]);
		}


		void update()
		{
			Frame += speed;
			int n = frames.size();
			if (Frame >= n) Frame -= n;
			if (n>0) sprite.setTextureRect(frames[int(Frame)]);
		}

		bool isEnd()
		{
			return Frame + speed >= frames.size();
		}

	};

	class Entity
	{
	public:
		float x, y, dx, dy, R, angle,number;
		bool life;
		std::string name = "heart";
		Animation anim;

		Entity()
		{
			life = 1;
		}

		void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1, int n = -1)
		{
			anim = a;
			x = X; y = Y;
			angle = Angle;
			R = radius;
			number = n;
		}

		virtual void update() {};

		void draw(RenderWindow &app)
		{
			anim.sprite.setPosition(x, y);
			anim.sprite.setRotation(angle + 90);
			app.draw(anim.sprite);

			CircleShape circle(R);
			circle.setFillColor(Color(255, 0, 0, 170));
			circle.setPosition(x, y);
			circle.setOrigin(R, R);
			//app.draw(circle);
		}

		virtual ~Entity() {};
	};
	class asteroid : public Entity
	{
	public:
		asteroid()
		{
			dx = rand() % 8 - 4;
			dy = rand() % 8 - 4;
			name = "asteroid";
		}

		void update()
		{
			x += dx;
			y += dy;

			if (x>W) x = 0;  if (x<0) x = W;
			if (y>H) y = 0;  if (y<0) y = H;
		}

	};


	class bullet : public Entity
	{
		float DEGTORAD = 0.017453f;
	public:
		bullet()
		{
			name = "bullet";
		}

		void  update()
		{
			dx = cos(angle*DEGTORAD) * 6;
			dy = sin(angle*DEGTORAD) * 6;
			// angle+=rand()%7-3;  /*try this*/
			x += dx;
			y += dy;

			if (x>W || x<0 || y>H || y<0) life = 0;
		}

	};


	class player : public Entity
	{
	public:
		bool up, left, right, down;
		std::stack<int>power;

		player()
		{
			name = "player";
			power.push(1);
		}

		void update()
		{
			if (up)
			{
				dy -= 0.2;
				dx *= 0.88;
			}
			else if (right) {
				dx += 0.2;
				dy *= 0.88;
			}
			else if (left) {
				dx -= 0.2;
				dy *= 0.88;
			}
			else if (down) {
				dy += 0.2;
				dx *= 0.88;
			}
			else
			{
				dx *= 0.99;
				dy *= 0.99;
			}

			int maxSpeed = 10;
			float speed = sqrt(dx*dx + dy*dy);
			if (speed>maxSpeed)
			{
				dx *= maxSpeed / speed;
				dy *= maxSpeed / speed;
			}

			x += dx;
			y += dy;

			if (x>W - 50) x = W - 50; if (x<50) x = 50;
			if (y>H) y = H; if (y<50) y = 50;
		}
		void plus_Power() {
			if (power.top() >= 7)power.push(power.top());
			else power.push(power.top() + 1);
		}
		void minus_Power() {
			if (power.size() > 1)power.pop();
		}

	};

	class Egg : public Entity
	{
	public:
		int pow;
		Egg() {
			name = "egg";
			pow = 300;
		}
		void update()
		{
			if (y < 200)dy = 0.2;
			else dy = 0;
			dx = 0;
			y += dy;

		}

	};
	class EggFire : public Entity
	{
		float DEGTORAD = 0.017453f;
	public:
		EggFire() {
			name = "eggFire";
		}
		void update()
		{
			dx = cos(angle*DEGTORAD) * 6;
			dy = sin(angle*DEGTORAD) * 6;
			// angle+=rand()%7-3;
			x += dx;
			y += dy;

			if (x>W || x<0 || y>H || y<0) life = 0;

		}
	};
	class reward : public Entity
	{
	public:
		reward() {
			name = "reward";
		}
		void update() {
			dy = 2;
			y += dy;
			if (x>W || x<0 || y>H || y<0) life = 0;
		}

	};

	bool isCollide(Entity *a, Entity *b)
	{
		return (b->x - a->x)*(b->x - a->x) +
			(b->y - a->y)*(b->y - a->y)<
			(a->R + b->R)*(a->R + b->R);
	}

	~Amr();
};

