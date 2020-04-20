/**
  ****************************************************************************
  * @file time.js
  * @author simek
  * @version V1.0
  * @date 19.04.2020
  * @brief system time example
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
var test_static_text = 0;
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
	test_static_text = gui.static_text.add(main_panel_sizer, "", 0, false);
	// Set timer
	main_timer = timer.add("on_timer_event", 100, true, false);
}

/** @brief Timer event
 *
 * @param
 * @return
 *
 */

function on_timer_event(component)
{
var time_str = "";
	
	time_str += "Local : ";
	time_str += time.local_str(time.now());
	time_str += "\nUTC   : ";
	time_str += time.str(time.now());
	time_str += "\nSEC   : ";
	time_str += time.now();
	time_str += "\nmSEC  : ";
	time_str += time.now_ms();
	gui.static_text.set(test_static_text, time_str);
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
