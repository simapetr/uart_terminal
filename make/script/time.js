/**
  ****************************************************************************
  * @file    time.js
  * @author  Ing. Petr Simek
  * @version V1.0
  * @date    16.04.2018
  * @brief   Time example
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

var time_data;
var text_str;
 
/**
  ****************************************************************************
  * script
  ****************************************************************************
  */

main_frame.clear();
main_frame.printf("Now is :\n");
// Time in milisecond
time_data = time.now_ms();
text_str = "Timestamp in (ms) : ";
text_str += time_data;
text_str += "\n";
main_frame.printf(text_str);
// Time in second
time_data = time.now();
text_str = "Timestamp in (s)  : ";
text_str += time_data;
text_str += "\n";
main_frame.printf(text_str);
// Date time UTC
text_str = "Date & time UTC   : ";
text_str += time.str(time_data);
text_str += "\n";
main_frame.printf(text_str);
// Date time UTC
text_str = "Date & time local : ";
text_str += time.local_str(time_data);
text_str += "\n";
main_frame.printf(text_str);


/*****************************************************END OF FILE************/