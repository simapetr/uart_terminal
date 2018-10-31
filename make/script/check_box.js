/**
  ****************************************************************************
  * @file    check_box.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    12.09.2018
  * @brief   Check box use example
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
var check_box_id;
var button_id;
 
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
// Add check box in to panel
check_box_id = gui.check_box.add(panel_sizer, "test", 0, false,false);
// Register button event
gui.check_box.reg_event(check_box_id, "on_check_box_click");
// Add button in to panel
button_id = gui.button.add(panel_sizer, "toggle", 0, false);
// Register button event
gui.button.reg_event(button_id, "on_button_click");

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Check box event
 *
 * @param component_id : ID clicked check box
 * @return void
 *
 */
 
function on_check_box_click (component_id)
{
	alert("You clicked on check box.");
}

/** @brief Button event
 *
 * @param component_id : ID clicked button
 * @return void
 *
 */
 
function on_button_click (component_id)
{
	if (gui.check_box.get(component_id))
	{
		gui.check_box.set(component_id, false);
	}
	else
	{
		gui.check_box.set(component_id, true);
	}
}

/*****************************************************END OF FILE************/