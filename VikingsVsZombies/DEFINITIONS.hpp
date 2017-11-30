#pragma once

//View Attributes
#define MAX_LENGTH 2048*2

//Texture File Names
#define VIKING_FILE "Viking1Run.png"
#define BOY_ZOMBIE "Zombie.png"
#define DEAD_BOY_ZOMBIE_FILE "deadZombie.png"
#define GROUND_FLOOR_FILE "BackgroundSprites-0.png"
#define FRONT_TREES_FILE "BackgroundSprites-1.png"
#define BACK_TREES_FILE "BackgroundSprites-2.png"
#define GRASS_FILE "BackgroundSprites-3.png"
#define LOWER_BACK_GRASS_FILE "BackgroundSprites-4.png"
#define BACK_GRASS_FILE "BackgroundSprites-5.png"
#define BACK_CLOUDS_FILE "BackgroundSprites-6.png"
#define CLOUDS_FILE "BackgroundSprites-7.png"
#define HIGH_CLOUDS_FILE1 "BackgroundSprites-8.png"
#define BACKGROUND_FILE "BackgroundSprites-10.png"
#define CACTUS_FILE "Cactus.png"
#define ARROW_FILE "SignArrow.png"

//Character Positions & Attributes
#define PLAYER_POSX 550.0f
#define PLAYER_POSY 1225.0f

#define PLAYER_HALF_WIDTH 250.0f

#define CHARACTER_SPEED 500.0f
#define SWING_SPEED 0.075f

#define RUN_ROW 0
#define IDLE_ROW 1
#define ATTACK_ROW 2

//Enemy Positions & Attributes

#define ZB_ROWS 3
#define ZB_COLUMNS 15
#define LAST_ATTACK_COLUMN 8
#define LAST_IDLE_COLUMN 15
#define LAST_RUN_COLUMN 10
#define LAST_DEAD_COLUMN 12

#define ENEMY_POSX 1800.0f
#define ENEMY_POSY 1275.0f

#define ZATTACK_WIDTH 3480.0f
#define ZATTACK_HEIGHT 519.0f
#define ZDEAD_WIDTH 7548.0F
#define ZDEAD_HEIGHT 526.0f

#define ZOMBIE_IDLE_SPEED 0.15f
#define ZOMBIE_ATTACK_SPEED 0.2f
#define ZOMBIE_DEATH_SPEED 0.3f

#define ZOMBIE_ATTACK_ROW 0
#define ZOMBIE_IDLE_ROW 1
#define ZOMBIE_RUN_ROW 2
