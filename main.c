#include <QuickGame.h>
#include <gu2gl.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>
//#include "collision_lookup.h"

QGTimer timer;

// Player velocities

int vel_x, vel_y;
bool started = false;
bool canJump = false;
int collision_direction;

// In-game varivables

QGSprite_t mainT, bold;
QGSprite_t block, enemy, player, home, university, hint[2];

typedef struct
{
    QGSprite_t sprite;
    bool isBold;
} Button;

Button button[4];

typedef struct
{
    int x, y;
} Coordinate;

Coordinate* lvl_layout;

// State Machine
enum mode
{
    MENU,
    LANGUAGE,
    LVL_1,
    LVL_2
};

// Language Options
enum lang
{
    ENGLISH,
    RUSSIAN
};

// Game stats
int state = MENU;
int language = ENGLISH;


// Load Methods

void load_menu()
{
    char L[4]; 

    if(language == RUSSIAN)
    {
        sprintf(L, "rus");
    }
    else
    {
        sprintf(L, "eng");
    }

    char filename[256];
    sprintf(filename, "./assets/text/%s/main.png", L);
    QGTexInfo mainTexInfo = {.filename = filename, .flip = true, .vram = 0};
    mainT = QuickGame_Sprite_Create_Contained(240, 136, 544, 272, mainTexInfo);

    sprintf(filename, "./assets/text/%s/play.png", L);
    QGTexInfo playTexInfo = {.filename = filename, .flip = true, .vram = 0};
    button[0].sprite = QuickGame_Sprite_Create_Contained(160, 110, 128, 32, playTexInfo);

    sprintf(filename, "./assets/text/%s/lang.png", L);
    QGTexInfo langTexInfo = {.filename = filename, .flip = true, .vram = 0};
    button[1].sprite = QuickGame_Sprite_Create_Contained(160, 60, 128, 32, langTexInfo);

    QGTexInfo boldTexInfo = {.filename = "./assets/text/button_bold.png", .flip = true, .vram = 0};
    bold = QuickGame_Sprite_Create_Contained(160, 110, 128, 32, boldTexInfo);

    button[0].isBold = true;
    button[1].isBold = false;
}

void load_lang()
{
    char L[4]; 

    if(language == RUSSIAN)
    {
        sprintf(L, "rus");
        button[2].isBold = false;
        button[3].isBold = true;
    }
    else
    {
        sprintf(L, "eng");
        button[2].isBold = true;
        button[3].isBold = false;
    }

    char filename[256];
    sprintf(filename, "./assets/text/%s/main.png", L);
    QGTexInfo mainTexInfo = {.filename = filename, .flip = true, .vram = 0};
    mainT = QuickGame_Sprite_Create_Contained(240, 136, 544, 272, mainTexInfo);

    QGTexInfo engTexInfo = {.filename = "./assets/text/eng/eng.png", .flip = true, .vram = 0};
    button[2].sprite = QuickGame_Sprite_Create_Contained(160, 110, 128, 32, engTexInfo);

    QGTexInfo rusTexInfo = {.filename = "./assets/text/rus/rus.png", .flip = true, .vram = 0};
    button[3].sprite = QuickGame_Sprite_Create_Contained(160, 60, 128, 32, rusTexInfo);

    QGTexInfo boldTexInfo = {.filename = "./assets/text/button_bold.png", .flip = true, .vram = 0};
    bold = QuickGame_Sprite_Create_Contained(160, 110, 128, 32, boldTexInfo);
}

void change_lang()
{
    if(button[2].isBold)
    {
        language = ENGLISH;
    }
    else if(button[3].isBold)
    {
        language = RUSSIAN;
    }
}

void load_lvl1()
{
    started = false;
    vel_x = 0.0f;
    vel_y = 0.0f;
    canJump = true;

    char L[4]; 

    if(language == RUSSIAN)
    {
        sprintf(L, "rus");
    }
    else
    {
        sprintf(L, "eng");
    }

    char filename[256];
    sprintf(filename, "./assets/text/%s/lvl1_hint.png", L);
    QGTexInfo hint1TexInfo = {.filename = filename, .flip = true, .vram = 0};
    hint[0] = QuickGame_Sprite_Create_Contained(112, 272, 256, 256, hint1TexInfo);

    QGTexInfo blockTexInfo = {.filename = "./assets/block.png", .flip = true, .vram = 0};
    block = QuickGame_Sprite_Create_Contained(0, 0, 16, 16, blockTexInfo);

    QGTexInfo enemyTexInfo = {.filename = "./assets/enemy.png", .flip = true, .vram = 0};
    enemy = QuickGame_Sprite_Create_Contained(0, 0, 16, 32, enemyTexInfo);

    QGTexInfo playerTexInfo = {.filename = "./assets/player.png", .flip = true, .vram = 0};
    player = QuickGame_Sprite_Create_Contained(0, 0, 16, 32, playerTexInfo);

    QGTexInfo homeTexInfo = {.filename = "./assets/home.png", .flip = true, .vram = 0};
    home = QuickGame_Sprite_Create_Contained(0, 0, 32, 32, homeTexInfo);    

    QGTexInfo uniTexInfo = {.filename = "./assets/university.png", .flip = true, .vram = 0};
    university = QuickGame_Sprite_Create_Contained(0, 0, 32, 64, uniTexInfo);   


    // Making the level layout
    lvl_layout = (Coordinate *)malloc(30 * sizeof(Coordinate));

    home->transform.position.x = 80;
    home->transform.position.y = 32;

    university->transform.position.x = 48;
    university->transform.position.y = 13 * 16;

    player->transform.position.x = 40;
    player->transform.position.y = 32;

    Coordinate temp;
    int numb = 0;
    for(int i = 0; i < 11; i++)
    {
        temp.x = i + 1;
        temp.y = 10;
        lvl_layout[numb++] = temp;
    }
    for(int i = 0; i < 9; i++)
    {
        temp.x = i + 16;
        temp.y = 10;
        lvl_layout[numb++] = temp;
    }
    for(int i = 0; i < 3; i++)
    {
        temp.x = i + 14;
        temp.y = 4;
        lvl_layout[numb++] = temp;
    }
    for(int i = 0; i < 3; i++)
    {
        temp.x = i + 19;
        temp.y = 5;
        lvl_layout[numb++] = temp;
    }
    for(int i = 0; i < 4; i++)
    {
        temp.x = i + 25;
        temp.y = 6;
        lvl_layout[numb++] = temp;
    }

    for(int i = 0; i < 30; i++)
    {
        lvl_layout[i].x *= 16;
        lvl_layout[i].x += 8;
        lvl_layout[i].y *= 16;
        lvl_layout[i].y += 8;
    }
}

void load_lvl2()
{
    started = false;

    QGTexInfo hint2TexInfo;

    if(language == RUSSIAN)
    {
        hint2TexInfo.filename = "./assets/text/rus/lvl2_hint.png";
    }
    else
    {
        hint2TexInfo.filename = "./assets/text/eng/lvl2_hint.png";
    }

    hint2TexInfo.flip = true;
    hint2TexInfo.vram = 0;

    hint[1] = QuickGame_Sprite_Create_Contained(112, 272, 256, 256, hint2TexInfo);
}

// Unload methods

void unload_menu()
{
    QuickGame_Sprite_Destroy(&bold);
    QuickGame_Sprite_Destroy(&button[0].sprite);
    QuickGame_Sprite_Destroy(&button[1].sprite);
    QuickGame_Sprite_Destroy(&mainT);
}

void unload_lang()
{
    QuickGame_Sprite_Destroy(&bold);
    QuickGame_Sprite_Destroy(&button[2].sprite);
    QuickGame_Sprite_Destroy(&button[3].sprite);
    QuickGame_Sprite_Destroy(&mainT);
}

void unload_lvl1() // only for lvl_1 -> lvl_2
{
    QuickGame_Sprite_Destroy(&hint[0]);
}

void unload_lvl2()
{
    QuickGame_Sprite_Destroy(&hint[1]);
    QuickGame_Sprite_Destroy(&block);
    QuickGame_Sprite_Destroy(&player);
    QuickGame_Sprite_Destroy(&enemy);
    QuickGame_Sprite_Destroy(&home);
    QuickGame_Sprite_Destroy(&university);
}

// Draw methods

void draw_lvl_border()
{
    for(int i = 0; i < 30; i++)
    {
        block->transform.position.x = i * 16 + 8;
        block->transform.position.y = 8;

        QuickGame_Sprite_Draw(block);

        block->transform.position.y = 264;

        QuickGame_Sprite_Draw(block);   
    }

    for(int i = 1; i < 16; i++)
    {
        block->transform.position.y = i * 16 + 8;
        block->transform.position.x = 8;

        QuickGame_Sprite_Draw(block);

        block->transform.position.x = 472;

        QuickGame_Sprite_Draw(block);   
    }
}

void draw_lvl1()
{
    draw_lvl_border();

    collision_direction = 0;

    for(int i = 0; i < 30; i++)
    {
        block->transform.position.x = lvl_layout[i].x;
        block->transform.position.y = lvl_layout[i].y;

        QuickGame_Sprite_Draw(block);

        collision_direction |= (int)QuickGame_Sprite_Intersect_Direction(block, player);
    }

    QuickGame_Sprite_Draw(home);
    QuickGame_Sprite_Draw(university);

    QuickGame_Sprite_Draw(player);

    if(!started)
    {
        QuickGame_Sprite_Draw(hint[0]);
    }
}

void draw()
{
    QuickGame_Graphics_Start_Frame();
    QuickGame_Graphics_Clear();

    switch(state)
    {
        case MENU:

            QuickGame_Sprite_Draw(mainT);
            QuickGame_Sprite_Draw(button[0].sprite);
            QuickGame_Sprite_Draw(button[1].sprite);

            if(button[0].isBold)
            {
                bold->transform.position.y = 110;
            }
            else
            {
                bold->transform.position.y = 60;
            }

            QuickGame_Sprite_Draw(bold);
        
        break;
        case LANGUAGE:
            QuickGame_Sprite_Draw(mainT);
            QuickGame_Sprite_Draw(button[2].sprite);
            QuickGame_Sprite_Draw(button[3].sprite);

            if(button[2].isBold)
            {
                bold->transform.position.y = 110;
            }
            else
            {
                bold->transform.position.y = 60;
            }

            QuickGame_Sprite_Draw(bold);

        break;
        case LVL_1:
            draw_lvl1();
        case LVL_2:
        break;
    };

    QuickGame_Graphics_End_Frame(true);
}

void switch_state(int oldS, int newS)
{
    switch(oldS)
    {
        case MENU:
            unload_menu();
        break;
        case LANGUAGE:
            unload_lang();
        break;
        case LVL_1:
            unload_lvl1();
        break;
        case LVL_2:
            unload_lvl2();
        break;
    }

    switch(newS)
    {
        case MENU:
            load_menu();
        break;
        case LANGUAGE:
            load_lang();
        break;
        case LVL_1:
            load_lvl1();
        break;
        case LVL_2:
            load_lvl2();
        break;
    }
}

void update_player(double dt)
{
    if(QuickGame_Button_Pressed(PSP_CTRL_CROSS))
    {
        if(canJump)
        {
            canJump = false;
            started = true;
            vel_y = 287;
        }
    }
    if(QuickGame_Button_Held(PSP_CTRL_LEFT))
    {
        started = true;
        vel_x = -150;
    }
    if(QuickGame_Button_Held(PSP_CTRL_RIGHT))
    {
        started = true;
        vel_x = 150;
    }

    //u8 collision_direction = QuickGame_Sprite_Intersect_Direction(player, block);

    if(started)
    {
        vel_y -= 512 * dt;

        if(vel_x > 10)
        {
            vel_x -= 800 * dt;
        }
        else if(vel_x < -10)
        {
            vel_x += 800 * dt;
        }
        else
        {
            vel_x = 0;
        }

        if(player->transform.position.y <= 32)
        {
            if(vel_y < 0)
            {
                vel_y = 0;
                canJump = true;
            }
        }

        switch(collision_direction)
        {
            case QG_DIR_DOWN:
                vel_y = 0;
                canJump = true;
            break;
            case QG_DIR_UP:
                vel_y = 0;
            break;
            case QG_DIR_LEFT:
                if (vel_x < 0)
                {
                    vel_x = 0;
                }
            break;
            case QG_DIR_RIGHT:
                if (vel_x > 0)
                {
                    vel_x = 0;
                }
            break;
        }
        
        player->transform.position.y += vel_y * dt;
        player->transform.position.x += vel_x * dt;
        /*if(QuickGame_Sprite_Intersects(player, block))
        {
            vel_y = 0.0f;
        switch(collision_direction)
        {
            case QG_DIR_DOWN:
                //vel_y = -512.0f * dt;
                vel_y = 0.0f;
            break;
            case QG_DIR_UP:
                vel_y = 0.0f;
            break;
            case QG_DIR_LEFT:
                if(vel_x < 0)
                {
                    vel_x = 0;
                }
            break;
            case QG_DIR_RIGHT:
               if(vel_x > 0)
                {
                    vel_x = 0;
                }
            break;
            default:
                
            break;
        }
        }*/

    }
}

void update(double dt)
{
    QuickGame_Input_Update();

    int old_state = state;

    switch(state)
    {
        case MENU:
            if(QuickGame_Button_Pressed(PSP_CTRL_DOWN))
            {
                button[0].isBold = false;
                button[1].isBold = true;
            }
            else if(QuickGame_Button_Pressed(PSP_CTRL_UP))
            {
                button[0].isBold = true;
                button[1].isBold = false;
            }
            else if(QuickGame_Button_Pressed(PSP_CTRL_CROSS))
            {
                if(button[0].isBold)
                {
                    state = LVL_1;
                }
                else if(button[1].isBold)
                {
                    state = LANGUAGE;
                }
            }
        break;
        case LANGUAGE:
            if(QuickGame_Button_Pressed(PSP_CTRL_DOWN))
            {
                button[2].isBold = false;
                button[3].isBold = true;
            }
            else if(QuickGame_Button_Pressed(PSP_CTRL_UP))
            {
                button[2].isBold = true;
                button[3].isBold = false;
            }
            else if(QuickGame_Button_Pressed(PSP_CTRL_CROSS))
            {
                if(button[2].isBold)
                {
                    language = ENGLISH;
                }
                else if(button[3].isBold)
                {   
                    language = RUSSIAN;
                }

                state = MENU;
            }
        break;
        case LVL_1:
            update_player(dt);
        break;
        case LVL_2:
            update_player(dt);
        break;
    }

    if(old_state != state)
    {
        switch_state(old_state, state);
    }
}

int main()
{
    if (QuickGame_Init() < 0)
    {
        return 1;
    }

    QGColor white = {.color = 0xFFFFFF};

    QuickGame_Graphics_Set2D();
    QuickGame_Graphics_Set_Clear_Color(white);
    QuickGame_Timer_Start(&timer);

    state = MENU;
    language = ENGLISH;
    button[0].isBold = true;
    button[1].isBold = false;

    load_menu();

    while(QuickGame_Running())
    {
        update(QuickGame_Timer_Delta(&timer));
        draw();
    }
    
    QuickGame_Terminate();
    return 0;
}