/**
  ****************************************************************************
  * @file graph.js
  * @author simek
  * @version V1.0
  * @date 19.04.2020
  * @brief Graph example
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
var main_slider = 0;
var main_graph = 0;
var main_graph_signal = [];
var system_timer = 0;
var range_static_text = 0;
//var event_cnt;
var range_val = 250;

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
	main_panel = gui.panel.add("Random plot", false);
	// Add basic sizer in to panel
	main_panel_sizer = gui.panel.get_sizer(main_panel);
	// Add slider in to panel
	main_slider = gui.slider.add(main_panel_sizer, 0, 500, 0, true);
	// Register slider event
	gui.slider.reg_event(main_slider, "on_slider_update");
	// Set init value
	gui.slider.set(main_slider, 250);
	// Add random range
	range_static_text = gui.static_text.add(main_panel_sizer, "range : -250 <-> 250", 0, false); 
	// Add graph
	main_graph = gui.graph.add(main_panel_sizer, "Random range", 500, 60.0, 0.1);
	// Insert slider position
	main_graph_signal.push(gui.graph.insert_signal(main_graph, "Random value",0x00000000,2,0));
	// Set init data
	gui.graph.set(main_graph, main_graph_signal);
	// Run main system event counter
	system_timer = timer.add("system_event", 100, true, false); 
}

/** @brief Slider update event
 *
 * @param component_id : ID clicked slider
 * @return void
 *
 */
 
function on_slider_update (component)
{
var text_str = '';

	range_val = gui.slider.get(main_slider);
	// Set serial number
	text_str = "range : -";
	text_str += range_val;
	text_str += " <-> ";
	text_str += range_val;
	gui.static_text.set(range_static_text, text_str); 
}

/** @brief System thread 40 ms
 *
 * @param [IN] component_id : Event timer ID
 * @return void
 *
 */

function system_event(component)
{
	main_graph_signal[0] = rand(-range_val, range_val);
	gui.graph.set(main_graph, main_graph_signal);
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
