/**
  ****************************************************************************
  * @file uart.js
  * @author simek
  * @version V1.0
  * @date 19.04.2020
  * @brief UART use example loopback connect generate 100ms pulse on DTR line
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
var open_status_var = 0;
var dtr_state_b = false;

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
	// Open UART port selected in main frame
	main_frame.open(1,9600,0,0,8,0);
	// Clear main frame console
	main_frame.clear();
	// Get open status
	open_status_var = main_frame.get_open_status();
	// Check open status
	if (open_status_var == 1)
	{
		main_frame.printf("Open\n");
	}
	else if(open_status_var == 7)
	{
		main_frame.printf("Port is open\n");
	}
	else
	{
		status_string = "Open port error : ";
		status_string += open_status_var;
		status_string += "\n";
		main_frame.printf(status_string);
	}
	// Check for port open
	if((open_status_var == 7) || (open_status_var == 1))
	{
		// Reset sensor
		uart.reg_event("read_data");
		// Show gui frame
		gui(true);
		// Create new AUI panel
		main_panel = gui.panel.add("test_panel", true);
		// Add basic sizer in to panel
		main_panel_sizer = gui.panel.get_sizer(main_panel);
		// Create test led
		test_led = gui.led.add(main_panel_sizer);
		// Set timer
		main_timer = timer.add("on_timer_event", 100, true, false); 
	}
}

/** @brief UART event
 *
 * @param [IN] event_var : Event type
 * @param [IN] data_var : Data array
 * @return
 *
 */

function read_data(event_var, data_var)
{
	if(event_var & 0x1)
	{
		if((data_var.length == 1) && (data_var[0] == 0x55))
		{
			gui.led.set(test_led, true);
		}
		else
		{
			gui.led.set(test_led, false);
		}
	}
}

/** @brief Timer event
 *
 * @param
 * @return
 *
 */

function on_timer_event(component)
{
	if(dtr_state_b)
	{
		dtr_state_b = false;
	}
	else
	{
		dtr_state_b = true;
	}
	uart.set_ctrl("DTR", dtr_state_b);
} 

/** @brief Exit event
 *
 * @param
 * @return
 *
 */

function exit()
{
	main_frame.close();
}

/*****************************************************END OF FILE************/
