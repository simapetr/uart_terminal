/**
  ****************************************************************************
  * @file file.js
  * @author simek
  * @version V1.0
  * @date 19.04.2020
  * @brief Read write file example
  ****************************************************************************
  * @attention
  * <h2><center>&copy; PORTTRONIC </center></h2>
  ****************************************************************************
  */

/**
  ****************************************************************************
  * Variable
  ****************************************************************************
  */

var write_file_data_str;
var write_file_data_arr = [];
var read_file_data_str;
var read_file_data_arr = [];
var array_text_str;

/**
  ****************************************************************************
  * Initialize
  ****************************************************************************
  */

// Register exit function
reg_exit("exit");
setup();

/**
  ****************************************************************************
  * Function
  ****************************************************************************
  */

/** @brief Setup
 *
 * @param
 * @return
 *
 */

function setup()
{
	main_frame.clear();
	main_frame.printf("File R/W example\n");
	main_frame.printf("\nWrite data string :\n");
	// Write text file
	write_file_data_str = "Write from script.";
	if(file.write("./script/file.txt", write_file_data_str))
	{
		main_frame.printf("write OK\n");
	}
	else
	{
		main_frame.printf("write ERROR\n");
	}

	main_frame.printf("\nAppend data string :\n");
	// Append text file
	write_file_data_str = "\nAppended data";
	if(file.append("./script/file.txt", write_file_data_str))
	{
		main_frame.printf("write OK\n");
	}
	else
	{
		main_frame.printf("write ERROR\n");
	}

	main_frame.printf("\nWrite data array :\n");
	// Write binary file
	write_file_data_arr[0] = 0xff;
	write_file_data_arr[1] = 0x02;
	write_file_data_arr[2] = 0x03;
	write_file_data_arr[3] = 0x55;
	if(file.write("./script/file.bin", write_file_data_arr))
	{
		main_frame.printf("write OK\n");
	}
	else
	{
		main_frame.printf("write ERROR\n");
	}

	main_frame.printf("\nAppend data array :\n");
	// Write binary file
	write_file_data_arr[0] = 0xAA;
	write_file_data_arr[1] = 0xFF;
	write_file_data_arr[2] = 0x00;
	write_file_data_arr[3] = 0xFF;
	if(file.append("./script/file.bin", write_file_data_arr))
	{
		main_frame.printf("write OK\n");
	}
	else
	{
		main_frame.printf("write ERROR\n");
	}

	main_frame.printf("\nReaded string data :\n");
	// Read file 
	read_file_data_str = file.read("./script/file.txt");
	main_frame.printf(read_file_data_str);
	main_frame.printf("\n");

	main_frame.printf("\nReaded array data :\n");
	// Read file 
	read_file_data_arr = file.read_b("./script/file.bin");
	for (var cnt = 0 ; cnt < read_file_data_arr.length ; cnt++)
	{
		array_text_str = "0x" + ("0"+(read_file_data_arr[cnt].toString(16))).slice(-2).toUpperCase() + " ";
		main_frame.printf(array_text_str);
	}

	// Input dialog
	var data = main_frame.get_data("Get file data");
	main_frame.printf("\n");
	main_frame.printf(data);
	main_frame.printf("\n");
	if(file.append("./script/file.txt", data))
	{
		main_frame.printf("write OK\n");
	}
	else
	{
		main_frame.printf("write ERROR\n");
	}

	main_frame.set_progress("Test", 0);
	delay(500);
	main_frame.set_progress(25);
	delay(500);
	main_frame.set_progress(50);
	delay(500);
	main_frame.set_progress(75);
	delay(500);
	main_frame.set_progress(100);
	delay(500);
	main_frame.set_progress(101); 
}

/** @brief Exit event
 *
 * @param
 * @return
 *
 */

function exit()
{
	// Enf of script
	main_frame.printf("\n");
	main_frame.printf("END\n");
}

/*****************************************************END OF FILE************/
