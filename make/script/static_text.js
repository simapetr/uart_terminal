/**
  ****************************************************************************
  * @file    static_text.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    12.09.2018
  * @brief   Static text use example
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
var static_text_id;
 
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
panel_id = gui.panel.add("test_panel", true);
// Add basic sizer in to panel
panel_sizer = gui.panel.get_sizer(panel_id);
// Add button in to panel
static_text_id = gui.static_text.add(panel_sizer, "Test static text", 0, false);
// Wait for text change
delay(3000);
//change text
gui.static_text.set(static_text_id, "Static test change 0");
// Wait for text change
delay(1000);
//change text
gui.static_text.set(static_text_id, "Static test change 1");
// Wait for text change
delay(1000);
//change text
gui.static_text.set(static_text_id, "Static test change 2");

/*****************************************************END OF FILE************/