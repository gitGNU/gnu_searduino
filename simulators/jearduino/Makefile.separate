
PKG_PATH=com/sandklef/jearduino/
JAVA_SOURCE= \
	$(PKG_PATH)/Jearduino.java \
	$(PKG_PATH)/PinTable.java  \
	$(PKG_PATH)/PinEvent.java \
	$(PKG_PATH)/ExecControl.java \
	$(PKG_PATH)/ExecEvent.java \
	$(PKG_PATH)/Logger.java \
	$(PKG_PATH)/Board.java \
	$(PKG_PATH)/BoardEvent.java \
	$(PKG_PATH)/JearduinoPreferences.java \
	$(PKG_PATH)/InfoPanel.java    \
	$(PKG_PATH)/JearduinoMenu.java   \
	$(PKG_PATH)/JearduinoAbout.java   \
	$(PKG_PATH)/ArduinoCodeNameEvent.java   \
	$(PKG_PATH)/FileEvent.java 

#	$(PKG_PATH)/CodeEvent.java \

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
	rm -f $(PKG_PATH)/*.class
