#ifndef header_h
#define header_h

float water_level = 0.0;

String file=
"<!DOCTYPE html>\r\n"
"<html lang=en>\r\n"
  "<head>\r\n"
    "<title> ESP8266 Web Server </title>\r\n"
    "<meta http-equiv=refresh content=60/>\r\n"
  "</head>\r\n"
  "<body bgcolor=black>\r\n"
      "<h2 align=center> <i> <b> <font color=blue> ***Automatic Plant Watering System*** </font> </b> </i></h2>\r\n"
        "<br>\r\n"
        "<br>\r\n"
            "<p align=center> <font color=red> </font> &nbsp; &nbsp; &nbsp; <a href=\\\"?pin=ON0\\\"> <button style=height:250px;width:250px> ON </button> </a> &nbsp; &nbsp; &nbsp; &nbsp; <a href=\\\"?pin=OFF0\\\"> <button style=height:250px;width:250px> OFF </button> </a> </p>\r\n"        
            "<br>\r\n"       
        "<br>\r\n"
  "</body>\r\n"
"</html>";

#endif
