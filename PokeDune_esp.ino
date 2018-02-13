/*This is the Main function file for the GameR-Iot Multiple MCU Arduino driven
   game system and DIY console. This is a demo game RPG set in the Dune Universe
   created by Frank Herbert.
*/
#include <Grafx_esp.h>
#include <SPI.h>
#include <EEPROM.h>
#include "Variables.h"
#include "Player.h"
#include "Battle.h"
#include "Player.h"
#include "Menu.h"
#include "Inventory.h"
//////////////////////////////////////////////////////////////////////////////
#include "Adafruit_seesaw.h"

//#include <ili9341_esp_font_Arial.h>
//#include <ili9341_esp_font_ArialBold.h>
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#define TFT_SCK 5
#define TFT_MISO 19
#define TFT_MOSI 18
#define TFT_DC 33
#define TFT_CS 15
#define TFT_RST 12
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
uint8_t use_fb = 1;
uint8_t use_clip_rect = 0;
uint8_t use_set_origin = 0;
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
byte buttons = 0;
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Grafx_esp tft = Grafx_esp(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////Set-up//////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void setup() {
  while (!Serial && (millis() < 4000)) ;
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  //tft.setFrameRate(60);
  tft.persistence = false;
  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////
  if (!ss1.begin(0x49)) {
    Serial.println("ERROR!");
    while (1);
  }
  if (!ss2.begin(0x4a)) {
    Serial.println("ERROR!");
    while (1);
  }
  else {
    Serial.println("seesaw started");
    Serial.print("version: ");
    Serial.println(ss1.getVersion(), HEX);
  }
  /////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////
  ss1.pinModeBulk(button_mask, INPUT_PULLUP);
  ss1.setGPIOInterrupts(button_mask, 1);
  pinMode(IRQ_PIN1, INPUT);
  /////////////////////////////////////////////////////////
  ss2.pinModeBulk(button_mask2, INPUT_PULLUP);
  ss2.setGPIOInterrupts(button_mask2, 1);
  pinMode(IRQ_PIN2, INPUT);
  /////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  Serial.println(" bytes read from Flash . Values are:");
  for (int i = 0; i < EEPROM_SIZE; i++)
  {
    Serial.print(byte(EEPROM.read(i))); Serial.print(" ");
  }
  Serial.println();
  Serial.println("writing random n. in memory");

  tft.useFrameBuffer(use_fb);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Loop////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void loop() {

  switch (state) {

    case STATE_Title:

      titlepage();
      if (!digitalRead(IRQ_PIN1)) {
        uint32_t buttons = ss1.digitalReadBulk(button_mask);
        if (! (buttons & (1 << BUTTON_SEL))) {
          Serial.println("Button SEL pressed");
          state = STATE_Game_select;

        }
      }
      break;

    case STATE_Game_select:
      loadgame();
      break;

    case STATE_Player:
      tft.fillScreen(BLACK);
      drawplayer();
      //      triggerBattle(player.player_x, player.player_y);
      break;

    case STATE_Menu:
      tft.fillScreen(BLACK);
      Menu();
      break;

    case STATE_Item_list:
      printItemlist();
      break;

    case STATE_Battle:
      drawBattle();
      break;

    case STATE_Item_list_bat:
      ItemlistBat();
      break;

    case STATE_Save_game:
      savegame();
      break;
  }
  tft.updateScreen();

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void titlepage() {
  palette[0] = 0; palette[1] = BLACK;  palette[2] = BLUE; palette[3] = BROWN; palette[4] = DARKGREEN; palette[5] = GREY;
  palette[6] = PINK; palette[7] = RED; palette[8] = BEIGE; palette[9] = GREEN; palette[a] = DARKGREY; palette[b] = LIGHTGREY;
  palette[c] = YELLOW; palette[d] = PURPLE; palette[e] = WHITE; palette[f] = ORANGE;
  tft.writeRectNBPP(0, 0, 320, 240, 4, title_1, palette);

}



