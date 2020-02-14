/**
  ****************************************************************************
  * @file    javascript_h.h
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
  * @defgroup JS_Doc
  * @brief JavaScript class documentation
  * @{
  */

/**
  * @defgroup JS_Class
  * @brief JavaScript class
  * @{
  */

/**
  * @defgroup JS_UART
  * @brief UART class definition
  * @{
  */

class uart
{

    public:

        /** @brief Open and set port communication
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
         * @code
         * uart.open(1,57600,0,0,8,4);
         * @endcode
         *
         */

        double open(double bite_timeout_d, double baudrate_d double stop_bits_d double parity_d double bit_length_d double port_num_d);

        /** @brief Close port communication
         *
         * @param void
         * @return void
         * @code
         * uart.close();
         * @endcode
         *
         */

        void close(void);

        /** @brief Register receive event
         *
         * @param [IN] event_name_str : Event function name
         * @return double : Register status
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
         */

        double reg_event(string event_name_str);

        /** @brief Write character
         *
         * @param [IN] char_d : Character
         * @return double : Send status
         * @code
         * uart.open(1,57600,0,0,8,4);
         * uart.write(0x20);
         * @endcode
         *
         */

        double write(double char_d);

        /** @brief Write data array
         *
         * @param [IN] v_data_d : Data array
         * @return double : Send status
         * @code
         * var data_array;
         * uart.open(1,57600,0,0,8,4);
         * data_array.push(0x01);
         * data_array.push(0x02);
         * data_array.push(0x03);
         * uart.write(data_array);
         * @endcode
         *
         */

        double write(vector<double>& v_data_d);

        /** @brief Write ASCI string
         *
         * @param [IN] char_str : Text string
         * @return double : Send status
         * @code
         * var data_str;
         * uart.open(1,57600,0,0,8,4);
         * data_str = "Hello World!";
         * uart.write(data_str);
         * @endcode
         *
         */

        double write(string char_str);

        /** @brief Write data array user size
         *
         * @param [IN] v_data_d : Data array
         * @param [IN] length_d : Number of send data
         * @return double : Send status
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
         */

        double write(vector<double>& v_data_d, double length_d);

        /** @brief Get port control line state
         *
         * @param [IN] name_str : Control line name
         *   @arg RX : Rx line logic state
         *   @arg CTS : Clear to send
         *   @arg DSR : Data set ready
         *   @arg RING : Ring indication
         *   @arg RLSD : Receive line signal detect
         * @return bool : Control line logic state
         * @code
         * var data_bool;
         * uart.open(1,57600,0,0,8,4);
         * data_bool = uart.get_ctrl("CTS");
         * @endcode
         *
         */

        bool get_ctrl(string name_str);

        /** @brief Set port control line state
         *
         * @param [IN] name_str : Control line name
         *   @arg DTR : Data terminal ready
         *   @arg RTS : Request to send
         *   @arg BREAK : Tx line break
         *   @arg XOFF : Transmit OFF
         *   @arg XON : Transmit ON
         * @param [IN] state_b : New logic state
         * @return void
         * @code
         * uart.open(1,57600,0,0,8,4);
         * uart.set_ctrl("DTR");
         * @endcode
         *
         */

        void set_ctrl(string name_str, bool state_b);

};

/**
* @}
*/

/**
  * @defgroup JS_Time
  * @brief System time class definition
  * @{
  */



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
