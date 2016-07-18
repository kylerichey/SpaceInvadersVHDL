/*
 * globals.h
 *
 *  Created on: Oct 1, 2014
 *      Author: superman
 */

#include "bitmask.h"

#ifndef GLOBALS_H_
#define GLOBALS_H_

#define ALIEN_Y_GAP 8
#define XPAR_AUDIO_CODEC_BASEADDR 0xFFFF8000


///////////////////////////////////////// GLOBAL VARIABLES ////////////////////////////////////////////

extern direction tank_direction;
extern direction alien_direction;

extern short alien_life[55];
extern short alien_columns[11];

extern position tank_bullet;
extern short tank_bullet_exists;
extern int tank_bullet_sound_already_played;

extern alien_bullet alien_bullet_1;
extern alien_bullet alien_bullet_2;
extern alien_bullet alien_bullet_3;
extern alien_bullet alien_bullet_4;

extern position tank;
extern block alien_block;

extern int alien_delay_speed;
extern int remaning_aliens;
extern int score;
extern int lives;
extern int tank_hit;
extern int tank_dead_count;
extern int * tankDeath_symbol;
extern int gameOver;
extern int ufoDie;
extern int right_alien_block_edge;
extern int left_alien_block_edge;

extern int* alien_bullet_states[4];
extern int* alien_missle_states[4];
extern int* bunker_baseBlock[5];
extern int* bunker_baseBlockLeft[5];
extern int* bunker_baseBlockRight[5];
extern int* bunker_baseBlockLeftUnder[5];
extern int* bunker_baseBlockRightUnder[5];

extern int tank_shoot_soundData[];
extern int tank_shoot_numberOfSamples;
extern int tank_shoot_sampleRate;


extern int silent_soundData[];
extern int silent_numberOfSamples;
extern int silent_sampleRate;

extern int explosion_numberOfSamples;
extern int explosion_sampleRate;
extern int tank_explosion_soundData[];

extern int ufo_highpitch_numberOfSamples;
extern int ufo_highpitch_sampleRate;
extern int ufo_highpitch_soundData[];


extern int invader1_soundData[];
extern int invader1_sampleRate;
extern int invader1_numberOfSamples;

extern int invader2_soundData[];
extern int invader2_sampleRate;
extern int invader2_numberOfSamples;


extern int invader3_soundData[];
extern int invader3_sampleRate;
extern int invader3_numberOfSamples;


extern int invader4_soundData[];
extern int invader4_sampleRate;
extern int invader4_numberOfSamples;

extern int invaderkilled_soundData[];
extern int invaderkilled_sampleRate;
extern int invaderkilled_numberOfSamples;

extern int gameover_soundData[];
extern int gameover_numberOfSamples;
extern int gameover_sampleRate;


///////////////////////////////////////// FUNCTIONS ////////////////////////////////////////////


void drawHUD();
void updateScore(int);
void updateLives();
void draw( int, int,  int *, int, int, int );

void clearAliens();
void drawAliens();
void draw_aliens(int);
void move_aliens();
void killAlien(int);

void play_game_over();
void play_game_win();
void check_lowest_row();

void init(unsigned int *);

void move_tank();
void draw_tank(int);

void redraw();

void shootTankBullet();
void shootAlienBullet();
void moveBullets();
void drawBullets(int);

char getKeyChar();
void processKeyPress(char input);

void erode_bunkers(int);
void draw_bunker(int);
void drawBlock(int , int , int , int , int );
void checkCollisions();

void checkBunkerAlienBulletCollision();
void checkBunkerTankBulletCollision();
void checkBunkerAlienBlockCollision();
void checkAlienBlockCollision();
void checkTankCollision();
void checkUFOCollision();

void moveUFO();
void spawnUFO();

void playSound(int);

#endif
