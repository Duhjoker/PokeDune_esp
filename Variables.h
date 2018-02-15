#ifndef _Variables_H_
#define _Variables_H_
#include <EEPROM.h>
#include "Adafruit_seesaw.h"
#include <elapsedMillis.h>

extern Grafx_esp tft;
Adafruit_seesaw ss1;
Adafruit_seesaw ss2;
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
#define STATE_Title          0
#define STATE_Game_select    1
#define STATE_Player         2
#define STATE_Menu           3
#define STATE_Item_list      4
#define STATE_Battle         5
#define STATE_Item_list_bat  6
#define STATE_Save_game      7


byte state = STATE_Title;
byte nextState = STATE_Player;
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
struct CursorA
{
  int cursorA_x;
  int cursorA_y;
  int cursor_direction;
};

CursorA cursora = { 0, 27, 1};
///////////////////////////////////////////////////////////////////////////////////////////
struct CursorB
{
  int cursorB_x;
  int cursorB_y;
  int cursorB_direction;
};

CursorB cursorb = { 9, 138, 1};
///////////////////////////////////////////////////////////////////////////////////////////
struct CursorC
{
  int cursorC_x;
  int cursorC_y;
  int cursor_direction;
};

CursorC cursorc = { 68, 94, 1};
///////////////////////////////////////////////////////////////////////////////////////////
struct CursorD
{
  int cursorD_x;
  int cursorD_y;
  int cursor_direction;
};

CursorD cursord = { 68, 94, 1};
///////////////////////////////////////////////////////////////////////////////////////////
struct CursorE
{
  int cursorE_x;
  int cursorE_y;
  int cursor_direction;
};

CursorE cursore = { 142, 14, 1};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
struct Player
{
  int player_x;
  int player_y;
  int w;
  int h;
  int attack;
  int defense;
  int health;
  int room;
  int cameraX;
  int cameraY;
  int player_direction;
  int player_directionRepeat;
};

  Player player = { 160, 170, 16, 16, 20, 15, 100, 3, -128, -254, 2, 0};
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// Camera speed in pixels per update
int cameraXSpeed = 3;
int cameraYSpeed = 3;
///////////////////////////////////////////////////////////////////////////////////////////
// Camera offset boundaries
int cameraXMin = -336;   /////// -320 0f total tilemap pixels x right >>>>
int cameraXMax = 0;
int cameraYMin = -448;   /////// -256 0f total tilemap pixels y down VVVV
int cameraYMax = 0;
///////////////////////////////////////////////////////////////////////////////////////////
// Player offset boundaries allows camera to scroll when player moves to boundary
int playerXMin = 80;    //////// do not change if resolution of tft is 320x240
int playerXMax = 240;
int playerYMin = 80;
int playerYMax = 168;
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#define IRQ_PIN1   13
#define IRQ_PIN2   27
////////////////////////////////////////////////////////////////////////////
int last_x = 0, last_y = 0;
int last_x2 = 0, last_y2 = 0;
////////////////////////////////////////////////////////////////////////////
#define BUTTON_RIGHT 6  /////////////what are these integers
#define BUTTON_DOWN  7  /////////////"                      "
#define BUTTON_LEFT  9  /////////////"                      "
#define BUTTON_UP    10 /////////////"                      "
#define BUTTON_SEL   14 /////////////"                      "
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
#define BUTTON_A      6  /////////////what are these integers
#define BUTTON_B      7  /////////////"                      "
#define BUTTON_Y      9  /////////////"                      "
#define BUTTON_X      10 /////////////"                      "
#define BUTTON_START  14 /////////////"                      "
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
uint32_t button_mask = (1 << BUTTON_RIGHT) | (1 << BUTTON_DOWN) |
                       (1 << BUTTON_LEFT) | (1 << BUTTON_UP) | (1 << BUTTON_SEL);
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
uint32_t button_mask2 = (1 << BUTTON_A) | (1 << BUTTON_B) |
                        (1 << BUTTON_Y) | (1 << BUTTON_X) | (1 << BUTTON_START);
///////////////////////////////////////////////////////////////////////////////
///////////////////////////Pixel Color Includes////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uint16_t palette[16];  // Should probably be 256, but I don't use many colors...
uint16_t pixel_data[2500];

//Extra integers for color palette
int a = 0xa; int b = 0xb; int c = 0xc;
int d = 0xd; int e = 0xe; int f = 0xf;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int addr = 0;
#define EEPROM_SIZE 64  

void save()
{
  EEPROM.put(0, player);
  //EEPROM.put(36, slots);
  EEPROM.commit();
  Serial.println(player.player_x);
  Serial.println(player.player_y);
  Serial.println(player.w);
  Serial.println(player.h);
  Serial.println(player.cameraX);
  Serial.println(player.cameraY);
  Serial.println(player.player_direction);
  Serial.println(player.player_directionRepeat);
  Serial.print("saved");
}

void load()
{
    EEPROM.get(0, player);
    //EEPROM.get(36, slots);
  Serial.println(player.player_x);
  Serial.println(player.player_y);
  Serial.println(player.w);
  Serial.println(player.h);
  Serial.println(player.cameraX);
  Serial.println(player.cameraY);
  Serial.println(player.player_direction);
  Serial.println(player.player_directionRepeat);
}
#endif
