/**
  ****************************************************************************
  * @file    in_jerryscript_date_c.c
  * @author  js.foundation
  * @version V1.0
  * @date    22.04.2018
  * @brief   JavaScript interpreter date function
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

#ifdef __GNUC__
#include <sys/time.h>
#endif

#include "in_jerryscript_core_h.h"
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
  * @defgroup Date
  * @brief JavaScript interpreter date function
  * @{
  */

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Get time zone implementation
 *
 * @param [OUT] jerry_time_zone_t : buffer for timezone data
 * @return bool : function available
 *    @arg true : Time of day is available and execute correct
 *    @arg false : function fail
 *
 */

bool jerry_port_get_time_zone (jerry_time_zone_t *p_data_jerry_time_zone)
{
#ifdef __GNUC__
  struct timeval tv;
  struct timezone tz;

  /* gettimeofday may not fill tz, so zero-initializing */
  tz.tz_minuteswest = 0;
  tz.tz_dsttime = 0;

  if (gettimeofday (&tv, &tz) != 0)
  {
    return false;
  }

  p_data_jerry_time_zone->offset = tz.tz_minuteswest;
  p_data_jerry_time_zone->daylight_saving_time = tz.tz_dsttime > 0 ? 1 : 0;

  return true;
#else /* !__GNUC__ */
  return false;
#endif /* __GNUC__ */
}

/** @brief Get time Unix epoch in ms
 *
 * @param void
 * @return double : Milliseconds since Unix epoch
 *
 */

double jerry_port_get_current_time (void)
{
#ifdef __GNUC__
  struct timeval tv;

  if (gettimeofday (&tv, NULL) != 0)
  {
    return 0.0;
  }

  return ((double) tv.tv_sec) * 1000.0 + ((double) tv.tv_usec) / 1000.0;
#else /* __!GNUC__ */
  return 0.0;
#endif /* __GNUC__ */
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
