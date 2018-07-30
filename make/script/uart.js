var open_status;
var status_string;
var text_bfr;
var termination_flag = 0;

// Disable console RX
main_frame.console_rx_enable(false);
// Open UART port
main_frame.open(1,57600,0,0,8,4);
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
	uart.reg_event("read_data");
	for(var cnt = 0 ; cnt < 2 ; cnt++)
	{
		text_bfr = "test : ";
		text_bfr += cnt;
		text_bfr += "\n";
		// Send data
		uart.write(text_bfr);
	}
	while(!termination_flag)
	{
		delay(10);
	}
	main_frame.printf("Script terminated\n");
	alert("Script terminated")
	main_frame.console_rx_enable(true);
}

function read_data ( event_var, data_var )
{
var text_str;

	if (event_var & 0x1)
	{
		if (data_var.length)
		{
			if(!main_frame.is_console_rx_enable())
			{
				main_frame.printf("Rx : ");
				text_str = "(";
				for (var cnt = 0 ; cnt < data_var.length ; cnt++)
				{
					main_frame.printf(("0"+(data_var[cnt].toString(16))).slice(-2).toUpperCase() + " ");
					text_str += String.fromCharCode(data_var[cnt]);
				}
				text_str += ")";
				main_frame.printf(text_str);
				main_frame.printf("\n");
			}
			if(data_var[0] === 0x55)
			{
				termination_flag = 1;
			}
		}
	}
}

// Script termination
//exit();
