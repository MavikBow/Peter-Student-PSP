#include <QuickGame.h>
#include <gu2gl.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>

QGTimer timer;

// In-game varivables

QGSprite_t mainT, bold;
QGSprite_t block, enemy, player, home, university, hint[2];

typedef struct
{
    QGSprite_t sprite;
    bool isBold;
} Button;

Button button[4];

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
}

void load_lang()
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

    QGTexInfo engTexInfo = {.filename = "./assets/text/eng/eng.png", .flip = true, .vram = 0};
    button[2].sprite = QuickGame_Sprite_Create_Contained(160, 110, 128, 32, engTexInfo);

    QGTexInfo rusTexInfo = {.filename = "./assets/text/rus/rus.png", .flip = true, .vram = 0};
    button[3].sprite = QuickGame_Sprite_Create_Contained(160, 110, 128, 32, rusTexInfo);

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

    QGTexInfo uniTexInfo = {.filename = "./assets/home.png", .flip = true, .vram = 0};
    university = QuickGame_Sprite_Create_Contained(0, 0, 32, 64, uniTexInfo);   
}

void load_lvl2()
{
    if(language == RUSSIAN)
    {
        QGTexInfo hint2TexInfo = {.filename = "./assets/text/rus/lvl2_hint.png", .flip = true, .vram = 0};
    }
    else
    {
        QGTexInfo hint2TexInfo = {.filename = "./assets/text/eng/lvl2_hint.png", .flip = true, .vram = 0};
    }

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
        break;
        case LVL_1:
        break;
        case LVL_2:
        break;
    };

    QuickGame_Graphics_End_Frame(true);
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
            else if(QuickGame_Button_Pressed(PSP_CTRL_CROSS)){
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
        break;
        case LVL_1:
        break;
        case LVL_2:
        break;
    }

    if(old_state != state){
        switch_state(old_state, state);
    }
}

int main()
{
    if (QuickGame_Init() < 0)
    {
        return 1;
    }   

    QuickGame_Graphics_Set2D();
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