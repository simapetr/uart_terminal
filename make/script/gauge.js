/**
  ****************************************************************************
  * @file    gauge.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    31.10.2018
  * @brief   Gauge use example
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
var gauge_id;
var gauge_value = 0;
var button_id;
var static_text_id;
 
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
// Add gauge in to panel
gauge_id = gui.gauge.add(panel_sizer, 3, false,1000);
// Set actual value
gui.gauge.set(gauge_id, 0);
// Get actual value
gauge_value = gui.gauge.get(gauge_id);
// Add static text
static_text_id = gui.static_text.add(panel_sizer, "Value : 0", 1, false);
// Add button in to panel
button_id = gui.button.add(panel_sizer, "increment", 0, false);
// Register button event
gui.button.reg_event(button_id, "on_button_click");

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */


/** @brief Button event
 *
 * @param component_id : ID clicked button
 * @return void
 *
 */
 
function on_button_click (component_id)
{
var text_str = "Value : ";

	gauge_value += 10;
	// Set gauge value
	gui.gauge.set(gauge_id, gauge_value);
	// Update text
	text_str += gui.gauge.get(gauge_id);
	gui.static_text.set(static_text_id, text_str);
	// Update counter
	if (gauge_value >= 1000)
	{
		gauge_value = 0;
	}
}

/*****************************************************END OF FILE************/