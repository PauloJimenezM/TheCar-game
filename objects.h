//objects

enum IDS { PLAYER, BULLET, ENEMY, ENERGIA, AGUA };


struct Car {
	int ID;
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int score;
	int Road;
	int speed2;
	int energy;
	int nitro;
	bool water_detector;
	int bullet;
	int aux;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	int animationRow;

	ALLEGRO_BITMAP* image;
};

struct Bullet {
	int ID;
	int x;
	int y;
	bool live;
	int speed;

	ALLEGRO_SAMPLE* sonido;

};

struct Rock {
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP* image;
};

struct Explosion {
	int x;
	int y;
	bool live;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;

	ALLEGRO_BITMAP* image;
};

struct Background
{
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP* image;
};
