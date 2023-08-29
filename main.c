#include <QuickGame.h>
#include <gu2gl.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <stdio.h>

QGTimer timer;

QGSprite_t mainT, bold;

typedef struct
{
    QGSprite_t sprite;
    bool isBold;
} Button;

Button button[2];

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


void load_menu()
{
    char L[4]; 

    switch(language)
    {
        case RUSSIAN:
            sprintf(L, "rus");
        break;
        case ENGLISH:
        default:
            sprintf(L, "eng");
        break;
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

    QGTexInfo boldTexInfo = {.filename = "./assets/text/button_bold.png"};
    bold = QuickGame_Sprite_Create_Contained(160, 110, 128, 32, boldTexInfo);
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
        break;
        case LVL_1:
        break;
        case LVL_2:
        break;
    };

    QuickGame_Graphics_End_Frame(true);
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
    //reset_menu();

    while(QuickGame_Running())
    {
        //update(QuickGame_Timer_Delta(&timer));
        draw();
    }
    
    QuickGame_Terminate();
    return 0;
}