#include "main.h"

int main(void)
{
    transmission.ip(true, "192.168.1.25", 80);
    while(1) Led = transmission.recv();
}

string transmission_processing(string cmd)
{
    pc.write(cmd.c_str(), cmd.size());
    ostringstream ssend;
    ssend << fixed;
    ssend.precision(2);
    if(cmd.empty());
    else if(cmd == "*IDN?")
        ssend << MBED_PROJECT << ", Mbed OS " << MBED_VERSION << ", Version dated, " << __DATE__ << ", " << __TIME__;
    else if(cmd == "IP?")
        ssend << "IP(" << transmission.ip() << ")";
    else if(cmd == "IP:ALL?")
        ssend << "IP(" << transmission.ip(transmission.ip()) << ")";
    else if(cmd.find("HEAD /") != string::npos)
        ssend << transmission.http.RETURN_OK << "Content-Type: text/html; charset=utf-8\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
    else if(cmd.find("GET / HTTP") != string::npos)
        ssend << transmission.http.RETURN_OK << "Content-Type: text/html; charset=utf-8\r\nAccess-Control-Allow-Origin: *\r\n\r\n<!DOCTYPE html>\r\n<html>\r\n\t<head>\r\n\t\t<title>" << MBED_PROJECT << "</title>\r\n\t\t<meta http-equiv=refresh content=10>\r\n\t</head>\r\n\t<body style=background-color:dimgray>\r\n\t\t<center>\r\n\t\t\t<h1>" << MBED_PROJECT << "</h1>\r\n\t\t\t<p>" << time(NULL) << "</p>\r\n\t\t</center>\r\n\t</body>\r\n</html>";
    else if(cmd.find("GET /FAVICON.ICO HTTP") != string::npos)
        ssend << transmission.http.RETURN_OK << "Content-Type: image/svg+xml\r\nAccess-Control-Allow-Origin: *\r\n\r\n<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 100 100\" style=\"background-color:steelblue\" xmlns=\"http://www.w3.org/2000/svg\"><title>" << MBED_PROJECT << "</title><text x=\"0\" y=\"85\" textLength=\"100\" font-weight=\"bold\" font-size=\"110\" lengthAdjust=\"spacingAndGlyphs\" fill=\"white\" stroke=\"skyblue\">EL</text></svg>";
    else if(cmd[cmd.size()-1] == '?')
        ssend << "incorrect requeste [" << cmd << "]";
    return ssend.str();
}