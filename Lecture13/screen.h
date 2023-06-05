#pragma once
//중복해서 include하지 않게 막아준다.

/* 화면이 차지하는 최대 메모리를 65,536*/
char ScreenBuffer[65536];

void setScreenSize(int width, int height);
void setCursorPos(int x, int y);
void setCursorVisibility(int visible);
void SetColor(unsigned short backgroundColor, unsigned short textColor);

void ClearBuffer();
int WriteToBuffer(int x, int y, const char* str);
