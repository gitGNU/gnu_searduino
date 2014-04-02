AUTOMAKE_OPTIONS = gnu

JAVA_FILES=com/sandklef/searduino/OpenCloseArduinoCode.java
LIB_PATHS=./:../../../faked-arduino/.libs/:../
JAVACFLAGS=  -cp $(LIB_PATHS)


CLASS_FILES=$(JAVA_FILES:.java=.class)
JAVA_RESULTS=$(CLASS_FILES:.class=.stdout)

CLEANFILES=*.stdout *.class

all: $(CLASS_FILES) $(JAVA_RESULTS)

%.class:%.java
	javac $(JAVACFLAGS) $<

$(CLASS_FILES): $(JAVA_FILES)
$(JAVA_RESULTS): $(CLASS_FILES)

EXTRA_DIST = $(JAVA_FILES)


%.stdout:%.class
	@echo "Generating java printouts ( $< => $@ )"
	-@./runclass  $< 
#> $@  2> $@.stderr

