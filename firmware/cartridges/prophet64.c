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
* C64 bus read callback
******************************************************************************/
FORCE_INLINE bool prophet64_read_handler(u32 control, u32 addr)
{
    if (!(control & C64_ROML))
    {
        C64_DATA_WRITE(crt_ptr[addr & 0x1fff]);
        return true;
    }

    return false;
}

/******************************************************************************
* C64 bus write callback
******************************************************************************/
FORCE_INLINE void prophet64_write_handler(u32 control, u32 addr, u32 data)
{
    if (!(control & C64_IO2))
    {
        crt_ptr = crt_banks[data & 0x1f];

        if (data & 0x20)
        {
            // Disable cartridge
            C64_CRT_CONTROL(STATUS_LED_OFF|CRT_PORT_NONE);
        }
        else
        {
            // Enable cartridge
            C64_CRT_CONTROL(STATUS_LED_ON|CRT_PORT_8K);
        }
    }
}

C64_BUS_HANDLER(prophet64)
