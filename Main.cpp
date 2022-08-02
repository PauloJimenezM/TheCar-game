
// Libraries
#pragma warning(disable:4996)
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "objects.h"
#include <string> 
#include <ctime>


using namespace std;


// Global constants
const int WIDTH = 1487;
const int HEIGHT = 900;
const int NUM_BULLETS = 5;
const int NUM_ROCKS = 30;
const int NUM_ENERGY = 5;
const int NUM_WATER = 8;
const int NUM_EXPLOSIONS = 5;
const int MUSIC = 9;


// Structures created in objects.h
Car car;
Bullet bullets[NUM_BULLETS];
Rock Rocks[NUM_ROCKS];
Rock Energy[NUM_ENERGY];
Rock Water[NUM_WATER];
Explosion explosions[NUM_EXPLOSIONS];


enum STATE { TITLE, PLAYING, LOST }; // Set of values
enum KEYS { W, S, A, D, SPACE, C, Q, R, H }; // Keys to use
bool keys[9] = { false, false, false, false, false, false, false, false, false };


// Function declaration
void Initcar(Car& car, ALLEGRO_BITMAP* image);
void Drawcar(Car& car);
void MovecarUp(Car& car);
void MovecarDown(Car& car);
void MovecarLeft(Car& car);
void MovecarRight(Car& car);

void InitBullet(Bullet bullet[], int size);
void DrawBullet(Bullet bullet[], int size, ALLEGRO_BITMAP* Laser, ALLEGRO_SAMPLE* shot,
	ALLEGRO_SAMPLE_ID& shotID, ALLEGRO_FONT* Numbers2);
void FireBullet(Bullet bullet[], int size, Car& car);
void UpdateBullet(Bullet bullet[], int size);
void CollideBullet(Bullet bullet[], int bSize, Rock Rocks[], int cSize, Car& car,
	Explosion explosions[], int eSize, ALLEGRO_SAMPLE* rocks, ALLEGRO_SAMPLE_ID& rocksID);

void InitRock(Rock Rocks[], int size, ALLEGRO_BITMAP* image);
void DrawRock(Rock Rocks[], int size);
void StartRock(Rock Rocks[], int size);
void UpdateRock(Rock Rocks[], int size);
void ColliRock1(Rock Rocks[], int cSize, Car& car, Explosion explosions[], int eSize);
void ColliRock2(Rock Rocks[], int cSize, Car& car, Explosion explosions[], int eSize);

void InitEnergy(Rock Rocks[], int size, ALLEGRO_BITMAP* image);
void DrawEnergy(Rock Rocks[], int size);
void StartEnergy(Rock Rocks[], int size);
void UpdateEnergy(Rock Rocks[], int size);
void CollideEnergy(Rock Rocks[], int cSize, Car& car, Explosion explosions[], int eSize);

void InitWater(Rock Rocks[], int size, ALLEGRO_BITMAP* image);
void DrawWater(Rock Rocks[], int size);
void StartWater(Rock Rocks[], int size);
void UpdateWater(Rock Rocks[], int size);
void ColliWater(Rock Rocks[], int cSize, Car& car, Explosion explosions[], int eSize,
	ALLEGRO_SAMPLE* Water_pool, ALLEGRO_SAMPLE_ID& Water_poolID);

void InitExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP* image);
void DrawExplosions(Explosion explosions[], int size);
void StartExplosions(Explosion explosions[], int size, int x, int y);
void UpdateExplosions(Explosion explosions[], int size);


// This functions allows the background to have movement 										 
void InitBackground(Background& back, float x, float y, float velx, float vely, int width,
	int height, int dirX, int dirY, ALLEGRO_BITMAP* image); 							 
void UpdateBackground(Background& back);												
void DrawBackground(Background& back);	

void energy();
void nitro();
void Updatenitro();

void ChangeState(int& state, int newState); // States function



//	Main
int main(void) {


	// Variable declarations
	bool done = false;
	bool redraw = true; // Render
	const int FPS = 60; // Frames per second
	int state = -1;
	float introMUSIC = 0.3;
	int cont = 0;
	int air = 0;
	int air2 = 0;

	time_t sec;
	tm* curTime;

	// Map Variables
	Background BG; //Background
	Background MG; //Middle Ground
	Background FG; //Foreground


	// Allegro Variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;


	// Fonts used 
	ALLEGRO_FONT* font18 = NULL;   
	ALLEGRO_FONT* Numbers = NULL;  
	ALLEGRO_FONT* Numbers1 = NULL; 
	ALLEGRO_FONT* Numbers2 = NULL; 
	ALLEGRO_FONT* Clock = NULL;    

	// Abstract type representing a bitmap
	ALLEGRO_BITMAP* carImage; 
	ALLEGRO_BITMAP* DashBoard;

	ALLEGRO_BITMAP* speedometer;
	ALLEGRO_BITMAP* speedometer1;
	ALLEGRO_BITMAP* speedometer2;
	ALLEGRO_BITMAP* speedometer3;
	ALLEGRO_BITMAP* speedometer4;
	ALLEGRO_BITMAP* speedometer5;
	ALLEGRO_BITMAP* speedometer6;
	ALLEGRO_BITMAP* speedometer7;
	ALLEGRO_BITMAP* speedometer8;
	ALLEGRO_BITMAP* speedometer9;

	ALLEGRO_BITMAP* power1;
	ALLEGRO_BITMAP* power2;
	ALLEGRO_BITMAP* power3;
	ALLEGRO_BITMAP* power4;
	ALLEGRO_BITMAP* power5;
	ALLEGRO_BITMAP* power6;

	ALLEGRO_BITMAP* battery0;
	ALLEGRO_BITMAP* battery1;
	ALLEGRO_BITMAP* battery2;
	ALLEGRO_BITMAP* battery3;
	ALLEGRO_BITMAP* battery4;
	ALLEGRO_BITMAP* battery5;
	ALLEGRO_BITMAP* battery6;
	ALLEGRO_BITMAP* battery7;

	ALLEGRO_BITMAP* Gears1;
	ALLEGRO_BITMAP* Gears2;
	ALLEGRO_BITMAP* Gears3;
	ALLEGRO_BITMAP* Gears4;
	ALLEGRO_BITMAP* Gears5;
	ALLEGRO_BITMAP* Gears6;

	ALLEGRO_BITMAP* Nitro0;
	ALLEGRO_BITMAP* Nitro1;
	ALLEGRO_BITMAP* Nitro2;
	ALLEGRO_BITMAP* Nitro3;
	ALLEGRO_BITMAP* Nitro4;
	ALLEGRO_BITMAP* Nitro5;

	ALLEGRO_BITMAP* Distance;
	ALLEGRO_BITMAP* Ignition;
	ALLEGRO_BITMAP* Ignition2;
	ALLEGRO_BITMAP* warning;

	ALLEGRO_BITMAP* steering_wheel0;
	ALLEGRO_BITMAP* steering_wheel1;
	ALLEGRO_BITMAP* steering_wheel2;

	ALLEGRO_BITMAP* DRight;
	ALLEGRO_BITMAP* DLeft;
	ALLEGRO_BITMAP* RockImage;
	ALLEGRO_BITMAP* EnergyImage;
	ALLEGRO_BITMAP* WaterImage;
	ALLEGRO_BITMAP* expImage;
	ALLEGRO_BITMAP* title = NULL;
	ALLEGRO_BITMAP* lost = NULL;
	ALLEGRO_BITMAP* bgImage = NULL;
	ALLEGRO_BITMAP* mgImage = NULL;
	ALLEGRO_BITMAP* fgImage = NULL;
	ALLEGRO_BITMAP* Laser;

	ALLEGRO_BITMAP* Chassis0;
	ALLEGRO_BITMAP* Chassis1;
	ALLEGRO_BITMAP* Chassis2;
	ALLEGRO_BITMAP* Chassis3;
	ALLEGRO_BITMAP* Chassis4;
	ALLEGRO_BITMAP* Chassis5;

	ALLEGRO_BITMAP* Target;
	ALLEGRO_BITMAP* Belt;

	// Object that stores the data necessary for playing pre-defined digital audio
	ALLEGRO_SAMPLE* Menu; 
	ALLEGRO_SAMPLE* Game_over;
	ALLEGRO_SAMPLE* Low_battery;
	ALLEGRO_SAMPLE* shot;
	ALLEGRO_SAMPLE* Water_pool;
	ALLEGRO_SAMPLE* Engine;
	ALLEGRO_SAMPLE* rocks;
	ALLEGRO_SAMPLE* NO2;

	// Samples being played via al_play_sample
	ALLEGRO_SAMPLE_ID MenuID; 
	ALLEGRO_SAMPLE_ID Game_overID;
	ALLEGRO_SAMPLE_ID Low_batteryID;
	ALLEGRO_SAMPLE_ID shotID;
	ALLEGRO_SAMPLE_ID Water_poolID;
	ALLEGRO_SAMPLE_ID EngineID;
	ALLEGRO_SAMPLE_ID rocksID;
	ALLEGRO_SAMPLE_ID NO2ID;

					
	if (!al_init()) { // Initialize the Allegro system
		return -1;
	}

	display = al_create_display(WIDTH, HEIGHT);	// Create a display with the specified dimensions

	if (!display) {	// Test display
		return -1;
	}

	// initialize the addons
	al_init_primitives_addon();
	al_install_keyboard(); // Install a keyboard driver
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	// Audio
	al_install_audio();    
	al_init_acodec_addon(); 

	al_install_mouse(); // Install a mouse driver

	event_queue = al_create_event_queue(); // Create a new, empty event queue
	timer = al_create_timer(1.0 / FPS); // Allocates and initializes a timer


				
	// Sounds
	al_reserve_samples(MUSIC); // Reserves a number of sample instances
	
	Menu = al_load_sample("Sounds/Menu.wav");	// Loads a audio file
	Game_over = al_load_sample("Sounds/GameOver.wav");
	Low_battery = al_load_sample("Sounds/Battery_Low.wav");
	shot = al_load_sample("Sounds/Laser_shot.wav");
	Water_pool = al_load_sample("Sounds/Water.wav");
	Engine = al_load_sample("Sounds/Car_Engine.wav");
	rocks = al_load_sample("Sounds/Rocks.wav");
	NO2 = al_load_sample("Sounds/Nitrous_Burst.wav");




			
	// Images
	carImage = al_load_bitmap("Images/Car2.png"); // Loads a image file

	al_convert_mask_to_alpha(carImage, al_map_rgb(255, 0, 255)); // Convert carImage color to an alpha channel in the bitmap

	RockImage = al_load_bitmap("Images/rock.png");
	EnergyImage = al_load_bitmap("Images/lightning.png");
	WaterImage = al_load_bitmap("Images/Water.png");
	DashBoard = al_load_bitmap("Images/Dashboardnew.png");

	steering_wheel0 = al_load_bitmap("Images/steering_wheel0.png");
	steering_wheel1 = al_load_bitmap("Images/steering_wheel1.png");
	steering_wheel2 = al_load_bitmap("Images/steering_wheel2.png");

	DRight = al_load_bitmap("Images/DRight.png");
	DLeft = al_load_bitmap("Images/DLeft.png");

	speedometer = al_load_bitmap("Images/speedometer0.png");
	speedometer1 = al_load_bitmap("Images/speedometer1.png");
	speedometer2 = al_load_bitmap("Images/speedometer2.png");
	speedometer3 = al_load_bitmap("Images/speedometer3.png");
	speedometer4 = al_load_bitmap("Images/speedometer4.png");
	speedometer5 = al_load_bitmap("Images/speedometer5.png");
	speedometer6 = al_load_bitmap("Images/speedometer6.png");
	speedometer7 = al_load_bitmap("Images/speedometer7.png");
	speedometer8 = al_load_bitmap("Images/speedometer8.png");
	speedometer9 = al_load_bitmap("Images/speedometer9.png");

	power1 = al_load_bitmap("Images/power1.png");
	power2 = al_load_bitmap("Images/power2.png");
	power3 = al_load_bitmap("Images/power3.png");
	power4 = al_load_bitmap("Images/power4.png");
	power5 = al_load_bitmap("Images/power5.png");
	power6 = al_load_bitmap("Images/power6.png");

	battery0 = al_load_bitmap("Images/battery0.png");
	battery1 = al_load_bitmap("Images/battery1.png");
	battery2 = al_load_bitmap("Images/battery2.png");
	battery3 = al_load_bitmap("Images/battery3.png");
	battery4 = al_load_bitmap("Images/battery4.png");
	battery5 = al_load_bitmap("Images/battery5.png");
	battery6 = al_load_bitmap("Images/battery6.png");
	battery7 = al_load_bitmap("Images/battery7.png");

	Gears1 = al_load_bitmap("Images/Gears1.png");
	Gears2 = al_load_bitmap("Images/Gears2.png");
	Gears3 = al_load_bitmap("Images/Gears3.png");
	Gears4 = al_load_bitmap("Images/Gears4.png");
	Gears5 = al_load_bitmap("Images/Gears5.png");
	Gears6 = al_load_bitmap("Images/Gears6.png");

	Nitro0 = al_load_bitmap("Images/Nitro0.png");
	Nitro1 = al_load_bitmap("Images/Nitro1.png");
	Nitro2 = al_load_bitmap("Images/Nitro2.png");
	Nitro3 = al_load_bitmap("Images/Nitro3.png");
	Nitro4 = al_load_bitmap("Images/Nitro4.png");
	Nitro5 = al_load_bitmap("Images/Nitro5.png");

	Distance = al_load_bitmap("Images/Distance.png");
	Ignition = al_load_bitmap("Images/Ignition.png");
	Ignition2 = al_load_bitmap("Images/Ignition2.png");
	warning = al_load_bitmap("Images/warning.png");

	Chassis0 = al_load_bitmap("Images/Chassis_Top0.png");
	Chassis1 = al_load_bitmap("Images/Chassis_Top1.png");
	Chassis2 = al_load_bitmap("Images/Chassis_Top2.png");
	Chassis3 = al_load_bitmap("Images/Chassis_Top3.png");
	Chassis4 = al_load_bitmap("Images/Chassis_Top4.png");
	Chassis5 = al_load_bitmap("Images/Chassis_Top5.png");

	expImage = al_load_bitmap("Images/explosion.png");
	title = al_load_bitmap("Images/Menu.png");
	lost = al_load_bitmap("Images/Lose.png");
	bgImage = al_load_bitmap("Images/road.png");
	mgImage = al_load_bitmap("Images/bush.png");
	fgImage = al_load_bitmap("Images/bush.png");
	Laser = al_load_bitmap("Images/Laser.png");

	Target = al_load_bitmap("Images/Target.png");
	Belt = al_load_bitmap("Images/Belt.png");

	// Initialize random number
	srand(time(NULL));

	// Change the current state to TITLE state
	ChangeState(state, TITLE);


							
	// Initializing car and map
	Initcar(car, carImage);
	InitBullet(bullets, NUM_BULLETS);
	InitRock(Rocks, NUM_ROCKS, RockImage);
	InitEnergy(Energy, NUM_ENERGY, EnergyImage);
	InitWater(Water, NUM_WATER, WaterImage);
	InitExplosions(explosions, NUM_EXPLOSIONS, expImage);

	InitBackground(BG, 390, 0, 0, 0, 600, 800, 1, -1, bgImage);
	InitBackground(MG, 235, 0, 0, 0, 500, 800, 1, -1, mgImage);
	InitBackground(FG, 775, 0, 0, car.speed2, 100, 800, 1, -1, fgImage);


	font18 = al_load_font("Font/arial.ttf", 16, 0);	// Loads a font
	Numbers = al_load_font("Font/DS-DIGIB.ttf", 20, 0);
	Numbers1 = al_load_font("Font/DS-DIGIB.ttf", 20, 0);
	Numbers2 = al_load_font("Font/DS-DIGIB.ttf", 25, 0);
	Clock = al_load_font("Font/The_Led_Display_St.ttf", 40, 0);

	// Register the event source with the event queue specified
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer); //Start the timer


															
	// The game
	while (!done) {
		sec = time(NULL); //  Returned time in seconds from 1 January 1970
		curTime = localtime(&sec); // Convert time in seconds into an understandable format
		ALLEGRO_EVENT ev; // ALLEGRO_EVENT is a union of all builtin event structures
		al_wait_for_event(event_queue, &ev); // Wait until the event queue specified is non-empty


	
		// keys
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			if (keys[Q]) { // Start the car
				if (keys[W]) {
					if (state == PLAYING) {
						if (car.energy > 0) {
							MovecarUp(car);
						}
						else {
							keys[W] = false;
						}
					}
					else {
						keys[W] = false;
					}

				}
				else if (keys[S]) {
					if (state == PLAYING) {
						MovecarDown(car);
					}
					else {
						keys[S] = false;
					}

				}
				else if (keys[A]) {
					if (state == PLAYING) {
						MovecarLeft(car);
					}
					else {
						keys[A] = false;
					}
				}
				else if (keys[D]) {
					if (state == PLAYING) {
						MovecarRight(car);
					}
					else {
						keys[D] = false;
					}
				}
				else {
					car.animationRow = 1; // Rows of the car image which has different positions
				}

				if (keys[C]) { // Car nitrous
					if (state == PLAYING) {
						if (car.nitro != 0 && car.speed2 != 0 && car.energy != 0) {
							al_play_sample(NO2, 0.3, 0.1, 1.0, ALLEGRO_PLAYMODE_ONCE, &NO2ID); // Loads a audio file
							nitro();
						}
						else if (car.nitro == 0) {
							car.speed2 = 40;
							if (keys[W]) {
								if (car.energy > 0) {
									MovecarUp(car);
								}
							}
						}
					}
					else {
						keys[C] = false;
					}

				}
			}

			if (state == TITLE) {
				al_play_sample(Menu, introMUSIC, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &MenuID); // Loads a audio file

			}
			else if (state == PLAYING) {
				UpdateBackground(BG);
				UpdateBackground(MG);
				UpdateBackground(FG);
				energy();
				Updatenitro();

				UpdateExplosions(explosions, NUM_EXPLOSIONS);
				UpdateBullet(bullets, NUM_BULLETS);
				StartRock(Rocks, NUM_ROCKS);
				StartEnergy(Energy, NUM_ENERGY);
				StartWater(Water, NUM_WATER);
				UpdateRock(Rocks, NUM_ROCKS);
				UpdateEnergy(Energy, NUM_ENERGY);
				UpdateWater(Water, NUM_WATER);
				CollideBullet(bullets, NUM_BULLETS, Rocks, NUM_ROCKS, car, explosions,
					NUM_EXPLOSIONS, rocks, rocksID);

				if (keys[C]) {
					ColliRock2(Rocks, NUM_ROCKS, car, explosions, NUM_EXPLOSIONS); // When using nitro the rocks score points
				}
				else {
					ColliRock1(Rocks, NUM_ROCKS, car, explosions, NUM_EXPLOSIONS); // When nitro is not used, rocks reduce the lives of the car.
				}

				CollideEnergy(Energy, NUM_ENERGY, car, explosions, NUM_EXPLOSIONS);

				ColliWater(Water, NUM_WATER, car, explosions, NUM_EXPLOSIONS, Water_pool, Water_poolID);

				if (car.lives <= 0 || car.speed2 == 0 && car.energy == 0) { // Game Over
					ChangeState(state, LOST);
				}
			}
			else if (state == LOST) {
				al_play_sample(Game_over, 0.3, 0.0, 0.9, ALLEGRO_PLAYMODE_ONCE, &Game_overID);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // The window is closed
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) { // The key is pressed
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = true;
				break;
			case ALLEGRO_KEY_Q:
				keys[Q] = true;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = true;
				break;
			case ALLEGRO_KEY_C:
				keys[C] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;

				if (state == TITLE) {
					ChangeState(state, PLAYING);
				}
				else if (state == PLAYING) {
					FireBullet(bullets, NUM_BULLETS, car);
				}
				else if (state == LOST) {
					ChangeState(state, PLAYING);
				}
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) { // The key is released
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_W:
				keys[W] = false;
				break;
			case ALLEGRO_KEY_S:
				keys[S] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[D] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_C:
				keys[C] = false;
				break;
			case ALLEGRO_KEY_Q:
				keys[Q] = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue)) { // If the tail is empty it does not redraw
			redraw = false;

			if (state == TITLE) {
				al_draw_bitmap(title, 0, 0, 0); // Set menu image
				introMUSIC = 0; // The audio intro repeats once
			}

			else if (state == PLAYING) {
				DrawBackground(BG);
				DrawBackground(MG);
				DrawBackground(FG);

				DrawWater(Water, NUM_WATER);
				Drawcar(car);
				DrawBullet(bullets, NUM_BULLETS, Laser, shot, shotID, Numbers2);
				DrawRock(Rocks, NUM_ROCKS);
				DrawEnergy(Energy, NUM_ENERGY);

				DrawExplosions(explosions, NUM_EXPLOSIONS);

				al_draw_bitmap(DashBoard, 0, 0, 0);


				if (car.speed2 == 0) { // Doing the speedometer animation
					al_draw_bitmap(speedometer, 325, 620, 0);
				}
				else if (car.speed2 <= 5.5) {
					al_draw_bitmap(speedometer1, 325, 620, 0);
				}
				else if (car.speed2 > 5.5 && car.speed2 <= 11) {
					al_draw_bitmap(speedometer2, 325, 620, 0);
				}
				else if (car.speed2 > 11 && car.speed2 <= 16.5) {
					al_draw_bitmap(speedometer3, 325, 620, 0);
				}
				else if (car.speed2 > 16.5 && car.speed2 <= 22) {
					al_draw_bitmap(speedometer4, 325, 620, 0);
				}
				else if (car.speed2 > 22 && car.speed2 <= 27.5) {
					al_draw_bitmap(speedometer5, 325, 620, 0);
				}
				else if (car.speed2 > 27.5 && car.speed2 <= 33) {
					al_draw_bitmap(speedometer6, 325, 620, 0);
				}
				else if (car.speed2 > 33 && car.speed2 <= 38.5) {
					al_draw_bitmap(speedometer7, 325, 620, 0);
				}
				else if (car.speed2 > 38.5 && car.speed2 <= 44) {
					al_draw_bitmap(speedometer8, 325, 620, 0);
				}
				else if (car.speed2 > 44) {
					al_draw_bitmap(speedometer9, 325, 620, 0);
				}


				if (car.energy > 12) { // Doing the battery animation
					al_draw_bitmap(battery7, 590, 620, 0);
				}
				else if (car.energy == 12 || car.energy == 11) {
					al_draw_bitmap(battery6, 590, 620, 0);
				}
				else if (car.energy == 10 || car.energy == 9) {
					al_draw_bitmap(battery5, 590, 620, 0);
				}
				else if (car.energy == 8 || car.energy == 7) {
					al_draw_bitmap(battery4, 590, 620, 0);
				}
				else if (car.energy == 6 || car.energy == 5) {
					al_draw_bitmap(battery3, 590, 620, 0);
				}
				else if (car.energy == 4 || car.energy == 3) {
					if (car.energy == 3) {
						al_play_sample(Low_battery, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &Low_batteryID);
					}
					al_draw_bitmap(battery2, 590, 620, 0);
				}
				else if (car.energy == 2 || car.energy == 1) {
					al_draw_bitmap(battery1, 590, 620, 0);
				}
				else if (car.energy == 0) {
					al_draw_bitmap(battery0, 590, 620, 0);
				}


				if (car.nitro == 5) { // Doing the nitro animation
					al_draw_bitmap(Nitro5, 77, 260, 0);
				}
				else if (car.nitro == 4) {
					al_draw_bitmap(Nitro4, 77, 260, 0);
				}
				else if (car.nitro == 3) {
					al_draw_bitmap(Nitro3, 77, 260, 0);
				}
				else if (car.nitro == 2) {
					al_draw_bitmap(Nitro2, 77, 260, 0);
				}
				else if (car.nitro == 1) {
					al_draw_bitmap(Nitro1, 77, 260, 0);
				}
				else if (car.nitro == 0) {
					al_draw_bitmap(Nitro0, 77, 260, 0);
				}

				if (car.speed2 == 0) { // Doing the animation of the car gears
					al_draw_bitmap(Gears1, 1065, 750, 0);
				}
				else if (car.speed2 <= 10) {
					al_draw_bitmap(Gears2, 1065, 750, 0);
				}
				else if (car.speed2 > 10 && car.speed2 <= 20) {
					al_draw_bitmap(Gears3, 1065, 750, 0);
				}
				else if (car.speed2 > 20 && car.speed2 <= 30) {
					al_draw_bitmap(Gears4, 1065, 750, 0);
				}
				else if (car.speed2 > 30 && car.speed2 <= 40) {
					al_draw_bitmap(Gears5, 1065, 750, 0);
				}
				else if (car.speed2 > 40) {
					al_draw_bitmap(Gears6, 1065, 750, 0);
				}

				if (car.lives == 5) { // Doing the animation of the lives
					al_draw_bitmap(Chassis0, 1012, 550, 0);
				}
				else if (car.lives == 4) {
					al_draw_bitmap(Chassis1, 1012, 550, 0);
				}
				else if (car.lives == 3) {
					al_draw_bitmap(Chassis2, 1012, 550, 0);
				}
				else if (car.lives == 2) {
					al_draw_bitmap(Chassis3, 1012, 550, 0);
				}
				else if (car.lives == 1) {
					al_draw_bitmap(Chassis4, 1012, 550, 0);
				}
				else if (car.lives == 0) {
					al_draw_bitmap(Chassis5, 1012, 550, 0);
				}

				if (car.water_detector == 1) { // If water is detected 
					al_draw_bitmap(warning, 500, 640, 0);
					al_draw_textf(font18, al_map_rgb(0, 145, 255), 515, 710, 0, "Wet Road");
				}

				al_draw_bitmap(Distance, 485, 602, 0);
				al_draw_bitmap(Distance, 485, 630, 0);

				if (keys[A]) { // Displaying the direction on the dashboard
					al_draw_bitmap(DLeft, 455, 610, 0);
				}

				else if (keys[D]) { // Displaying the direction on the dashboard
					al_draw_bitmap(DRight, 580, 608, 0);
				}

				// Displaying the low battery icon on the dashboard
				if (car.energy <= 6 && car.energy >= 5) {
					al_draw_bitmap(power1, 400, 690, 0);
				}
				else if (car.energy <= 4 && car.energy >= 1) {
					al_draw_bitmap(power2, 400, 690, 0);
				}
				else if (car.energy == 0) {
					al_draw_bitmap(power6, 390, 690, 0);
				}

				if (car.speed2 == 0) {
					al_draw_bitmap(Ignition, 210, 560, 0);
					if (keys[Q]) {
						al_draw_bitmap(Ignition2, 227, 559, 0);
					}
				}
				else if (car.speed2 != 0) { // Dashboard data
					al_draw_textf(Numbers, al_map_rgb(255, 0, 0), 375, 665, 0, "%i km/h",
						car.speed2 * 4);
					al_draw_textf(Numbers1, al_map_rgb(255, 255, 255), 500, 603, 0, "%i m",
						car.Road / 100);
					al_draw_textf(Numbers1, al_map_rgb(255, 255, 255), 525, 630, 0, "%i",
						car.score);
					al_draw_textf(Numbers2, al_map_rgb(0, 50, 250), 75, 650, 0, "%i ",
						(car.speed2 * 4) * 6,143081); // With 17-inch wheels
				}

				// Steering wheel rotation
				if (keys[A]) { 
					al_draw_bitmap(steering_wheel1, 155, 540, 0);
				}

				else if (keys[D]) {
					al_draw_bitmap(steering_wheel2, 155, 540, 0);
				}
				else {
					al_draw_bitmap(steering_wheel0, 155, 540, 0);
				}

				al_draw_textf(Numbers2, al_map_rgb(0, 50, 240), 1375, 595, 0, "%i", car.bullet / 40); // Bullet count

				// Time
				al_draw_textf(Clock, al_map_rgb(0, 50, 240), 1120, 70, 0, "%i", curTime->tm_hour);
				al_draw_textf(Clock, al_map_rgb(80, 120, 240), 1190, 70, 0, ": %i", curTime->tm_min);
				al_draw_textf(Clock, al_map_rgb(160, 170, 240), 1280, 70, 0, ": %i", curTime->tm_sec);
				al_draw_textf(Clock, al_map_rgb(240, 0, 45), 1120, 150, 0, "%i", curTime->tm_mday);
				al_draw_textf(Clock, al_map_rgb(240, 100, 100), 1190, 150, 0, ": %i", curTime->tm_mon+1);
				al_draw_textf(Clock, al_map_rgb(240, 200, 155), 1260, 150, 0, ": %i", curTime->tm_year + 1900);
				
				// Air flow
				if ((car.speed2 + ((rand() % 30) + -30) < 0)) { 
					air = -((rand() % 30) + -30);
					al_draw_textf(Numbers2, al_map_rgb(240, 10, 10), 1439, 595, 0, "%i", air);
				}
				else if ((car.speed2 + ((rand() % 30) + -30) > 0)) {
					air2 = car.speed2 + ((rand() % 30) + -30);
					al_draw_textf(Numbers2, al_map_rgb(0, 50, 240), 1439, 595, 0, "%i", air2);
				}
				if (curTime->tm_sec % 3 == 0) { // Displaying belt icon
					al_draw_bitmap(Belt, 665, 670, 0);
				}

			}

			else if (state == LOST) {
		
				// Score
				
				al_rest(1.0); // Pause
				al_draw_bitmap(lost, 0, 0, 0); // Loads game over image
				al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - 155, 55, ALLEGRO_ALIGN_RIGHT,
					"Final Score     ");
				al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - 130, 95, ALLEGRO_ALIGN_RIGHT,
					"Rocks destroyed........... %i", car.score);
				al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - 123.5, 118, ALLEGRO_ALIGN_RIGHT,
					"Distance.................. %i m", car.Road / 100);
				al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - 140, 140, ALLEGRO_ALIGN_RIGHT,
					"Score....................... %i", ((car.Road / 100) + car.score * 10)); // Distance + Score*10.

			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear the complete target bitmap
		}
	}
					
	// The previously used variables are destroyed
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(mgImage);
	al_destroy_bitmap(fgImage);
	al_destroy_bitmap(title);
	al_destroy_bitmap(lost);
	al_destroy_bitmap(expImage);
	al_destroy_bitmap(RockImage);
	al_destroy_bitmap(EnergyImage);
	al_destroy_bitmap(WaterImage);
	al_destroy_bitmap(carImage);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font18);
	al_destroy_font(Numbers);
	al_destroy_font(Numbers1);
	al_destroy_font(Numbers2);
	al_destroy_font(Clock);
	al_destroy_display(display);
	al_destroy_sample(Menu);
	al_destroy_sample(Game_over);
	al_destroy_sample(Low_battery);
	al_destroy_sample(shot);
	al_destroy_sample(Water_pool);
	al_destroy_sample(Engine);
	al_destroy_sample(rocks);
	al_destroy_sample(NO2);
	al_destroy_bitmap(Target);
	al_destroy_bitmap(Belt);

	return 0;
}


					
// Functions

void ChangeState(int& state, int newState) { // Change of state

	state = newState;
	if (state == TITLE) {
	}
	else if (state == PLAYING) {
		Initcar(car, NULL);
		InitBullet(bullets, NUM_BULLETS);
		InitRock(Rocks, NUM_ROCKS, NULL);
		InitExplosions(explosions, NUM_EXPLOSIONS, NULL);
	}
	else if (state == LOST) {
	}
}

void Initcar(Car& car, ALLEGRO_BITMAP* image) { // Adds value to the car

	car.x = WIDTH / 2 - 150;
	car.y = 500;
	car.ID = PLAYER;
	car.lives = 5;
	car.speed = 6;
	car.boundx =  50;
	car.boundy =  0;
	car.score = 0;
	car.speed2 = 0;
	car.energy = 12;
	car.nitro = 5;
	car.water_detector = 0;
	car.bullet = 0;
	car.aux = 0;

	car.maxFrame = 3;
	car.curFrame = 0;
	car.frameCount = 0;
	car.frameDelay = 50;
	car.frameWidth = 140;
	car.frameHeight = 124;
	car.animationColumns = 3;
	car.animationDirection = 1;

	car.animationRow = 1;

	if (image != NULL) {
		car.image = image;
	}
}

void Drawcar(Car& car) { // Draw the car in the corresponding position.
	int fx = (car.curFrame % car.animationColumns) * car.frameWidth;
	int fy = car.animationRow * car.frameHeight;
	al_draw_bitmap_region(car.image, fx, fy, car.frameWidth, car.frameHeight, car.x -
		car.frameWidth / 2, car.y - car.frameHeight / 2, 0); //  Draws a region of the given bitmap to the target bitmap

}

void MovecarUp(Car& car) { // Function when pressing the w key 
	car.animationRow = 1;
	if (car.speed2 <= 50) {
		car.speed2++;
	}
}

void MovecarDown(Car& car) { // Function when pressing the s key 
	if (car.speed2 >= 20) {
		car.speed2--;
	}
}

void MovecarLeft(Car& car) { // Function when pressing the a key 
	car.animationRow = 0;
	car.x -= car.speed;
	if (car.x < 450) {
		car.x = 450;
	}
}

void MovecarRight(Car& car) { // Function when pressing the d key 
	car.animationRow = 2;
	car.x += car.speed;
	if (car.x > 750) {
		car.x = 750;
	}
}

void InitBullet(Bullet bullet[], int size) {  // Initialize the bullets
	for (int i = 0; i < size; i++) {
		bullet[i].ID = BULLET;
		bullet[i].speed = 10;
		bullet[i].live = false;
	}
}


void DrawBullet(Bullet bullet[], int size, ALLEGRO_BITMAP* Laser, ALLEGRO_SAMPLE* shot,
	ALLEGRO_SAMPLE_ID& shotID, ALLEGRO_FONT* Numbers2) { // Function when pressing the space key 
	for (int i = 0; i < size; i++) {
		if (bullet[i].live) {
			car.bullet++;
			al_play_sample(shot, 0.3, 0.1, 1.0, ALLEGRO_PLAYMODE_ONCE, &shotID);
			al_draw_bitmap(Laser, bullet[i].x - 5, bullet[i].y - 35, 0);
		}
	}
}

void FireBullet(Bullet bullet[], int size, Car& car) { // Bullet shot
	for (int i = 0; i < size; i++) {
		if (!bullet[i].live) {
			bullet[i].x = car.x;
			bullet[i].y = car.y - 50;
			bullet[i].live = true;
			break;
		}
	}
}

void UpdateBullet(Bullet bullet[], int size) { // Updates the bullets
	for (int i = 0; i < size; i++) {
		if (bullet[i].live) {
			bullet[i].y -= bullet[i].speed;
			if (bullet[i].y == 0) {
				bullet[i].live = false;
			}
		}
	}
}

void CollideBullet(Bullet bullet[], int bSize, Rock Rocks[], int cSize, Car& car,
	Explosion explosions[], int eSize, ALLEGRO_SAMPLE* rocks, ALLEGRO_SAMPLE_ID& rocksID) { // Function when a bullet hits a rock
	for (int i = 0; i < bSize; i++) {
		if (bullet[i].live) {
			for (int j = 0; j < cSize; j++) {
				if (Rocks[j].live) {
					if (bullet[i].x > (Rocks[j].x - Rocks[j].boundx) &&
						bullet[i].x < (Rocks[j].x + Rocks[j].boundx) &&
						bullet[i].y >(Rocks[j].y - Rocks[j].boundy) &&
						bullet[i].y < (Rocks[j].y + Rocks[j].boundy))
					{
						al_play_sample(rocks, 0.3, 0.1, 1.0, ALLEGRO_PLAYMODE_ONCE, &rocksID);
						bullet[i].live = false;
						Rocks[j].live = false;

						car.score++;

						StartExplosions(explosions, eSize, bullet[i].x, bullet[i].y);
					}
				}
			}
		}
	}
}

void InitRock(Rock Rocks[], int size, ALLEGRO_BITMAP* image) { // Initialize the rocks
	for (int i = 0; i < size; i++) {
		Rocks[i].ID = ENEMY;
		Rocks[i].live = false;
		Rocks[i].speed = car.speed2;
		Rocks[i].boundx = 70;
		Rocks[i].boundy = 40;

		Rocks[i].maxFrame = 143;
		Rocks[i].curFrame = 0;
		Rocks[i].frameCount = 0;
		Rocks[i].frameDelay = 2;
		Rocks[i].frameWidth = 150;
		Rocks[i].frameHeight = 200;
		Rocks[i].animationColumns = 21;

		if (rand() % 2) {
			Rocks[i].animationDirection = 1;
		}
		else {
			Rocks[i].animationDirection = -1;
		}
		if (image != NULL) {
			Rocks[i].image = image;
		}
	}
}

void InitWater(Rock Rocks[], int size, ALLEGRO_BITMAP* image) { // Initialize the pools of water
	for (int i = 0; i < size; i++) {
		Rocks[i].ID = AGUA;
		Rocks[i].live = false;
		Rocks[i].speed = car.speed2;
		Rocks[i].boundx = 200;
		Rocks[i].boundy = 200;

		Rocks[i].maxFrame = 143;
		Rocks[i].curFrame = 0;
		Rocks[i].frameCount = 0;
		Rocks[i].frameDelay = 2;
		Rocks[i].frameWidth = 100;
		Rocks[i].frameHeight = 500;
		Rocks[i].animationColumns = 21;

		if (rand() % 2) {
			Rocks[i].animationDirection = 1;
		}
		else {
			Rocks[i].animationDirection = -1;
		}

		if (image != NULL) {
			Rocks[i].image = image;
		}
	}
}

void InitEnergy(Rock Rocks[], int size, ALLEGRO_BITMAP* image) { // Initialize the energy
	for (int i = 0; i < size; i++) {
		Rocks[i].ID = ENERGIA;
		Rocks[i].live = false;
		Rocks[i].speed = car.speed2;
		Rocks[i].boundx = 50;
		Rocks[i].boundy = 50;

		Rocks[i].maxFrame = 143;
		Rocks[i].curFrame = 0;
		Rocks[i].frameCount = 0;
		Rocks[i].frameDelay = 2;
		Rocks[i].frameWidth = 125;
		Rocks[i].frameHeight = 96;
		Rocks[i].animationColumns = 21;

		if (rand() % 2) {
			Rocks[i].animationDirection = 1;
		}
		else {
			Rocks[i].animationDirection = -1;
		}
		if (image != NULL) {
			Rocks[i].image = image;
		}
	}
}

void DrawRock(Rock Rocks[], int size) { // Draws the rocks
	for (int i = 0; i < size; i++) {
		if (Rocks[i].live) {
			int fx = (Rocks[i].curFrame % Rocks[i].animationColumns) * Rocks[i].frameWidth;
			int fy = (Rocks[i].curFrame / Rocks[i].animationColumns) * Rocks[i].frameHeight;

			al_draw_bitmap_region(Rocks[i].image, fx, fy, Rocks[i].frameWidth,
				Rocks[i].frameHeight, Rocks[i].x - Rocks[i].frameWidth / 2, Rocks[i].y -
				Rocks[i].frameHeight / 2, 0);
		}
	}
}

void DrawWater(Rock Rocks[], int size) { // Draws pools of water
	for (int i = 0; i < size; i++) {
		if (Rocks[i].live) {
			int fx = (Rocks[i].curFrame % Rocks[i].animationColumns) * Rocks[i].frameWidth;
			int fy = (Rocks[i].curFrame / Rocks[i].animationColumns) * Rocks[i].frameHeight;

			al_draw_bitmap_region(Rocks[i].image, fx, fy, Rocks[i].frameWidth,
				Rocks[i].frameHeight, Rocks[i].x - Rocks[i].frameWidth / 2, Rocks[i].y -
				Rocks[i].frameHeight / 2, 0);
		}
	}
}

void DrawEnergy(Rock Rocks[], int size) { // Draws the energy
	for (int i = 0; i < size; i++) {
		if (Rocks[i].live) {
			int fx = (Rocks[i].curFrame % Rocks[i].animationColumns) * Rocks[i].frameWidth;
			int fy = (Rocks[i].curFrame / Rocks[i].animationColumns) * Rocks[i].frameHeight;

			al_draw_bitmap_region(Rocks[i].image, fx, fy, Rocks[i].frameWidth,
				Rocks[i].frameHeight, Rocks[i].x - Rocks[i].frameWidth / 2, Rocks[i].y -
				Rocks[i].frameHeight / 2, 0);

		}
	}
}

void StartRock(Rock Rocks[], int size) { // Function that generates the rocks
	for (int i = 0; i < size; i++) {
		if (!Rocks[i].live) {
			if (rand() % 500 == 0) {
				Rocks[i].live = true;
				Rocks[i].x = 350 + rand() % (WIDTH / 2);
				Rocks[i].y = 0;
				break;
			}
		}
	}
}

void StartWater(Rock Rocks[], int size) { // Function that generates the water pools
	for (int i = 0; i < size; i++) {
		if (!Rocks[i].live) {
			if (rand() % 500 == 0) {
				Rocks[i].live = true;
				Rocks[i].x = 300 + rand() % (WIDTH) / 2;
				Rocks[i].y = 0;
				break;
			}
		}
	}
}

void StartEnergy(Rock Rocks[], int size) { // Function that generates the energy
	for (int i = 0; i < size; i++) {
		if (!Rocks[i].live) {
			if (rand() % 500 == 0) {
				Rocks[i].live = true;
				Rocks[i].x = 350 + rand() % (WIDTH / 2);
				Rocks[i].y = 0;
				break;
			}
		}
	}
}

void UpdateRock(Rock Rocks[], int size) { // Updates the rocks
	for (int i = 0; i < size; i++) {
		if (Rocks[i].live) {
			if (++Rocks[i].frameCount >= Rocks[i].frameDelay) {
				Rocks[i].curFrame += Rocks[i].animationDirection;
				if (Rocks[i].curFrame <= Rocks[i].maxFrame) {
					Rocks[i].curFrame = 0;
				}
				else if (Rocks[i].curFrame <= 0) {
					Rocks[i].curFrame = Rocks[i].maxFrame - 1;
				}
				Rocks[i].frameCount = 0;
			}
			Rocks[i].y += car.speed2 / 2;
		}
	}
}

void UpdateWater(Rock Rocks[], int size) { // Updates the water pools
	for (int i = 0; i < size; i++) {
		if (Rocks[i].live) {
			if (++Rocks[i].frameCount >= Rocks[i].frameDelay) {
				Rocks[i].curFrame += Rocks[i].animationDirection;
				if (Rocks[i].curFrame <= Rocks[i].maxFrame) {
					Rocks[i].curFrame = 0;
				}
				else if (Rocks[i].curFrame <= 0) {
					Rocks[i].curFrame = Rocks[i].maxFrame - 1;
				}
				Rocks[i].frameCount = 0;
			}
			Rocks[i].y += car.speed2 / 2;
		}
	}
}

void UpdateEnergy(Rock Rocks[], int size) { // Updates the energy
	for (int i = 0; i < size; i++) {
		if (Rocks[i].live) {
			if (++Rocks[i].frameCount >= Rocks[i].frameDelay) {
				Rocks[i].curFrame += Rocks[i].animationDirection;
				if (Rocks[i].curFrame <= Rocks[i].maxFrame) {
					Rocks[i].curFrame = 0;
				}
				else if (Rocks[i].curFrame <= 0) {
					Rocks[i].curFrame = Rocks[i].maxFrame - 1;
				}
				Rocks[i].frameCount = 0;
			}
			Rocks[i].y += car.speed2 / 4;
		}
	}
}

void ColliRock1(Rock Rocks[], int cSize, Car& car, Explosion explosions[], int eSize) { // Rocks hit the car
	for (int i = 0; i < cSize; i++) {
		if (Rocks[i].live) {
			if (Rocks[i].x - Rocks[i].boundx < car.x + car.boundx &&
				Rocks[i].x + Rocks[i].boundx > car.x - car.boundx &&
				Rocks[i].y - Rocks[i].boundy < car.y + car.boundy &&
				Rocks[i].y + Rocks[i].boundy > car.y - car.boundy)
			{
				car.lives--;
				Rocks[i].live = false;
				StartExplosions(explosions, eSize, car.x, car.y);
			}
			else if (Rocks[i].y < 0) {
				Rocks[i].live = false;
				car.lives--;
			}
		}
	}
}

void ColliWater(Rock Rocks[], int cSize, Car& car, Explosion explosions[], int eSize,
	ALLEGRO_SAMPLE* Water_pool, ALLEGRO_SAMPLE_ID& Water_poolID) { // The car goes through a pool of water
	for (int i = 0; i < cSize; i++) {
		if (Rocks[i].live) {
			if (Rocks[i].x - Rocks[i].boundx < car.x + car.boundx &&
				Rocks[i].x + Rocks[i].boundx > car.x - car.boundx &&
				Rocks[i].y - Rocks[i].boundy < car.y + car.boundy &&
				Rocks[i].y + Rocks[i].boundy > car.y - car.boundy)
			{
				al_play_sample(Water_pool, 0.4, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &Water_poolID);
				car.water_detector = 1;
				Rocks[i].live = true;
			}
			else {
				car.water_detector = 0;
			}
		}
	}
}

void ColliRock2(Rock Rock[], int cSize, Car& car, Explosion explosions[], int eSize) { // Function when the car hits the rocks using nitro
	for (int i = 0; i < cSize; i++) { 
		if (Rocks[i].live) {
			if (Rocks[i].x - Rocks[i].boundx < car.x + car.boundx &&
				Rocks[i].x + Rocks[i].boundx > car.x - car.boundx &&
				Rocks[i].y - Rocks[i].boundy < car.y + car.boundy &&
				Rocks[i].y + Rocks[i].boundy > car.y - car.boundy)
			{
				car.score++;
				Rocks[i].live = false;
				StartExplosions(explosions, eSize, car.x, car.y);
			}
			else if (Rocks[i].y < 0)
			{
				Rocks[i].live = false;
				car.score++;
			}
		}
	}
}

void CollideEnergy(Rock Rocks[], int cSize, Car& car, Explosion explosions[], int eSize) { // Function when the car hits the energy lightning
	for (int i = 0; i < cSize; i++) {
		if (Rocks[i].live) {
			if (Rocks[i].x - Rocks[i].boundx < car.x + car.boundx &&
				Rocks[i].x + Rocks[i].boundx > car.x - car.boundx &&
				Rocks[i].y - Rocks[i].boundy < car.y + car.boundy &&
				Rocks[i].y + Rocks[i].boundy > car.y - car.boundy)
			{
				car.energy++;
				Rocks[i].live = false;
				//StartExplosions(explosions, eSize, car.x, car.y);
			}
			else if (Rocks[i].y < 0) {
				Rocks[i].live = false;
				car.energy++;
			}
		}
	}
}

void InitExplosions(Explosion explosions[], int size, ALLEGRO_BITMAP* image) { // Initialize explosions
	for (int i = 0; i < size; i++) {
		explosions[i].live = false;
		explosions[i].maxFrame = 31;
		explosions[i].curFrame = 0;
		explosions[i].frameCount = 0;
		explosions[i].frameDelay = 1;
		explosions[i].frameWidth = 150;
		explosions[i].frameHeight = 100;
		explosions[i].animationColumns = 8;
		explosions[i].animationDirection = 1;

		if (image != NULL) {
			explosions[i].image = image;
		}
	}
}

void DrawExplosions(Explosion explosions[], int size) { // Draws explosions
	for (int i = 0; i < size; i++) {
		if (explosions[i].live) {
			int fx = (explosions[i].curFrame % explosions[i].animationColumns) * explosions[i].frameWidth;
			int fy = (explosions[i].curFrame / explosions[i].animationColumns) * explosions[i].frameHeight;
			al_draw_bitmap_region(explosions[i].image, fx, fy, explosions[i].frameWidth,
				explosions[i].frameHeight, explosions[i].x - explosions[i].frameWidth / 2,
				explosions[i].y - explosions[i].frameHeight / 2, 0);
		}
	}
}

void StartExplosions(Explosion explosions[], int size, int x, int y) { // Function that generates explosions
	for (int i = 0; i < size; i++) {
		if (!explosions[i].live) {
			explosions[i].live = true;
			explosions[i].x = x;
			explosions[i].y = y;
			break;
		}
	}
}

void UpdateExplosions(Explosion explosions[], int size) { // Updates explosions
	for (int i = 0; i < size; i++) {
		if (explosions[i].live) {
			if (++explosions[i].frameCount >= explosions[i].frameDelay) {
				explosions[i].curFrame += explosions[i].animationDirection;
				if (explosions[i].curFrame >= explosions[i].maxFrame) {
					explosions[i].curFrame = 0;
					explosions[i].live = false;
				}
				explosions[i].frameCount = 0;
			}
		}
	}
}



// These functions allow the map to have movement
void InitBackground(Background& back, float x, float y, float velx, float vely, int width,
	int height, int dirX, int dirY, ALLEGRO_BITMAP* image) { // Initializes the background
	back.x = x;
	back.y = y;
	back.velX = velx;
	back.velY = vely;
	back.width = width;
	back.height = height;
	back.dirX = dirX;
	back.dirY = dirY;
	back.image = image;
}

void UpdateBackground(Background& back) { // Updates the background
	if (car.speed2 != 0) {
		car.Road++;
	}
	car.Road += car.speed2;
	back.y -= car.speed2 / 2 * back.dirY;
	if (back.y - back.height >= 0) {
		back.y = 0;
	}
}

void DrawBackground(Background& back) { // Draws the background
	al_draw_bitmap(back.image, back.x, back.y, 0);
	if (back.y - back.height < HEIGHT) {
		al_draw_bitmap(back.image, back.x, back.y - back.height, 0);
	}
}

void energy() { // Car power
	if ((car.Road / 100) % 100 == 0 && car.Road >= 99) {
		if (car.energy >= 1) {
			car.energy -= 1;
		}
		else if (car.energy == 0) {
			if (car.speed2 >= 40) {
				car.speed2 -= 30;
			}
			else if (car.speed2 < 40 && car.speed2 >= 6) {
				car.speed2 -= 5;
			}
			else if (car.speed2 < 6 && car.speed2 > 0) {
				car.speed2 -= 1;
			}
		}
	}
}

void nitro() { // Car speed when nitro is activated
	if (car.nitro > 0) {
		car.speed2 = 100;
	}
}

void Updatenitro() { // Updates the nitro

	if (car.speed2 >= 90) {
		if ((car.Road / 100) % 200 == 0 && (car.Road / 100) > 10) {
			if (car.nitro >= 0) {
				car.nitro -= 1;
			}
		}
		if ((car.Road / 100) % 100 == 0 && car.Road >= 99) {
			if (car.energy >= 1) {
				car.energy += 1;
			}
		}
	}
}