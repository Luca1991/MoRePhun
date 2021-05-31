#include "../mophun_os.h"
#include "input_facilities.h"

uint32_t MophunOS::vGetButtonData()
{
    uint32_t pressedKeys = 0;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[input->keys[KEYUP]])           pressedKeys += KEY_UP;
    if (keystate[input->keys[KEYDOWN]])         pressedKeys += KEY_DOWN;
    if (keystate[input->keys[KEYLEFT]])         pressedKeys += KEY_LEFT;
    if (keystate[input->keys[KEYRIGHT]])        pressedKeys += KEY_RIGHT;
    if (keystate[input->keys[KEYFIRE]])         pressedKeys += KEY_FIRE;
    if (keystate[input->keys[KEYFIRE2]])        pressedKeys += KEY_FIRE2;
    if (keystate[input->keys[KEYSELECT]])       pressedKeys += KEY_SELECT;
    if (keystate[input->keys[POINTERDOWN]])     pressedKeys += POINTER_DOWN;
    if (keystate[input->keys[POINTERALTDOWN]])  pressedKeys += POINTER_ALTDOWN;

    return pressedKeys;
}