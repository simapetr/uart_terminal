/**
  ****************************************************************************
  * @file    in_js_gui_led_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    11.03.2020
  * @brief   GUI window LED component
  ****************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT PORTTRONIC</center></h2>
  ****************************************************************************
  */

/**
  ****************************************************************************
  * Library
  ****************************************************************************
  */

#include "in_js_gui_frame_h.h"
#include "in_jerryscript_port_h.h"
#include <wx/led.h>

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @addtogroup JerryScript
  * @{
  */

/**
  * @addtogroup GUI
  * @{
  */

/**
  * @addtogroup LED
  * @brief GUI LED component
  * @{
  */

/**
  ****************************************************************************
  * Define
  ****************************************************************************
  */



/**
  ****************************************************************************
  * Struct
  ****************************************************************************
  */

typedef struct
{
    double sizer_index_d;
    double on_color_d;
    double off_color_d;
    wxLed* p_data_wxled;
    bool state_b;
    bool state_old_b;
}led_buffer_t;

/**
  ****************************************************************************
  * Local variable
  ****************************************************************************
  */

static vector<led_buffer_t> lv_data_led_buffer;
static uint32_t l_cnt_led_ui32 = 0;

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Add LED
 *
 * @param sizer_index_d : Parent sizer index
 * @param on_color_d : On LED color
 * @param off_color_d : Off LED color
 * @return uint32_t : New LED buffer index
 *
 */

uint32_t gui_frame::add_led (double sizer_index_d, double on_color_d, double off_color_d)
{
led_buffer_t l_data_led_buffer;
uint32_t index_ui32 = lv_data_led_buffer.size();

    l_data_led_buffer.sizer_index_d = sizer_index_d;
    l_data_led_buffer.on_color_d = on_color_d;
    l_data_led_buffer.off_color_d = off_color_d;
    l_data_led_buffer.state_b = false;
    l_data_led_buffer.state_old_b = false;
    l_data_led_buffer.p_data_wxled = NULL;
    lv_data_led_buffer.push_back(l_data_led_buffer);
    while(!lv_data_led_buffer[index_ui32].p_data_wxled){wxMilliSleep(1);}
    wxMilliSleep(1);
    return index_ui32;
}

/** @brief Set Led state
 *
 * @param led_index_d : LED index
 * @param state_b : LED state
 * @return void
 *
 */

void gui_frame::set_led (double led_index_d, bool state_b)
{
    if (led_index_d < lv_data_led_buffer.size())
    {
        lv_data_led_buffer[led_index_d].state_b = state_b;
    }
    return;
}

/** @brief Get Led state
 *
 * @param led_index_d : LED index
 * @return bool : LED state
 *
 */

bool gui_frame::get_led (double led_index_d)
{
bool status_b = false;

    if (led_index_d < lv_data_led_buffer.size())
    {
        status_b = lv_data_led_buffer[led_index_d].state_b;
    }
    return status_b;
}

/**
  ****************************************************************************
  * Local function
  ****************************************************************************
  */

/** @brief LED constructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_update_led(void)
{
wxPanel* p_data_wxpanel;
wxBoxSizer* p_data_wxboxsizer;
uint32_t item_cnt_ui32;
wxLed* p_data_wxled;

    // Add Static text
    while (l_cnt_led_ui32 < lv_data_led_buffer.size())
    {
        // Get box sizer
        p_data_wxboxsizer = this->get_sizer(lv_data_led_buffer[l_cnt_led_ui32].sizer_index_d);
        // Get origin panel
        p_data_wxpanel = this->get_sizer_panel(lv_data_led_buffer[l_cnt_led_ui32].sizer_index_d);
        // Create new LED
        p_data_wxled = new wxLed(p_data_wxpanel,wxNewId(),wxColour(128,128,128),wxColour(lv_data_led_buffer[l_cnt_led_ui32].on_color_d),wxColour(lv_data_led_buffer[l_cnt_led_ui32].off_color_d),wxDefaultPosition,wxDefaultSize);
        if(p_data_wxled)
        {
            p_data_wxled->SwitchOff();
            p_data_wxboxsizer->Add(p_data_wxled, 0, wxALL|wxSHAPED|wxFIXED_MINSIZE, 5);
            p_data_wxboxsizer->Fit(p_data_wxpanel);
            p_data_wxboxsizer->SetSizeHints(p_data_wxpanel);
            p_data_wxboxsizer->Layout();
            lp_main_wxauimanager->Update();
            // Save object
            lv_data_led_buffer[l_cnt_led_ui32].p_data_wxled = p_data_wxled;
        }
        l_cnt_led_ui32++;
    }
    for (item_cnt_ui32 = 0 ; item_cnt_ui32 < lv_data_led_buffer.size() ; item_cnt_ui32++)
    {
        if (lv_data_led_buffer[item_cnt_ui32].state_b != lv_data_led_buffer[item_cnt_ui32].state_old_b)
        {
            // Set LED state
            if (lv_data_led_buffer[item_cnt_ui32].state_b)
            {
               lv_data_led_buffer[item_cnt_ui32].p_data_wxled->SwitchOn();
            }
            else
            {
                lv_data_led_buffer[item_cnt_ui32].p_data_wxled->SwitchOff();
            }
            lv_data_led_buffer[item_cnt_ui32].state_old_b = lv_data_led_buffer[item_cnt_ui32].state_b;
        }
    }
    return;
}

/** @brief LED destructor event (must be called from GUI context)
 *
 * @param void
 * @return void
 *
 */

void gui_frame::on_clear_led(void)
{
    lv_data_led_buffer.clear();
    l_cnt_led_ui32 = 0;
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

/**
* @}
*/

/*****************************************************END OF FILE************/


