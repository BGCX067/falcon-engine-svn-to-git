#ifndef FALCONENGINE_DIALOGLOGGER_H
#define FALCONENGINE_DIALOGLOGGER_H

#include "Logger.h"

namespace falcon
{
	class DialogLogger : public Logger
	{
	public:
		DialogLogger(){};
		virtual ~DialogLogger(){};

		virtual void Log(LogChannel channel, std::string message);	
	private:
		DialogLogger(const DialogLogger& t);
		DialogLogger& operator=(const DialogLogger& t);
	};
}
#endif // FALCONENGINE_DIALOGLOGGER_H