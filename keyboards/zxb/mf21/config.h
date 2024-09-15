/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef VIA_QMK_RGBLIGHT_ENABLE
    #define VIA_QMK_RGBLIGHT_ENABLE
#endif

/* RGB settings. */
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_PWM_DMA_CHANNEL 3

/*-layer settings.*/
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
