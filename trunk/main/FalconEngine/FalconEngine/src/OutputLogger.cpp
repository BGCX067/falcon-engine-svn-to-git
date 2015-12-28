#include "stdafx.h"
#include "OutputLogger.h"

void falcon::OutputLogger::Log(LogChannel channel, std::string message)
{
	std::string out = "Log: ";
	switch(channel)
	{
		case LOG_Info: out += ("INFO -- " + message + "\n");break;
		case LOG_Warning: out += ("WARNING -- " + message + "\n");break;
		case LOG_Error: out += ("ERROR -- " + message + "\n");break;
	}
	OutputDebugString(out.c_str());
}