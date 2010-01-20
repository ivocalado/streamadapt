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
		jobs.readLock();
		AbstractJob* job = jobs.front();
		jobs.unlock();
		job->executeJob();
		jobs.writeLock();
		jobs.pop_front();
		jobs.unlock();
		delete job;
	}
}

void JobManager::addJob(AbstractJob* newJob) {
	jobs.writeLock();
	jobs.push_back(newJob);
	jobs.unlock();
}

void JobManager::endSession() {

}

}
