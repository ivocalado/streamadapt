/*
 * session.h
 *
 *  Created on: 13/01/2010
 *      Author: ivocalado
 */

#ifndef SESSION_H_
#define SESSION_H_
#include "infraexceptions.h"
#include "event.h"
#include "eventtype.h"
#include "logger/logger.h"
#include "plugins/pluginnegotiation.h"
#include "jobmanager.h"
#include "adaptationjob.h"

#include <map>
#include <set>

using namespace std;

namespace infrastream {

/**
 * This class describes a stream session.
 */
class Session {
	PluginNegotiationPtrlIF *negotiation;
	string pluginName;
	string libName;

public:
	Session(string pluginName, string libName,
			PluginNegotiationPtrlIF* negotiation)
			throw(CannotCreateSessionException);
	virtual ~Session();

	virtual void newEvent(Event event) throw(InvalidEventException) = 0;
	virtual set<EventType> getDependencies() throw(InvalidPolicyException) = 0;

	PluginNegotiationPtrlIF* getNegotiation() const;

	string getPluginName() const;
	string getLibName() const;

	virtual void endSession() = 0;

	virtual string retrievePluginInformation(string key) = 0;

protected:

	template<class PolicyDesc, class Ss, class Engine> void runInference(
			PolicyDesc *policy, Ss &session, map<EventType,
const					typename PolicyDesc::policy_type*>dependencies,
					Engine* engine, Event event) throw(InvalidEventException) {

						if (policy) {
							typename map<EventType, const typename PolicyDesc::policy_type*>::iterator
				it = dependencies.find(event.getType());
				if (it != dependencies.end()) {

					double eventValue = event.getPayload();
					const typename PolicyDesc::policy_type* p = it->second;
					if (p->lower().present() && eventValue
							< p->lower().get().threshold()) {
						JobManager::getInstance()->addJob(
								new AdaptationJob<const typename PolicyDesc::policy_type::lower_type, Ss>(p->lower().get(), session,negotiation));

//						configurePlugin(p->lower().get(), session, negotiation); //configuring simple properties


						//Now configuring if instances
						typename PolicyDesc::policy_type::lower_type::if_const_iterator
								ifIt(p->lower().get().if_().begin());

						for (; ifIt != p->lower().get().if_().end(); ++ifIt) {
							bool result = true;

							typename PolicyDesc::policy_type::lower_type::if_type::equals_const_iterator
									eqIt(ifIt->equals().begin());
							for (; result && eqIt != ifIt->equals().end(); ++eqIt) {
								EventType l = EventType(eqIt->Lhs());
								//** Recuperar ultimo Event

								Event lhs = engine->getLastEvent(l);

								result = (lhs.getPayload() == eqIt->Rhs());
							}

							typename PolicyDesc::policy_type::lower_type::if_type::lower_const_iterator
									lwIt(ifIt->lower().begin());
							for (; result && lwIt != ifIt->lower().end(); ++eqIt) {
								EventType l = EventType(lwIt->Lhs());

								Event lhs = engine->getLastEvent(l);

								//fazer verificacao do event

								result = lwIt->equals() ? (lhs.getPayload()
										<= lwIt->Rhs()) : (lhs.getPayload()
										< lwIt->Rhs());

							}

							typename PolicyDesc::policy_type::lower_type::if_type::greater_const_iterator
									grIt(ifIt->greater().begin());
							for (; result && grIt != ifIt->greater().end(); ++eqIt) {
								EventType l = EventType(grIt->Lhs());

								Event lhs = engine->getLastEvent(l);
								//fazer verificacao do event

								result = grIt->equals() ? (lhs.getPayload()
										>= grIt->Rhs()) : (lhs.getPayload()
										> grIt->Rhs());
							}

							if (result)
								JobManager::getInstance()->addJob(
																new AdaptationJob<const typename PolicyDesc::policy_type::lower_type::if_type::operations_type, Ss>
																(ifIt->operations(), session, negotiation));
//								configurePlugin(ifIt->operations(), session, negotiation);
						}

					} else if (p->greater().present() && eventValue
							>= p->greater().get().threshold()) {
						JobManager::getInstance()->addJob(
								new AdaptationJob<const typename PolicyDesc::policy_type::greater_type, Ss>
									(p->greater().get(), session, negotiation));
//						configurePlugin(p->greater().get(), session, negotiation); //adapting greater


						//Now configuring if instances
						typename PolicyDesc::policy_type::greater_type::if_const_iterator
								ifIt(p->greater().get().if_().begin());

						for (; ifIt != p->greater().get().if_().end(); ++ifIt) {
							bool result = true;

							typename PolicyDesc::policy_type::greater_type::if_type::equals_const_iterator
									eqIt(ifIt->equals().begin());
							for (; result && eqIt != ifIt->equals().end(); ++eqIt) {
								EventType l = EventType(eqIt->Lhs());

								Event lhs = engine->getLastEvent(l);

								//fazer verificacao do event
								result = (lhs.getPayload() == eqIt->Rhs());
							}

							typename PolicyDesc::policy_type::greater_type::if_type::lower_const_iterator
									lwIt(ifIt->lower().begin());
							for (; result && lwIt != ifIt->lower().end(); ++eqIt) {
								EventType l = EventType(lwIt->Lhs());

								Event lhs = engine->getLastEvent(l);
								//fazer verificacao do event

								result = lwIt->equals() ? (lhs.getPayload()
										<= lwIt->Rhs()) : (lhs.getPayload()
										< lwIt->Rhs());

							}

							typename PolicyDesc::policy_type::greater_type::if_type::greater_const_iterator
									grIt(ifIt->greater().begin());
							for (; result && grIt != ifIt->greater().end(); ++eqIt) {
								EventType l = EventType(grIt->Lhs());

								Event lhs = engine->getLastEvent(l);

								//fazer verificacao do event

								result = grIt->equals() ? (lhs.getPayload()
										>= grIt->Rhs()) : (lhs.getPayload()
										> grIt->Rhs());

							}

							if (result)
								JobManager::getInstance()->addJob(
											new AdaptationJob<const typename PolicyDesc::policy_type::greater_type::if_type::operations_type, Ss>
												(ifIt->operations(), session, negotiation));
//								configurePlugin(ifIt->operations(), session, negotiation);
						}

					} else {
						typename PolicyDesc::policy_type::range_const_iterator
								itRange(p->range().begin());
						for (; itRange != p->range().end(); ++itRange)
							//				for (adapt_config::transport_type::policy_type::range_iterator
							//						it = p->range().begin(); it != p->range().end(); it++)
							if (itRange->from() <= eventValue && eventValue
									< itRange->from()) {
								JobManager::getInstance()->addJob(
											new AdaptationJob<const typename PolicyDesc::policy_type::range_type, Ss>
												(*itRange, session, negotiation));

//								configurePlugin(*itRange, session, negotiation); // adapting ranges


								//Now configuring 'if' instances
								typename PolicyDesc::policy_type::range_type::if_const_iterator
										ifIt(itRange->if_().begin());

								for (; ifIt != itRange->if_().end(); ++ifIt) {
									bool result = true;

									typename PolicyDesc::policy_type::range_type::if_type::equals_const_iterator
											eqIt(ifIt->equals().begin());
									for (; result && eqIt != ifIt->equals().end(); ++eqIt) {
										EventType l = EventType(eqIt->Lhs());

										Event lhs = engine->getLastEvent(l);

										//fazer verificacao do event
										result = (lhs.getPayload() == eqIt->Rhs());
									}

									typename PolicyDesc::policy_type::range_type::if_type::lower_const_iterator
											lwIt(ifIt->lower().begin());
									for (; result && lwIt != ifIt->lower().end(); ++eqIt) {
										EventType l = EventType(lwIt->Lhs());

										Event lhs = engine->getLastEvent(l);
										//fazer verificacao do event

										result = lwIt->equals() ? (lhs.getPayload()
												<= lwIt->Rhs()) : (lhs.getPayload()
												< lwIt->Rhs());
									}

									typename PolicyDesc::policy_type::range_type::if_type::greater_const_iterator
											grIt(ifIt->greater().begin());
									for (; result && grIt != ifIt->greater().end(); ++eqIt) {
										EventType l = EventType(grIt->Lhs());

										Event lhs = engine->getLastEvent(l);

										//fazer verificacao do event

										result = grIt->equals() ? (lhs.getPayload()
												>= grIt->Rhs()) : (lhs.getPayload()
												> grIt->Rhs());
									}

									if (result)
										JobManager::getInstance()->addJob(
												new AdaptationJob<const typename PolicyDesc::policy_type::range_type::if_type::operations_type, Ss>
													(ifIt->operations(), session, negotiation));
									break;
								}

							}
					}
			} else {
				log_error("Invalid event");
				throw InvalidEventException();
			}
		} else
			log_error("Unrequested event");

	}

						};

					}
#endif /* SESSION_H_ */
