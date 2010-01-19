/*
 * jobmanager.h
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#ifndef JOBMANAGER_H_
#define JOBMANAGER_H_
#include <list>
#include "abstractjob.h"

namespace infrastream {

class JobManager {
	std::list<AbstractJob*> jobs;
	static JobManager* instance;

	JobManager();

public:

	static JobManager* getInstance();
	virtual ~JobManager();

	void run();
	void addJob(AbstractJob* newJob);

};

}

#endif /* JOBMANAGER_H_ */
