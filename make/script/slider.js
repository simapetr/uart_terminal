/**
  ****************************************************************************
  * @file    slider.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    13.09.2018
  * @brief   Slider use example
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
var slider_id;
var graph_id;
var graph_signal = [];
var text_str;
var event_cnt;
 
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
panel_id = gui.panel.add("test_panel", false);
// Add basic sizer in to panel
panel_sizer = gui.panel.get_sizer(panel_id);
// Add slider in to panel
slider_id = gui.slider.add(panel_sizer, -10, 200, 0, true);
// Register slider event
gui.slider.reg_event(slider_id, "on_slider_update");
// Set init value
gui.slider.set(slider_id, 100);
// Add graph
graph_id = gui.graph.add(panel_sizer, "Slider position", 200, 100.0, 1);
// Insert slider position
graph_signal.push(gui.graph.insert_signal(graph_id, "position",0x00000000,1,0));
// Set init data
gui.graph.set_data(graph_id, graph_signal);

event_cnt = 0;

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
 
function on_slider_update (component_id)
{
	graph_signal[0] = gui.slider.get(slider_id);
	gui.graph.set_data(graph_id, graph_signal);
	text_str = "";
	text_str += event_cnt;
	text_str += "value is : ";
	text_str += gui.slider.get(slider_id);
	text_str += "\n";
	main_frame.printf(text_str);
	event_cnt++;
}

/*****************************************************END OF FILE************/