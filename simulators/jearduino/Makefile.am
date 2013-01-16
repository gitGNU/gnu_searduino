
if PEARDUINO_SUPPORT

LIB_PATHS=./:../../faked-arduino/.libs/:../../extensions/java

AUTOMAKE_OPTIONS = gnu

#
# Waiting for Automake to have good Java support
# so we're doing a bit of hack until then
#
#   .... automake is great. The comment above reflects the deprecated
#        still not replaced old way of working with Java.
# 
PKG_PATH=com/sandklef/jearduino/
JAVA_SOURCES = \
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


JAVACFLAGS=  -cp $(LIB_PATHS)

JEARDUINO_JAR=Jearduino.jar

$(JEARDUINO_JAR):
	javac $(JAVACFLAGS) $(JAVA_SOURCES)
	jar cf  $(JEARDUINO_JAR) ./com/sandklef/jearduino/*.class

bin_SCRIPTS = searduino-jearduino.sh 

EXTRA_DIST = searduino-jearduino.sh.tmpl $(bin_SCRIPTS) $(JAVA_SOURCES)




install-exec-hook: $(JEARDUINO_JAR)
	cp $(JEARDUINO_JAR)  $(DESTDIR)$(libdir)/


CLEAN_FILES=jearduino.sh

endif
