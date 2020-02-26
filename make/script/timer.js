/**
  ****************************************************************************
  * @file    timer.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    19.02.2020
  * @brief   Timer example
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

var timer_panel = 0;
var timer_panel_sizer = 0;
var test_1_button = 0;
var test_2_button = 0;
var test_3_button = 0;
var reset_button = 0;

var test_1_timer = -1;
var test_2_timer = -1;
var test_3_timer = -1;
var event_1_cnt_var = 0;
var event_2_cnt_var = 0;
var event_3_cnt_var = 0;
 
/**
  ****************************************************************************
  * script
  ****************************************************************************
  */

// Clear console
main_frame.clear();
// Close gui frame
gui(true);
// Create new AUI panel
timer_panel = gui.panel.add("Timer panel", false);
// Add basic sizer in to panel
timer_panel_sizer = gui.panel.get_sizer(timer_panel);
// Add test 1 button
test_1_button = gui.button.add(timer_panel_sizer, "Tmr 1", 0, false);
gui.button.reg_event(test_1_button, "on_test_1_click");
gui.static_text.add(timer_panel_sizer, "Auto start timer", 0, false);
// Add test 2 button
test_2_button = gui.button.add(timer_panel_sizer, "Tmr 2", 0, false);
gui.button.reg_event(test_2_button, "on_test_2_click");
gui.static_text.add(timer_panel_sizer, "Manual start timer", 0, false);
// Add test 3 button
test_3_button = gui.button.add(timer_panel_sizer, "Tmr 3", 0, false);
gui.button.reg_event(test_3_button, "on_test_3_click");
gui.static_text.add(timer_panel_sizer, "One shot timer", 0, false);
// Add reset button
reset_button = gui.button.add(timer_panel_sizer, "Reset", 0, false);
gui.button.reg_event(reset_button, "on_reset_click");
gui.static_text.add(timer_panel_sizer, "Reset all timer", 0, false);
// Add timer 1s
main_frame.printf("Run timer 2\n");
test_2_timer = timer.add("timer_event", 1000);
// Add timer 1s one shot
main_frame.printf("Run timer 3\n");
test_3_timer = timer.add("timer_event", 1000, false, true);

/** @brief On test 1 button click event
 *
 * @param [IN] component_id : Clicked button ID
 * @return void
 *
 */

function on_test_1_click (component_id)
{
	if(test_1_timer == -1)
	{
		// Add timer 1s
		main_frame.printf("Run timer 1\n");
		test_1_timer = timer.add("timer_event", 1000, true, false);
	}
	else
	{
		timer.start(test_1_timer);
	}
}

/** @brief On test 1 button click event
 *
 * @param [IN] component_id : Clicked button ID
 * @return void
 *
 */

function on_test_2_click (component_id)
{
	timer.start(test_2_timer);
}

/** @brief On test 1 button click event
 *
 * @param [IN] component_id : Clicked button ID
 * @return void
 *
 */

function on_test_3_click (component_id)
{
	timer.start(test_3_timer);
}

/** @brief On test 1 button click event
 *
 * @param [IN] component_id : Clicked button ID
 * @return void
 *
 */

function on_reset_click (component_id)
{
	timer.stop(test_1_timer);
	timer.stop(test_2_timer);
	event_1_cnt_var = 0;
	event_2_cnt_var = 0;
	event_3_cnt_var = 0;
}

/** @brief On timer event
 *
 * @param [IN] component_id : Event timer ID
 * @return void
 *
 */

function timer_event (component_id)
{
var text_str;

	if(component_id == test_1_timer)
	{
		text_str = "Tmr1 : ";
		text_str += event_1_cnt_var;
		text_str += "\n";
		main_frame.printf(text_str);
		event_1_cnt_var++;
		if(event_1_cnt_var == 5)
		{
			timer.set(test_1_timer, 2000);
		}
	}
	else if(component_id == test_2_timer)
	{
		text_str = "Tmr2 : ";
		text_str += event_2_cnt_var;
		text_str += "\n";
		main_frame.printf(text_str);
		event_2_cnt_var++;
		if(event_2_cnt_var == 5)
		{
			timer.set(test_2_timer, 2000);
		}
	}
	else if(component_id == test_3_timer)
	{
		text_str = "Tmr3 : ";
		text_str += event_3_cnt_var;
		text_str += "\n";
		main_frame.printf(text_str);
		event_3_cnt_var++;
		if(event_3_cnt_var == 3)
		{
			timer.set(test_3_timer, 200);
		}
	}
	else
	{
	}
}

/*****************************************************END OF FILE************/