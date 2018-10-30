/**
  ****************************************************************************
  * @file    in_jerryscript_fatal_c.c
  * @author  js.foundation
  * @version V1.0
  * @date    22.04.2018
  * @brief   JavaScript interpreter error handler function
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

#include <windows.h>
#include <stdarg.h>

#include "in_jerryscript_core_h.h"
#include "jerryscript-port.h"
//#include "debugger.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JavaScript
  * @{
  */

/**
  * @defgroup IO
  * @brief JavaScript interpreter in/out interface
  * @{
  */

#ifndef DISABLE_EXTRA_API

/**
  ****************************************************************************
  * Define
  ****************************************************************************
  */

#define JERRY_PORT_DEFAULT_LOG_LEVEL l_actual_jerry_log_level

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static jerry_log_level_t l_actual_jerry_log_level = JERRY_LOG_LEVEL_ERROR;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Get the log level
 *
 * @param void
 * @return jerry_log_level_t : Current log level
 *
 */

jerry_log_level_t jerry_port_default_get_log_level (void)
{
    return l_actual_jerry_log_level;
}

/** @brief Set the log level
 *
 * @param [IN] actual_jerry_log_level : Actual log level
 * @return void
 *
 */

void jerry_port_default_set_log_level (jerry_log_level_t actual_jerry_log_level)
{
    l_actual_jerry_log_level = actual_jerry_log_level;
    return;
}

#else /* DISABLE_EXTRA_API */
#define JERRY_PORT_DEFAULT_LOG_LEVEL JERRY_LOG_LEVEL_ERROR
#endif /* !DISABLE_EXTRA_API */

/** @brief Printf implementation
 *
 * @param [IN] type_jerry_log_level : Log level type
 * @param [IN] p_format_char : Data format string
 * @param [IN] ... : Var list defined in p_format_char
 * @return void
 *
 */

void jerry_port_log (jerry_log_level_t level, const char *format, ...)
{
  if (level <= JERRY_PORT_DEFAULT_LOG_LEVEL)
  {
    va_list args;
    va_start (args, format);
#ifdef JERRY_DEBUGGER
    int length = vsnprintf (NULL, 0, format, args);
    va_end (args);
    va_start (args, format);

    char buffer[length + 1];
    vsnprintf (buffer, (size_t) length + 1, format, args);

    fprintf (stderr, "%s", buffer);
    jerry_debugger_send_log (level, (jerry_char_t *) buffer, (jerry_size_t) length);
#else /* If jerry-debugger isn't defined, libc is turned on */
    vfprintf (stderr, format, args);
#endif /* JERRY_DEBUGGER */
    va_end (args);
  }
} /* jerry_port_log */


/** @brief Wrapper for system sleep
 *
 * @param [IN] sleep_time : Sleep time in ms
 * @return void
 *
 */

void jerry_port_sleep (uint32_t sleep_time)
{
    Sleep(sleep_time);
    return;
}

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
