/**
  ****************************************************************************
  * @file    led.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    12.03.2020
  * @brief   LED use example
  ****************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT PORTTRONIC</center></h2>
  ****************************************************************************
  */

/**
  ****************************************************************************
  * Variable
  ****************************************************************************
  */

var main_panel = 0;
var main_panel_sizer = 0;
var set_button = 0;
var state_led = 0;
var custom_led = 0;
var state_b = false;

/**
  ****************************************************************************
  * script
  ****************************************************************************
  */

// Show gui frame
gui(true);
// Create new AUI panel
main_panel = gui.panel.add("LED example", false);
// Add basic sizer in to panel
main_panel_sizer = gui.panel.get_sizer(main_panel);
// Add set button
set_button = gui.button.add(main_panel_sizer, "Set", 0, false);
reg_event_bool = gui.button.reg_event(set_button, "on_set_button_click");
// Add default LED
state_led = gui.led.add(main_panel_sizer);
// Add custom LED
custom_led = gui.led.add(main_panel_sizer, 0x0000FFFF, 0x00808080);


/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Slider update event
 *
 * @param component_id : ID clicked slider
 * @return void
 *
 */

function on_set_button_click (component_id)
{
    if(state_b)
    {
        gui.led.set(state_led, false);
        gui.led.set(custom_led, false);
        state_b = false;
    }
    else
    {
        gui.led.set(state_led, true);
        gui.led.set(custom_led, true);
        state_b = true;
    }
}

/*****************************************************END OF FILE************/
