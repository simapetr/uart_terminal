/**
  ****************************************************************************
  * @file    textctrl.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    29.10.2018
  * @brief   Text control use example
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
var textctrl_id;
var static_text_id;
var read_text_str = "";
 
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
// Add textctrl in to panel
textctrl_id = gui.textctrl.add(panel_sizer, "Test static text", 1, true, true);
// Add static text in to panel
static_text_id = gui.static_text.add(panel_sizer, "", 1, true);
// Wait for text change
delay(1000);
//change text
gui.textctrl.set(textctrl_id, "Static test change 0\n");
// Wait for text change
delay(500);
// Append text
gui.textctrl.append(textctrl_id, "line 1\n");
// Wait for text change
delay(500);
// Show data from text control
read_text_str = "Text control test:\n\n";
read_text_str += "Line 0:\n";
read_text_str += gui.textctrl.get(textctrl_id, 0);
read_text_str += "\n\nLine 1:\n";
read_text_str += gui.textctrl.get(textctrl_id, 1);
read_text_str += "\n\nAll:\n";
read_text_str += gui.textctrl.get(textctrl_id);
gui.static_text.set(static_text_id, read_text_str);


/*****************************************************END OF FILE************/