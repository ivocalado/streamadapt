/*
 * jobmanager.cpp
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#include <jobmanager.h>

namespace infrastream {

JobManager* JobManager::instance = 0;

JobManager* JobManager::getInstance() {
	if(!instance)
		instance = new JobManager;
	return instance;
}

JobManager::JobManager() {

}

JobManager::~JobManager() {
	// TODO Auto-generated destructor stub
}

void JobManager::run() {
	while(jobs.size()) {
		AbstractJob* job = jobs.front();
		job->executeJob();
		jobs.pop_front();
		delete job;
	}
}

void JobManager::addJob(AbstractJob* newJob) {
	jobs.push_back(newJob);
}

}
