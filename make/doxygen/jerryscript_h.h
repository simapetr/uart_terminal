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
         * @return
         *
         */

        gui(show_b);

        /** @brief Set show Rx data in main frame console
         *
         * @code
         * main_frame.console_rx_enable(false);
         * @endcode
         *
         * @param [IN] enable_b : Show Rx data in console
         *   @arg false : Hide
         *   @arg true : Show
         * @return
         *
         */

        console_rx_enable(enable_b);

        /** @brief Get console enable state
         *
         * @code
         * var state_var;
         * state_var = main_frame.is_console_rx_enable();
         * @endcode
         *
         * @param
         * @return Console enable state
         *   @arg false : Disable
         *   @arg true : Enable
         *
         */

        is_console_rx_enable();

        /** @brief Print text sting in to console
         *
         * @code
         * main_frame.printf("Hello world!");
         * @endcode
         *
         * @param [IN] text_str : Print text
         * @return
         *
         */

        printf(text_str);

        /** @brief Print status text sting in to main frame status
         *
         * @code
         * main_frame.status("Hello world!");
         * @endcode
         *
         * @param [IN] text_str : Print text
         * @return
         *
         */

        status(text_str);

        /** @brief Clear main frame console text
         *
         * @code
         * main_frame.clear();
         * @endcode
         *
         * @param
         * @return
         *
         */

        clear();

        /** @brief Open communication and GUI component in main frame
         *
         * @code
         * main_frame.open();
         * @endcode
         *
         * @param
         * @return
         *
         */

        open();

        /** @brief Open and set port communication and GUI component in main frame
         *
         * @code
         * main_frame.open(1,57600,0,0,8,4);
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
         *   @arg 0 : Get number from main frame port setting
         * @return
         *
         */

        open(bite_timeout_d, baudrate_d, stop_bits_d, parity_d, bit_length_d, port_num_d);

        /** @brief Close communication in main frame
         *
         * @code
         * main_frame.close();
         * @endcode
         *
         * @param
         * @return
         *
         */

        close();

        /** @brief Get communication open status
         *
         * @code
         * var state_var;
         * state_var = main_frame.get_open_status();
         * @endcode
         *
         * @param
         * @return communication status
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

        get_open_status();

        /** @brief Show input dialog with user info text and return user input data
         *
         * @code
         * var text_str;
         * text_str = main_frame.get_data("Get input text:");
         * @endcode
         *
         * @param [IN] info_str : User text
         * @return User input text string
         *
         */

        get_data(info_str)

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
         * @return
         *
         */

        set_progress(text_str, progress_d);

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
         * @return registration status
         *   @arg 0 : Registration error
         *   @arg 1 : Registered
         *
         */

        reg_event(event_fct_str);

        /** @brief Set show main frame
         *
         * @code
         * main_frame.hide(true);
         * @endcode
         *
         * @param [IN] enable_b : Show main frame
         *   @arg false : Show
         *   @arg true : Hide
         * @return
         *
         */

        hide(enable_b);

};

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
         * @return Open status (See uart_status_t)
         *
         */

        open(bite_timeout_d, baudrate_d, stop_bits_d, parity_d, bit_length_d, port_num_d);

        /** @brief Close port communication
         *
         * @code
         * uart.close();
         * @endcode
         *
         * @param
         * @return
         *
         */

        close();

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
         * @return Register status
         *
         */

        reg_event(event_name_str);

        /** @brief Write character
         *
         * @code
         * uart.open(1,57600,0,0,8,4);
         * uart.write(0x20);
         * @endcode
         *
         * @param [IN] char_d : Character
         * @return Send status
         *
         */

        write(char_d);

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
         * @return Send status
         *
         */

        write(v_data_d);

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
         * @return Send status
         *
         */

        write(char_str);

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
         * @return Send status
         *
         */

        write(v_data_d, length_d);

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
         * @return Control line logic state
         *
         */

        get_ctrl(name_str);

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
         * @return
         *
         */

        set_ctrl(name_str, state_b);

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
         * @param
         * @return Number of s from (ISO 8601: 1970-01-01T00:00:00Z)
         *
         */

        now();

        /** @brief Get actual time in ms
         *
         * @code
         * var time_var;
         * time_var = time.now_ms();
         * @endcode
         *
         * @param
         * @return Number of ms from (ISO 8601: 1970-01-01T00:00:00Z)
         *
         */

        now_ms();

        /** @brief Get actual UTC time string
         *
         * @code
         * var time_str;
         * time_str = time.str(time.now());
         * @endcode
         *
         * @param [IN] time_d : time ISO 8601
         * @return String time and date (YYYY-MM-DD HH:MM:SS)
         *
         */

        str(time_d);

        /** @brief Get actual system time string
         *
         * @code
         * var time_str;
         * time_str = time.local_str(time.now());
         * @endcode
         *
         * @param [IN] time_d : time ISO 8601
         * @return String time and date (YYYY-MM-DD HH:MM:SS)
         *
         */

        local_str(time_d);

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
         * @return Timer ID
         *
         */

        add(event_str, period_d, start_b, one_shot_b);

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
         * @return
         *
         */

        set(timer_index_d, period_d);

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
         * @return
         *
         */

        start(timer_index_d);

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
         * @return
         *
         */

        stop(timer_index_d);

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
         * @return
         *
         */

        reset(timer_index_d);

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
         * @return Read string
         *
         */

        read(path_str);

        /** @brief Read array from binary file
         *
         * @code
         * var data_array;
         * data_array = file.read("file.bin");
         * @endcode
         *
         * @param [IN] path_str : File path
         * @return Read data array
         *
         */

        read_b(path_str);

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
         * @return Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        write(path_str, v_data_d);

        /** @brief Write text string
         *
         * @code
         * var state_b;
         * state_b = file.write("file.txt", "Hello world!");
         * @endcode
         *
         * @param [IN] path_str : File path
         * @param [IN] data_str : Write data text string
         * @return Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        write(path_str, data_str);

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
         * @return Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        append(path_str, v_data_d);

        /** @brief Append text string
         *
         * @code
         * var state_b;
         * state_b = file.append("file.txt", "Hello world!");
         * @endcode
         *
         * @param [IN] path_str : File path
         * @param [IN] data_str : Write data text string
         * @return Write status
         *   @arg 0 : Write failed
         *   @arg 1 : Write success
         *
         */

        append(path_str, data_str);

};

/**
  * @class project
  * @brief Script project file
  *
  */

class project
{

    public:

        /** @brief Read string from project file
         *
         * @code
         * var data_str;
         * data_str = file.read("JS_DATA/user_text", "Hello World!");
         * @endcode
         *
         * @param [IN] path_str : Variable path
         * @param [IN] default_str : Default data
         * @return Read string
         *
         */

        read(path_str, default_str);

        /** @brief Read value from project file
         *
         * @code
         * var data_var;
         * data_var = file.read("JS_DATA/user_var", 100);
         * @endcode
         *
         * @param [IN] path_str : Variable path
         * @param [IN] default_d : Default data
         * @return Read string
         *
         */

        read(path_str, default_d);

        /** @brief Write string to project file
         *
         * @code
         * file.write("JS_DATA/user_text", "Hello World!");
         * @endcode
         *
         * @param [IN] path_str : Variable path
         * @param [IN] data_str : Data string
         * @return
         *
         */

        write(path_str, data_str);

        /** @brief Write value to project file
         *
         * @code
         * file.write("JS_DATA/user_var", 100);
         * @endcode
         *
         * @param [IN] path_str : Variable path
         * @param [IN] data_d : Data variable
         * @return void
         *
         */

        write(path_str, data_d);

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
         * @return Panel index
         *
         */

        add(name_str, horizontal_b);

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
         * @return
         *
         */

        set(panel_d, show_b);

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
         * @return Show status
         *
         */

        get(panel_d);

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
         * @return Sizer index
         *
         */

        get_sizer(panel_d);

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
         * @return Sizer index
         *
         */

        add(sizer_index_d, proportion_d, horizontal_b);

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
         * @return Button index
         *
         */

        add(sizer_index_d, text_str, proportion_d, expand_b);

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
         * @return Event register status
         *   @arg false : Fail
         *   @arg true : Event registered
         *
         */

        reg_event(button_index_d, event_fct_str);

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
         * @return Check box index
         *
         */

        add(sizer_index_d, text_str, proportion_d, expand_b, state_b);

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
         * @return Event register status
         *   @arg false : Fail
         *   @arg true : Event registered
         *
         */

        reg_event(check_box_index_d, event_fct_str);

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
         * @return Check box state
         *   @arg false : Un-checked
         *   @arg true : Checked
         *
         */

        get(check_box_index_d);

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
         * @return Change status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        set(check_box_index_d, state_b);

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
         * @return textctrl index
         *
         */

        add(sizer_index_d, text_str, proportion_d, expand_b, multiline_b);

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
         * @return Read data
         *
         */

        get(textctrl_index_d, line_d);

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
         * @return Change status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        set(textctrl_index_d, text_str);

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
         * @return Append status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        append(textctrl_index_d, text_str);

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
         * @return static_text index
         *
         */

        add(sizer_index_d, text_str, proportion_d, expand_b);

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
         * @return Set status
         *   @arg false : Fail
         *   @arg true : Changed
         *
         */

        set(static_text_index_d, text_str);

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
         * @return slider index
         *
         */

        add(sizer_index_d, min_d, max_d, proportion_d, expand_b);

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
         * @return Event register status
         *   @arg false : Fail
         *   @arg true : Event registered
         *
         */

        reg_event(slider_index_d, event_fct_str);

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
         * @return Set value
         *
         */

        get(slider_index_d);

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
         * @return
         *
         */

        set(slider_index_d, value_b);

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
         * @return Gauge index
         *
         */

        add(sizer_index_d, proportion_d, expand_b, size_d);

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
         * @return Set value
         *
         */

        get(gauge_index_d);

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
         * @return
         *
         */

        set(gauge_index_d, value_b);

};

/**
  * @class led
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
         * @return LED index
         *
         */

        add(sizer_index_d);

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
         * @return LED buffer index
         *
         */

        add(sizer_index_d, on_color_d, off_color_d)

        /** @brief Get LED value
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
         * @return Set value
         *
         */

        get(led_index_d);

        /** @brief Set led value
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
         * @return Set value
         *
         */

        set(led_index_d, value_b);

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
         * @return graph index
         *
         */

        add(sizer_index_d, name_str, graph_range_d, buffer_length_d, time_step_d);

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
         * @return Signal insert status
         *
         */

        insert_signal(graph_index_d, name_str, color_d, width_d, style_d);

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
         * @return Set status
         *   @arg false : Fail
         *   @arg true : Update
         *
         */

        set(graph_index_d, v_data_d);

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

/**
  * @defgroup Public_function
  * @brief Global public function
  * @{
  */

/** @brief Delay
 *
 * @code
 * // Delay 1s
 * delay(1000);
 * @endcode
 *
 * @param [IN] time_d : Delay time in ms
 * @return
 *
 */

delay(time_d);

/** @brief Get random value
 *
 * @code
 * var random_val = rand();
 * @endcode
 *
 * @param
 * @return Random value
 *
 */

rand();

/** @brief Get random value from range
 *
 * @code
 * var random_val = rand(-10, 10);
 * @endcode
 *
 * @param [IN] min_d : Min value
 * @param [IN] max_d : Max value
 * @return Random value
 *
 */

rand(min_d, max_d);

/** @brief Show alert dialog
 *
 * @code
 * alert("Hello world!");
 * @endcode
 *
 * @param [IN] text_str : Alert text
 * @return
 *
 */

alert(text_str);

/** @brief Set show main frame
 *
 * @code
 * gui(false);
 * @endcode
 *
 * @param [IN] show_main_b : Show main frame
 *   @arg false : Hide
 *   @arg true : Show
 * @return
 *
 */

gui(show_main_b);

/** @brief Set show main frame and Script frame name
 *
 * @code
 * gui(false, "Script frame");
 * @endcode
 *
 * @param [IN] show_main_b : Show main frame
 *   @arg false : Hide
 *   @arg true : Show
 * @param [IN] text_str : Script frame name
 * @return
 *
 */

gui(show_main_b, text_str);

/** @brief Set show main frame and Script frame name
 *
 * @code
 * gui(false, "Script frame", true);
 * @endcode
 *
 * @param [IN] show_main_b : Show main frame
 *   @arg false : Hide
 *   @arg true : Show
 * @param [IN] text_str : Script frame name
 * @param [IN] show_script_b : Show script frame
 *   @arg false : Hide
 *   @arg true : Show
 * @return
 *
 */

gui(show_main_b, text_str, show_script_b);

/** @brief Register exit callback
 *
 * @code
 * reg_exit("exit");
 * function exit()
 * {
 * }
 * @endcode
 *
 * @param [IN] function_str : Callback function
 * @return
 *
 */

reg_exit(function_str);

/**
* @}
*/

/**
  * @defgroup Public_variable
  * @brief Global public variable
  * @{
  */

main_frame main_frame;
uart uart;
time time;
timer timer;
file file;
project project;
gui gui;

/**
* @}
*/

/*****************************************************END OF FILE************/
