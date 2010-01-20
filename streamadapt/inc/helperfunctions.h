/*
 * helperfunctions.h
 *
 *  Created on: 19/01/2010
 *      Author: ivocalado
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include <cc++/thread.h>

namespace infrastream {
template<class T> class ThreadSafeObject : public ost::ThreadLock, public T {};

}

#endif /* HELPERFUNCTIONS_H_ */
