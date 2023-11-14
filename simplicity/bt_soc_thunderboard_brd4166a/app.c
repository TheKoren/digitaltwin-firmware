/***************************************************************************//**
 * @file
 * @brief Thunderboard demo application
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
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
 *
 ******************************************************************************/

#include <stdbool.h>
#include "em_common.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "sl_status.h"
#include "sl_simple_button_instances.h"
#include "app_log.h"
#include "app_assert.h"
#include "sl_power_supply.h"
#include "board.h"
#include "app.h"

#include "measurement.h"


// -----------------------------------------------------------------------------
// Public function definitions


void app_init(void)
{
  app_log_info("Silicon Labs Thunderboard / DevKit demo" APP_LOG_NL);
  sl_power_supply_probe();
  measurement_init();
}

SL_WEAK void app_process_action(void)
{
  measurement_process_action();
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

// -----------------------------------------------------------------------------
// Push button event handler

void sl_button_on_change(const sl_button_t *handle)
{
  (void)handle;
}

