/*
piratewings.cpp

Modifies the behavior of the Wings skill:
+ Increases horizontal movement speed while Wings is active
+ Allows faster left/right movement (sets velocity to ±300)
+ Prevents movement if the game window is not focused

Thanks to Aviv, Teto, and Angel
*/

#include "pch.h"
#include "hook.h"
#include "debug.h"
#include "config.h"
#include "common/secure.h"
#include "common/dbbasic.h"
#include "common/iteminfo.h"
#include "wvs/wvscontext.h"
#include "wvs/uitooltip.h"
#include <cstdint>

static auto _ZtlSecureFuse_double = reinterpret_cast<double(__cdecl*)(double* at, unsigned int uCS)>(0x0052A210);
static auto _ZtlSecureTear_double = reinterpret_cast<unsigned int(__fastcall*)(double* at, double t)>(0x0052B370);
static auto CVecCtrl__CalcFloat_original = reinterpret_cast<signed int(__thiscall*)(void*, int)>(0x009934C0);


void __fastcall CVecCtrl__CalcFloat_hook(void* this_, void* _EDX, int tElapse) {
    // Call the original function first
    signed int result = CVecCtrl__CalcFloat_original(this_, tElapse);


    // Check if wings are active (m_bWingsNow at offset 0x214)
    bool isWingsActive = *(bool*)((uintptr_t)this_ + 0x214);

    if (isWingsActive) {
        // Ensure the game window is active so that we can't move when tabbed out.
        HWND foregroundWindow = GetForegroundWindow();
        HWND gameWindow = FindWindowA(NULL, CONFIG_WINDOW_NAME);

        if (foregroundWindow != gameWindow) {
            return;
        }

        // Get the horizontal velocity (if you want to use it)
        double vx = _ZtlSecureFuse_double(
                reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(this_) + 0x50),
                *reinterpret_cast<unsigned int*>(reinterpret_cast<uintptr_t>(this_) + 0x60));
        // Check if left or right keys are pressed
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            *reinterpret_cast<unsigned int*>(reinterpret_cast<uintptr_t>(this_) + 0x60) = _ZtlSecureTear_double(
                    reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(this_) + 0x50),
                    -300.0);
        } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            *reinterpret_cast<unsigned int*>(reinterpret_cast<uintptr_t>(this_) + 0x60) = _ZtlSecureTear_double(
                    reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(this_) + 0x50),
                    300.0);
        }
    }
}



void AttachWingsMod() {
    ATTACH_HOOK(CVecCtrl__CalcFloat_original, CVecCtrl__CalcFloat_hook);
}