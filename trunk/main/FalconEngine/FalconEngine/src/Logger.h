#ifndef FALCONENGINE_LOGGER_H
#define FALCONENGINE_LOGGER_H

#include "LogManager.h"

namespace falcon
{
	class Logger
	{
	public:
		Logger():m_channels(0) {}
		virtual ~Logger(){}

		virtual void Log(LogChannel channel, std::string message) = 0;	

		void EnableLogging(int channels) { m_channels = m_channels | channels; }
		void DisableLogging(int channels) { m_channels = m_channels & ~(channels); }
		bool IsLogging(int channels) { return (m_channels & channels) != 0; }
	protected:
		int m_channels;
	};
}
#endif // FALCONENGINE_LOGGER_H