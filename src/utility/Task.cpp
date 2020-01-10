#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string>

#include "Task.h"

static char tag[] = "Task";

Task::Task(std::string taskName, uint16_t taskSize, uint8_t priority)
{
	m_handle 	= nullptr;
	m_taskdata 	= nullptr;
	m_taskname	= taskName;
	m_tasksize 	= taskSize;
	m_priority 	= priority;
	m_coreid	= tskNO_AFFINITY;
}

Task::~Task()
{
}

void Task::runTask(void* pTaskInstance)
{
	Task* pTask = (Task*)pTaskInstance;
	ESP_LOGD(tag, ">> Task %s run", pTask->m_taskname.c_str());
	pTask->run(pTask->m_taskdata);
	ESP_LOGD(tag, "<< Task %s stop", pTask->m_taskname.c_str());
	pTask->stop();
}

void Task::start(void* taskData)
{
	if( m_handle != nullptr )
	{
		ESP_LOGD(tag, "[] Task %s is already running", m_taskname.c_str());
	}
	m_taskdata = taskData;
	::xTaskCreatePinnedToCore(&runTask, m_taskname.c_str(), m_tasksize, this, m_priority, &m_handle, m_coreid);
}

void Task::stop()
{
	if( m_handle == nullptr )
	{
		return;
	}
	xTaskHandle handleTemp = m_handle;
	m_handle = nullptr;
	::vTaskDelete(handleTemp);
}

void Task::delay(int ms)
{
	::vTaskDelay(ms/portTICK_PERIOD_MS);
}

void Task::setTaskSize( uint16_t size )
{
	m_tasksize = size;
}

void Task::setTaskPriority( uint8_t priority)
{
	m_priority = priority;
}

void Task::setTaskName(std::string name)
{
	m_taskname = name;
}

void Task::setCore(BaseType_t coreID)
{
	m_coreid = coreID;
}

