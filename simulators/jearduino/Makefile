
#com/sandklef/searduino/SearduinoMain.java
JAVA_SOURCE=   com/sandklef/jearduino/Jearduino.java com/sandklef/jearduino/PinTable.java com/sandklef/jearduino/Pin.java com/sandklef/jearduino/PinEvent.java com/sandklef/jearduino/ExecControl.java com/sandklef/jearduino/ExecEvent.java com/sandklef/jearduino/Logger.java com/sandklef/jearduino/Board.java com/sandklef/jearduino/BoardEvent.java
#com/sandklef/jearduino/SearduinoMain.class  
JAVA_CLASSES= com/sandklef/jearduino/Jearduino.class com/sandklef/jearduino/PinTable.class com/sandklef/jearduino/Pin.class com/sandklef/jearduino/ExecControl.class com/sandklef/jearduino/ExecEvent.class com/sandklef/jearduino/Logger.class  com/sandklef/jearduino/PinEvent.class  com/sandklef/jearduino/Board.class com/sandklef/jearduino/BoardEvent.class

LIB_PATHS=./:../../faked-arduino/.libs/:../../extensions/java

all: build run

build: buildso
	javac  -cp $(LIB_PATHS)  $(JAVA_SOURCE)

buildso:
	cd test/fast-digital-out && make clean && make


run:
	LD_LIBRARY_PATH=$(LIB_PATHS) java -cp $(LIB_PATHS)  -Djava.library.path=$(LIB_PATHS)  com.sandklef.jearduino.Jearduino

#	LD_LIBRARY_PATH=./c/ java -cp  .:/./c/ -Djava.class.library=.:/./c/ com.sandklef.searduino.SearduinoMain

clean:
	rm -f $(JAVA_CLASSES) 