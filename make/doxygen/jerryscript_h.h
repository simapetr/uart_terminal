/**
  ****************************************************************************
  * @file    jerryscript_h.h
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    05.12.2019
  * @brief   JerryScript class documentation
  ****************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT PORTTRONIC</center></h2>
  ****************************************************************************
  */

/**
  * @mainpage JerryScript documentation
  *
  * <h1><b>Introduction</b></h1>
  *
  * Documentation user interface for JerryScript interpreter <br>
  * The documented interface is implemented here :<br>
  * https://github.com/simapetr/uart_terminal/tree/master/infrastructure/jerryscript
  *
  * <h2>Supported function:</h2>
  *
  * - Control main frame GUI
  * - Read system time
  * - Event timer
  * - Read/Write file
  * - UART communication
  * - Create AUI panel and use selected wxWidget3.0 component
  *
  * <h2>The documentation is based on:</h2>
  *
  * - Jerry script ECMAScript 5.1 (https://github.com/jerryscript-project/jerryscript)
  * - UART terminal (https://github.com/simapetr/uart_terminal)
  *
  * <h2>Supported platforms:</h2>
  *
  * - Windows 7, 8 and 10.
  *
  * <b>Copyright Notice</b>
  *
  * Copyright (C) PORTTRONIC All rights reserved.
  *
  */

/**
  * @defgroup System_object
  * @brief Basic system object
  * @{
  */

/**
  * @class main_frame
  * @brief System Main frame GUI control
  *
  */

class main_frame
{

    public:

        /** @brief Set show main frame
         *
         * @code
         * main_frame.gui(false);
         * @endcode
         *
         * @param [IN] show_b : Show frame status
         *   @arg false : Hide
         *   @arg true : Show
         * @return void
         *
         */

        void gui(bool show_b);

        /** @brief Set show Rx data in main frame console
         *
         * @code
         * main_frame.console_rx_enable(false);
         * @endcode
         *
         * @param [IN] enable_b : Show Rx data in console
         *   @arg false : Hide
         *   @arg true : Show
         * @return void
         *
         */

        void console_rx_enable(bool enable_b);

        /** @brief Get console enable state
         *
         * @code
         * var state_var;
         * state_var = main_frame.is_console_rx_enable();
         * @endcode
         *
         * @param void
         * @return bool : Console enable state
         *   @arg false : Disable
         *   @arg true : Enable
         *
         */

        bool is_console_rx_enable(void);

        /** @brief Print text sting in to console
         *
         * @code
         * main_frame.printf("Hello world!");
         * @endcode
         *
         * @param [IN] text_str : Print text
         * @return void
         *
         */

        void printf(string text_str);

        /** @brief Print status text sting in to main frame status
         *
         * @code
         * main_frame.status("Hello world!");
         * @endcode
         *
         * @param [IN] text_str : Print text
         * @return void
         *
         */

        void status(string text_str);

        /** @brief Clear main frame console text
         *
         * @code
         * main_frame.clear();
         * @endcode
         *
         * @param void
         * @return void
         *
         */

        void clear(void);

        /** @brief Open and set port communication and GUI component in main frame
         *
         * @code
         * uart.open(1,57600,0,0,8,4);
         * @endcode
         *
         * @param [IN] bite_timeout_d : Packet timeout
         * @param [IN] baudrate_d : Communication speed
         * @param [IN] stop_bits_d : Number of character stop bits
         *   @arg 0 : 1
         *   @arg 1 : 1,5
         *   @arg 2 : 2
         * @param [IN] parity_d : Character parity type
         *   @arg 0 : None
         *   @arg 1 : Odd
         *   @arg 2 : Even
         *   @arg 3 : Char
         *   @arg 4 : Space
         * @param [IN] bit_length_d : Character bit length
         * @param [IN] port_num_d : Port number
         * @return void
         *
         */

        void open(double bite_timeout_d, double baudrate_d double stop_bits_d double parity_d double bit_length_d double port_num_d);

        /** @brief Close communication in main frame
         *
         * @code
         * main_frame.close();
         * @endcode
         *
         * @param void
         * @return void
         *
         */

        void close(void);

        /** @brief Get communication open status
         *
         * @code
         * var state_var;
         * state_var = main_frame.get_open_status();
         * @endcode
         *
         * @param void
         * @return double : communication status
         *   @arg 0 : Open error
         *   @arg 1 : Open
         *   @arg 2 : Handle error
         *   @arg 3 : Write configuration error
         *   @arg 4 : Write timeout error
         *   @arg 5 : Close error
         *   @arg 6 : Close
         *   @arg 7 : Opened
         *
         */

        double get_open_status(void);

        /** @brief Show input dialog with user info text and return user input data
         *
         * @code
         * var text_str;
         * text_str = main_frame.get_data("Get input text:");
         * @endcode
         *
         * @param [IN] info_str : User text
         * @return string : User input text
         *
         */

        string get_data(string info_str)

        /** @brief Set status progress in progress dialog
         *
         * @code
         * // Show 50% progress
         * main_frame.set_progress("User process progress:", 50);
         * // Close dialog
         * main_frame.set_progress("User process progress:", 101);
         * @endcode
         *
         * @param [IN] text_str : User text
         * @param [IN] progress_d : actual progress
         *   @arg 0 - 100 : Show progress value
         *   @arg >100 : Close progress dialog
         * @return void
         *
         */

        void set_progress(string text_str, double progress_d);

        /** @brief Register event on send button click (in event function is parameter array with console input data)
         *
         * @code
         * main_frame.reg_event("on_send_click");
         * function on_send_click(data_array)
         * {
         * }
         * @endcode
         *
         * @param [IN] event_fct_str : Print text
         * @return double : registration status
         *   @arg 0 : Registration error
         *   @arg 1 : Registered
         *
         */

        double reg_event(string event_fct_str);

        /** @brief Set show main frame
         *
         * @code
         * main_frame.hide(true);
         * @endcode
         *
         * @param [IN] enable_b : Show main frame
         *   @arg false : Show
         *   @arg true : Hide
         * @return void
         *
         */

        void hide(bool enable_b);

};

/** @brief Delay
 *
 * @code
 * // Delay 1s
 * delay(1000);
 * @endcode
 *
 * @param [IN] time_d : Delay time in ms
 * @return void
 *
 */

void delay(double time_d);

/** @brief Get random value
 *
 * @code
 * var random_val = rand();
 * @endcode
 *
 * @param void
 * @return double : Random value
 *
 */

double rand(void);

/** @brief Get random value from range
 *
 * @code
 * var random_val = rand(-10, 10);
 * @endcode
 *
 * @param [IN] min_d : Min value
 * @param [IN] max_d : Max value
 * @return double : Random value
 *
 */

double rand(double min_d, double max_d);

/** @brief Show alert dialog
 *
 * @code
 * alert("Hello world!");
 * @endcode
 *
 * @param [IN] text_str : Alert text
 * @return void
 *
 */

void alert(string text_str);

/** @brief Set show main frame
 *
 * @code
 * gui(false);
 * @endcode
 *
 * @param [IN] enable_b : Show main frame
 *   @arg false : Hide
 *   @arg true : Show
 * @return void
 *
 */

void gui(bool enable_b);

/** @brief Set show main frame and Script frame name
 *
 * @code
 * gui(false, "Script frame");
 * @endcode
 *
 * @param [IN] enable_b : Show main frame
 *   @arg false : Hide
 *   @arg true : Show
 * @param [IN] text_str : Script frame name
 * @return void
 *
 */

void gui(bool enable_b, string text_str);

/** @brief Set show main frame and Script frame name
 *
 * @code
 * gui(false, "Script frame", true);
 * @endcode
 *
 * @param [IN] enable_b : Show main frame
 *   @arg false : Hide
 *   @arg true : Show
 * @param [IN] text_str : Script frame name
 * @param [IN] enable_b : Show script frame
 *   @arg false : Hide
 *   @arg true : Show
 * @return void
 *
 */

void gui(bool enable_b, string text_str, bool enable_b);

/**
  * @class uart
  * @brief System UART port driver
  *
  */

class uart
{

    public:

        /** @brief Open and set port communication
         *
         * @code
         * uart.open(1,57600,0,0,8,4);
         * @endcode
         *
         * @param [IN] bite_timeout_d : Packet timeout
         * @param [IN] baudrate_d : Communication speed
         * @param [IN] stop_bits_d : Number of character stop bits
         *   @arg 0 : 1
         *   @arg 1 : 1,5
         *   @arg 2 : 2
         * @param [IN] parity_d : Character parity type
         *   @arg 0 : None
         *   @arg 1 : Odd
         *   @arg 2 : Even
         *   @arg 3 : Char
         *   @arg 4 : Space
         * @param [IN] bit_length_d : Character bit length
         * @param [IN] port_num_d : Port number
         * @return double : Open status (See uart_status_t)
         *
         */

        double open(double bite_timeout_d, double baudrate_d double stop_bits_d double parity_d double bit_length_d double port_num_d);

        /** @brief Close port communication
         *
         * @code
         * uart.close();
         * @endcode
         *
         * @param void
         * @return void
         *
         */

        void close(void);

        /** @brief Register receive event
         *
         * @code
         * uart.open(1,57600,0,0,8,4);
         * uart.reg_event("rx_data");
         * function rx_data ( event_var, data_var )
         * {
         *     // Check if data event
         *     if (event_var & 0x1)
         *     {
         *         if (data_var.length)
         *         {
         *             // Process data
         *         }
         *     }
         * }
         * @endcode
         *
         * @param [IN] event_name_str : Event function name
         * @return double : Register status
         *
         */

        double reg_event(string event_name_str);

        /** @brief Write character
         *
         * @code
         * uart.open(1,57600,0,0,8,4);
         * uart.write(0x20);
         * @endcode
         *
         * @param [IN] char_d : Character
         * @return double : Send status
         *
         */

        double write(double char_d);

        /** @brief Write data array
         *
         * @code
         * var data_array;
         * uart.open(1,57600,0,0,8,4);
         * data_array.push(0x01);
         * data_array.push(0x02);
         * data_array.push(0x03);
         * uart.write(data_array);
         * @endcode
         *
         * @param [IN] v_data_d : Data array
         * @return double : Send status
         *
         */

        double write(vector<double>& v_data_d);

        /** @brief Write ASCI string
         *
         * @code
         * var data_str;
         * uart.open(1,57600,0,0,8,4);
         * data_str = "Hello World!";
         * uart.write(data_str);
         * @endcode
         *
         * @param [IN] char_str : Text string
         * @return double : Send status
         *
         */

        double write(string char_str);

        /** @brief Write data array user size
         *
         * @code
         * var data_array;
         * uart.open(1,57600,0,0,8,4);
         * data_array.push(0x01);
         * data_array.push(0x02);
         * data_array.push(0x03);
         * // Send only 2 char from array
         * uart.write(data_array, 2);
         * @endcode
         *
         * @param [IN] v_data_d : Data array
         * @param [IN] length_d : Number of send data
         * @return double : Send status
         *
         */

        double write(vector<double>& v_data_d, double length_d);

        /** @brief Get port control line state
         *
         * @code
         * var data_bool;
         * uart.open(1,57600,0,0,8,4);
         * data_bool = uart.get_ctrl("CTS");
         * @endcode
         *
         * @param [IN] name_str : Control line name
         *   @arg RX : Rx line logic state
         *   @arg CTS : Clear to send
         *   @arg DSR : Data set ready
         *   @arg RING : Ring indication
         *   @arg RLSD : Receive line signal detect
         * @return bool : Control line logic state
         *
         */

        bool get_ctrl(string name_str);

        /** @brief Set port control line state
         *
         * @code
         * uart.open(1,57600,0,0,8,4);
         * uart.set_ctrl("DTR");
         * @endcode
         *
         * @param [IN] name_str : Control line name
         *   @arg DTR : Data terminal ready
         *   @arg RTS : Request to send
         *   @arg BREAK : Tx line break
         *   @arg XOFF : Transmit OFF
         *   @arg XON : Transmit ON
         * @param [IN] state_b : New logic state
         * @return void
         *
         */

        void set_ctrl(string name_str, bool state_b);

};

/**
  * @class time
  * @brief System time interface
  *
  */

class time
{

    public:

        /** @brief Get actual time in s
         *
         * @code
         * var time_var;
         * time_var = time.now();
         * @endcode
         *
         * @param void
         * @return double : Number of s from (ISO 8601: 1970-01-01T00:00:00Z)
         *
         */

        double now(void);

        /** @brief Get actual time in ms
         *
         * @code
         * var time_var;
         * time_var = time.now_ms();
         * @endcode
         *
         * @param void
         * @return double : Number of ms from (ISO 8601: 1970-01-01T00:00:00Z)
         *
         */

        double now_ms(void);

        /** @brief Get actual UTC time string
         *
         * @code
         * var time_str;
         * time_str = time.str();
         * @endcode
         *
         * @param void
         * @return string : Time and date (YYYY-MM-DD HH:MM:SS)
         *
         */

        string str(void);

        /** @brief Get actual local time string
         *
         * @code
         * var time_str;
         * time_str = time.local_str();
         * @endcode
         *
         * @param void
         * @return string : Time and date (YYYY-MM-DD HH:MM:SS)
         *
         */

        string local_str(void);

};

/**
  * @class timer
  * @brief Event timer
  *
  */

class timer
{

    public:

        /** @brief Add new timer event
         *
         * @code
         * var system_timer;
         * system_timer = timer.add("timer_event", 10, true, false);
         * function timer_event()
         * {
         * }
         * @endcode
         *
         * @param [IN] event_str : Event function name
         * @param [IN] period_d : Time period
         * @param [IN] start_b :Start timer after add
         * @param [IN] one_shot_b : Call event only one after overflow
         * @return double : Timer ID
         *
         */

        double add(string event_str, double period_d, bool start_b, bool one_shot_b);

        /** @brief Set timer period
         *
         * @code
         * var system_timer;
         * system_timer = timer.add("timer_event", 10, true, false);
         * timer.set(system_timer, 200);
         * function timer_event()
         * {
         * }
         * @endcode
         *
         * @param [IN] timer_index_d : Timer index
         * @param [IN] period_d : Time period
         * @return void
         *
         */

        void set(double timer_index_d, double period_d);

        /** @brief Start timer
         *
         * @code
         * var system_timer;
         * system_timer = timer.add("timer_event", 10);
         * timer.start(system_timer);
         * function timer_event()
         * {
         * }
         * @endcode
         *
         * @param [IN] timer_index_d : Timer index
         * @return void
         *
         */

        void start(double timer_index_d);

        /** @brief Stop timer
         *
         * @code
         * var system_timer;
         * system_timer = timer.add("timer_event", 10, true, false);
         * timer.stop(system_timer);
         * function timer_event()
         * {
         * }
         * @endcode
         *
         * @param [IN] timer_index_d : Timer index
         * @return void
         *
         */

        void stop(double timer_index_d);

        /** @brief Reset delay time
         *
         * @code
         * var system_timer;
         * system_timer = timer.add("timer_event", 10, true, true);
         * function timer_event()
         * {
         *     timer.reset(system_timer);
         * }
         * @endcode
         *
         * @param [IN] timer_index_d : Timer index
         * @return void
         *
         */

        void reset(double timer_index_d);

};

/**
  * @class file
  * @brief System file read/write
  *
  */

class file
{

    public:

        /** @brief Read string from text file
         *
         * @code
         * var state_str;
         * state_str = file.read("file.txt");
         * @endcode
         *
         * @param [IN] path_str : File path
         * @return string : Read string
         *
         */

        string read(string path_str);

        /** @brief Read array from binary file
         *
         * @code
         * var data_array;
         * data_array = file.read("file.bin");
         * @endcode
         *
         * @param [IN] path_str : File path
         * @return string : Read string
         *
         */

        vector<double>& read_b(string path_str);

        /** @brief Write binary array
         *
         * @code
         * var state_b;
         * var data_array;
         * data_array.push(0x01);
         * data_array.push(0x02);
         * data_array.push(0x03);
         * state_b = file.write("file.bin", data_array);
         * @endcode
         *
         * @param [IN] path_str : File path
         * @param [IN] v_data_d : Write data buffer
         * @return bool : Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        bool write(string path_str, vector<double>& v_data_d);

        /** @brief Write text string
         *
         * @code
         * var state_b;
         * state_b = file.write("file.txt", "Hello world!");
         * @endcode
         *
         * @param [IN] path_str : File path
         * @param [IN] data_str : Write data text string
         * @return bool : Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        bool write(string path_str, string data_str);

        /** @brief Append binary array
         *
         * @code
         * var state_b;
         * var data_array;
         * data_array.push(0x01);
         * data_array.push(0x02);
         * data_array.push(0x03);
         * state_b = file.append("file.bin", data_array);
         * @endcode
         *
         * @param [IN] path_str : File path
         * @param [IN] v_data_d : Write data buffer
         * @return bool : Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        bool append(string path_str, vector<double>& v_data_d);

        /** @brief Append text string
         *
         * @code
         * var state_b;
         * state_b = file.append("file.txt", "Hello world!");
         * @endcode
         *
         * @param [IN] path_str : File path
         * @param [IN] data_str : Write data text string
         * @return bool : Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        bool append(string path_str, string data_str);

};

/**
* @}
*/

/**
  * @defgroup GUI
  * @brief Main GUI object
  * @{
  */

/**
  * @defgroup GUI_object
  * @brief wxWidget GUI object
  * @{
  */

/**
  * @class panel
  * @brief wxAui panel class
  *
  */

class panel
{

    public:

        /** @brief Add new AUI panel
         *
         * @code
         * var test_panel;
         * test_panel = gui.panel.add("test_panel", true);
         * @endcode
         *
         * @param [IN] name_str : Panel name
         * @param [IN] horizontal_b : Basic sizer orientation
         *   @arg false : Vertical
         *   @arg true : Horizontal
         * @return double : Panel buffer index
         *
         */

        double add(string name_str, bool horizontal_b);

        /** @brief Get panel show status
         *
         * @code
         * var test_panel;
         * test_panel = gui.panel.add("test_panel", true);
         * gui.panel.set(test_panel, false);
         * @endcode
         *
         * @param [IN] panel_d : Panel buffer index
         * @param [IN] show_b : Panel show status
         * @return void
         *
         */

        void set(double panel_d, bool show_b);

        /** @brief Get panel show status
         *
         * @code
         * var test_panel;
         * var show_status;
         * test_panel = gui.panel.add("test_panel", true);
         * show_status = gui.panel.get(test_panel);
         * @endcode
         *
         * @param [IN] panel_d : Panel buffer index
         * @return bool : Show status
         *
         */

        bool get(double panel_d);

        /** @brief Get panel main sizer
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * @endcode
         *
         * @param [IN] panel_d : Panel buffer index
         * @return double : Sizer buffer index
         *
         */

        double get_sizer(double panel_d);

};

/**
  * @class sizer
  * @brief wxSizer class interface
  *
  */

class sizer
{

    public:

        /** @brief Add new AUI panel
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var item_sizer;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * item_sizer = gui.sizer.add(test_sizer, 0, true);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] proportion_d : Proportion in parent sizer element
         * @param [IN] horizontal_b : Sizer orientation
         *   @arg false : Vertical
         *   @arg true : Horizontal
         * @return double : Sizer buffer index
         *
         */

        double add(double sizer_index_d, double proportion_d, bool horizontal_b);

};

/**
  * @class button
  * @brief wxButton class interface
  *
  */

class button
{

    public:

        /** @brief Add new button
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_button;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_button = gui.button.add(test_sizer, "test", 0, false);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] text_str : Button text
         * @param [IN] proportion_d : Proportion in parent sizer element
         * @param [IN] expand_b : Expand in sizer flag
         *   @arg false : Default size
         *   @arg true : Expand
         * @return double : Button buffer index
         *
         */

        double add(double sizer_index_d, string text_str, double proportion_d, bool expand_b);

        /** @brief Register button event
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_button;
         * var reg_event_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_button = gui.button.add(test_sizer, "test", 0, false);
         * reg_event_bool = gui.button.reg_event(test_button, "on_button_click");
         * function on_button_click (component_id)
         * {
         * }
         * @endcode
         *
         * @param [IN] button_index_d : Button index
         * @param [IN] event_fct_str : Function name
         * @return bool : Event register status
         *   @arg false : Fail
         *   @arg true : Event registered
         *
         */

        bool reg_event(double button_index_d, string event_fct_str);

};

/**
  * @class check_box
  * @brief wxCheckBox class interface
  *
  */

class check_box
{

    public:

        /** @brief Add new check box
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_check_box;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_check_box = gui.check_box.add(test_sizer, "test", 0, false,false);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] text_str : Button text
         * @param [IN] proportion_d : Proportion in parent sizer element
         * @param [IN] expand_b : Expand in sizer flag
         *   @arg false : Default size
         *   @arg true : Expand
         * @param [IN] state_b : Initial state
         *   @arg false : Un-checked
         *   @arg true : Checked
         * @return double : Check box buffer index
         *
         */

        double add(double sizer_index_d, string text_str, double proportion_d, bool expand_b, bool state_b);

        /** @brief Register check box event
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_check_box;
         * var reg_event_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_check_box = gui.check_box.add(test_sizer, "test", 0, false,false);
         * reg_event_bool = gui.check_box.reg_event(test_check_box, "on_check_box_click");
         * function on_check_box_click (component_id)
         * {
         * }
         * @endcode
         *
         * @param [IN] check_box_index_d : Check box index
         * @param [IN] event_fct_str : Function name
         * @return bool : Event register status
         *   @arg false : Fail
         *   @arg true : Event registered
         *
         */

        bool reg_event(double check_box_index_d, string event_fct_str);

        /** @brief Get check box state
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_check_box;
         * var test_state_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_check_box = gui.check_box.add(test_sizer, "test", 0, false,false);
         * test_state_bool = gui.check_box.get(test_check_box);
         * @endcode
         *
         * @param [IN] check_box_index_d : Check box index
         * @return bool : Check box state
         *   @arg false : Un-checked
         *   @arg true : Checked
         *
         */

        bool get(double check_box_index_d);

        /** @brief Set check box state
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_check_box;
         * var test_status_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_check_box = gui.check_box.add(test_sizer, "test", 0, false,false);
         * test_status_bool = gui.check_box.set(test_check_box, true);
         * @endcode
         *
         * @param [IN] check_box_index_d : Check box index
         * @param [IN] state_b : New check box state
         *   @arg false : Un-checked
         *   @arg true : Checked
         * @return bool : Change status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        bool set(double check_box_index_d, bool state_b);

};

/**
  * @class textctrl
  * @brief wxTextCtrl class interface
  *
  */

class textctrl
{

    public:

        /** @brief Add new text control
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_textctrl;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_textctrl = gui.textctrl.add(test_sizer, "Hello world!", 0, false, true);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] text_str : Default text
         * @param [IN] proportion_d : Proportion in parent sizer element
         * @param [IN] expand_b : Expand in sizer flag
         *   @arg false : Default size
         *   @arg true : Expand
         * @param [IN] multiline_b : Multiline enable
         *   @arg false : One line
         *   @arg true : Multiline
         * @return double : textctrl buffer index
         *
         */

        double add(double sizer_index_d, wxString text_str, double proportion_d, bool expand_b, bool multiline_b);

        /** @brief Get text control string
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_textctrl;
         * var text_str;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_textctrl = gui.textctrl.add(test_sizer, "", 0, false, true);
         * text_str = gui.textctrl.get(test_textctrl, 0);
         * @endcode
         *
         * @param [IN] textctrl_index_d : Text control index
         * @param [IN] line_d : Read line number
         * @return string : Read data
         *
         */

        string get(double textctrl_index_d, double line_d);

        /** @brief Set text control string
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_textctrl;
         * var test_status_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_textctrl = gui.textctrl.add(test_sizer, "", 0, false, true);
         * test_status_bool = gui.textctrl.set(test_textctrl, "Hello world!");
         * @endcode
         *
         * @param [IN] textctrl_index_d : Text control index
         * @param [IN] text_str : New text (Erase textctrl before set)
         * @return bool : Change status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        bool set(double textctrl_index_d, string text_str);

        /** @brief Append text control string
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_textctrl;
         * var test_status_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_textctrl = gui.textctrl.add(test_sizer, "", 0, false, true);
         * test_status_bool = gui.textctrl.append(test_textctrl, "Hello world!");
         * @endcode
         *
         * @param [IN] textctrl_index_d : Text control index
         * @param [IN] text_str : New text (Append text at the end)
         * @return bool : Append status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        bool append(double textctrl_index_d, string text_str);

};

/**
  * @class static_text
  * @brief wxStaticText class interface
  *
  */

class static_text
{

    public:

        /** @brief Add new static text
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_static_text;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_static_text = gui.static_text.add(test_sizer, "Hello world!", 0, false);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] text_str : Default text
         * @param [IN] proportion_d : Proportion in parent sizer element
         * @param [IN] expand_b : Expand in sizer flag
         *   @arg false : Default size
         *   @arg true : Expand
         * @return double : static_text buffer index
         *
         */

        double add(double sizer_index_d, wxString text_str, double proportion_d, bool expand_b);

        /** @brief Set static text string
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_static_text;
         * var test_status_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_static_text = gui.static_text.add(test_sizer, "Test", 0, false);
         * test_status_bool = gui.static_text.set(test_static_text, "Hello world!");
         * @endcode
         *
         * @param [IN] static_text_index_d : static_text index
         * @param [IN] text_str : New text (Erase static_text before set)
         * @return bool : Set status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        bool set(double static_text_index_d, string text_str);

};

/**
  * @class slider
  * @brief wxSlider class interface
  *
  */

class slider
{

    public:

        /** @brief Add new slider
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_slider;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] min_d : Minimum set value
         * @param [IN] max_d : Maximum set value
         * @param [IN] proportion_d : Proportion in parent sizer element
         * @param [IN] expand_b : Expand in sizer flag
         *   @arg false : Default size
         *   @arg true : Expand
         * @return double : slider buffer index
         *
         */

        double add(double sizer_index_d, double min_d, double max_d, double proportion_d, bool expand_b);

        /** @brief Register slider event
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_slider;
         * var reg_event_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);
         * reg_event_bool = gui.slider.reg_event(test_slider, "on_slider_update");
         * function on_slider_update (component_id)
         * {
         * }
         * @endcode
         *
         * @param [IN] slider_index_d : slider index
         * @param [IN] event_fct_str : Function name
         * @return bool : Event register status
         *   @arg false : Fail
         *   @arg true : Event registered
         *
         */

        bool reg_event(double slider_index_d, string event_fct_str);

        /** @brief Get slider value
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_slider;
         * var test_slider_value;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);
         * test_slider_value = gui.slider.get(test_slider);
         * @endcode
         *
         * @param [IN] slider_index_d : slider index
         * @return double : Set value
         *
         */

        double get(double slider_index_d);

        /** @brief Set slider value
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_slider;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_slider = gui.slider.add(test_sizer, -10, 200, 0, true);
         * gui.slider.set(test_slider, 80);
         * @endcode
         *
         * @param [IN] slider_index_d : slider index
         * @param [IN] value_b : New slider value
         * @return void
         *
         */

        void set(double slider_index_d, double value_b);

};

/**
  * @class gauge
  * @brief wxGauge class interface
  *
  */

class gauge
{

    public:

        /** @brief Add new gauge
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_gauge;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_gauge = gui.gauge.add(test_sizer, 0, true,1000);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] proportion_d : Proportion in parent sizer element
         * @param [IN] expand_b : Expand in sizer flag
         *   @arg false : Default size
         *   @arg true : Expand
         * @param [IN] size_d : Gauge size
         * @return double : gauge buffer index
         *
         */

        double add(double sizer_index_d, double proportion_d, bool expand_b, double size_d);

        /** @brief Get gauge value
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_gauge;
         * var test_gauge_value;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_gauge = gui.gauge.add(test_sizer, 0, true,1000);
         * test_gauge_value = gui.gauge.get(test_gauge);
         * @endcode
         *
         * @param [IN] gauge_index_d : gauge index
         * @return double : Set value
         *
         */

        double get(double gauge_index_d);

        /** @brief Set gauge value
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_gauge;
         * var test_status_bool;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_gauge = gui.gauge.add(test_sizer, 0, true,1000);
         * test_status_bool = gui.gauge.set(test_gauge, 600);
         * @endcode
         *
         * @param [IN] gauge_index_d : gauge index
         * @param [IN] value_b : New gauge value
         * @return void
         *
         */

        void set(double gauge_index_d, double value_b);

};

/**
  * @class LED
  * @brief wxLed class interface
  *
  */

class led
{

    public:

        /** @brief Add new LED
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_led;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_led = gui.led.add(test_sizer);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @return double : LED buffer index
         *
         */

        double add(double sizer_index_d);

        /** @brief Add new LED with custom state color
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_led;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_led = gui.led.add(test_sizer, 0x0000FFFF, 0x00808080);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] on_color_d : On state LED color
         * @param [IN] off_color_d : On state LED color
         * @return double : LED buffer index
         *
         */

        double add(double sizer_index_d, double on_color_d, double off_color_d)

        /** @brief Get gauge value
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_led;
         * var state_led_b;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_led = gui.led.add(test_sizer);
         * state_led_b = gui.led.get(test_led);
         * @endcode
         *
         * @param [IN] led_index_d : LED index
         * @return bool : Set value
         *
         */

        bool get(double led_index_d);

        /** @brief Get gauge value
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_led;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_led = gui.led.add(test_sizer);
         * gui.led.set(test_led, true);
         * @endcode
         *
         * @param [IN] led_index_d : LED index
         * @param [IN] value_b : New LED state
         * @return bool : Set value
         *
         */

        void set(double gauge_index_d, bool value_b);

};

/**
* @}
*/

/**
  * @defgroup GUI_user_object
  * @brief User GUI object
  * @{
  */

/**
  * @class graph
  * @brief data_plot class interface
  *
  */

class graph
{

    public:

        /** @brief Add new graph
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_graph;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_graph = gui.graph.add(test_sizer, "data", 3000.0, 40.0, 0.1);
         * @endcode
         *
         * @param [IN] sizer_index_d : Parent sizer index
         * @param [IN] name_str : Graph name
         * @param [IN] graph_range_d : Range symetrical around 0
         * @param [IN] buffer_length_d : Sample memory size
         * @param [IN] time_step_d : Sample time.
         * @return double : graph buffer index
         *
         */

        double add(double sizer_index_d, string name_str, double graph_range_d, double buffer_length_d, double time_step_d);

        /** @brief Insert graph signal
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_graph;
         * var graph_signal = [];
         * var insert_state_val;
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_graph = gui.graph.add(test_sizer, "data", 3000.0, 40.0, 0.1);
         * insert_state_val = gui.graph.insert_signal(test_graph, "signal",0xff000000,1,0);
         * graph_signal.push(0);
         * @endcode
         *
         * @param [IN] graph_index_d : graph index
         * @param [IN] name_str : Signal name
         * @param [IN] color_d : Signal line color
         * @param [IN] width_d : Signal line width
         * @param [IN] style_d : Signal style width
         *   @arg 0 : Solid
         *   @arg 1 : Dot
         *   @arg 2 : Long dash
         *   @arg 3 : Short dash
         *   @arg 4 : Dot dash
         * @return double : Signal insert status
         *
         */

        double insert_signal(double graph_index_d, string name_str, double color_d, double width_d, double style_d);

        /** @brief Set graph value
         *
         * @code
         * var test_panel;
         * var test_sizer;
         * var test_graph;
         * var graph_signal = [];
         * test_panel = gui.panel.add("test_panel", true);
         * test_sizer = gui.panel.get_sizer(test_panel);
         * test_graph = gui.graph.add(test_sizer, "data", 10.0, 5.0, 1);
         * graph_signal.push(gui.graph.insert_signal(test_graph, "signal",0xff000000,1,0));
         * graph_signal[0] = 10;
         * gui.graph.set(test_graph, graph_signal);
         * graph_signal[0] = 4;
         * gui.graph.set(test_graph, graph_signal);
         * graph_signal[0] = -8;
         * gui.graph.set(test_graph, graph_signal);
         * graph_signal[0] = 0;
         * gui.graph.set(test_graph, graph_signal);
         * @endcode
         *
         * @param [IN] graph_index_d : graph index
         * @param [IN] v_data_d : Signal data array with one sample per signal
         * @return bool : Set status
         *   @arg false : Fail
         *   @arg true : Update
         *
         */

        bool set(double graph_index_d, vector<double>& v_data_d);

};

/**
* @}
*/

/**
  * @class gui
  * @brief Main JS GUI object
  *
  */

class gui
{

    public:

    panel panel;
    sizer sizer;
    button button;
    check_box check_box;
    textctrl textctrl;
    static_text static_text;
    slider slider;
    gauge gauge;
    led led;
    graph graph;

};

/**
* @}
*/

/*****************************************************END OF FILE************/
