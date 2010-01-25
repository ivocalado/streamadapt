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
	if (!instance)
		instance = new JobManager;
	return instance;
}

JobManager::JobManager() {

}

JobManager::~JobManager() {
	// TODO Auto-generated destructor stub
}

#include <iostream>
using namespace std;

void JobManager::run() {
	while (jobs.size()) {
		jobs.writeLock();
		AbstractJob* job = jobs.front();
		jobs.pop_front();
		jobs.unlock();
		job->executeJob();
		delete job;
	}
}

void JobManager::addJob(AbstractJob* newJob) {
	jobs.writeLock();
	jobs.push_back(newJob);
	jobs.unlock();
}

void JobManager::endSession() {
	jobs.writeLock();
	while (jobs.size()) {
		AbstractJob* job = jobs.front();
		jobs.pop_front();
		delete job;
	}
	jobs.unlock();
}

}
