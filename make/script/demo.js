/**
  ****************************************************************************
  * @file    demo.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    7.11.2018
  * @brief   Demo GUI application
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
var panel_sizer_id = 0;
var command_sizer_id = 0;
var console_sizer_id = 0;
var command_textctrl_id = 0;
var console_textctrl_id = 0;
var button_id = 0;
var static_text_id = 0;
var open_status;


var graph_motor_signal = [];
var graph_sensor_signal = [];
var graph_sensor_status_signal = [];
 
/**
  ****************************************************************************
  * script
  ****************************************************************************
  */

// Show gui frame
gui(true, "Demo");
// Create new AUI panel
panel_id = gui.panel.add("terminal", false);
// Add basic sizer in to panel
panel_sizer_id = gui.panel.get_sizer(panel_id);

// Create command text controllers
command_sizer_id = gui.sizer.add(panel_sizer_id, 0, true);
// Add static text
static_text_id = gui.static_text.add(command_sizer_id, "Command : ", 0, false);
// Add command textcontrol in to panel
command_textctrl_id = gui.textctrl.add(command_sizer_id, "", 1, true, false);
// Add button in to panel
button_id = gui.button.add(command_sizer_id, "Send", 0, false);
// Register button event
gui.button.reg_event(button_id, "on_button_click");

// Create command text controllers
console_sizer_id = gui.sizer.add(panel_sizer_id, 1, false);
// Add console textcontrol in to panel
console_textctrl_id = gui.textctrl.add(console_sizer_id, "", 1, true, true);

// Open UART port
main_frame.open();
open_status = main_frame.get_open_status();
// Check for port open
if ((open_status === 7) || (open_status === 1))
{
	// Reg UART Rx event
	uart.reg_event("read_data");
	// Enable debug
	delay(200);
}

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */


/** @brief Button event
 *
 * @param component_id : ID clicked button
 * @return void
 *
 */
 
function on_button_click (component_id)
{
var packet_array = [];
var sum_number = 0;

	// Set diagnostic mode
	packet_array.push(0x57);
	packet_array.push(0x02);
	packet_array.push(0x01);
	// Calculate checksum
	sum_number = ((~(packet_array[1] + packet_array[2])) + 1);
	packet_array.push(sum_number);
	packet_array.push(0xf0);
	uart.write(packet_array, 5);
	return;
}

/** @brief UART event
 *
 * @param event_var : Eventy type
 * @param data_var : Data array
 * @return void
 *
 */
 
function read_data ( event_var, data_var )
{
	//if (event_var & 0x1)
	{
		if (data_var.length == 19)
		{
			if (data_var[0] == 0x69)
			{
				sum_number = data_var[1];
				for (data_cnt = 0 ; data_cnt < (data_var[1] - 1) ; data_cnt++)
				{
					sum_number += data_var[data_cnt + 2];
				}
				sum_number = (((~sum_number) + 1) & 0xff);
				if (data_var[(data_var[1] + 1)] == sum_number)
				{
					// Set motor state
					graph_motor_signal[0] = conv_i16((256 * data_var[3]) + data_var[2]);
					graph_motor_signal[1] = conv_i16((256 * data_var[5]) + data_var[4]);
					graph_motor_signal[1] *= 100;
					//gui.graph.set(graph_motor, graph_motor_signal);
					gui.textctrl.append(console_textctrl_id, graph_motor_signal[0].toString());
					gui.textctrl.append(console_textctrl_id, "\n");
					// Set sensor signal
					graph_sensor_signal[0] = conv_i16((256 * data_var[11]) + data_var[10]); //analog lock
					graph_sensor_signal[1] = conv_i16((256 * data_var[13]) + data_var[12]); //analog gest_1
					graph_sensor_signal[2] = conv_i16((256 * data_var[15]) + data_var[14]); //analog gest_2
					graph_sensor_signal[3] = conv_i16((256 * data_var[17]) + data_var[16]); //analog unlock
					//gui.graph.set(graph_sensor, graph_sensor_signal);
					gui.textctrl.append(console_textctrl_id, graph_sensor_signal.toString());
					gui.textctrl.append(console_textctrl_id, "\n");
					// Set sensor state
					graph_sensor_status_signal[0] = (data_var[12] & 0x01); //status gest_1
					graph_sensor_status_signal[1] = (data_var[14] & 0x01); //status gest_2
					graph_sensor_status_signal[2] = (data_var[10] & 0x02); //status lock
					graph_sensor_status_signal[3] = (data_var[16] & 0x02); //status unlock
					//gui.graph.set(graph_sensor_status, graph_sensor_status_signal);
					gui.textctrl.append(console_textctrl_id, graph_sensor_status_signal.toString());
					gui.textctrl.append(console_textctrl_id, "\n");
					
					
					// Show Lock state
					/*if (lock_state != (graph_sensor_signal[0] & 1))
					{
						if((graph_sensor_signal[0] & 1))
						{
							//main_frame.printf("lock");
						}
						else
						{
							//main_frame.printf("ed\n");
						}
					}
					lock_state = (graph_sensor_signal[0] & 1);
					// Show Unlock state
					if (unlock_state != (graph_sensor_signal[3] & 1))
					{
						if((graph_sensor_signal[3] & 1))
						{
							//main_frame.printf("unlock");
						}
						else
						{
							//main_frame.printf("ed\n");
						}
					}
					unlock_state = (graph_sensor_signal[3] & 1);
					
					// Show Gest A
					if (gest_a != (graph_sensor_signal[1] & 2))
					{
						if((graph_sensor_signal[1] & 2))
						{
							//main_frame.printf("->\n");
						}
						else
						{
							//main_frame.printf("\n");
						}
					}
					gest_a = (graph_sensor_signal[1] & 2);
					// Show Gest B
					if (gest_b != (graph_sensor_signal[2] & 2))
					{
						if((graph_sensor_signal[2] & 2))
						{
							//main_frame.printf("<-\n");
						}
						else
						{
							//main_frame.printf("\n");
						}
					}
					gest_b = (graph_sensor_signal[2] & 2);*/
				}
			}
			else
			{
			}
		}
	}
	return;
}

function conv_i16 ( data_ui16_var )
{
	if (data_ui16_var & 0x8000)
	{
		data_ui16_var = 0 - (0x10000 - data_ui16_var);
	}
	return data_ui16_var;
}

/*****************************************************END OF FILE************/