/*
 * jobmanager.h
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#ifndef JOBMANAGER_H_
#define JOBMANAGER_H_
#include <list>
#include "helperfunctions.h"
#include "abstractjob.h"

namespace infrastream {

class JobManager {
	ThreadSafeObject <std::list<AbstractJob*> > jobs;

	static JobManager* instance;

	JobManager();

public:

	static JobManager* getInstance();
	virtual ~JobManager();

	void run();
	void addJob(AbstractJob* newJob);

	void endSession();

};

}

#endif /* JOBMANAGER_H_ */
