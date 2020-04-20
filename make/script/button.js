/**
  ****************************************************************************
  * @file button.js
  * @author simek
  * @version V1.0
  * @date 15.04.2020
  * @brief Button use example 
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
	main_frame.console_rx_enable(false);
	main_frame.clear();
	main_frame.printf("GUI test :\n");
	// Show gui frame
	gui(true);
	// Create new AUI panel
	main_panel = gui.panel.add("test_panel", true);
	// Add basic sizer in to panel
	main_panel_sizer = gui.panel.get_sizer(main_panel);
	// Add button in to panel
	demo_button = gui.button.add(main_panel_sizer, "test", 0, false);
	// Register button event
	gui.button.reg_event(demo_button, "on_button_click"); 
}

/** @brief Button click event
 *
 * @param component : Clicked button
 * @return
 *
 */
 
function on_button_click(component)
{
	alert("You clicked on button.");
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
