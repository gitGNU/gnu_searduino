
#com/sandklef/searduino/SearduinoMain.java
JAVA_SOURCE=  com/sandklef/searduino/Searduino.java com/sandklef/searduino/SearduinoObserver.java com/sandklef/searduino/Jearduino.java com/sandklef/searduino/PinTable.java com/sandklef/searduino/Pin.java com/sandklef/searduino/PinEvent.java com/sandklef/searduino/ExecControl.java com/sandklef/searduino/ExecEvent.java com/sandklef/searduino/Logger.java com/sandklef/searduino/Board.java com/sandklef/searduino/BoardEvent.java
#com/sandklef/searduino/SearduinoMain.class  
JAVA_CLASSES=com/sandklef/searduino/Searduino.class com/sandklef/searduino/SearduinoObserver.class com/sandklef/searduino/Jearduino.class com/sandklef/searduino/PinTable.class com/sandklef/searduino/Pin.class com/sandklef/searduino/ExecControl.class com/sandklef/searduino/ExecEvent.class com/sandklef/searduino/Logger.class  com/sandklef/searduino/PinEvent.class  com/sandklef/searduino/Board.class com/sandklef/searduino/BoardEvent.class

JAVA_HEADER=com/sandklef/searduino/Searduino.java 

all: build run

buildj:
	javac  $(JAVA_SOURCE)
	javah  com.sandklef.searduino.Searduino

buildjc:
	javah  com.sandklef.searduino.Searduino
	gcj  $(JAVA_SOURCE)

buildc:
	g++ -fPIC -I. -I../../arduino-sources/core/ -I../../faked-arduino/include/ -I../../faked-arduino/include/arduino/ -I../../arduino-extras/include/ c/searduino-jni.cpp  -shared -Wl,-soname,libsearduinojni.so  -o libsearduinojni.so -L../../faked-arduino/.libs/ -lsearduinostub

buildso:
	cd test/fast-digital-out && make clean && make

build: buildj buildc buildso

run:
	LD_LIBRARY_PATH=./:../../faked-arduino/.libs/ java -cp .  -Djava.library.path=.  com.sandklef.searduino.Jearduino

#	LD_LIBRARY_PATH=./c/ java -cp  .:/./c/ -Djava.class.library=.:/./c/ com.sandklef.searduino.SearduinoMain

clean:
	rm -f $(JAVA_CLASSES) 