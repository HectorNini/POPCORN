#pragma once
#include "Config.h"
//---------------------------------------------------------------------------------------
class ABall;
class AHit_Checker
{
public:
    virtual bool Check_Hit(double next_x_pos, double next_y_pos, ABall* ball) = 0;
    bool Hit_Circle_On_Line(double y, double next_x_pos, double left_x, double right_x, double radius, double& x);

};

//---------------------------------------------------------------------------------------
class AMover
{
public:
    virtual ~AMover();
    virtual void Begin_Movement() = 0;
    virtual void Finish_Movement() = 0;
    virtual void Advance(double max_speed) = 0;
    virtual double Get_Speed() = 0;


};


//---------------------------------------------------------------------------------------

enum EBall_State 
{
    EBS_Disabled,
    EBS_Normal,
    EBS_Lost,
    EBS_On_Platform,
    EBS_On_Parachute,
    EBS_Off_Parachute,
    EBS_Teleporting
};


class ABall : public AMover
{
public:
    ABall();   
    virtual void Begin_Movement();
    virtual void Finish_Movement();
    virtual double Get_Speed();
    virtual void Advance(double max_speed);
    void Draw(HDC hdc, RECT& paint_area);
    void Set_For_Test();
    bool Is_Test_Finished();
    EBall_State Get_State();
    void Set_State(EBall_State new_state, double x_pos = 0, double y_pos = 0);
    void Get_Center(double& x_pos, double& y_pos);
    double Get_Direction();
    void Set_Direction(double new_direction);
    void Reflect(bool from_horizontal);
    bool Is_Moving_Up();
    bool Is_Moving_Left();
    void Set_On_Parachute(int brick_x, int brick_y);
    void Draw_Teleporting(HDC hdc, int step);
    static void Add_Hit_Checker(AHit_Checker * hit_checker);
    static const double Radius;

    RECT Ball_Rect, Prev_Ball_Rect, Parachute_Rect, Prev_Parachute_Rect;


private:

    void Redraw_Ball();
    void Draw_Parachute(HDC hdc, RECT &paint_area);
    void Redraw_Parachute();
    void Clear_Parachute(HDC hdc);

    static const int Parachute_Size = 15;
    static int Hit_Checkers_Count;
    static AHit_Checker* Hit_Checkers[3];
    EBall_State Ball_State, Prev_Ball_State;
    
    double Ball_Direction;
    double Ball_Speed;
    //double Rest_Distance;
    double Center_X_Pos, Center_Y_Pos;
    double Rest_Test_Distance;
    int Test_Iteration;
    bool Testing_Is_Active;
    
};