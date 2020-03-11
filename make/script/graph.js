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
var system_timer = 0;
var range_text = 0;
//var event_cnt;
var range_val = 250;
 
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
panel_id = gui.panel.add("Random plot", false);
// Add basic sizer in to panel
panel_sizer = gui.panel.get_sizer(panel_id);
// Add slider in to panel
slider_id = gui.slider.add(panel_sizer, 0, 500, 0, true);
// Register slider event
gui.slider.reg_event(slider_id, "on_slider_update");
// Set init value
gui.slider.set(slider_id, 250);
// Add random range
range_text = gui.static_text.add(panel_sizer, "range : -250 <-> 250", 0, false); 
// Add graph
graph_id = gui.graph.add(panel_sizer, "Random range", 500, 60.0, 0.1);
// Insert slider position
graph_signal.push(gui.graph.insert_signal(graph_id, "Random value",0x00000000,2,0));
// Set init data
gui.graph.set(graph_id, graph_signal);
// Run main system event counter
system_timer = timer.add("system_event", 100, true, false);


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
var text_str = '';

	range_val = gui.slider.get(slider_id);
	// Set serial number
	text_str = "range : -";
	text_str += range_val;
	text_str += " <-> ";
	text_str += range_val;
	gui.static_text.set(range_text, text_str); 
}

/** @brief System thread 40 ms
 *
 * @param [IN] component_id : Event timer ID
 * @return void
 *
 */

function system_event(component_id)
{
	graph_signal[0] = rand(-range_val, range_val);
	gui.graph.set(graph_id, graph_signal);
}

/*****************************************************END OF FILE************/