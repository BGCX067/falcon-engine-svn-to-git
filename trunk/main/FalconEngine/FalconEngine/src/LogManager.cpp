#include "stdafx.h"
#include "LogManager.h"
#include "Logger.h"
#include "OutputLogger.h"
#include "DialogLogger.h"

bool falcon::LogManager::s_bLoggerInitialized = false;
falcon::LogManager* falcon::LogManager::s_Instance = 0;

falcon::LogManager::LogManager()
{
	m_LoggerCount = 0;

	falcon::OutputLogger* outputLogger = new falcon::OutputLogger();
	outputLogger->EnableLogging(LOG_Info | LOG_Warning | LOG_Error);

	falcon::DialogLogger* dialogLogger = new falcon::DialogLogger();
	dialogLogger->EnableLogging(LOG_Error);

	RegisterLogger(outputLogger);
	RegisterLogger(dialogLogger);

	s_bLoggerInitialized = true;
}

falcon::LogManager::~LogManager()
{
	ClearLoggers();
}

void falcon::LogManager::Create()
{
	s_Instance = new falcon::LogManager();
}

falcon::LogManager* falcon::LogManager::GetInstance()
{
	return s_Instance;
}

void falcon::LogManager::Destroy()
{
	delete s_Instance;
	s_Instance = 0;
}

void falcon::LogManager::ClearLoggers()
{
	for (int i=0;i<m_LoggerCount;++i)
	{
		delete m_Loggers[i];
	}
}

void falcon::LogManager::RegisterLogger(falcon::Logger* logger )
{
	m_Loggers[m_LoggerCount] = logger;
	m_LoggerCount++;
}

void falcon::LogManager::Log(LogChannel channel, std::string message)
{
	assert(s_bLoggerInitialized);

	if(s_bLoggerInitialized)
	{
		for (int i=0;i<m_LoggerCount;++i)
		{
			if (m_Loggers[i]->IsLogging(channel))
				m_Loggers[i]->Log(channel,message);
		}
	}
}