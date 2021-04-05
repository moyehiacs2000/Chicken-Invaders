#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <sstream>
#include "chicken_game.h";
using namespace std;
using namespace sf;
#define pos 500
bool is = false, upL = false, upR = false, downL = false, downR = true,start_Game=true,mission=false,level_Amr=false,level_Ahmed=false;
bool chicken_up = false, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false,back_ground_up=false;
bool chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = false, after_die = false, asteroid_start = false, big_enemy_start = false;
int counter_big_enemy_egg = 0, wait_after_asteroid = 0, counter_big_enemy_life = 0, bullet_counter = 0, ani = 0, button = 0, d_move, after_level1 = 0;
const int W = 1900, H = 1000; int lifes = 5, after_end_lifes = 0;
int sco = 0, life = 5; bool bigg = false;
void Score_Time::Score(int score, Text &mscore, Font &font){
	mscore.setFont(font);  mscore.setCharacterSize(40);
	mscore.setScale(0.8, 0.8);  mscore.setFillColor(Color(134, 140, 151));
	mscore.setPosition(30, 10);   stringstream ss;
	ss << "Score : " << score;   mscore.setString(ss.str());
}
void Score_Time::TIME(Time elapsed1, Text &ttime, Font &font){
	ttime.setFont(font);  ttime.setCharacterSize(40);
	ttime.setScale(0.8, 0.8);  ttime.setFillColor(Color(134, 140, 151));
	ttime.setPosition(W - 300, 10);  stringstream ss1;
	ss1 << "Time : " << (int)elapsed1.asSeconds();  ttime.setString(ss1.str());
}
void Score_Time::LIFE(int life, Text &l_life, Font &font){
	l_life.setFont(font);  l_life.setCharacterSize(40);
	l_life.setScale(0.8, 0.8);  l_life.setFillColor(Color(134, 140, 151));
	l_life.setPosition(W / 2 - 30, 10);  stringstream ss2;
	ss2 << "Lifes : " << life;  l_life.setString(ss2.str());
}
void Score_Time::Finsh(Text &finsh, Font &font){
	finsh.setFont(font);  finsh.setCharacterSize(50);
	finsh.setScale(2, 2);  finsh.setString(" Game Over ");
	finsh.setFillColor(Color(134, 140, 151));  finsh.setPosition(W / 2, 200);
}
bool levels::level1(){
	return mission;
}
bool levels::start_game1(){
	return start_Game;
}
bool levels::levelAhmed(){
	return level_Ahmed;
}
bool levels::levelAmr(){
	return level_Amr;
}
Animation::Animation(Texture &t, int x, int y, int w, int h, int count, float Speed, string s){
	Frame = 0;
	speed = Speed;

	for (int i = 0; i<count; i++)
		frames.push_back(IntRect(x + i*w, y, w, h));

	sprite.setTexture(t);
	sprite.setOrigin(w / 2, h / 2);
	if (s == "order"){
		sprite.setScale(1.25, 1.25);
	}
	if ((count == 1 || count == 8) && s != "order"){ sprite.setScale(2, 2); }
	if (s == "egg"){ sprite.setScale(0.5, 0.5); }
	if (s == "bigenemy"){
		sprite.setScale(0.8, 0.8);
	}
	if (s == "heart"){
		sprite.setScale(0.4, 0.4);
	}
	sprite.setTextureRect(frames[0]);
}
void Animation::update(){
	Frame += speed;
	int n = frames.size();
	if (Frame >= n) Frame -= n;
	if (n>0) sprite.setTextureRect(frames[int(Frame)]);
}
bool Animation::isEnd(){
	return Frame + speed >= frames.size();
}
Entity::Entity(){
	life = 1;
	name = "heart";
}	
void Entity::settings(Animation &a, int X, int Y, float Angle, int radius , int n){
	anim = a;
	x = X; y = Y;
	angle = Angle;
	R = radius;
	number = n;
}
void Entity::draw(RenderWindow &app){
	anim.sprite.setPosition(x, y);
	anim.sprite.setRotation(angle + 90);
	app.draw(anim.sprite);
}
chicken_enenmy::chicken_enenmy(){
	dx = 1;
	dy = 1;
	name = "chicken_enenmy";
}
void chicken_enenmy::update(){
	if (lifes != 0){
		if (x == 170 || (chicken_down == false && chicken_up == false && chicken_left == false && chicken_right == false &&
			chicken_tri_down_right == false && chicken_tri_down_left == false && chicken_tri_up_left == false &&
			chicken_tri_up_right == false)){
			back_ground_up = false;
			chicken_down = false; chicken_up = false; chicken_left = false; chicken_right = false;
			chicken_tri_down_right = true;; chicken_tri_down_left = false; chicken_tri_up_left = false;
			chicken_tri_up_right = false;
		}
		//1777 487
		else if (y == 750 && chicken_tri_down_right == true){
			back_ground_up = true;
			chicken_down = false; chicken_up = true; chicken_left = false; chicken_right = false;
			chicken_tri_down_right = false; chicken_tri_down_left = false; chicken_tri_up_left = false;
			chicken_tri_up_right = false;
		}
		else if (y == 70 && chicken_up == true){
			back_ground_up = false;
			chicken_down = false; chicken_up = false; chicken_left = false; chicken_right = false;
			chicken_tri_down_right = false;; chicken_tri_down_left = true; chicken_tri_up_left = false;
			chicken_tri_up_right = false;
		}
		else if (y == 750 && chicken_tri_down_left == true){
			back_ground_up = true;
			chicken_down = false; chicken_up = true; chicken_left = false; chicken_right = false;
			chicken_tri_down_right = false;; chicken_tri_down_left = false; chicken_tri_up_left = false;
			chicken_tri_up_right = false;

		}
	}
	else if (lifes == 0){
		back_ground_up = true;
		chicken_down = false; chicken_up = true; chicken_left = false; chicken_right = false;
		chicken_tri_down_right = false; chicken_tri_down_left = false; chicken_tri_up_left = false;
		chicken_tri_up_right = false;
	}
	if (chicken_down == true){ y++; }
	else if (chicken_up == true){ y--; }
	else if (chicken_right == true){ x++; }
	else if (chicken_left == true){ x--; }
	else if (chicken_tri_down_right == true){ x++; y++; }
	else if (chicken_tri_down_left == true){ x--; y++; }
	else if (chicken_tri_up_left == true){ x--; y--; }
	else if (chicken_tri_up_right == true){ x++; y--; }
	//cout << x << " " << y << endl;
}
bullet::bullet(){ 
	name = "bullet"; }
void bullet::update(){
	dy = 6;
	y -= dy;

	if (x>W || x<0 || y>H || y<0) life = 0;
}
player::player(){
	name = "player";
}
void player::update(){
	if (up)
	{
		dy -= 0.25;

	}
	else if (right){
		dx += 5;
	}
	else if (left){
		dx -= 5;
	}
	else if (down){
		dy += 0.5;
	}
	else
	{
		dx *= 0.99;
		dy *= 0.99;
	}
	int maxSpeed = 5;
	float speed = sqrt(dx*dx + dy*dy);
	if (speed>maxSpeed)
	{
		dx *= maxSpeed / speed;
		dy *= maxSpeed / speed;
	}

	x += dx;
	y += dy;

	if (x>W-50) x = W-50; if (x<50) x =50;
	if (y>H) y = H; if (y<50) y = 50;
}
chicken_f::chicken_f(){
	name = "chicken_f";
}
void chicken_f::update(){
	dy = 3;
	y += dy;

	if (x>W || x<0 || y>H || y<0) life = 0;
}
chicken_egg::chicken_egg(){
	name = "chicken_egg";
}
void chicken_egg::update(){
	y += 3;
	if (x>W || x<0 || y>H || y<0) life = 0;
}
asteroid::asteroid(){
	dx = rand() % 8 - 4;
	dy = rand() % 8 - 4;
	name = "asteroid";
}
void asteroid::update(){
	x += dx;
	y += dy;

	if (x>W) x = 0;  if (x<0) x = W;
	if (y>H) y = 0;  if (y<0) y = H;
}
bigenemy::bigenemy(){
	name = "chickenenemy_egg";
}
void bigenemy::update(){
	int dir = -1;
	if (lifes != 0){
	if (y < 200)y += 2;
	else if (y == 200 || y == 700){
		if (chicken_up == false && chicken_down == false && chicken_left == false && chicken_right == false && chicken_tri_down_right == false
			&& chicken_tri_up_right == false && chicken_tri_up_left == false && chicken_tri_down_left == false){
			chicken_up = false, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
			chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = true;
		}
		else if (y == 700 && chicken_tri_down_left == true){
			back_ground_up = true;
			chicken_up = true, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
			chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = false;

		}
		else if (y == 200 && chicken_up == true && x < 1000){
			chicken_up = false, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = true;
			chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = false;
		}
		else if (y == 700 && chicken_tri_down_right == true){
			chicken_up = false, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
			chicken_tri_up_right = true, chicken_tri_up_left = false, chicken_tri_down_left = false;
		}
		else if (y == 200 && chicken_tri_up_right == true){
			chicken_up = false, chicken_down = true, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
			chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = false;
		}
		else if (y == 700 && chicken_down == true){
			chicken_up = false, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
			chicken_tri_up_right = false, chicken_tri_up_left = true, chicken_tri_down_left = false;
		}
		else if (y == 200 && chicken_tri_up_left == true){
			chicken_up = false, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
			chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = true;
		}
	}
	}
	else{
		back_ground_up = true;
		chicken_up = true, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
		chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = false;
	}
	if (chicken_tri_down_left){ y += 2; x -= 3; }
	else if (chicken_up){ y -= 2; }
	else if (chicken_tri_down_right){ y += 2; x += 3; }
	else if (chicken_tri_down_left){ y += 2; x -= 2; }
	else if (chicken_tri_up_right){ y -= 2; x += 2.5; }
	else if (chicken_down){ y += 2; }
	else if (chicken_tri_up_left){ y -= 2; x -= 2.5; }
}
chickenenemy_egg::chickenenemy_egg(){
	name = "chicken_egg";
}
void chickenenemy_egg::update(){
	if (number == 1){
		y += 3;
		x -= 3;
	}
	else if (number == 2){
		y += 3;
		x -= 2;
	}
	else if (number == 3){
		y += 3;
		x -= 1;
	}
	else if (number == 4){
		y += 3;
	}
	else if (number == 5){
		y += 3;
		x += 1;
	}
	else if (number == 6){
		y += 3;
		x += 2;
	}
	else if (number == 7){
		y += 3;
		x += 3;
	}
	if (x>W || x<0 || y>H || y<0) life = 0;
}
void back_groung(Sprite &s, int &ani, RenderWindow &window){
	s.setTextureRect(IntRect(0, ani*0.125, 2000, 2000));
	if (ani >= 1250 * 8)ani = 0;
	window.draw(s);
}
time_score::time_score(){
	score = 0; time = 0; }
void time_score::calculate_time(Font &font, Text &text_time){
	text_time.setFont(font);  text_time.setCharacterSize(40);
	text_time.setScale(0.8, 0.8);  text_time.setFillColor(Color(113, 130, 130));
	text_time.setPosition(1100 + pos, 10);
	stringstream ss5;
	ss5 << " Time : " << time;  text_time.setString(ss5.str());
}
void time_score::Score(Font &font, Text &text_score){
	text_score.setFont(font);  text_score.setCharacterSize(40);
	text_score.setScale(0.8, 0.8);  text_score.setFillColor(Color(113, 130, 130));
	text_score.setPosition(350 + pos, 10);
	stringstream ss5;
	ss5 << " Score : " << score;  text_score.setString(ss5.str());
}
void time_score::gameover(Font &font, Text &game_over){
	game_over.setFont(font);  game_over.setCharacterSize(40);
	game_over.setScale(3, 3);  game_over.setFillColor(Color::Green);
	game_over.setPosition(600, 450);
	stringstream ss5;
	ss5 << " GAME OVER!! ";  game_over.setString(ss5.str());
}
void time_score::update_time(Time m){
	time = m.asSeconds();
}
void time_score::updete(string n){
	if (n == "c")
		score += 5;
	else
		score++;
}
void mohmed::mohmed_yehia(){
	lifes = 5;
	srand(time(0));
	RenderWindow app(VideoMode(W, H), "Chicken Invaders!", Style::Fullscreen);
	app.setFramerateLimit(60);
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11,t12,t13;
	Text SCORE, TIME,Gameover;
	Font font;
	font.loadFromFile("comicz.ttf");
	t1.loadFromFile("images/spaceship.png");	
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_red.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");
	t8.loadFromFile("images/chicken.png");
	t9.loadFromFile("images/Pataepollo.png");
	t10.loadFromFile("images/egg_1.png");
	t11.loadFromFile("images/c3.png");
	t2.loadFromFile("images/ch_background2.jpg");
	t13.loadFromFile("images/heart.png");
	Sprite background(t2);
	Animation sExplosion(t3, 0, 0, 256, 256, 44, 0.5, "0");
	Animation sRock(t4, 0, 0, 64, 64, 16, 0.2, "0");
	Animation chicken1(t8, 0, 0, 60, 50, 8, 0.1, "0");
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2, "0");
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8, "0");
	Animation sPlayer(t1, 40, 0, 40, 40, 1, 0, "0");
	Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0, "0");
	Animation sPlayer_right(t1, 80, 0, 40, 40, 1, 0, "0");
	Animation sPlayer_left(t1, 0, 0, 39, 40, 1, 0, "0");
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5, "0");
	Animation chieken_order(t9, 0, 0, 32, 48, 1, 0, "order");
	Animation egg(t10, 0, 0, 40, 40, 1, 0, "egg");
	Animation bigchicken_enemy(t11, 0, 0, 565, 462, 1, 0, "bigenemy");
	Animation heart(t13, 0, 0, 200, 200, 1, 0, "heart");
	list<Entity*> entities;
	time_score wr;
	wr.Score(font, SCORE);
	wr.calculate_time(font, TIME);
	
	for (int j = 1; j <= 5; j++){
		for (int i = 1; i <= 8; i++)
		{
			
			chicken_enenmy *a = new chicken_enenmy();
			a->settings(chicken1, i * 170, j * 70, -90, 25);
			entities.push_back(a);
		}
	}
	bigenemy *big = NULL;
	for (int i = 1; i <= 5; i++){
		Entity *h = new Entity();
		h->settings(heart,i*65, 35, -90,0,i);
		
		entities.push_back(h);
	}
	
	int enemy_number = entities.size();
	int cont = 0, m = 0;
	int wait_after_chicken = 0;
	player *p = new player();
	p->settings(sPlayer, 1000, 750, -90, 20);
	entities.push_back(p);
	Music music;
	music.openFromFile("Chicken invaders soundtrack.wav");
	music.setVolume(300);
	music.setLoop(true);
	music.play();
	Sound bullt1,pump1,sound_gameover;
	SoundBuffer bfbullt, bfpump, bfsound_gameover;
	bfbullt.loadFromFile("bullt1.wav");
	bfpump.loadFromFile("pump1.wav");
	bfsound_gameover.loadFromFile("gameover.wav");
	bullt1.setBuffer(bfbullt);
	pump1.setBuffer(bfpump);
	sound_gameover.setBuffer(bfsound_gameover);
	Clock clock;
	/////main loop/////
	while (app.isOpen())
	{
		if (after_die){
			after_level1++;
			
		}
		cout << after_level1 << endl;
		if (after_level1 >= 200){
			mission = false;
			
			start_Game = false;
			level_Ahmed = true;
			button = 0;
			app.close();
		}
		if (lifes == 0){
			music.stop();
			if (after_end_lifes==200)
			sound_gameover.play();
			after_end_lifes++;
			wr.gameover(font, Gameover);
			if (after_end_lifes == 700){
				mission = false;
				start_Game = true;
				button = 0;
				app.close();
				
			}
		}
		wr.Score(font, SCORE);
		wr.calculate_time(font, TIME);
		Time elapsed1 = clock.getElapsedTime();
		wr.update_time(elapsed1);
		ani += 30;
		if (back_ground_up){
			if (ani < 0){
				ani = 2000;
			}
			ani -= 50;
		}
		bullet_counter++;
		if (wait_after_asteroid == 2000){
			big_enemy_start = true;
			asteroid_start = false;
			wait_after_asteroid = 0;
			for (auto i : entities){
				if (i->name == "asteroid"){
					i->life = 0;
				}
			}
		}
		if (big_enemy_start&&wait_after_asteroid<200){
			wait_after_asteroid++;
		}
		if (big_enemy_start&&wait_after_asteroid == 200){
			big = new bigenemy();
			big->settings(bigchicken_enemy, 1000, -150, -90, 200);
			entities.push_back(big);
			wait_after_asteroid++;
		}

		if (big_enemy_start&&wait_after_asteroid > 200 && after_die == false){
			counter_big_enemy_egg++;
			if (counter_big_enemy_egg == 200){
				for (int i = 1; i <= 7; i++){
					chickenenemy_egg *e = new chickenenemy_egg();
					e->settings(egg, big->x, big->y + 100, -90, 15, i);
					entities.push_back(e);
				}
				counter_big_enemy_egg = 0;
			}
		}

		if (m == 40){
			chicken_up = false, chicken_down = false, chicken_left = false, chicken_right = false, chicken_tri_down_right = false;
			chicken_tri_up_right = false, chicken_tri_up_left = false, chicken_tri_down_left = false;
			wait_after_chicken++;
			if (wait_after_chicken == 300){
				for (int i = 0; i < 15; i++)
				{
					asteroid *a = new asteroid();
					a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
					entities.push_back(a);
				}
				m = 0; wait_after_chicken = 0; asteroid_start = true;
			}
		}
		if (asteroid_start){
			wait_after_asteroid++;
		}
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
			if (event.key.code == Keyboard::Space&&lifes!=0)
			{
				bullt1.play();
				bullet *b = new bullet();
				b->settings(sBullet, p->x, p->y, p->angle, 10);
				entities.push_back(b);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) p->right = true;
		else p->right = false;
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->left = true;
		else p->left = false;
		if (Keyboard::isKeyPressed(Keyboard::Up)) p->up = true;
		else p->up = false;
		if (Keyboard::isKeyPressed(Keyboard::Down)) p->down = true;
		else p->down = false;

		for (auto a : entities)
		for (auto b : entities)
		{
			if (a->name == "chickenenemy_egg" && b->name == "bullet")
			if (isCollide(a, b))
			{
				b->life = false;
				counter_big_enemy_life++;
				if (counter_big_enemy_life == 50){
					pump1.play();
					after_die = true;
						Entity *e = new Entity();
						e->settings(sExplosion, a->x + (rand() % 100), a->y + (rand() % 100));
						e->name = "explosion";
						entities.push_back(e);
					for (int i = 1; i <= 7; i++){
						chickenenemy_egg *e = new chickenenemy_egg();
						e->settings(chieken_order, big->x, big->y + 100, -90, 15, i);
						entities.push_back(e);
					}
					a->life = 0;

				}

			}

			if (a->name == "asteroid" && b->name == "bullet")
			if (isCollide(a, b))
			{
				string s = "c";
				wr.updete(s);
				pump1.play();
				a->life = false;
				b->life = false;

				Entity *e = new Entity();
				e->settings(sExplosion, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);


				for (int i = 0; i<2; i++)
				{
					if (a->R == 15) continue;
					Entity *e = new asteroid();
					e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
					entities.push_back(e);
				}

			}
			if (a->name == "player" && b->name == "asteroid"&&lifes != 0)
			if (isCollide(a, b))
			{
				pump1.play();
				b->life = false;
				for (auto g : entities){
					if (g->name == "heart"&&g->number == lifes){
						g->life = false;
					}
				}
				lifes--;
				Entity *e = new Entity();
				e->settings(sExplosion_ship, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);

				p->settings(sPlayer, 1000, 800, -90, 20);
				p->dx = 0; p->dy = 0;
			}
			if (a->name == "chicken_enenmy" && b->name == "bullet")
			if (isCollide(a, b))
			{
				string s = "c";
				wr.updete(s);
				pump1.play();
				a->life = false;
				b->life = false;

				Entity *e = new Entity();
				e->settings(sExplosion, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);


				for (int i = 0; i<1; i++)
				{
					Entity *e = new chicken_f();
					e->settings(chieken_order, a->x, a->y, rand() % 360, 15);
					entities.push_back(e);
				}

			}
			if ((a->name == "player" && b->name == "chicken_f"))
			if (isCollide(a, b)){
				string s = "e";
				wr.updete(s);
				b->life = false;
			}
			if (a->name == "player"&&b->name == "chickenenemy_egg"&&lifes != 0){
				if (isCollide(a, b))
				{
					pump1.play();
					Entity *e = new Entity();
					e->settings(sExplosion_ship, a->x, a->y);
					e->name = "explosion";
					entities.push_back(e);

					p->settings(sPlayer, 1000,800, -90, 20);
					p->dx = 0; p->dy = 0;
				}
			}
			if (((a->name == "player" && b->name == "chicken_enenmy") || (a->name == "player" && b->name == "chicken_egg")) && lifes != 0)
			if (isCollide(a, b))
			{
				if (after_die == true)
					b->life = false;
				else{

					for (auto g : entities){
						if (g->name == "heart"&&g->number == lifes){
							g->life = false; 
						}
					}
					lifes--;
					pump1.play();
					b->life = false;
					Entity *e = new Entity();
					e->settings(sExplosion_ship, a->x, a->y);
					e->name = "explosion";
					entities.push_back(e);

					p->settings(sPlayer, 1000, 800, -90, 20);
					p->dx = 0; p->dy = 0;
				}


			}
		}


		if (p->up)  p->anim = sPlayer_go;
		else if (p->right)p->anim = sPlayer_right;
		else if (p->left)p->anim = sPlayer_left;
		else   p->anim = sPlayer;


		for (auto e : entities)
		if (e->name == "explosion")
		if (e->anim.isEnd()) e->life = 0;
		cont++;
		for (auto c : entities){
			if (c->name == "chicken_enenmy"&&rand() % 150 == 0 && cont % 15 == 0&&lifes!=0){
				Entity *e = new chicken_egg();
				e->settings(egg, c->x, c->y, -90, 15);
				entities.push_back(e);
			}
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { if (e->name == "chicken_enenmy")m++; i = entities.erase(i); delete e; }
			else i++;
		}
		back_groung(background, ani, app);
		//////draw//////

		app.draw(background);
		for (auto i : entities) i->draw(app);
		app.draw(SCORE);
		app.draw(TIME);
		app.draw(Gameover);
		app.display();
	}
}
bool isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}
enter::enter(string x){
	name = x;
	mx = 0; my = 0;
}
void enter::ent_name(Text &fr_name, Font &font){
	fr_name.setFont(font);  fr_name.setCharacterSize(40);
	fr_name.setScale(0.8, 0.8);  fr_name.setFillColor(Color(172, 192, 210));
	fr_name.setPosition(350 + pos, 320);
	stringstream ss5;
	ss5 << " Hello " << name;  fr_name.setString(ss5.str());
}
void enter::all_image(Texture &texture, Texture &ch_inva){
	texture.loadFromFile("images/ch_background2.jpg");
	ch_inva.loadFromFile("images/chicken inva2.png");
}
void enter::enter_form(RectangleShape &shape1, Text &frist, Font &font, RectangleShape &shape2, Text &secand,
	RectangleShape &shape3, Text &third, RectangleShape &shape4, Text &four, RectangleShape &shape5, Text &five){
	shape1.setFillColor(Color(0, 0, 250, 70));
	shape1.setPosition(320 + pos, 400);
	shape1.setOutlineColor(Color(45, 147, 238, 200));
	frist.setFont(font);  frist.setCharacterSize(50);
	frist.setScale(0.5, 0.5);  frist.setString(" Save The World ");
	frist.setFillColor(Color::White);  frist.setPosition(350 + pos, 412);

	shape2.setFillColor(Color(0, 0, 250, 70));
	shape2.setPosition(320 + pos, 490);
	shape2.setOutlineColor(Color(45, 147, 238, 200));
	secand.setFont(font);  secand.setCharacterSize(50);
	secand.setScale(0.5, 0.5);  secand.setString(" Hall Of Fame ");
	secand.setFillColor(Color::White);  secand.setPosition(350 + pos, 502);

	shape3.setFillColor(Color(0, 0, 250, 70));
	shape3.setPosition(320 + pos, 580);
	shape3.setOutlineColor(Color(45, 147, 238, 200));
	third.setFont(font);  third.setCharacterSize(50);
	third.setScale(0.5, 0.5);  third.setString(" Options... ");
	third.setFillColor(Color::White);  third.setPosition(350 + pos, 592);

	shape4.setFillColor(Color(0, 0, 250, 70));
	shape4.setPosition(320 + pos, 670);
	shape4.setOutlineColor(Color(45, 147, 238, 200));
	four.setFont(font);  four.setCharacterSize(50);
	four.setScale(0.5, 0.5);  four.setString(" Credits ");
	four.setFillColor(Color::White);  four.setPosition(350 + pos, 682);

	shape5.setFillColor(Color(0, 0, 250, 70));
	shape5.setPosition(320 + pos, 760);
	shape5.setOutlineColor(Color(45, 147, 238, 200));
	five.setFont(font);  five.setCharacterSize(50);
	five.setScale(0.5, 0.5);  five.setString(" X Quit ");
	five.setFillColor(Color::White);  five.setPosition(350 + pos, 772);
}
void enter::mouse_moves(RenderWindow &window, Event &event, RectangleShape &shape1, RectangleShape &shape2, RectangleShape &shape3,
	RectangleShape &shape4, RectangleShape &shape5){
	switch (event.type)
	{
	case Event::Closed:
		window.close();
		break;
	case Event::MouseMoved:
		if ((event.mouseMove.x > 320 + pos && event.mouseMove.x < 620 + pos) && (event.mouseMove.y>400 && event.mouseMove.y < 470))
			shape1.setOutlineThickness(7);
		else
			shape1.setOutlineThickness(0);

		if ((event.mouseMove.x > 320 + pos && event.mouseMove.x < 620 + pos) && (event.mouseMove.y>490 && event.mouseMove.y < 560))
			shape2.setOutlineThickness(7);
		else
			shape2.setOutlineThickness(0);

		if ((event.mouseMove.x > 320 + pos && event.mouseMove.x < 620 + pos) && (event.mouseMove.y>580 && event.mouseMove.y < 650))
			shape3.setOutlineThickness(7);
		else
			shape3.setOutlineThickness(0);

		if ((event.mouseMove.x > 320 + pos && event.mouseMove.x < 620 + pos) && (event.mouseMove.y>670 && event.mouseMove.y < 740))
			shape4.setOutlineThickness(7);
		else
			shape4.setOutlineThickness(0);

		if ((event.mouseMove.x > 320 + pos && event.mouseMove.x < 620 + pos) && (event.mouseMove.y>760 && event.mouseMove.y < 830)){
			shape5.setOutlineThickness(7);
		}
		else
			shape5.setOutlineThickness(0);

		mx = event.mouseMove.x;
		my = event.mouseMove.y;

		break;
	case Event::MouseButtonPressed:
		if ((mx > 320 + pos && mx < 620 + pos) && (my>760 && my < 830)){
			button = 5;
			window.close();
		}
		else if ((mx > 320 + pos && mx < 620 + pos) && (my>400 && my < 470)){
			button = 1;
		}
		else if ((mx > 320 + pos && mx < 620 + pos) && (my>490 && my < 560))
			button = 2;
		else if ((mx > 320 + pos && mx < 620 + pos) && (my>580 && my < 650))
			button = 3;
		else if ((mx > 320 + pos && mx < 620 + pos) && (my>670 && my < 740))
			button = 4;

		break;
	}
}
void enter::frist_enter(RenderWindow &window, Text frist, Text secand, Text third, Text four, Text five, Text fr_name,
	RectangleShape shape1, RectangleShape shape2, RectangleShape shape3, RectangleShape shape4, RectangleShape shape5, Sprite f_image){
	window.draw(frist);
	window.draw(secand);
	window.draw(third);
	window.draw(four);
	window.draw(five);
	window.draw(fr_name);
	window.draw(shape1);
	window.draw(shape2);
	window.draw(shape3);
	window.draw(shape4);
	window.draw(shape5);
	window.draw(f_image);
}
void home(){
	string fname; cin >> fname;
	enter a(fname);
	RenderWindow window(sf::VideoMode(800, 800), "Enter Form", Style::Fullscreen);
	Texture texture, ch_inva, big_ch, eggs;
	Text frist, secand, third, four, five, fr_name;
	Font font;
	font.loadFromFile("comicz.ttf");
	a.all_image(texture, ch_inva);
	a.ent_name(fr_name, font);
	RectangleShape shape1(Vector2f(300.f, 70.f));
	RectangleShape shape2(Vector2f(300.f, 70.f));
	RectangleShape shape3(Vector2f(300.f, 70.f));
	RectangleShape shape4(Vector2f(300.f, 70.f));
	RectangleShape shape5(Vector2f(300.f, 70.f));
	a.enter_form(shape1, frist, font, shape2, secand, shape3, third, shape4, four, shape5, five);
	Sprite s(texture), f_image(ch_inva), level(big_ch), egg(eggs);
	f_image.setPosition(150 + pos, 10);
	f_image.setScale(1.5, 1.5);
	level.setPosition(600, 100);
	int x = 0;
	srand(time(NULL));
	d_move = 1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			a.mouse_moves(window, event, shape1, shape2, shape3, shape4, shape5);
			//big_chicken(level, x, window);
			if (button != 0)
				break;
		}
		if (button != 0)
			break;
		ani++;
		window.clear();
		//window.draw(s);
		//window.draw(level);
		back_groung(s, ani, window);
		a.frist_enter(window, frist, secand, third, four, five, fr_name, shape1, shape2, shape3, shape4, shape5, f_image);
		//big_chicken(level, x, window, elapsed1,egg);
		window.display();
	}
}
void creit_button(){
	int x = 0, y = 0;
	RenderWindow window2(sf::VideoMode(800, 800), "credit Form", Style::Fullscreen);
	Text decrabtion, Exit;
	Texture texture;
	texture.loadFromFile("images/ch_background2.jpg");
	Font font; Sprite s(texture);
	font.loadFromFile("comicz.ttf");
	decrabtion.setFont(font);  decrabtion.setCharacterSize(50);
	decrabtion.setScale(0.5, 0.5);  decrabtion.setString(" Chicken Invaders is the first game in the series. It is both a single player and two-player game. The player takes control of a lone spacecraft,\n and must protect Earth from swarms of invading chickens. The game features weapon power-ups that resemble gift boxes, and the player can use these to upgrade their weapons.\n Chickens drop eggs which must be avoided, otherwise the player will die if they collide with these projectiles.\n Chicken drumsticks fall from the chickens when they're killed, and if the player collects enough of these they earn a missile.\n These missiles can then be used to wipe out everything (except the player) on the screen.The game also features infinite levels.\n In each level, there are 10 waves, and at the end of every level is a boss,\n which must be defeated in order to advance (or warp) to a new system. The gameplay is endless,\n so there is no ending to the game; it continues on and on, until the player has finally lost all of their lives and the game is over.\n The difficulty increases each time players advance to a new chapter; the enemies move or fall faster,\n and objects like asteroids move faster, too. There are no holiday editions of this game. this is the only game that has no Christmas,\n Easter, Thanksgiving, or Halloween Editions made for it.\n This is also the only game in the series that hasn't been ported to other platforms.\n Chicken Invaders: The Next Wave (or Chicken Invaders 2) is the second game in the series and the first game to have an ending.\n It has 110 Waves in 11 Chapters and 3 different weapons. It can be played by one or two players.\n The player takes command of the same lone spacecraft of the previous and must eliminate the chicken infestation of the solar system.\n The game features eleven chapters, moving inwards from Pluto, each of which consists of 10 waves of attacking hostiles.\n In all the waves, chickens attack by dropping eggs which have to be dodged.\n The player can collect different items that help them in the game.\n Primary weapons may be changed by collecting parcels.\n Power-ups may also be collected to upgrade the primary weapon.\n Weapons may be upgraded up to eleven levels.\n The eleventh level, however, is only acquired by collecting ten power-ups.\n The player may collect and accumulate drumsticks and roasts to get missiles, powerful weapons that can wipe out an entire wave.\n In all levels, except in the asteroid belt level, the ninth wave has a bonus (usually a new weapon, or extra firepower) awarded for not using\n missiles throughout the level, while the last wave features a boss.\n This game also comes out with an Remastered Edition and a Christmas Edition in for the original and Remastered.\n");
	decrabtion.setFillColor(Color::White);  decrabtion.setPosition(10, 10);
	Exit.setFont(font);  Exit.setCharacterSize(50);
	Exit.setScale(0.8, 0.8); Exit.setPosition(320 + pos, 970);
	Exit.setString("Cancle"); Exit.setFillColor(Color::Cyan);
	if (button == 4){
		while (window2.isOpen())
		{
			Event event;
			while (window2.pollEvent(event)){
				switch (event.type)
				{
				case Event::MouseMoved:
					x = event.mouseMove.x;
					y = event.mouseMove.y;
					break;
				case Event::MouseButtonPressed:
					if ((x > 320 + pos && x < 420 + pos) && (y>970 && y < 1001)){
						button = 0;
					}
					ani++;
				}
				if (button != 4)
					break;
			}
			if (button != 4)
				break;
			window2.clear();
			back_groung(s, ani, window2);
			window2.draw(decrabtion);
			window2.draw(Exit);
			window2.display();

		}
	}
}
void start::start_game(){
	while (button != -1){
		if (button == 0){
			home();
		}
		if (button == 1){
			start_Game = false;
			mission = true;
			button = -1;
		}
		else if (button == 4){
			creit_button();
		}
		else if (button == 5){
			start_Game = false;
			mission = false; button = -1;
		}
	}
}

ch_move_level::ch_move_level(){
	dx = 1;
	dy = 1;
	name = "move_level";
}
void ch_move_level::update(){
	y += 2;
}
void ahmed::Gemy(){
	int num = 0;
	RenderWindow window(VideoMode(W, H), "Move Level ", Style::Fullscreen);
	window.setFramerateLimit(50);
	Texture pla, t2, t3, t5, t7, chi, foo, t10, t12;
	pla.loadFromFile("images/spaceship.png");
	t3.loadFromFile("images/explosions/type_C.png");
	t5.loadFromFile("images/fire_red.png");
	t7.loadFromFile("images/explosions/type_B.png");
	chi.loadFromFile("images/chicken.png");
	foo.loadFromFile("images/Pataepollo.png");
	t10.loadFromFile("images/egg_1.png");
	t2.loadFromFile("images/ch_background2.jpg");
	Sprite background(t2);
	Text mscore, ttime, l_life, finsh;
	Font font;
	font.loadFromFile("comicz.ttf");
	Animation sExplosion(t3, 0, 0, 256, 256, 44, 0.5, "0");
	Animation chicken1(chi, 0, 0, 60, 50, 8, 0.1, "0");
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8, "0");
	Animation sPlayer(pla, 40, 0, 40, 40, 1, 0, "0");
	Animation sPlayer_go(pla, 40, 40, 40, 40, 1, 0, "0");
	Animation sPlayer_right(pla, 80, 0, 40, 40, 1, 0, "0");
	Animation sPlayer_left(pla, 0, 0, 39, 40, 1, 0, "0");
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5, "0");
	Animation chieken_order(foo, 0, 0, 32, 48, 1, 0, "order");
	Animation egg(t10, 0, 0, 40, 40, 1, 0, "egg");
	Event event;
	list<Entity*> entities;
	player *p = new player();
	p->settings(sPlayer, 600, 750, -90, 20);
	entities.push_back(p);
	int x = 0, cont = 0;
	Clock clock;
	Music music;
	music.openFromFile("Chicken invaders soundtrack.wav");
	music.setVolume(300);
	music.setLoop(true);
	music.play();
	Sound bullt1, pump1;
	SoundBuffer bfbullt, bfpump;
	bfbullt.loadFromFile("bullt1.wav");
	bfpump.loadFromFile("pump1.wav");
	bullt1.setBuffer(bfbullt);
	pump1.setBuffer(bfpump);
	srand(time(NULL));
	Score_Time q;
	while (window.isOpen())
	{
		ani += 10; x++;
		Time elapsed1 = clock.getElapsedTime();
		q.Score(sco, mscore, font);
		q.TIME(elapsed1, ttime, font);
		q.LIFE(life, l_life, font);

		if ((int)elapsed1.asSeconds() % 5 == 0 && x % 10 == 0){
			ch_move_level *i = new ch_move_level();
			i->settings(chicken1, rand() % 1980 + 10, 0, -90, 25);
			entities.push_back(i);
			num++;
		}

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			if (event.key.code == Keyboard::Space)
			{
				bullt1.play();
				bullet *b = new bullet();
				b->settings(sBullet, p->x, p->y, p->angle, 10);
				entities.push_back(b);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) p->right = true;
		else p->right = false;
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->left = true;
		else p->left = false;
		if (Keyboard::isKeyPressed(Keyboard::Up)) p->up = true;
		else p->up = false;
		if (Keyboard::isKeyPressed(Keyboard::Down)) p->down = true;
		else p->down = false;

		if (num >= 70){
			bigg = true;
			window.close();
		}

		for (auto a : entities)
		for (auto b : entities)
		{
			if (a->name == "move_level" && b->name == "bullet")
			if (isCollide(a, b))
			{
				pump1.play();
				a->life = false;
				b->life = false;
				sco += 5;
				Entity *e = new Entity();
				e->settings(sExplosion, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);

				Entity *i = new chicken_f();
				i->settings(chieken_order, a->x, a->y, rand() % 360, 15);
				entities.push_back(i);
			}
			if ((a->name == "player" && b->name == "chicken_f"))
			if (isCollide(a, b)){
				b->life = false;
				sco++;
			}
			if (a->name == "player"&&b->name == "chickenenemy_egg"){
				if (isCollide(a, b))
				{
					pump1.play();
					Entity *e = new Entity();
					e->settings(sExplosion_ship, a->x, a->y);
					e->name = "explosion";
					entities.push_back(e);

					p->settings(sPlayer, 600, 750, -90, 20);
					p->dx = 0; p->dy = 0;
				}
			}
			if ((a->name == "player" && b->name == "move_level") || (a->name == "player" && b->name == "chicken_egg"))
			if (isCollide(a, b))
			{
				life--;
				pump1.play();
				b->life = false;
				Entity *e = new Entity();
				e->settings(sExplosion_ship, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);

				p->settings(sPlayer, 600, 750, -90, 20);
				p->dx = 0; p->dy = 0;
			}
		}
		if (p->up)  p->anim = sPlayer_go;
		else if (p->right)p->anim = sPlayer_right;
		else if (p->left)p->anim = sPlayer_left;
		else   p->anim = sPlayer;


		for (auto e : entities)
		if (e->name == "explosion")
		if (e->anim.isEnd()) e->life = 0;
		cont++;
		for (auto c : entities){
			if (c->name == "move_level"&&rand() % 60 == 0 && cont % 10 == 0){
				Entity *e = new chicken_egg();
				e->settings(egg, c->x, c->y, -90, 15);
				entities.push_back(e);
			}
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}
		if (life == 0){
			button = 0;
			q.Finsh(finsh, font);  window.draw(finsh);  window.display();
			window.close(); start a;
			a.start_game();
		}
		back_groung(background, ani, window);
		//update_score(mscore,ttime,font,window, sco, ti);
		//////draw//////
		window.draw(background);
		for (auto i : entities) i->draw(window);
		window.draw(mscore);
		window.draw(ttime);
		window.draw(l_life);
		window.display();
	}
	if (bigg){
		LevelFour x;
		x.Progress();
		bigg = false;
	}
}
void LevelFour::Progress()
{

	const int ScreenWidth = 1900, ScreenHeight = 900;

	RenderWindow window(VideoMode(W, H), "Space Invaders!!", Style::Fullscreen);
	window.setFramerateLimit(60);
	Texture backGround, spaceShip, bigChicken, bigChicken2, fires, boom, shipDoomed, eggs, bonus;
	backGround.loadFromFile("images/ch_background2.jpg");
	spaceShip.loadFromFile("images/spaceship.png");
	fires.loadFromFile("images/fire_red.png");
	shipDoomed.loadFromFile("images/explosions/type_B.png");
	bigChicken.loadFromFile("images/BlueBigChicken.png");
	bigChicken2.loadFromFile("images/RedBigChicken.png");
	eggs.loadFromFile("images/egg_1.png");
	boom.loadFromFile("images/explosions/type_A.png");
	bonus.loadFromFile("images/Pataepollo.png");
	Sprite Background(backGround);

	Animation Spaceship(spaceShip, 40, 0, 40, 40, 1, 0, "0");
	Animation SpaceshipLaunch(spaceShip, 40, 40, 40, 40, 1, 0, "0");
	Animation SpaceshipTurningRight(spaceShip, 80, 0, 40, 40, 1, 0, "0");
	Animation SpaceshipTurningLeft(spaceShip, 0, 0, 39, 40, 1, 0, "0");
	Animation ShipDoomed(shipDoomed, 0, 0, 192, 192, 64, 0.5, "0");
	Animation Boom(boom, 0, 0, 256, 256, 44, 0.5, "0");
	Animation Fires(fires, 0, 0, 32, 64, 16, 0.8, "0");
	Animation BigChicken(bigChicken, 0, 0, 565, 462, 2, 0.05, "bigenemy");
	Animation BigChicken2(bigChicken2, 0, 0, 565, 462, 2, 0.05, "bigenemy");
	Animation Eggs(eggs, 0, 0, 40, 40, 1, 0, "egg");
	Animation Bonus(bonus, 0, 0, 32, 48, 1, 0, "order");

	Sound bulletSound, CrashSound;
	SoundBuffer BulletSound, Crash;
	BulletSound.loadFromFile("bullt1.wav");
	Crash.loadFromFile("pump1.wav");
	bulletSound.setBuffer(BulletSound);
	CrashSound.setBuffer(Crash);


	Music music;
	music.openFromFile("Perseus Galactic Arm.wav");
	music.setVolume(300);
	music.setLoop(true);
	music.play();

	player *spacship = new player();
	spacship->settings(Spaceship, ScreenWidth / 1.38, ScreenHeight / 1.026666667, -90, ScreenWidth / 6.9);
	Objects.push_back(spacship);
	Text mscore, ttime, l_life, finsh;
	Font font;
	font.loadFromFile("comicz.ttf");
	Score_Time q;
	Clock clock;
	while (window.isOpen())
	{

		Event event;
		Time elapsed1 = clock.getElapsedTime();
		q.Score(sco, mscore, font);
		q.TIME(elapsed1, ttime, font);
		q.LIFE(life, l_life, font);
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			if (event.key.code == Keyboard::Space)
			{
				bulletSound.play();
				bullet *bullets = new bullet();
				bullets->settings(Fires, spacship->x, spacship->y, spacship->angle, 10);
				Objects.push_back(bullets);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) spacship->right = true;
		else spacship->right = false;
		if (Keyboard::isKeyPressed(Keyboard::Left))  spacship->left = true;
		else spacship->left = false;
		if (Keyboard::isKeyPressed(Keyboard::Up)) spacship->up = true;
		else spacship->up = false;
		if (Keyboard::isKeyPressed(Keyboard::Down)) spacship->down = true;
		else spacship->down = false;

		if (spacship->up)  spacship->anim = SpaceshipLaunch;
		else if (spacship->right)spacship->anim = SpaceshipTurningRight;
		else if (spacship->left)spacship->anim = SpaceshipTurningLeft;
		else   spacship->anim = Spaceship;

		// The First Sentence will be Entered.....
		if (Lag<100)Lag++;

		// hai5och ta7t mara wa7da 
		if (Lag == 100)
		{
			BlueChicken = new bigenemy(); RedChicken = new bigenemy();
			BlueChicken->settings(BigChicken, 1200, -150, -90, 200, 10);
			RedChicken->settings(BigChicken2, 700, -150, -90, 200, 11);
			Objects.push_back(BlueChicken);
			Objects.push_back(RedChicken);
			Lag++;
		}
		// ta7t ma5soos ll eggs
		if (Lag > 100 && (BlueDied == false || RedDied == false))
		{
			EggGapTime++;
			if (EggGapTime == 200)
			{
				for (int i = 1; i <= 5; i++)
				{
					chickenenemy_egg *e = new chickenenemy_egg();
					e->settings(Eggs, BlueChicken->x, BlueChicken->y + 100, -90, 15, i);
					Objects.push_back(e);
				}

			}
			else if (EggGapTime == 300)
			{
				for (int i = 1; i <= 5; i++)
				{
					chickenenemy_egg *e = new chickenenemy_egg();
					e->settings(Eggs, RedChicken->x, RedChicken->y + 100, -90, 15, i);
					Objects.push_back(e);
				}
				EggGapTime = 0;
			}
		}

		for (auto a : Objects)
		for (auto b : Objects)
		{
			// Ta7t Lama El Tal2a Tegy Fl Far5a....
			if (a->name == "chickenenemy_egg" && b->name == "bullet"&&a->number == 10)
			if (isCollide(a, b))
			{
				sco += 10;
				b->life = false;
				BlueHpPoints--;
				if (BlueHpPoints == 0)
				{
					BlueDied = true;
					CrashSound.play();
					Entity *e = new Entity();
					e->settings(Boom, a->x + (rand() % 100), a->y + (rand() % 100));
					e->name = "explosion";
					Objects.push_back(e);
					for (int i = 1; i <= 5; i++)
					{	// Meats......
						chickenenemy_egg *e = new chickenenemy_egg();
						e->settings(Bonus, BlueChicken->x, BlueChicken->y + 100, -90, 15, i);
						Objects.push_back(e);
					}
					a->life = false;
				}
			}
			if (a->name == "chickenenemy_egg" && b->name == "bullet"&&a->number == 11)
			if (isCollide(a, b))
			{
				sco += 10;
				b->life = false;
				RedHpPoints--;
				if (RedHpPoints == 0)
				{
					RedDied = true;
					CrashSound.play();
					Entity *e = new Entity();
					e->settings(Boom, a->x + (rand() % 100), a->y + (rand() % 100));
					e->name = "explosion";
					Objects.push_back(e);
					for (int i = 1; i <= 5; i++)
					{	// Meats......
						chickenenemy_egg *e = new chickenenemy_egg();
						e->settings(Bonus, RedChicken->x, RedChicken->y + 100, -90, 15, i);
						Objects.push_back(e);
					}
					a->life = false;
				}
			}
			// Lama El Spaceship tegy fl Far5a
			if (a->name == "player"&&b->name == "chickenenemy_egg")
			{
				if (isCollide(a, b))
				{
					life--;
					CrashSound.play();
					Entity *e = new Entity();
					e->settings(ShipDoomed, a->x, a->y);
					e->name = "explosion";
					Objects.push_back(e);

					spacship->settings(Spaceship, 1000, 800, -90, 20);
					spacship->dx = 0; spacship->dy = 0;


				}
			}
			// Lama El Spaceship te5bt fl Eggs wl Meats....
			if (a->name == "player" && b->name == "chicken_egg")
			if (isCollide(a, b))
			{
				life--;
				if (BlueDied&&RedDied)b->life = false;

				else
				{
					CrashSound.play();

					Entity *e = new Entity();
					e->settings(ShipDoomed, a->x, a->y);
					e->name = "explosion";
					Objects.push_back(e);

					spacship->settings(Spaceship, 1000, 800, -90, 20);
					spacship->dx = 0; spacship->dy = 0;
				}
			}
		}

		for (auto e : Objects)
		if (e->name == "explosion")
		if (e->anim.isEnd()) e->life = 0;

		for (auto i = Objects.begin(); i != Objects.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = Objects.erase(i); delete e; }
			else i++;
		}

		ani += 50;
		if (life == 0){
			button = 0;
			window.draw(finsh);  window.display();
			window.close(); start a;
			a.start_game();
		}
		back_groung(Background, ani, window);
		window.draw(Background);
		for (auto i : Objects) i->draw(window);
		window.draw(mscore);
		window.draw(ttime);
		window.draw(l_life);
		window.display();
	}
}