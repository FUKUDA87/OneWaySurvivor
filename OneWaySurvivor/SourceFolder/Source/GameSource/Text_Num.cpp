#include "Text_Num.h"

extern LPD3DXFONT lpFontS;

void C_Text_Num::Draw_Text_float(const float * Num, const D3DXVECTOR2 * Pos)
{
	int x = (int)Pos->x, y = (int)Pos->y;

	RECT rcNum = { x,y,0,0 };
	char Text[200];
	sprintf_s(Text, sizeof(Text), "%f", *Num);
	lpFontS->DrawTextA(NULL, Text, -1, &rcNum, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void C_Text_Num::Draw_Text_int(const int * Num, const D3DXVECTOR2 * Pos)
{
	int x = (int)Pos->x, y = (int)Pos->y;

	RECT rcNum = { x,y,0,0 };
	char Text[200];
	sprintf_s(Text, sizeof(Text), "%d", *Num);
	lpFontS->DrawTextA(NULL, Text, -1, &rcNum, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void C_Text_Num::Draw_Text_char(const char * Text, const D3DXVECTOR2 * Pos)
{
	int x = (int)Pos->x, y = (int)Pos->y;

	RECT rcNum = { x,y,0,0 };
	lpFontS->DrawTextA(NULL, Text, -1, &rcNum, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}
