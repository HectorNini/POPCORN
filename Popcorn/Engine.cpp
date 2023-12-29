#include "Engine.h"



//AsEngine
AsEngine::AsEngine() 
    :Game_State(EGS_Lost_Ball)
{ 
}

//---------------------------------------------------------------------------------------
void AsEngine::Init_Engine(HWND hwnd) 
{//Первоначальная настройка
    SYSTEMTIME sys_time;
    FILETIME file_time;
    GetSystemTime(&sys_time);
    SystemTimeToFileTime(&sys_time, &file_time);
    srand(file_time.dwLowDateTime);

    AsConfig::Hwnd = hwnd;

    AActive_Brick_Red_Blue::Setup_Colors(); 

    Level.Init();
    AFalling_Letter::Init();
    ABall::Add_Hit_Checker(&Border);
    ABall::Add_Hit_Checker(&Level);
    ABall::Add_Hit_Checker(&Platform);
    Level.Set_Current_Level(AsLevel::Level_01);
    Platform.Redraw();
    SetTimer(AsConfig::Hwnd, Timer_ID, 1000 / AsConfig::FPS, 0);
}
//---------------------------------------------------------------------------------------
void AsEngine::Draw_Frame(HDC hdc, RECT& paint_area)
{//Отрисовка экрана игры
    SetGraphicsMode(hdc, GM_ADVANCED);
    Level.Draw(hdc, paint_area);
    Border.Draw(hdc, paint_area);
    Platform.Draw(hdc, paint_area);
    for (int i = 0; i < AsConfig::Max_Balls_Count; i++)
        Balls[i].Draw(hdc, paint_area);
    //Ball.Draw(hdc, paint_area);
}
//---------------------------------------------------------------------------------------------------------
int AsEngine::On_Key(EKey_Type key_type, bool key_down)
{
    switch (key_type) 
    {
    case EKT_Left:
        Platform.Move(true, key_down);
        break;
    case EKT_Right:
        Platform.Move(false, key_down);
        break;
    case EKT_Space:
        if (key_down)
            if (Platform.Get_State() == EPS_Ready)
            {
                for (int i = 0; i < AsConfig::Max_Balls_Count; i++)
                    if (Balls[i].Get_State() == EBS_On_Platform)
                        Balls[i].Set_State(EBS_Normal, Platform.Get_Middle_Pos(), AsConfig::Start_Y_Pos);
                Platform.Set_State(EPS_Normal);
            }
        break;
    }

    return 0;
}
//---------------------------------------------------------------------------------------------------------

void AsEngine::Act()
{
    int index = 0;
    AFalling_Letter* falling_letter;
    Platform.Act();
    Level.Act();

    while (Level.Get_Next_Falling_Letter(index, &falling_letter) ) 
    {
        if (Platform.Hit_By(falling_letter) )
            On_Falling_Letter(falling_letter);
    }

}
//---------------------------------------------------------------------------------------------------------

void AsEngine::On_Falling_Letter(AFalling_Letter* falling_letter)
{
    switch (falling_letter->Letter_Type) 
    {
         case ELT_O:       //отмена
             break;

         case ELT_I:       // инверсия
             break;

         case ELT_C:       //скорость
             break;

         case ELT_M:       // монстры
             break;

         case ELT_G:       //жизнь
             break;

         case ELT_K:       //клей
             break;

         case ELT_W:       //шире  
             break;

         case ELT_T:       //три

             break;

         case ELT_L:       //лазер
             break;

         case ELT_P:       //пол
             break;

         case ELT_Plus:    //переход на следующий уровень
             break;

         default:
             AsConfig::Throw();

    }
    falling_letter->Finalize();
}
//---------------------------------------------------------------------------------------------------------

void AsEngine::Play_Level()
{
    int active_balls_count = 0;
    int lost_balls_count = 0;
    double rest_distance;
    double max_speed;
    //1. Смещение платформы

    max_speed = fabs(Platform.Speed);

    rest_distance = max_speed;
    
    while (rest_distance > 0.0)
    {
        Platform.Advance(max_speed);
        rest_distance -= AsConfig::Moving_Step_Size;
    }

    Platform.Redraw();

    //2. Смещение мячиков
    for (int i = 0; i < AsConfig::Max_Balls_Count; i++)
    {
        if (Balls[i].Get_State() == EBS_Disabled)
            continue;

        ++active_balls_count;

        if (Balls[i].Get_State() == EBS_Lost)
        {
            ++lost_balls_count;
            continue;
        }


        Balls[i].Move();
    }

    if (active_balls_count == lost_balls_count) 
    {// Потеря всех мячиков
        Game_State = EGS_Lost_Ball;
        Level.Stop();
        Platform.Set_State(EPS_Meltdown);
    }

    if (active_balls_count == 1)
        if (Balls[0].Is_Test_Finished())
            Game_State = EGS_Test_Ball;
}
//---------------------------------------------------------------------------------------------------------

void AsEngine::Restart_Level()
{
    int i;
   
    Game_State = EGS_Play_Level;
    for (i = 0; i < 3; i++)
        Balls[i].Set_State(EBS_On_Platform, Platform.Get_Middle_Pos(), AsConfig::Start_Y_Pos);

    for (; i < AsConfig::Max_Balls_Count; i++)
        Balls[i].Set_State(EBS_Disabled);

}
//---------------------------------------------------------------------------------------------------------

int AsEngine::On_Timer() 
{
    ++AsConfig::Current_Timer_Tick;
    switch (Game_State) 
    {
    case EGS_Test_Ball:
        Balls[0].Set_For_Test();
        Game_State = EGS_Play_Level;
        break;

    case EGS_Play_Level:
        Play_Level();
        break;


    case EGS_Lost_Ball:
        if (Platform.Get_State() == EPS_Missing)
        {
            Game_State = EGS_Restart_Level;
            Platform.Set_State(EPS_Roll_In);
        }
        break;

    case EGS_Restart_Level:
        if (Platform.Get_State() == EPS_Ready)
            Restart_Level();
        break;
    }

    Act();

    return 0;
}
//---------------------------------------------------------------------------------------------------------

