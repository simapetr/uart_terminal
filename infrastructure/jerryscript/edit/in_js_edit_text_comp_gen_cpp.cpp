/**
  ****************************************************************************
  * @file    in_js_edit_text_comp_gen_cpp.cpp
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    Apr  6 2020
  * @brief   JerryScript text editor auto competation generated on wxScintilla
  ****************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT PORTTRONIC</center></h2>
  ****************************************************************************
  */

/**
  ****************************************************************************
  * Library
  ****************************************************************************
  */

#include "in_js_edit_text_h.h"

/**
  * @addtogroup Infrastructure
  * @{
  */

/**
  * @defgroup JerryScript
  * @brief JavaScript interpret
  * @{
  */

/**
  * @defgroup Edit_text_gen
  * @brief JavaScript text editor generated autocompetation
  * @{
  */

/**
  ****************************************************************************
  * Source
  ****************************************************************************
  */

/** @brief Initialize autocompetation data generated
 *
 * @param void
 * @return void
 *
 */

void text_edit_c::auto_comp_gen_init(void)
{
autocomp_buffer_t data_autocomp_buffer;

	// Global class
	this->l_class_autocomp_buffer.class_str = wxT("main_frame uart time timer file project gui delay rand alert reg_exit");
	this->l_class_autocomp_buffer.method_str = wxT("main_frame\n0\ruart\n0\rtime\n0\rtimer\n0\rfile\n0\rproject\n0\rgui\n0\rdelay\n1\rrand\n1\ralert\n1\rreg_exit\n1");
	// Add Global class to lexer word list
	this->l_wordlist_3_str = wxT("main_frame uart time timer file project gui delay rand alert reg_exit");
	SetKeyWords(3, this->l_wordlist_3_str.To8BitData().data());
	// delay info
	data_autocomp_buffer.class_str = wxT("delay");
	data_autocomp_buffer.method_str = wxT("delay(time_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Delay\n *\n * @code\n * // Delay 1s\n * delay(1000);\n * @endcode\n *\n * @param [IN] time_d : Delay time in ms\n * @return\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// rand info
	data_autocomp_buffer.class_str = wxT("rand");
	data_autocomp_buffer.method_str = wxT("rand()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get random value\n *\n * @code\n * var random_val = rand();\n * @endcode\n *\n * @param\n * @return Random value\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// rand info
	data_autocomp_buffer.class_str = wxT("rand");
	data_autocomp_buffer.method_str = wxT("rand(min_d, max_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get random value from range\n *\n * @code\n * var random_val = rand(-10, 10);\n * @endcode\n *\n * @param [IN] min_d : Min value\n * @param [IN] max_d : Max value\n * @return Random value\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// alert info
	data_autocomp_buffer.class_str = wxT("alert");
	data_autocomp_buffer.method_str = wxT("alert(text_str, show_b, true)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Show alert dialog\n *\n * @code\n * alert(\"Hello world!\");\n * // Print to shell\n * alert(\"Hello world!\", false);\n * @endcode\n *\n * @param [IN] text_str : Alert text\n * @param [IN] show_b : Show alert box\n *   @arg true : Show alert box\n *   @arg true : Print to shell\n * @return\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui info
	data_autocomp_buffer.class_str = wxT("gui");
	data_autocomp_buffer.method_str = wxT("gui(enable_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set show main frame\n *\n * @code\n * gui(false);\n * @endcode\n *\n * @param [IN] enable_b : Show main frame\n *   @arg false : Hide\n *   @arg true : Show\n * @return\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui info
	data_autocomp_buffer.class_str = wxT("gui");
	data_autocomp_buffer.method_str = wxT("gui(enable_b, text_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set show main frame and Script frame name\n *\n * @code\n * gui(false, \"Script frame\");\n * @endcode\n *\n * @param [IN] enable_b : Show main frame\n *   @arg false : Hide\n *   @arg true : Show\n * @param [IN] text_str : Script frame name\n * @return\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui info
	data_autocomp_buffer.class_str = wxT("gui");
	data_autocomp_buffer.method_str = wxT("gui(enable_b, text_str, enable_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set show main frame and Script frame name\n *\n * @code\n * gui(false, \"Script frame\", true);\n * @endcode\n *\n * @param [IN] enable_b : Show main frame\n *   @arg false : Hide\n *   @arg true : Show\n * @param [IN] text_str : Script frame name\n * @param [IN] enable_b : Show script frame\n *   @arg false : Hide\n *   @arg true : Show\n * @return\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// reg_exit info
	data_autocomp_buffer.class_str = wxT("reg_exit");
	data_autocomp_buffer.method_str = wxT("reg_exit(function_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Register exit callback\n *\n * @code\n * reg_exit(\"exit\");\n * function exit()\n * {\n * }\n * @endcode\n *\n * @param [IN] function_str : Callback function\n * @return\n *\n */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame class
	data_autocomp_buffer.class_str = wxT("main_frame");
	data_autocomp_buffer.method_str = wxT("gui\n1\rconsole_rx_enable\n1\ris_console_rx_enable\n1\rprintf\n1\rstatus\n1\rclear\n1\ropen\n1\rclose\n1\rget_open_status\n1\rset_progress\n1\rreg_event\n1\rhide\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame gui info
	data_autocomp_buffer.class_str = wxT("main_frame.gui");
	data_autocomp_buffer.method_str = wxT("gui(show_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set show main frame\n  *\n  * @code\n  * main_frame.gui(false);\n  * @endcode\n  *\n  * @param [IN] show_b : Show frame status\n  *   @arg false : Hide\n  *   @arg true : Show\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame console_rx_enable info
	data_autocomp_buffer.class_str = wxT("main_frame.console_rx_enable");
	data_autocomp_buffer.method_str = wxT("console_rx_enable(enable_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set show Rx data in main frame console\n  *\n  * @code\n  * main_frame.console_rx_enable(false);\n  * @endcode\n  *\n  * @param [IN] enable_b : Show Rx data in console\n  *   @arg false : Hide\n  *   @arg true : Show\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame is_console_rx_enable info
	data_autocomp_buffer.class_str = wxT("main_frame.is_console_rx_enable");
	data_autocomp_buffer.method_str = wxT("is_console_rx_enable()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get console enable state\n  *\n  * @code\n  * var state_var;\n  * state_var = main_frame.is_console_rx_enable();\n  * @endcode\n  *\n  * @param\n  * @return Console enable state\n  *   @arg false : Disable\n  *   @arg true : Enable\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame printf info
	data_autocomp_buffer.class_str = wxT("main_frame.printf");
	data_autocomp_buffer.method_str = wxT("printf(text_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Print text sting in to console\n  *\n  * @code\n  * main_frame.printf(\"Hello world!\");\n  * @endcode\n  *\n  * @param [IN] text_str : Print text\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame status info
	data_autocomp_buffer.class_str = wxT("main_frame.status");
	data_autocomp_buffer.method_str = wxT("status(text_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Print status text sting in to main frame status\n  *\n  * @code\n  * main_frame.status(\"Hello world!\");\n  * @endcode\n  *\n  * @param [IN] text_str : Print text\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame clear info
	data_autocomp_buffer.class_str = wxT("main_frame.clear");
	data_autocomp_buffer.method_str = wxT("clear()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Clear main frame console text\n  *\n  * @code\n  * main_frame.clear();\n  * @endcode\n  *\n  * @param\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame open info
	data_autocomp_buffer.class_str = wxT("main_frame.open");
	data_autocomp_buffer.method_str = wxT("open()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Open communication and GUI component in main frame\n  *\n  * @code\n  * main_frame.open();\n  * @endcode\n  *\n  * @param\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame open info
	data_autocomp_buffer.class_str = wxT("main_frame.open");
	data_autocomp_buffer.method_str = wxT("open(bite_timeout_d, baudrate_d, stop_bits_d, parity_d, bit_length_d, port_num_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Open and set port communication and GUI component in main frame\n  *\n  * @code\n  * uart.open(1,57600,0,0,8,4);\n  * @endcode\n  *\n  * @param [IN] bite_timeout_d : Packet timeout\n  * @param [IN] baudrate_d : Communication speed\n  * @param [IN] stop_bits_d : Number of character stop bits\n  *   @arg 0 : 1\n  *   @arg 1 : 1,5\n  *   @arg 2 : 2\n  * @param [IN] parity_d : Character parity type\n  *   @arg 0 : None\n  *   @arg 1 : Odd\n  *   @arg 2 : Even\n  *   @arg 3 : Char\n  *   @arg 4 : Space\n  * @param [IN] bit_length_d : Character bit length\n  * @param [IN] port_num_d : Port number\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame close info
	data_autocomp_buffer.class_str = wxT("main_frame.close");
	data_autocomp_buffer.method_str = wxT("close()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Close communication in main frame\n  *\n  * @code\n  * main_frame.close();\n  * @endcode\n  *\n  * @param\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame get_open_status info
	data_autocomp_buffer.class_str = wxT("main_frame.get_open_status");
	data_autocomp_buffer.method_str = wxT("get_open_status()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get communication open status\n  *\n  * @code\n  * var state_var;\n  * state_var = main_frame.get_open_status();\n  * @endcode\n  *\n  * @param\n  * @return communication status\n  *   @arg 0 : Open error\n  *   @arg 1 : Open\n  *   @arg 2 : Handle error\n  *   @arg 3 : Write configuration error\n  *   @arg 4 : Write timeout error\n  *   @arg 5 : Close error\n  *   @arg 6 : Close\n  *   @arg 7 : Opened\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame set_progress info
	data_autocomp_buffer.class_str = wxT("main_frame.set_progress");
	data_autocomp_buffer.method_str = wxT("set_progress(text_str, progress_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set status progress in progress dialog\n  *\n  * @code\n  * // Show 50% progress\n  * main_frame.set_progress(\"User process progress:\", 50);\n  * // Close dialog\n  * main_frame.set_progress(\"User process progress:\", 101);\n  * @endcode\n  *\n  * @param [IN] text_str : User text\n  * @param [IN] progress_d : actual progress\n  *   @arg 0 - 100 : Show progress value\n  *   @arg >100 : Close progress dialog\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame reg_event info
	data_autocomp_buffer.class_str = wxT("main_frame.reg_event");
	data_autocomp_buffer.method_str = wxT("reg_event(event_fct_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Register event on send button click (in event function is parameter array with console input data)\n  *\n  * @code\n  * main_frame.reg_event(\"on_send_click\");\n  * function on_send_click(data_array)\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] event_fct_str : Print text\n  * @return registration status\n  *   @arg 0 : Registration error\n  *   @arg 1 : Registered\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// main_frame hide info
	data_autocomp_buffer.class_str = wxT("main_frame.hide");
	data_autocomp_buffer.method_str = wxT("hide(enable_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set show main frame\n  *\n  * @code\n  * main_frame.hide(true);\n  * @endcode\n  *\n  * @param [IN] enable_b : Show main frame\n  *   @arg false : Show\n  *   @arg true : Hide\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart class
	data_autocomp_buffer.class_str = wxT("uart");
	data_autocomp_buffer.method_str = wxT("open\n1\rclose\n1\rreg_event\n1\rwrite\n1\rget_ctrl\n1\rset_ctrl\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart open info
	data_autocomp_buffer.class_str = wxT("uart.open");
	data_autocomp_buffer.method_str = wxT("open(bite_timeout_d, baudrate_d, stop_bits_d, parity_d, bit_length_d, port_num_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Open and set port communication\n  *\n  * @code\n  * uart.open(1,57600,0,0,8,4);\n  * @endcode\n  *\n  * @param [IN] bite_timeout_d : Packet timeout\n  * @param [IN] baudrate_d : Communication speed\n  * @param [IN] stop_bits_d : Number of character stop bits\n  *   @arg 0 : 1\n  *   @arg 1 : 1,5\n  *   @arg 2 : 2\n  * @param [IN] parity_d : Character parity type\n  *   @arg 0 : None\n  *   @arg 1 : Odd\n  *   @arg 2 : Even\n  *   @arg 3 : Char\n  *   @arg 4 : Space\n  * @param [IN] bit_length_d : Character bit length\n  * @param [IN] port_num_d : Port number\n  * @return Open status (See uart_status_t)\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart close info
	data_autocomp_buffer.class_str = wxT("uart.close");
	data_autocomp_buffer.method_str = wxT("close()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Close port communication\n  *\n  * @code\n  * uart.close();\n  * @endcode\n  *\n  * @param\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart reg_event info
	data_autocomp_buffer.class_str = wxT("uart.reg_event");
	data_autocomp_buffer.method_str = wxT("reg_event(event_name_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Register receive event\n  *\n  * @code\n  * uart.open(1,57600,0,0,8,4);\n  * uart.reg_event(\"rx_data\");\n  * function rx_data ( event_var, data_var )\n  * {\n  *     // Check if data event\n  *     if (event_var & 0x1)\n  *     {\n  *         if (data_var.length)\n  *         {\n  *             // Process data\n  *         }\n  *     }\n  * }\n  * @endcode\n  *\n  * @param [IN] event_name_str : Event function name\n  * @return Register status\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart write info
	data_autocomp_buffer.class_str = wxT("uart.write");
	data_autocomp_buffer.method_str = wxT("write(char_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write character\n  *\n  * @code\n  * uart.open(1,57600,0,0,8,4);\n  * uart.write(0x20);\n  * @endcode\n  *\n  * @param [IN] char_d : Character\n  * @return Send status\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart write info
	data_autocomp_buffer.class_str = wxT("uart.write");
	data_autocomp_buffer.method_str = wxT("write(v_data_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write data array\n  *\n  * @code\n  * var data_array;\n  * uart.open(1,57600,0,0,8,4);\n  * data_array.push(0x01);\n  * data_array.push(0x02);\n  * data_array.push(0x03);\n  * uart.write(data_array);\n  * @endcode\n  *\n  * @param [IN] v_data_d : Data array\n  * @return Send status\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart write info
	data_autocomp_buffer.class_str = wxT("uart.write");
	data_autocomp_buffer.method_str = wxT("write(char_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write ASCI string\n  *\n  * @code\n  * var data_str;\n  * uart.open(1,57600,0,0,8,4);\n  * data_str = \"Hello World!\";\n  * uart.write(data_str);\n  * @endcode\n  *\n  * @param [IN] char_str : Text string\n  * @return Send status\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart write info
	data_autocomp_buffer.class_str = wxT("uart.write");
	data_autocomp_buffer.method_str = wxT("write(v_data_d, length_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write data array user size\n  *\n  * @code\n  * var data_array;\n  * uart.open(1,57600,0,0,8,4);\n  * data_array.push(0x01);\n  * data_array.push(0x02);\n  * data_array.push(0x03);\n  * // Send only 2 char from array\n  * uart.write(data_array, 2);\n  * @endcode\n  *\n  * @param [IN] v_data_d : Data array\n  * @param [IN] length_d : Number of send data\n  * @return Send status\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart get_ctrl info
	data_autocomp_buffer.class_str = wxT("uart.get_ctrl");
	data_autocomp_buffer.method_str = wxT("get_ctrl(name_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get port control line state\n  *\n  * @code\n  * var data_bool;\n  * uart.open(1,57600,0,0,8,4);\n  * data_bool = uart.get_ctrl(\"CTS\");\n  * @endcode\n  *\n  * @param [IN] name_str : Control line name\n  *   @arg RX : Rx line logic state\n  *   @arg CTS : Clear to send\n  *   @arg DSR : Data set ready\n  *   @arg RING : Ring indication\n  *   @arg RLSD : Receive line signal detect\n  * @return Control line logic state\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// uart set_ctrl info
	data_autocomp_buffer.class_str = wxT("uart.set_ctrl");
	data_autocomp_buffer.method_str = wxT("set_ctrl(name_str, state_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set port control line state\n  *\n  * @code\n  * uart.open(1,57600,0,0,8,4);\n  * uart.set_ctrl(\"DTR\");\n  * @endcode\n  *\n  * @param [IN] name_str : Control line name\n  *   @arg DTR : Data terminal ready\n  *   @arg RTS : Request to send\n  *   @arg BREAK : Tx line break\n  *   @arg XOFF : Transmit OFF\n  *   @arg XON : Transmit ON\n  * @param [IN] state_b : New logic state\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// time class
	data_autocomp_buffer.class_str = wxT("time");
	data_autocomp_buffer.method_str = wxT("now\n1\rnow_ms\n1\rstr\n1\rlocal_str\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// time now info
	data_autocomp_buffer.class_str = wxT("time.now");
	data_autocomp_buffer.method_str = wxT("now()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get actual time in s\n  *\n  * @code\n  * var time_var;\n  * time_var = time.now();\n  * @endcode\n  *\n  * @param\n  * @return Number of s from (ISO 8601: 1970-01-01T00:00:00Z)\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// time now_ms info
	data_autocomp_buffer.class_str = wxT("time.now_ms");
	data_autocomp_buffer.method_str = wxT("now_ms()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get actual time in ms\n  *\n  * @code\n  * var time_var;\n  * time_var = time.now_ms();\n  * @endcode\n  *\n  * @param\n  * @return Number of ms from (ISO 8601: 1970-01-01T00:00:00Z)\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// time str info
	data_autocomp_buffer.class_str = wxT("time.str");
	data_autocomp_buffer.method_str = wxT("str()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get actual UTC time string\n  *\n  * @code\n  * var time_str;\n  * time_str = time.str();\n  * @endcode\n  *\n  * @param\n  * @return String time and date (YYYY-MM-DD HH:MM:SS)\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// time local_str info
	data_autocomp_buffer.class_str = wxT("time.local_str");
	data_autocomp_buffer.method_str = wxT("local_str()");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get actual local time string\n  *\n  * @code\n  * var time_str;\n  * time_str = time.local_str();\n  * @endcode\n  *\n  * @param\n  * @return String time and date (YYYY-MM-DD HH:MM:SS)\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// timer class
	data_autocomp_buffer.class_str = wxT("timer");
	data_autocomp_buffer.method_str = wxT("add\n1\rset\n1\rstart\n1\rstop\n1\rreset\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// timer add info
	data_autocomp_buffer.class_str = wxT("timer.add");
	data_autocomp_buffer.method_str = wxT("add(event_str, period_d, start_b, one_shot_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new timer event\n  *\n  * @code\n  * var system_timer;\n  * system_timer = timer.add(\"timer_event\", 10, true, false);\n  * function timer_event()\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] event_str : Event function name\n  * @param [IN] period_d : Time period\n  * @param [IN] start_b :Start timer after add\n  * @param [IN] one_shot_b : Call event only one after overflow\n  * @return Timer ID\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// timer set info
	data_autocomp_buffer.class_str = wxT("timer.set");
	data_autocomp_buffer.method_str = wxT("set(timer_index_d, period_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set timer period\n  *\n  * @code\n  * var system_timer;\n  * system_timer = timer.add(\"timer_event\", 10, true, false);\n  * timer.set(system_timer, 200);\n  * function timer_event()\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] timer_index_d : Timer index\n  * @param [IN] period_d : Time period\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// timer start info
	data_autocomp_buffer.class_str = wxT("timer.start");
	data_autocomp_buffer.method_str = wxT("start(timer_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Start timer\n  *\n  * @code\n  * var system_timer;\n  * system_timer = timer.add(\"timer_event\", 10);\n  * timer.start(system_timer);\n  * function timer_event()\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] timer_index_d : Timer index\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// timer stop info
	data_autocomp_buffer.class_str = wxT("timer.stop");
	data_autocomp_buffer.method_str = wxT("stop(timer_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Stop timer\n  *\n  * @code\n  * var system_timer;\n  * system_timer = timer.add(\"timer_event\", 10, true, false);\n  * timer.stop(system_timer);\n  * function timer_event()\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] timer_index_d : Timer index\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// timer reset info
	data_autocomp_buffer.class_str = wxT("timer.reset");
	data_autocomp_buffer.method_str = wxT("reset(timer_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Reset delay time\n  *\n  * @code\n  * var system_timer;\n  * system_timer = timer.add(\"timer_event\", 10, true, true);\n  * function timer_event()\n  * {\n  *     timer.reset(system_timer);\n  * }\n  * @endcode\n  *\n  * @param [IN] timer_index_d : Timer index\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// file class
	data_autocomp_buffer.class_str = wxT("file");
	data_autocomp_buffer.method_str = wxT("read\n1\rread_b\n1\rwrite\n1\rappend\n1\r");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// file read info
	data_autocomp_buffer.class_str = wxT("file.read");
	data_autocomp_buffer.method_str = wxT("read(path_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Read string from text file\n  *\n  * @code\n  * var state_str;\n  * state_str = file.read(\"file.txt\");\n  * @endcode\n  *\n  * @param [IN] path_str : File path\n  * @return Read string\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// file read_b info
	data_autocomp_buffer.class_str = wxT("file.read_b");
	data_autocomp_buffer.method_str = wxT("read_b(path_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Read array from binary file\n  *\n  * @code\n  * var data_array;\n  * data_array = file.read(\"file.bin\");\n  * @endcode\n  *\n  * @param [IN] path_str : File path\n  * @return Read data array\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// file write info
	data_autocomp_buffer.class_str = wxT("file.write");
	data_autocomp_buffer.method_str = wxT("write(path_str, v_data_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write binary array\n  *\n  * @code\n  * var state_b;\n  * var data_array;\n  * data_array.push(0x01);\n  * data_array.push(0x02);\n  * data_array.push(0x03);\n  * state_b = file.write(\"file.bin\", data_array);\n  * @endcode\n  *\n  * @param [IN] path_str : File path\n  * @param [IN] v_data_d : Write data buffer\n  * @return Write status\n  *   @arg 0 : Write failed\n  *   @arg 1 : Write success\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// file write info
	data_autocomp_buffer.class_str = wxT("file.write");
	data_autocomp_buffer.method_str = wxT("write(path_str, data_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write text string\n  *\n  * @code\n  * var state_b;\n  * state_b = file.write(\"file.txt\", \"Hello world!\");\n  * @endcode\n  *\n  * @param [IN] path_str : File path\n  * @param [IN] data_str : Write data text string\n  * @return Write status\n  *   @arg 0 : Write failed\n  *   @arg 1 : Write success\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// file append info
	data_autocomp_buffer.class_str = wxT("file.append");
	data_autocomp_buffer.method_str = wxT("append(path_str, v_data_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Append binary array\n  *\n  * @code\n  * var state_b;\n  * var data_array;\n  * data_array.push(0x01);\n  * data_array.push(0x02);\n  * data_array.push(0x03);\n  * state_b = file.append(\"file.bin\", data_array);\n  * @endcode\n  *\n  * @param [IN] path_str : File path\n  * @param [IN] v_data_d : Write data buffer\n  * @return Write status\n  *   @arg 0 : Write failed\n  *   @arg 1 : Write success\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// file append info
	data_autocomp_buffer.class_str = wxT("file.append");
	data_autocomp_buffer.method_str = wxT("append(path_str, data_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Append text string\n  *\n  * @code\n  * var state_b;\n  * state_b = file.append(\"file.txt\", \"Hello world!\");\n  * @endcode\n  *\n  * @param [IN] path_str : File path\n  * @param [IN] data_str : Write data text string\n  * @return Write status\n  *   @arg 0 : Write failed\n  *   @arg 1 : Write success\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// project class
	data_autocomp_buffer.class_str = wxT("project");
	data_autocomp_buffer.method_str = wxT("read\n1\rwrite\n1\r");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// project read info
	data_autocomp_buffer.class_str = wxT("project.read");
	data_autocomp_buffer.method_str = wxT("read(path_str, default_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Read string from project file\n  *\n  * @code\n  * var data_str;\n  * data_str = file.read(\"JS_DATA/user_text\", \"Hello World!\");\n  * @endcode\n  *\n  * @param [IN] path_str : Variable path\n  * @param [IN] default_str : Default data\n  * @return Read string\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// project read info
	data_autocomp_buffer.class_str = wxT("project.read");
	data_autocomp_buffer.method_str = wxT("read(path_str, default_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Read value from project file\n  *\n  * @code\n  * var data_var;\n  * data_var = file.read(\"JS_DATA/user_var\", 100);\n  * @endcode\n  *\n  * @param [IN] path_str : Variable path\n  * @param [IN] default_d : Default data\n  * @return Read string\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// project write info
	data_autocomp_buffer.class_str = wxT("project.write");
	data_autocomp_buffer.method_str = wxT("write(path_str, data_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write string to project file\n  *\n  * @code\n  * file.write(\"JS_DATA/user_text\", \"Hello World!\");\n  * @endcode\n  *\n  * @param [IN] path_str : Variable path\n  * @param [IN] data_str : Data string\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// project write info
	data_autocomp_buffer.class_str = wxT("project.write");
	data_autocomp_buffer.method_str = wxT("write(path_str, data_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Write value to project file\n  *\n  * @code\n  * file.write(\"JS_DATA/user_var\", 100);\n  * @endcode\n  *\n  * @param [IN] path_str : Variable path\n  * @param [IN] data_d : Data variable\n  * @return void\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui class
	data_autocomp_buffer.class_str = wxT("gui");
	data_autocomp_buffer.method_str = wxT("panel\n2\rsizer\n2\rbutton\n2\rcheck_box\n2\rtextctrl\n2\rstatic_text\n2\rslider\n2\rgauge\n2\rled\n2\rgraph\n2");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui panel
	data_autocomp_buffer.class_str = wxT("gui.panel");
	data_autocomp_buffer.method_str = wxT("add\n1\rset\n1\rget\n1\rget_sizer\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui panel add info
	data_autocomp_buffer.class_str = wxT("gui.panel.add");
	data_autocomp_buffer.method_str = wxT("add(name_str, horizontal_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new AUI panel\n  *\n  * @code\n  * var test_panel;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * @endcode\n  *\n  * @param [IN] name_str : Panel name\n  * @param [IN] horizontal_b : Basic sizer orientation\n  *   @arg false : Vertical\n  *   @arg true : Horizontal\n  * @return Panel index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui panel set info
	data_autocomp_buffer.class_str = wxT("gui.panel.set");
	data_autocomp_buffer.method_str = wxT("set(panel_d, show_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get panel show status\n  *\n  * @code\n  * var test_panel;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * gui.panel.set(test_panel, false);\n  * @endcode\n  *\n  * @param [IN] panel_d : Panel buffer index\n  * @param [IN] show_b : Panel show status\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui panel get info
	data_autocomp_buffer.class_str = wxT("gui.panel.get");
	data_autocomp_buffer.method_str = wxT("get(panel_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get panel show status\n  *\n  * @code\n  * var test_panel;\n  * var show_status;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * show_status = gui.panel.get(test_panel);\n  * @endcode\n  *\n  * @param [IN] panel_d : Panel buffer index\n  * @return Show status\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui panel get_sizer info
	data_autocomp_buffer.class_str = wxT("gui.panel.get_sizer");
	data_autocomp_buffer.method_str = wxT("get_sizer(panel_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get panel main sizer\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * @endcode\n  *\n  * @param [IN] panel_d : Panel buffer index\n  * @return Sizer index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui sizer
	data_autocomp_buffer.class_str = wxT("gui.sizer");
	data_autocomp_buffer.method_str = wxT("add\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui sizer add info
	data_autocomp_buffer.class_str = wxT("gui.sizer.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, proportion_d, horizontal_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new AUI panel\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var item_sizer;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * item_sizer = gui.sizer.add(test_sizer, 0, true);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] proportion_d : Proportion in parent sizer element\n  * @param [IN] horizontal_b : Sizer orientation\n  *   @arg false : Vertical\n  *   @arg true : Horizontal\n  * @return Sizer index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui button
	data_autocomp_buffer.class_str = wxT("gui.button");
	data_autocomp_buffer.method_str = wxT("add\n1\rreg_event\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui button add info
	data_autocomp_buffer.class_str = wxT("gui.button.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, text_str, proportion_d, expand_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new button\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_button;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_button = gui.button.add(test_sizer, \"test\", 0, false);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] text_str : Button text\n  * @param [IN] proportion_d : Proportion in parent sizer element\n  * @param [IN] expand_b : Expand in sizer flag\n  *   @arg false : Default size\n  *   @arg true : Expand\n  * @return Button index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui button reg_event info
	data_autocomp_buffer.class_str = wxT("gui.button.reg_event");
	data_autocomp_buffer.method_str = wxT("reg_event(button_index_d, event_fct_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Register button event\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_button;\n  * var reg_event_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_button = gui.button.add(test_sizer, \"test\", 0, false);\n  * reg_event_bool = gui.button.reg_event(test_button, \"on_button_click\");\n  * function on_button_click (component_id)\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] button_index_d : Button index\n  * @param [IN] event_fct_str : Function name\n  * @return Event register status\n  *   @arg false : Fail\n  *   @arg true : Event registered\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui check_box
	data_autocomp_buffer.class_str = wxT("gui.check_box");
	data_autocomp_buffer.method_str = wxT("add\n1\rreg_event\n1\rget\n1\rset\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui check_box add info
	data_autocomp_buffer.class_str = wxT("gui.check_box.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, text_str, proportion_d, expand_b, state_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new check box\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_check_box;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_check_box = gui.check_box.add(test_sizer, \"test\", 0, false,false);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] text_str : Button text\n  * @param [IN] proportion_d : Proportion in parent sizer element\n  * @param [IN] expand_b : Expand in sizer flag\n  *   @arg false : Default size\n  *   @arg true : Expand\n  * @param [IN] state_b : Initial state\n  *   @arg false : Un-checked\n  *   @arg true : Checked\n  * @return Check box index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui check_box reg_event info
	data_autocomp_buffer.class_str = wxT("gui.check_box.reg_event");
	data_autocomp_buffer.method_str = wxT("reg_event(check_box_index_d, event_fct_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Register check box event\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_check_box;\n  * var reg_event_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_check_box = gui.check_box.add(test_sizer, \"test\", 0, false,false);\n  * reg_event_bool = gui.check_box.reg_event(test_check_box, \"on_check_box_click\");\n  * function on_check_box_click (component_id)\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] check_box_index_d : Check box index\n  * @param [IN] event_fct_str : Function name\n  * @return Event register status\n  *   @arg false : Fail\n  *   @arg true : Event registered\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui check_box get info
	data_autocomp_buffer.class_str = wxT("gui.check_box.get");
	data_autocomp_buffer.method_str = wxT("get(check_box_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get check box state\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_check_box;\n  * var test_state_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_check_box = gui.check_box.add(test_sizer, \"test\", 0, false,false);\n  * test_state_bool = gui.check_box.get(test_check_box);\n  * @endcode\n  *\n  * @param [IN] check_box_index_d : Check box index\n  * @return Check box state\n  *   @arg false : Un-checked\n  *   @arg true : Checked\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui check_box set info
	data_autocomp_buffer.class_str = wxT("gui.check_box.set");
	data_autocomp_buffer.method_str = wxT("set(check_box_index_d, state_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set check box state\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_check_box;\n  * var test_status_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_check_box = gui.check_box.add(test_sizer, \"test\", 0, false,false);\n  * test_status_bool = gui.check_box.set(test_check_box, true);\n  * @endcode\n  *\n  * @param [IN] check_box_index_d : Check box index\n  * @param [IN] state_b : New check box state\n  *   @arg false : Un-checked\n  *   @arg true : Checked\n  * @return Change status\n  *   @arg false : Fail\n  *   @arg true : Changed\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui textctrl
	data_autocomp_buffer.class_str = wxT("gui.textctrl");
	data_autocomp_buffer.method_str = wxT("add\n1\rget\n1\rset\n1\rappend\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui textctrl add info
	data_autocomp_buffer.class_str = wxT("gui.textctrl.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, text_str, proportion_d, expand_b, multiline_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new text control\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_textctrl;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_textctrl = gui.textctrl.add(test_sizer, \"Hello world!\", 0, false, true);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] text_str : Default text\n  * @param [IN] proportion_d : Proportion in parent sizer element\n  * @param [IN] expand_b : Expand in sizer flag\n  *   @arg false : Default size\n  *   @arg true : Expand\n  * @param [IN] multiline_b : Multiline enable\n  *   @arg false : One line\n  *   @arg true : Multiline\n  * @return textctrl index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui textctrl get info
	data_autocomp_buffer.class_str = wxT("gui.textctrl.get");
	data_autocomp_buffer.method_str = wxT("get(textctrl_index_d, line_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get text control string\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_textctrl;\n  * var text_str;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_textctrl = gui.textctrl.add(test_sizer, \"\", 0, false, true);\n  * text_str = gui.textctrl.get(test_textctrl, 0);\n  * @endcode\n  *\n  * @param [IN] textctrl_index_d : Text control index\n  * @param [IN] line_d : Read line number\n  * @return Read data\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui textctrl set info
	data_autocomp_buffer.class_str = wxT("gui.textctrl.set");
	data_autocomp_buffer.method_str = wxT("set(textctrl_index_d, text_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set text control string\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_textctrl;\n  * var test_status_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_textctrl = gui.textctrl.add(test_sizer, \"\", 0, false, true);\n  * test_status_bool = gui.textctrl.set(test_textctrl, \"Hello world!\");\n  * @endcode\n  *\n  * @param [IN] textctrl_index_d : Text control index\n  * @param [IN] text_str : New text (Erase textctrl before set)\n  * @return Change status\n  *   @arg false : Fail\n  *   @arg true : Changed\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui textctrl append info
	data_autocomp_buffer.class_str = wxT("gui.textctrl.append");
	data_autocomp_buffer.method_str = wxT("append(textctrl_index_d, text_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Append text control string\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_textctrl;\n  * var test_status_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_textctrl = gui.textctrl.add(test_sizer, \"\", 0, false, true);\n  * test_status_bool = gui.textctrl.append(test_textctrl, \"Hello world!\");\n  * @endcode\n  *\n  * @param [IN] textctrl_index_d : Text control index\n  * @param [IN] text_str : New text (Append text at the end)\n  * @return Append status\n  *   @arg false : Fail\n  *   @arg true : Changed\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui static_text
	data_autocomp_buffer.class_str = wxT("gui.static_text");
	data_autocomp_buffer.method_str = wxT("add\n1\rset\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui static_text add info
	data_autocomp_buffer.class_str = wxT("gui.static_text.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, text_str, proportion_d, expand_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new static text\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_static_text;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_static_text = gui.static_text.add(test_sizer, \"Hello world!\", 0, false);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] text_str : Default text\n  * @param [IN] proportion_d : Proportion in parent sizer element\n  * @param [IN] expand_b : Expand in sizer flag\n  *   @arg false : Default size\n  *   @arg true : Expand\n  * @return static_text index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui static_text set info
	data_autocomp_buffer.class_str = wxT("gui.static_text.set");
	data_autocomp_buffer.method_str = wxT("set(static_text_index_d, text_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set static text string\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_static_text;\n  * var test_status_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_static_text = gui.static_text.add(test_sizer, \"Test\", 0, false);\n  * test_status_bool = gui.static_text.set(test_static_text, \"Hello world!\");\n  * @endcode\n  *\n  * @param [IN] static_text_index_d : static_text index\n  * @param [IN] text_str : New text (Erase static_text before set)\n  * @return Set status\n  *   @arg false : Fail\n  *   @arg true : Changed\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui slider
	data_autocomp_buffer.class_str = wxT("gui.slider");
	data_autocomp_buffer.method_str = wxT("add\n1\rreg_event\n1\rget\n1\rset\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui slider add info
	data_autocomp_buffer.class_str = wxT("gui.slider.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, min_d, max_d, proportion_d, expand_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new slider\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_slider;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] min_d : Minimum set value\n  * @param [IN] max_d : Maximum set value\n  * @param [IN] proportion_d : Proportion in parent sizer element\n  * @param [IN] expand_b : Expand in sizer flag\n  *   @arg false : Default size\n  *   @arg true : Expand\n  * @return slider index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui slider reg_event info
	data_autocomp_buffer.class_str = wxT("gui.slider.reg_event");
	data_autocomp_buffer.method_str = wxT("reg_event(slider_index_d, event_fct_str)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Register slider event\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_slider;\n  * var reg_event_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);\n  * reg_event_bool = gui.slider.reg_event(test_slider, \"on_slider_update\");\n  * function on_slider_update (component_id)\n  * {\n  * }\n  * @endcode\n  *\n  * @param [IN] slider_index_d : slider index\n  * @param [IN] event_fct_str : Function name\n  * @return Event register status\n  *   @arg false : Fail\n  *   @arg true : Event registered\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui slider get info
	data_autocomp_buffer.class_str = wxT("gui.slider.get");
	data_autocomp_buffer.method_str = wxT("get(slider_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get slider value\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_slider;\n  * var test_slider_value;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);\n  * test_slider_value = gui.slider.get(test_slider);\n  * @endcode\n  *\n  * @param [IN] slider_index_d : slider index\n  * @return Set value\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui slider set info
	data_autocomp_buffer.class_str = wxT("gui.slider.set");
	data_autocomp_buffer.method_str = wxT("set(slider_index_d, value_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set slider value\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_slider;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);\n  * gui.slider.set(test_slider, 80);\n  * @endcode\n  *\n  * @param [IN] slider_index_d : slider index\n  * @param [IN] value_b : New slider value\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui gauge
	data_autocomp_buffer.class_str = wxT("gui.gauge");
	data_autocomp_buffer.method_str = wxT("add\n1\rget\n1\rset\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui gauge add info
	data_autocomp_buffer.class_str = wxT("gui.gauge.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, proportion_d, expand_b, size_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new gauge\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_gauge;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_gauge = gui.gauge.add(test_sizer, 0, true,1000);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] proportion_d : Proportion in parent sizer element\n  * @param [IN] expand_b : Expand in sizer flag\n  *   @arg false : Default size\n  *   @arg true : Expand\n  * @param [IN] size_d : Gauge size\n  * @return Gauge index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui gauge get info
	data_autocomp_buffer.class_str = wxT("gui.gauge.get");
	data_autocomp_buffer.method_str = wxT("get(gauge_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get gauge value\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_gauge;\n  * var test_gauge_value;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_gauge = gui.gauge.add(test_sizer, 0, true,1000);\n  * test_gauge_value = gui.gauge.get(test_gauge);\n  * @endcode\n  *\n  * @param [IN] gauge_index_d : gauge index\n  * @return Set value\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui gauge set info
	data_autocomp_buffer.class_str = wxT("gui.gauge.set");
	data_autocomp_buffer.method_str = wxT("set(gauge_index_d, value_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set gauge value\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_gauge;\n  * var test_status_bool;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_gauge = gui.gauge.add(test_sizer, 0, true,1000);\n  * test_status_bool = gui.gauge.set(test_gauge, 600);\n  * @endcode\n  *\n  * @param [IN] gauge_index_d : gauge index\n  * @param [IN] value_b : New gauge value\n  * @return\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui led
	data_autocomp_buffer.class_str = wxT("gui.led");
	data_autocomp_buffer.method_str = wxT("add\n1\rget\n1\rset\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui led add info
	data_autocomp_buffer.class_str = wxT("gui.led.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new LED\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_led;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_led = gui.led.add(test_sizer);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @return LED index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui led get info
	data_autocomp_buffer.class_str = wxT("gui.led.get");
	data_autocomp_buffer.method_str = wxT("get(led_index_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get gauge value\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_led;\n  * var state_led_b;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_led = gui.led.add(test_sizer);\n  * state_led_b = gui.led.get(test_led);\n  * @endcode\n  *\n  * @param [IN] led_index_d : LED index\n  * @return Set value\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui led set info
	data_autocomp_buffer.class_str = wxT("gui.led.set");
	data_autocomp_buffer.method_str = wxT("set(gauge_index_d, value_b)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Get gauge value\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_led;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_led = gui.led.add(test_sizer);\n  * gui.led.set(test_led, true);\n  * @endcode\n  *\n  * @param [IN] led_index_d : LED index\n  * @param [IN] value_b : New LED state\n  * @return Set value\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui graph
	data_autocomp_buffer.class_str = wxT("gui.graph");
	data_autocomp_buffer.method_str = wxT("add\n1\rinsert_signal\n1\rset\n1");
	this->lv_data_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui graph add info
	data_autocomp_buffer.class_str = wxT("gui.graph.add");
	data_autocomp_buffer.method_str = wxT("add(sizer_index_d, name_str, graph_range_d, buffer_length_d, time_step_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Add new graph\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_graph;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_graph = gui.graph.add(test_sizer, \"data\", 3000.0, 40.0, 0.1);\n  * @endcode\n  *\n  * @param [IN] sizer_index_d : Parent sizer index\n  * @param [IN] name_str : Graph name\n  * @param [IN] graph_range_d : Range symetrical around 0\n  * @param [IN] buffer_length_d : Sample memory size\n  * @param [IN] time_step_d : Sample time.\n  * @return graph index\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui graph insert_signal info
	data_autocomp_buffer.class_str = wxT("gui.graph.insert_signal");
	data_autocomp_buffer.method_str = wxT("insert_signal(graph_index_d, name_str, color_d, width_d, style_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Insert graph signal\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_graph;\n  * var graph_signal = [];\n  * var insert_state_val;\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_graph = gui.graph.add(test_sizer, \"data\", 3000.0, 40.0, 0.1);\n  * insert_state_val = gui.graph.insert_signal(test_graph, \"signal\",0xff000000,1,0);\n  * graph_signal.push(0);\n  * @endcode\n  *\n  * @param [IN] graph_index_d : graph index\n  * @param [IN] name_str : Signal name\n  * @param [IN] color_d : Signal line color\n  * @param [IN] width_d : Signal line width\n  * @param [IN] style_d : Signal style width\n  *   @arg 0 : Solid\n  *   @arg 1 : Dot\n  *   @arg 2 : Long dash\n  *   @arg 3 : Short dash\n  *   @arg 4 : Dot dash\n  * @return Signal insert status\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);
	// gui graph set info
	data_autocomp_buffer.class_str = wxT("gui.graph.set");
	data_autocomp_buffer.method_str = wxT("set(graph_index_d, v_data_d)");
	data_autocomp_buffer.doc_str = wxT("/** @brief Set graph value\n  *\n  * @code\n  * var test_panel;\n  * var test_sizer;\n  * var test_graph;\n  * var graph_signal = [];\n  * test_panel = gui.panel.add(\"test_panel\", true);\n  * test_sizer = gui.panel.get_sizer(test_panel);\n  * test_graph = gui.graph.add(test_sizer, \"data\", 10.0, 5.0, 1);\n  * graph_signal.push(gui.graph.insert_signal(test_graph, \"signal\",0xff000000,1,0));\n  * graph_signal[0] = 10;\n  * gui.graph.set(test_graph, graph_signal);\n  * graph_signal[0] = 4;\n  * gui.graph.set(test_graph, graph_signal);\n  * graph_signal[0] = -8;\n  * gui.graph.set(test_graph, graph_signal);\n  * graph_signal[0] = 0;\n  * gui.graph.set(test_graph, graph_signal);\n  * @endcode\n  *\n  * @param [IN] graph_index_d : graph index\n  * @param [IN] v_data_d : Signal data array with one sample per signal\n  * @return Set status\n  *   @arg false : Fail\n  *   @arg true : Update\n  *\n  */");
	this->lv_info_autocomp_buffer.push_back(data_autocomp_buffer);

}

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*****************************************************END OF FILE************/

