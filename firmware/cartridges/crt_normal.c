/*
 * Copyright (c) 2019-2024 Kim Jørgensen
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

/******************************************************************************
* C64 bus read callback (early VIC-II cycle)
******************************************************************************/
FORCE_INLINE u32 crt_early_vic_handler(u32 addr)
{
    // Speculative read
    return crt_ptr[addr & 0x3fff];
}

/******************************************************************************
* C64 bus read callback (VIC-II cycle)
******************************************************************************/
FORCE_INLINE bool crt_vic_read_handler(u32 control, u32 data)
{
    if ((control & (C64_ROML|C64_ROMH)) != (C64_ROML|C64_ROMH))
    {
        C64_DATA_WRITE(data);
        return true;
    }

    return false;
}

/******************************************************************************
* C64 bus read callback
******************************************************************************/
FORCE_INLINE bool crt_read_handler(u32 control, u32 addr)
{
    if ((control & (C64_ROML|C64_ROMH)) != (C64_ROML|C64_ROMH))
    {
        C64_DATA_WRITE(crt_ptr[addr & 0x3fff]);
        return true;
    }

    return false;
}

/******************************************************************************
* C64 bus write callback
******************************************************************************/
FORCE_INLINE void crt_write_handler(u32 control, u32 addr, u32 data)
{
    // No write support
}

// Support MAX cartridges where the VIC-II reads character and sprite data
// directly from the cartridge
C64_VIC_BUS_HANDLER(crt)
