/**
  ****************************************************************************
  * @file    project.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    18.03.2020
  * @brief   Project use example
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

var main_panel = 0;
var main_panel_sizer = 0;
var set_slider = 0;
var save_button = 0;
var load_button = 0;
var slider_static_text = 0;
var data_textctrl = 0;
var default_text;

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
// Register exit function
reg_exit("exit");
// Create new AUI panel
main_panel = gui.panel.add("test_panel", false);
// Add basic sizer in to panel
main_panel_sizer = gui.panel.get_sizer(main_panel);
// Add slider in to panel
set_slider = gui.slider.add(main_panel_sizer, -10, 200, 0, true);
// Register slider event
gui.slider.reg_event(set_slider, "on_slider_update");
// Set init value
gui.slider.set(set_slider, project.read("JS_DATA/default_pos", 100));
// Add button
save_button = gui.button.add(main_panel_sizer, "Save", 0, false);
gui.button.reg_event(save_button, "on_button_click");
// Add button
load_button = gui.button.add(main_panel_sizer, "Load", 0, false);
gui.button.reg_event(load_button, "on_button_click");
// Add textctrl in to panel
default_text = project.read("JS_DATA/user_text", "Hello World!");
data_textctrl = gui.textctrl.add(main_panel_sizer, default_text, 1, true, false);
// Add show slider value
slider_static_text = gui.static_text.add(main_panel_sizer, "Value : 0", 1, false);
on_slider_update(set_slider);

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Slider update event
 *
 * @param component_id : ID clicked slider
 * @return void
 *
 */

function on_slider_update(component_id)
{
var text_str = "Value : ";

	// Update text
	text_str += gui.slider.get(set_slider);
	gui.static_text.set(slider_static_text, text_str);
}

/** @brief Button event
 *
 * @param component_id : ID clicked button
 * @return void
 *
 */

function on_button_click(component_id)
{
	switch(component_id)
	{
		case save_button:
		{
			project.write("JS_DATA/default_pos", gui.slider.get(set_slider));
			project.write("JS_DATA/user_text", gui.textctrl.get(data_textctrl, 0));
		}
		break;
		case load_button:
		{
			gui.slider.set(set_slider, project.read("JS_DATA/default_pos", 100));
			on_slider_update(set_slider);
			default_text = project.read("JS_DATA/user_text", "Hello World!");
			gui.textctrl.set(data_textctrl, default_text);
		}
		break;
	}
}

/** @brief Exit event
 *
 * @param void
 * @return void
 *
 */

function exit()
{
    project.write("JS_DATA/default_pos", gui.slider.get(set_slider));
    project.write("JS_DATA/user_text", gui.textctrl.get(data_textctrl, 0));
}

/*****************************************************END OF FILE************/
