#ifndef FALCONENGINE_LOGMANAGER_H
#define FALCONENGINE_LOGMANAGER_H

#define MAX_LOGGER_COUNT 16

#define LOG(channel,message) falcon::LogManager::GetInstance()->Log(channel,message);

namespace falcon
{
	class Logger;

	enum LogChannel
	{
		LOG_Info =		1 << 0,
		LOG_Warning =	2 << 1,
		LOG_Error =		3 << 3
	};
	class LogManager
	{
	public:

		static void Create();
		static LogManager* GetInstance();
		static void Destroy();

		void ClearLoggers();

		void RegisterLogger(falcon::Logger* logger);

		void Log(LogChannel channel, std::string message);

	private:
		LogManager();
		~LogManager();
		falcon::Logger* m_Loggers[MAX_LOGGER_COUNT];
		short m_LoggerCount;

		static bool s_bLoggerInitialized;
		static LogManager* s_Instance;
	};
}
#endif //FALCONENGINE_LOGMANAGER_H