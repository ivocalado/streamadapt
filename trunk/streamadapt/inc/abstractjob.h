/*
 * abstractjob.h
 *
 *  Created on: 18/01/2010
 *      Author: ivocalado
 */

#ifndef ABSTRACTJOB_H_
#define ABSTRACTJOB_H_

namespace infrastream {
class AbstractJob {
public:
	AbstractJob() {}
	virtual ~AbstractJob(){}
	virtual void executeJob() = 0;

};
}
#endif /* ABSTRACTJOB_H_ */
