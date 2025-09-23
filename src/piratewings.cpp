#include "pch.h"
#include "hook.h"
#include "debug.h"
#include "common/secure.h"
#include "common/dbbasic.h"
#include "common/iteminfo.h"
#include "wvs/wvscontext.h"
#include "wvs/uitooltip.h"
#include <cstdint>

static auto _ZtlSecureFuse_double = reinterpret_cast<double(__cdecl*)(double* at, unsigned int uCS)>(0x0052A210);
static auto _ZtlSecureTear_double = reinterpret_cast<unsigned int(__fastcall*)(double* at, double t)>(0x0052B370);

//auto OriginalCVecCtrl__CalcFloat = (signed int(__thiscall*)(void*, int))0x00900CB0;
static auto CVecCtrl__CalcFloat_original = reinterpret_cast<signed int(__thiscall*)(void*, int)>(0x00900CB0);


void __fastcall CVecCtrl__CalcFloat_hook(void* this_, void* _EDX, int tElapse) {
    // Call the original function first
    signed int result = CVecCtrl__CalcFloat_original(this_, tElapse);

    // Check if wings are active (m_bWingsNow at offset 0x214)
    bool isWingsActive = *(bool*)((uintptr_t)this_ + 0x214);

    if (isWingsActive) {
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