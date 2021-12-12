#ifndef RGE_CORE_INPUT_H
#define RGE_CORE_INPUT_H

#include "defs.h"

bool GetKey(int key);
bool GetKeyDown(int key);
bool GetKeyUp(int key);

bool GetMouseButton(int button);
bool GetMouseButtonDown(int button);
bool GetMouseButtonUp(int button);

void SetCursorMode(int mode);
void GetCursorPosition(int *x, int *y);

void GetMouseScroll(float *x, float *y);

#endif
