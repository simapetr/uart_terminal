var open_status;
var status_string;
var text_bfr;
var graph_0;
var graph_0_signal = [];
var graph_1;
var graph_1_signal = [];
var lock_state = -100;
var unlock_state = -100;

// Disable console RX
main_frame.console_rx_enable(false);
// Open UART port
main_frame.open();
open_status = main_frame.get_open_status();
// Check open status
if (open_status === 1)
{
	main_frame.status("Open\n");
	
}
else if(open_status === 7)
{
	main_frame.status("Port is open\n");
}
else
{
	status_string = "Open port error : ";
	status_string += open_status;
	status_string += "\n";
	main_frame.status(status_string);
}
// Check for port open
if ((open_status === 7) || (open_status === 1))
{
	uart.set_ctrl("BREAK", false);
	main_frame.console_rx_enable(false);
	main_frame.clear();
	uart.reg_event("read_data");
	main_frame.printf("Read data\n");
	// Open graph
	graph_0 = graph.add(500.0, 40.0, 0.1);
	graph_1 = graph.add(500.0, 40.0, 0.1);
	// Delaty for internal graph object create max 200ms must be call from host app
	delay(200);
	// create buffer for plot signal
	graph_0_signal.push(graph.insert_signal(graph_0, "unlock",0x00000000,1,0));
	graph_0_signal.push(graph.insert_signal(graph_0, "trigger_h",0x000000ff,1,0));
	graph_0_signal.push(graph.insert_signal(graph_0, "trigger_l",0x0000ff00,1,0));
	graph_0_signal.push(graph.insert_signal(graph_0, "state",0x00ff0000,1,0));
	graph_1_signal.push(graph.insert_signal(graph_1, "lock",0x00000000,1,0));
	graph_1_signal.push(graph.insert_signal(graph_1, "trigger_h",0x000000ff,1,0));
	graph_1_signal.push(graph.insert_signal(graph_1, "trigger_l",0x000ff000,1,0));
	graph_1_signal.push(graph.insert_signal(graph_1, "state",0x0ff00000,1,0));
	graph.set_data(graph_0, graph_0_signal);
	graph.set_data(graph_1, graph_1_signal);
	graph.show(true);
	delay(100);
	uart.set_ctrl("BREAK", true);
}

function read_data ( event_var, data_var )
{
	if (event_var & 0x1)
	{
		if (data_var.length == 11)
		{
			if(!main_frame.is_console_rx_enable())
			{
				if ((data_var[0] == 0x55) & (data_var[1] == 0x02))
				{
					graph_0_signal[0] = conv_i16((256 * data_var[3]) + data_var[2]);
					graph_0_signal[1] = conv_i16((256 * data_var[5]) + data_var[4]);
					graph_0_signal[2] = conv_i16((256 * data_var[7]) + data_var[6]);
					graph_0_signal[3] = conv_i16((256 * data_var[9]) + data_var[8]);
				}
				else if ((data_var[0] == 0x55) & (data_var[1] == 0x03))
				{
					graph_1_signal[0] = conv_i16((256 * data_var[3]) + data_var[2]);
					graph_1_signal[1] = conv_i16((256 * data_var[5]) + data_var[4]);
					graph_1_signal[2] = conv_i16((256 * data_var[7]) + data_var[6]);
					graph_1_signal[3] = conv_i16((256 * data_var[9]) + data_var[8]);
					
				}
				else
				{
				}
				if (lock_state != graph_0_signal[3])
				{
					if(graph_0_signal[3] == 100)
					{
						main_frame.printf("lock");
					}
					else
					{
						main_frame.printf("ed\n");
					}
				}
				lock_state = graph_0_signal[3];
				if (unlock_state != graph_1_signal[3])
				{
					if(graph_1_signal[3] == 100)
					{
						main_frame.printf("unlock");
					}
					else
					{
						main_frame.printf("ed\n");
					}
				}
				unlock_state = graph_1_signal[3];
				/*for (var cnt = 0 ; cnt < data.length ; cnt++)
				{
					main_frame.printf(("     "+(data[cnt].toString(10))).slice(-5));
					main_frame.printf(";");
				}
				main_frame.printf("\n");*/
				graph.set_data(graph_0, graph_0_signal);
				graph.set_data(graph_1, graph_1_signal);
			}
		}
	}
}

function conv_i16 ( data_ui16_var )
{
	if (data_ui16_var & 0x8000)
	{
		data_ui16_var = 0 - (0x10000 - data_ui16_var);
	}
	return data_ui16_var;
}

// Script termination
//exit();
