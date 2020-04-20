/**
  ****************************************************************************
  * @file led.js
  * @author simek
  * @version V1.0
  * @date 15.04.2020
  * @brief LED usage example
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
var test_led = 0;
var main_timer = 0;

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
	// Show gui frame
	gui(true);
	// Create new AUI panel
	main_panel = gui.panel.add("test_panel", true);
	// Add basic sizer in to panel
	main_panel_sizer = gui.panel.get_sizer(main_panel);
	// Create test led
	test_led = gui.led.add(main_panel_sizer);
	gui.led.set(test_led, true);
	// Set timer
	main_timer = timer.add("on_timer_event", 1000, true, false);
}

/** @brief Timer event
 *
 * @param
 * @return
 *
 */

function on_timer_event(component)
{
	if(gui.led.get(test_led))
	{
		gui.led.set(test_led, false);
	}
	else
	{
		gui.led.set(test_led, true);
	}
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
