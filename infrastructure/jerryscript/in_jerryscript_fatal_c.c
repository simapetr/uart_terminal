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

#include <stdlib.h>

#include "jerryscript-port.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JavaScript
  * @{
  */

/**
  * @defgroup Fatal
  * @brief JavaScript interpreter error handler
  * @{
  */

#ifndef DISABLE_EXTRA_API

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static bool l_abort_on_fail_b = false;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Set abort flag
 *
 * @param [IN] flag_b : Flag state
 * @return void
 *
 */

void jerry_port_default_set_abort_on_fail (bool flag_b) /**< new value of 'abort on fail' flag */
{
    l_abort_on_fail_b = flag_b;
    return;
}

/** @brief Get abort flag
 *
 * @param void
 * @return bool : Abort state
 *
 */

bool jerry_port_default_is_abort_on_fail (void)
{
    return l_abort_on_fail_b;
}

#endif /* !DISABLE_EXTRA_API */

/** @brief Fatal error handler
 *
 * @param [IN] error_jerry_fatal_code : Error code
 * @return void
 *
 */

void jerry_port_fatal (jerry_fatal_code_t error_jerry_fatal_code)
{
#ifndef DISABLE_EXTRA_API
    if (error_jerry_fatal_code != 0 && error_jerry_fatal_code != ERR_OUT_OF_MEMORY && jerry_port_default_is_abort_on_fail ())
    {
        abort ();
    }
    else
    {
        #endif /* !DISABLE_EXTRA_API */
        exit (error_jerry_fatal_code);
        #ifndef DISABLE_EXTRA_API
    }
#endif // DISABLE_EXTRA_API
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
