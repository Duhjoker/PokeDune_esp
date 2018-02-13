#ifndef _Menu_H_
#define _Menu_H_

#include "Variables.h"
#include "Player.h"
#include "Inventory.h"
#include <EEPROM.h>
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void Menu() {
  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////Palette////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  palette[0] = 0;            palette[8] = BEIGE;
  palette[1] = BLACK;        palette[9] = GREEN;
  palette[2] = BLUE;         palette[a] = DARKGREY;
  palette[3] = BROWN;        palette[b] = LIGHTGREY;
  palette[4] = DARKGREEN;    palette[c] = YELLOW;
  palette[5] = GREY;         palette[d] = PURPLE;
  palette[6] = PINK;         palette[e] = WHITE;
  palette[7] = RED;          palette[f] = ORANGE;
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  Rect rectA {0, 0, 136, 20};
  Rect rectB {0, 20, 136, 40};
  Rect rectC {0, 60, 136, 40};
  Rect rectD {0, 100, 136, 40};
  Rect rectE {0, 140, 136, 40};
  Rect rectF {0, 180, 136, 40};
  Rect rectG {0, 220, 136, 20};
  Rect rectH {cursora.cursorA_x, cursora.cursorA_y, 32, 32};
  /////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  tft.fillRoundRect(0, 0, 136, 240, 4, WHITE);
  tft.fillRoundRect(4, 4, 128, 232, 4, BLUE);
  tft.setCursor(24, 24);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Item");
  tft.setCursor(24, 64);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Equip");
  tft.setCursor(24, 104);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Weird");
  tft.setCursor(24, 144);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Stats");
  tft.setCursor(24, 184);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Save");
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int y = ss1.analogRead(2);
  int x = ss1.analogRead(3);

  /// if(tft.Bpressed(BTN_UP)){
  if (x > 600 && last_x < 600) {
    tft.writeRectNBPP(cursora.cursorA_x, cursora.cursorA_y, 32, 32, 4, cursor3, palette);
    cursora.cursor_direction = 1;
    cursora.cursorA_y -= 40;
  }
  if (cursora.cursorA_y <= 27) {
    cursora.cursorA_y = 27;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////Down///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  /// if(tft.Bpressed(BTN_DOWN)){
  if (x < 400 && last_x > 400) {
    tft.writeRectNBPP(cursora.cursorA_x, cursora.cursorA_y, 32, 32, 4, cursor3, palette);
    cursora.cursor_direction = 1;
    cursora.cursorA_y += 40;
  }
  if (cursora.cursorA_y >= 188) {
    cursora.cursorA_y = 188;
  }

  last_x = x;
  /////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////
  if (cursora.cursor_direction == 1) {
    tft.writeRectNBPP(cursora.cursorA_x, cursora.cursorA_y, 32, 32, 4, cursor3, palette);
  }

  //////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////exit menu////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  if (!digitalRead(IRQ_PIN2)) {
    uint32_t buttons = ss2.digitalReadBulk(button_mask2);
    if (! (buttons & (1 << BUTTON_A))) {
      state = STATE_Player;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectB.x, rectB.y, rectB.width, rectB.height, rectH.x, rectH.y, rectH.width, rectH.height)))
    {
      state = STATE_Item_list;
    }
    else if ((! (buttons & (1 << BUTTON_X))  && tft.collideRectRect( rectC.x, rectC.y, rectC.width, rectC.height, rectH.x, rectH.y, rectH.width, rectH.height)))
    {
      tft.fillScreen(GREEN);
    }
    else if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectD.x, rectD.y, rectD.width, rectD.height, rectH.x, rectH.y, rectH.width, rectH.height)))
    {
      tft.fillScreen(RED);
    }
    else if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectE.x, rectE.y, rectE.width, rectE.height, rectH.x, rectH.y, rectH.width, rectH.height)))
    {
      tft.fillScreen(YELLOW);
    }
    else if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectF.x, rectF.y, rectF.width, rectF.height, rectH.x, rectH.y, rectH.width, rectH.height)))
    {
      state = STATE_Save_game;
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loadgame() {
  /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////
  palette[0] = 0;            palette[8] = BEIGE;
  palette[1] = BLACK;        palette[9] = GREEN;
  palette[2] = BLUE;         palette[a] = DARKGREY;
  palette[3] = BROWN;        palette[b] = LIGHTGREY;
  palette[4] = DARKGREEN;    palette[c] = YELLOW;
  palette[5] = GREY;         palette[d] = PURPLE;
  palette[6] = PINK;         palette[e] = WHITE;
  palette[7] = RED;          palette[f] = ORANGE;
  //////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////

  Rect rectA {80, 94, 80, 20};
  Rect rectB {80, 128, 80, 20};
  Rect rectC {cursorc.cursorC_x, cursorc.cursorC_y, 32, 32};

  tft.fillScreen(BLACK);
  tft.fillRoundRect(80, 80, 162, 82, 4, WHITE);
  tft.fillRoundRect(85, 84, 153, 74, 4, BLUE);
  tft.setCursor(91, 94);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("New Game");
  tft.setCursor(91, 128);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Continue");
  ////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////
  int y = ss1.analogRead(2);
  int x = ss1.analogRead(3);

  /// if(tft.Bpressed(BTN_UP)){
  if (x > 600 && last_x < 600) {
    tft.writeRectNBPP(cursorc.cursorC_x, cursorc.cursorC_y, 32, 32, 4, cursor3, palette);
    cursorc.cursor_direction = 1;
    cursorc.cursorC_y -= 40;
  }
  if (cursorc.cursorC_y <= 94) {
    cursorc.cursorC_y = 94;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////Down///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  /// if(tft.Bpressed(BTN_DOWN)){
  if (x < 400 && last_x > 400) {
    tft.writeRectNBPP(cursorc.cursorC_x, cursorc.cursorC_y, 32, 32, 4, cursor3, palette);
    cursorc.cursor_direction = 1;
    cursorc.cursorC_y += 40;
  }
  if (cursorc.cursorC_y >= 130) {
    cursorc.cursorC_y = 130;
  }

  last_x = x;
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  if (cursorc.cursor_direction == 1) {
    tft.writeRectNBPP(cursorc.cursorC_x, cursorc.cursorC_y, 32, 32, 4, cursor3, palette);
  }
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  if (!digitalRead(IRQ_PIN2)) {
    uint32_t buttons = ss2.digitalReadBulk(button_mask2);
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectA.x, rectA.y, rectA.width, rectA.height, rectC.x, rectC.y, rectC.width, rectC.height)))
    {
      state = STATE_Player;
    }
    else if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectB.x, rectB.y, rectB.width, rectB.height, rectC.x, rectC.y, rectC.width, rectC.height)))
    {
 //      checkLoad(); {
        load();
        state = STATE_Player;
//      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void savegame() {
  /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////
  palette[0] = 0;            palette[8] = BEIGE;
  palette[1] = BLACK;        palette[9] = GREEN;
  palette[2] = BLUE;         palette[a] = DARKGREY;
  palette[3] = BROWN;        palette[b] = LIGHTGREY;
  palette[4] = DARKGREEN;    palette[c] = YELLOW;
  palette[5] = GREY;         palette[d] = PURPLE;
  palette[6] = PINK;         palette[e] = WHITE;
  palette[7] = RED;          palette[f] = ORANGE;
  //////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////

  Rect rectA {80, 94, 80, 20};
  Rect rectB {80, 128, 80, 20};
  Rect rectC {cursord.cursorD_x, cursord.cursorD_y, 32, 32};

  tft.fillRoundRect(80, 80, 162, 82, 4, WHITE);
  tft.fillRoundRect(85, 84, 153, 74, 4, BLUE);
  tft.setCursor(91, 94);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Save");
  tft.setCursor(91, 128);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("Load");
  ////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////
  int y = ss1.analogRead(2);
  int x = ss1.analogRead(3);

  /// if(tft.Bpressed(BTN_UP)){
  if (x > 600 && last_x < 600) {
    tft.writeRectNBPP(cursorc.cursorC_x, cursorc.cursorC_y, 32, 32, 4, cursor3, palette);
    cursord.cursor_direction = 1;
    cursord.cursorD_y -= 40;
  }
  if (cursord.cursorD_y <= 94) {
    cursord.cursorD_y = 94;
  }

  //////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////Down///////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  /// if(tft.Bpressed(BTN_DOWN)){
  if (x < 400 && last_x > 400) {
    tft.writeRectNBPP(cursorc.cursorC_x, cursorc.cursorC_y, 32, 32, 4, cursor3, palette);
    cursord.cursor_direction = 1;
    cursord.cursorD_y += 40;
  }
  if (cursord.cursorD_y >= 130) {
    cursord.cursorD_y = 130;
  }

  last_x = x;
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  if (cursord.cursor_direction == 1) {
    tft.writeRectNBPP(cursord.cursorD_x, cursord.cursorD_y, 32, 32, 4, cursor3, palette);
  }
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  if (!digitalRead(IRQ_PIN2)) {
    uint32_t buttons = ss2.digitalReadBulk(button_mask2);
    if (! (buttons & (1 << BUTTON_A))) {
      state = STATE_Menu;
    }
    //////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////exit menu////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectA.x, rectA.y, rectA.width, rectA.height, rectC.x, rectC.y, rectC.width, rectC.height)))
    {
      save();
      state = STATE_Player;
    }
    else if ((! (buttons & (1 << BUTTON_X)) && tft.collideRectRect( rectB.x, rectB.y, rectB.width, rectB.height, rectC.x, rectC.y, rectC.width, rectC.height)))
    {
      load();
        state = STATE_Player;
    }
  }
}


#endif

