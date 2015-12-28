#ifndef FALCONENGINE_OUTPUTLOGGER_H
#define FALCONENGINE_OUTPUTLOGGER_H

#include "Logger.h"

namespace falcon
{
	class OutputLogger : public Logger
	{
	public:
		OutputLogger(){};
		virtual ~OutputLogger(){};

		virtual void Log(LogChannel channel, std::string message);	
	private:
		OutputLogger(const OutputLogger& t);
		OutputLogger& operator=(const OutputLogger& t);
	};
}
#endif // FALCONENGINE_OUTPUTLOGGER_H