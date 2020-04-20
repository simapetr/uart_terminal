/**
  ****************************************************************************
  * @file gauge.js
  * @author simek
  * @version V1.0
  * @date 15.04.2020
  * @brief 
  ****************************************************************************
  * @attention
  * <h2><center>&copy; PORTTRONIC </center></h2>
  ****************************************************************************
  */

/**
  ****************************************************************************
  * Variable
  ****************************************************************************
  */

var main_panel = 0;
var main_panel_sizer = 0;
var test_gauge;
var gauge_val = 5;
var test_status_bool;
var demo_button;


/**
  ****************************************************************************
  * Initialize
  ****************************************************************************
  */

// Register exit function
reg_exit("exit");
setup();

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Setup
 *
 * @param
 * @return
 *
 */

function setup()
{
	gui(true);
	main_panel = gui.panel.add("test_panel", false);
	main_panel_sizer = gui.panel.get_sizer(main_panel);
	test_gauge = gui.gauge.add(main_panel_sizer, 0, false,10);
	test_status_bool = gui.gauge.set(test_gauge, gauge_val);
	// Add button
	demo_button = gui.button.add(main_panel_sizer, "+", 0, false);
	// Register button event
	gui.button.reg_event(demo_button, "on_button_click");  
}

/** @brief Button click event
 *
 * @param component : clicked button
 * @return void
 *
 */
 
function on_button_click (component)
{
	gauge_val++;
	if(gauge_val > 10)
	{
		gauge_val = 0;
	}
	gui.gauge.set(test_gauge, gauge_val);
} 

/** @brief Exit event
 *
 * @param
 * @return
 *
 */

function exit()
{
}

/*****************************************************END OF FILE************/
