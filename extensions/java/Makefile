
#com/sandklef/searduino/SearduinoMain.java
JAVA_SOURCE=  com/sandklef/searduino/Searduino.java  com/sandklef/searduino/SearduinoObserver.java 
JAVA_CLASSES= com/sandklef/searduino/Searduino.class com/sandklef/searduino/SearduinoObserver.class

JAVA_HEADER=com/sandklef/searduino/Searduino.java 

all: build 

buildj:
	javac  $(JAVA_SOURCE)
	javah  com.sandklef.searduino.Searduino

buildc:
	g++ -fPIC -I. -I../../arduino-sources/core/ -I../../faked-arduino/include/ -I../../faked-arduino/include/arduino/ -I../../arduino-extras/include/ c/searduino-jni.cpp  -shared -Wl,-soname,libsearduinojni.so  -o libsearduinojni.so -L../../faked-arduino/.libs/ -lsearduinostub

build: buildj buildc 

clean:
	rm -f $(JAVA_CLASSES) 