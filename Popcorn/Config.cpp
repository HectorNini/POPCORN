#include "Config.h"


//---------------------------------------------------------------------------------------------------------
AColor::AColor()
    : R(0), G(0), B(0), Pen(0), Brush(0)
{
}
//---------------------------------------------------------------------------------------------------------
AColor::AColor(unsigned char r, unsigned char g, unsigned char b)
    : R(r), G(g), B(b), Pen(0), Brush(0)
{
    Pen = CreatePen(PS_SOLID, 0, RGB(R, G, B));
    Brush = CreateSolidBrush(RGB(R, G, B));
}
//---------------------------------------------------------------------------------------
AColor::AColor(const AColor& color, int pen_size)
    : R(color.R), G(color.G), B(color.B), Pen(0), Brush(0)
{
    Pen = CreatePen(PS_SOLID, pen_size, color.Get_RGB());
}
//---------------------------------------------------------------------------------------
AColor::AColor(const AColor &pen_color, const AColor& brush_color, int pen_size)
    : R(0), G(0), B(0), Pen(0), Brush(0)
{
    Pen = CreatePen(PS_SOLID, pen_size, pen_color.Get_RGB());
    Brush = CreateSolidBrush(brush_color.Get_RGB());
}
//---------------------------------------------------------------------------------------
AColor::AColor(unsigned char r, unsigned char g, unsigned char b, int pen_size)
    : R(r), G(g), B(b), Pen(0), Brush(0)
{
    Pen = CreatePen(PS_SOLID, pen_size, RGB(R, G, B));
}
//---------------------------------------------------------------------------------------

int AColor::Get_RGB() const
{
    return RGB(R,G,B);
}
//---------------------------------------------------------------------------------------
void AColor::Select(HDC hdc) const
{
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);
}
//---------------------------------------------------------------------------------------
void AColor::Select_Pen(HDC hdc) const
{
    SelectObject(hdc, Pen);
}
//---------------------------------------------------------------------------------------
HBRUSH AColor::Get_Brush() const 
{
    return Brush;
}
//---------------------------------------------------------------------------------------

const AColor AsConfig::Red_Color(255,85,85);
const AColor AsConfig::Blue_Color(85, 255, 255);
const AColor AsConfig::White_Color(255, 255, 255);
const AColor AsConfig::BG_Color(15, 63, 31);
const AColor AsConfig::Letter_Color(White_Color, Global_Scale);
const AColor AsConfig::Teleport_Portal_Color(AsConfig::Blue_Color, AsConfig::BG_Color, AsConfig::Global_Scale);
const AColor AsConfig::Unbreakable_Blue_Highlight(AsConfig::Blue_Color, AsConfig::Global_Scale);
const AColor AsConfig::Unbreakable_Red_Highlight(AsConfig::Red_Color, 3 * AsConfig::Global_Scale);
const AColor AsConfig::Advertisement_Red_Table(AsConfig::Red_Color, 2 * AsConfig::Global_Scale);
const AColor AsConfig::Advertisement_Blue_Table(0, 159, 159, AsConfig::Global_Scale);

//---------------------------------------------------------------------------------------




const double AsConfig::Ball_Step_Size = 1.0 / Global_Scale;
const double AsConfig::Start_Y_Pos = 184.0;
int AsConfig::Current_Timer_Tick = 0;
bool AsConfig::Level_Has_Floor = false;
HWND AsConfig::Hwnd;

//---------------------------------------------------------------------------------------
int AsConfig::Rand(int range) 
{
    return rand() * range / RAND_MAX;
}
//---------------------------------------------------------------------------------------

void AsConfig::Round_Rect(HDC hdc, RECT& rect, int corner_radius) 
{
    int radius = corner_radius * AsConfig::Global_Scale;
    RoundRect(hdc, rect.left, rect.top, rect.right - 1, rect.bottom - 1, radius, radius);
}
//---------------------------------------------------------------------------------------

void AsConfig::Throw() 
{
    throw 0;
}