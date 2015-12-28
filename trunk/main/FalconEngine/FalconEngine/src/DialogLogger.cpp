#include "stdafx.h"
#include "DialogLogger.h"

void falcon::DialogLogger::Log(LogChannel channel, std::string message)
{
	std::string caption;
	switch(channel)
	{
		case LOG_Info:caption = "Log -- INFO";break;
		case LOG_Warning: caption = "Log -- WARNING";break;
		case LOG_Error: caption = "Log -- ERROR";break;
	}
	MessageBox(NULL,message.c_str(),caption.c_str(),MB_OK|MB_ICONEXCLAMATION);
}