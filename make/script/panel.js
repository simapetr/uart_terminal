/**
  ****************************************************************************
  * @file    panle.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    16.04.2018
  * @brief   Panel create example
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

var panel_0 = 0;
var panel_0_sizer = 0;
var panel_1 = 0;
var panel_1_sizer = 0;
var graph_0;
var graph_0_signal = [];
var graph_1;
var graph_1_signal = [];
var graph_2;
var graph_2_signal = [];
var text_str;
 
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
panel_0 = gui.panel.add("test_panel_0", true);
// Add basic sizer in to panle
panel_0_sizer = gui.panel.get_sizer(panel_0);

// Create new AUI panel
panel_1 = gui.panel.add("test_panel_1", false);
// Add basic sizer in to panle
panel_1_sizer = gui.panel.get_sizer(panel_1);

// Add graph in to panel
graph_0 = gui.graph.add(panel_0_sizer, "data_0", 1000.0, 40.0, 0.1);
graph_1 = gui.graph.add(panel_0_sizer, "data_1", 1000.0, 40.0, 0.1);
graph_2 = gui.graph.add(panel_1_sizer, "data_2", 1000.0, 40.0, 0.1);

// Add signal
graph_0_signal.push(gui.graph.insert_signal(graph_0, "test_1",0x00000000,1,0));
graph_0_signal.push(gui.graph.insert_signal(graph_0, "test_2",0x000000ff,1,0));
gui.graph.set_data(graph_0, graph_0_signal);
// Add signal
graph_1_signal.push(gui.graph.insert_signal(graph_1, "test_3",0x00000000,1,0));
graph_1_signal.push(gui.graph.insert_signal(graph_1, "test_4",0x000000ff,1,0));
gui.graph.set_data(graph_1, graph_1_signal);
// Add signal
graph_2_signal.push(gui.graph.insert_signal(graph_2, "test_5",0x00000000,1,0));
graph_2_signal.push(gui.graph.insert_signal(graph_2, "test_6",0x000000ff,1,0));
gui.graph.set_data(graph_2, graph_2_signal);

// Set data
graph_0_signal[0] = 20.0;
graph_0_signal[1] = 100.0;
gui.graph.set_data(graph_0, graph_0_signal);
delay(500);
graph_0_signal[0] = 80.0;
graph_0_signal[1] = 5.0;
gui.graph.set_data(graph_0, graph_0_signal);
delay(500);
graph_0_signal[0] = 300.0;
graph_0_signal[1] = 90.0;
gui.graph.set_data(graph_0, graph_0_signal);
delay(500);
graph_0_signal[0] = 80.0;
graph_0_signal[1] = 5.0;
gui.graph.set_data(graph_0, graph_0_signal);
delay(500);
graph_0_signal[0] = 10.0;
graph_0_signal[1] = 200.0;
gui.graph.set_data(graph_0, graph_0_signal);



/*****************************************************END OF FILE************/