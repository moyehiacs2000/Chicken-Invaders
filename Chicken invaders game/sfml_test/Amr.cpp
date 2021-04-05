#include "Amr.h"
#include<iostream>
using namespace std;


Amr::Amr()
{
}
void Amr::Run()
{
	bool s = false;
	int lifes = 5;
	srand(time(0));

	RenderWindow app(VideoMode(W+100, H+100), "Asteroids!", Style::Fullscreen);
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10,t13;
	Text SCORE, TIME, Gameover;
	Font font;
	font.loadFromFile("comicz.ttf");
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");
	t8.loadFromFile("images/Egg.png");
	t9.loadFromFile("images/egg_1.png");
	t10.loadFromFile("images/reward.png");
	t13.loadFromFile("images/heart.png");
	t1.setSmooth(true);
	t2.setSmooth(true);

	Sprite background(t2);

	Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
	Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
	Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
	Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
	Animation egg(t8, 0, 0, t8.getSize().x, t8.getSize().y, 1, 0);
	Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
	Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
	Animation Fire(t9, 0, 0, 40, 40, 1, 0.5);
	Animation rew(t10, 0, 0, 50, 53, 1, 0.5);
	Animation heart(t13, 0, 0, 200, 200, 1, 0, "heart");
	rew.sprite.setScale(50 / 40, 53 / 40);
	Egg *eg = new Egg();
	eg->settings(egg, W / 2, 0, -90, 240);
	std::list<Entity*> entities;
	entities.push_back(eg);
	time_score wr;	
	wr.Score(font, SCORE);
	wr.calculate_time(font, TIME);
	for (int i = 1; i <= 5; i++){
		Entity *h = new Entity();
			h->settings(heart, (i * 65), 1000, -90, 0, i);

		entities.push_back(h);
	}
	/*for (int i = 0;i<15;i++)
	{
	asteroid *a = new asteroid();
	a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
	entities.push_back(a);
	}*/

	player *p = new player();
	p->settings(sPlayer, 1000, 750, -90, 20);
	entities.push_back(p);
	Clock clock;
	Time time = clock.getElapsedTime();

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
	std::list<Sound*>ls;
	Sound sound_gameover;
	SoundBuffer bfsound_gameover;
	bfsound_gameover.loadFromFile("gameover.wav");
	sound_gameover.setBuffer(bfsound_gameover);
	/////main loop/////
	int num = 0;
    Clock clock1;
	int after_end_lifes = 0;
	while (app.isOpen())
	{
		Time elapsed1 = clock1.getElapsedTime();
		if (lifes != 0)
			wr.update_time(elapsed1);
		if (lifes == 0){
			s = true;
			for (auto i : entities){
				if (i->name == "asteroid" || i->name == "eggFire" )
				i->life = 0;
			}
			music.stop();
			if (after_end_lifes == 200)
				sound_gameover.play();
			after_end_lifes++;
			wr.gameover(font, Gameover);
			if (after_end_lifes == 700){
				app.close();

			}
		}
		wr.Score(font, SCORE);
		wr.calculate_time(font, TIME);
		
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
			if (event.key.code == Keyboard::Space)
			{
				bullt1.play();
				for (int i = 0; i <= (p->power.top() / 2) * 10; i += 10) {
					if (p->power.top() % 2 == 0 && i == 0)continue;
					bullet *b = new bullet();
					b->settings(sBullet, p->x, p->y, p->angle + i, 10);
					entities.push_back(b);
					if (i != 0) {
						bullet *b1 = new bullet();
						b1->settings(sBullet, p->x, p->y, p->angle - i, 10);
						entities.push_back(b1);
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) p->right = true;
		else p->right = false;
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->left = true;
		else p->left = false;
		if (Keyboard::isKeyPressed(Keyboard::Down))p->down = true;
		else p->down = false;
		if (Keyboard::isKeyPressed(Keyboard::Up))p->up = true;
		else p->up = false;

		time = clock.getElapsedTime();
		if ((int)time.asSeconds() == 5) {
			clock.restart();
			int p = rand();
			for (int i = -360; i < 360; i += 20) {
				EggFire *e = new EggFire();
				e->settings(Fire, eg->x, eg->y, i + p, 20);
				entities.push_back(e);

			}
			if (num % 3 == 0) {
				reward *r = new reward();
				r->settings(rew, eg->x, eg->y, -90, 20);
				entities.push_back(r);
			}
			num++;
		}


		for (auto a : entities)
		for (auto b : entities)
		{
			if (a->name == "asteroid" && b->name == "bullet")
			if (isCollide(a, b))
			{
				a->life = false;
				b->life = false;
				string s = "c";
				wr.updete(s);
				pump1.play();
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
			if (a->name == "egg" && b->name == "bullet")
			if (isCollide(a, b))
			{
				string s = "c";
				wr.updete(s);

				pump1.play();
				b->life = 0;
				Entity *e = new Entity();
				e->settings(sExplosion, b->x, b->y);
				e->name = "explosion";
				entities.push_back(e);
				eg->pow--;
				if (eg->pow <= 0) {
					a->life = 0;
					int bx = b->x, by = b->y;
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							Entity *e = new Entity();
							e->settings(sExplosion_ship, bx, by);
							e->name = "explosion";
							entities.push_back(e);
							by += 100;
						}
						bx += 100;
					}
				}
			}

			if (a->name == "player" && b->name == "asteroid")
			if (isCollide(a, b))
			{
				for (auto g : entities){
					if (g->name == "heart"&&g->number == lifes){
						g->life = false;
					}
				}
				if (lifes != 0)
				lifes--;
				b->life = false;
				pump1.play();
				Entity *e = new Entity();
				e->settings(sExplosion_ship, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);
				p->minus_Power();
				p->settings(sPlayer, W / 2, H - 1, -90, 20);
				p->dx = 0; p->dy = 0;
			}
			if (a->name == "player" && b->name == "eggFire")
			if (isCollide(a, b))
			{
				for (auto g : entities){
					if (g->name == "heart"&&g->number == lifes){
						g->life = false;
					}
				}
				if (lifes!=0)
				lifes--;
				b->life = false;
				pump1.play();
				Entity *e = new Entity();
				e->settings(sExplosion_ship, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);
				p->minus_Power();
				p->settings(sPlayer, W / 2, H - 1, -90, 20);
				p->dx = 0; p->dy = 0;
			}
			if (a->name == "player" && b->name == "egg")
			if (isCollide(a, b))
			{
				for (auto g : entities){
					
					if (g->name == "heart"&&g->number == lifes){
						g->life = false;
					}
				}
				if (lifes != 0)
				lifes--;
				pump1.play();
				eg->pow--;
				if (eg->pow <= 0) {
					b->life = false;
					int bx = b->x, by = b->y;
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							Entity *e = new Entity();
							e->settings(sExplosion_ship, bx, by);
							e->name = "explosion";
							entities.push_back(e);
							by += 100;
						}
						bx += 100;
					}

				}
				Entity *e = new Entity();
				e->settings(sExplosion_ship, a->x, a->y);
				e->name = "explosion";
				entities.push_back(e);
				p->minus_Power();
				p->settings(sPlayer, W / 2, H - 1, -90, 20);
				p->dx = 0; p->dy = 0;
			}
			if (a->name == "player" && b->name == "reward")
			if (isCollide(a, b))
			{
				b->life = 0;
				p->plus_Power();
			}
		}


		if (p->up)  p->anim = sPlayer_go;
		else   p->anim = sPlayer;

		for (auto e : entities)
		if (e->name == "explosion")
		if (e->anim.isEnd()) e->life = 0;
		int p = rand();
		if (p % 150 == 0)
		{
			asteroid *a = new asteroid();
			a->settings(sRock, 0, rand() % H, rand() % 360, 25);
			entities.push_back(a);
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}

		//////draw//////
		app.draw(background);
		app.draw(SCORE);
		app.draw(Gameover);
		app.draw(TIME);
		for (auto i : entities) i->draw(app);
		
		app.display();
	}

}

Amr::~Amr()
{
}
