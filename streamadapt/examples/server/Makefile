all: compile_main build_all

compile_main:
	g++ -I../../inc main.cpp -c -DMAIN_SERVER
	
build_all:
	g++  -o"streamadapt_server"  ../../Debug/adaptationmanager.o ../../Debug/consoleappender.o ../../Debug/event.o ../../Debug/eventregister.o ../../Debug/eventtype.o ../../Debug/facade.o ../../Debug/gsck.o ../../Debug/infrafactory.o ../../Debug/jobmanager.o ../../Debug/logger.o ../../Debug/loggingappender.o ./main.o ../../Debug/pluginbase.o ../../Debug/pluginsfactory.o ../../Debug/policy.o ../../Debug/policyengine.o ../../Debug/session.o ../../Debug/sessionmanager.o ../../Debug/streamsession.o ../../Debug/trpsession.o  -ldl -lccgnu2 -lccrtp1 -lxerces-c
	

clean:
	rm -rf *.o *.so streamadapt_server
