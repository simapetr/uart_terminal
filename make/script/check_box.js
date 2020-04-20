/**
  ****************************************************************************
  * @file check_box.js
  * @author simek
  * @version V1.0
  * @date 15.04.2020
  * @brief Check box use example
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
var test_check_box = 0;
var test_button = 0;

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
	main_frame.console_rx_enable(false);
	main_frame.clear();
	main_frame.printf("GUI test :\n");
	// Show gui frame
	gui(true);
	// Create new AUI panel
	main_panel = gui.panel.add("test_panel", true);
	// Add basic sizer in to panel
	main_panel_sizer = gui.panel.get_sizer(main_panel);
	// Add check box in to panel
	test_check_box = gui.check_box.add(main_panel_sizer, "test", 0, false,false);
	// Register button event
	gui.check_box.reg_event(test_check_box, "on_check_box_click");
	// Add button in to panel
	test_button = gui.button.add(main_panel_sizer, "toggle", 0, false);
	// Register button event
	gui.button.reg_event(test_button, "on_button_click"); 
}

/** @brief Check box event
 *
 * @param component : Clicked check box
 * @return void
 *
 */
 
function on_check_box_click (component)
{
	alert("You clicked on check box.");
}

/** @brief Button event
 *
 * @param component_id : Clicked button
 * @return void
 *
 */
 
function on_button_click (component)
{
	if (gui.check_box.get(test_check_box))
	{
		gui.check_box.set(test_check_box, false);
	}
	else
	{
		gui.check_box.set(test_check_box, true);
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
