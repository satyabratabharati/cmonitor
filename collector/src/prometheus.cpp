/* 
 * prometheus.cpp
 *
*/

#include "prometheus.h"

void CMonitorPromethues::init()
{
	m_exposer->RegisterCollectable(m_prometheus_registry);
}

void CMonitorPromethues::addKPI(const std::string& str, double value)
{
	//const prometheus::Labels more_labels = {{"function", "capture"}};
	prometheus::Labels more_labels;
	for (const auto& entry : m_labels_map)
		more_labels = {{entry.first, entry.second}};

	auto& metrics = prometheus::BuildGauge()
					  .Name(str)
					  .Help(str)
					  .Labels({{"cmonitor", "instance_1"}})
					  .Register(*m_prometheus_registry)
					  //.Add({{"system_id", "0"}})
					  .Add(more_labels);
	metrics.Set(value);
}
