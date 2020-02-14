#ifndef IN_JERRYSCRIPT_DEBUGGER_H_H_INCLUDED
#define IN_JERRYSCRIPT_DEBUGGER_H_H_INCLUDED

/**
  ****************************************************************************
  * @file    in_jerryscript_debugger_h.h
  * @author  js.foundation
  * @version V1.0
  * @date    22.04.2018
  * @brief   JavaScript interpreter core function
  ****************************************************************************
  * @attention
  * <h2><center>
  * &copy; JS Foundation and other contributors, http://js.foundation
  * </center></h2>
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  ****************************************************************************
  */

/**
  ****************************************************************************
  * Library
  ****************************************************************************
  */

#include "in_jerryscript_core_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup Debuger
  * @{
  */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

void jerryx_debugger_after_connect (bool success);

/*
 * Message transmission interfaces.
 */
bool jerryx_debugger_tcp_create (uint16_t port);

/*
 * Message encoding interfaces.
 */
bool jerryx_debugger_ws_create (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

#endif //IN_JERRYSCRIPT_DEBUGGER_H_H_INCLUDED
