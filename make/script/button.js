/**
  ****************************************************************************
  * @file    button.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    12.09.2018
  * @brief   Button use example
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

var panel_id = 0;
var panel_sizer = 0;
var button_id;
var text_str;
 
/**
  ****************************************************************************
  * script
  ****************************************************************************
  */

main_frame.console_rx_enable(false);
main_frame.clear();
main_frame.printf("GUI test :\n");
// Show gui frame
gui(true);
// Create new AUI panel
panel_id = gui.panel.add("test_panel", true);
// Add basic sizer in to panel
panel_sizer = gui.panel.get_sizer(panel_id);
// Add button in to panel
button_id = gui.button.add(panel_sizer, "test", 0, false);
// Register button event
gui.button.reg_event(button_id, "on_button_click");

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Get panel main sizer
 *
 * @param component_id : ID clicked button
 * @return void
 *
 */
 
function on_button_click (component_id)
{
	alert("You clicked on button.");
}

/*****************************************************END OF FILE************/