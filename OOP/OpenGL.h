#pragma once

//MOUSE
int mx, my;
//Keyboard
bool keystate[256];

void Display();

void Reshape(int width, int height);

void OnTimer(int id);

void OnKeyDown(unsigned char key, int x, int y);

void OnKeyPress(unsigned char key, int x, int y);

void OnKeyUp(unsigned char key, int x, int y);

void KeyboardFunc(unsigned char key, int x, int y);

void Idle();

void MouseButton(int button, int state, int x, int y);

void MousePassiveMotion(int x, int y);

void MouseMotion(int x, int y);

void EntryFunc(int state);
