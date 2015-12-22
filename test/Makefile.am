if SHAREDTEST
if CYGWIN_USED
SUBDIRS= arduino-lib mk hw stub searduino_loop arduino-code-dynamic arduino-code-static 
else
SUBDIRS= arduino-lib mk hw stub searduino_loop arduino-code-dynamic arduino-code-static shared shared-main 
endif
else
fi
SUBDIRS= arduino-lib mk hw stub searduino_loop arduino-code-dynamic arduino-code-static
endif

EXTRA_DIST =           \
    ./stub/Makefile.tmpl \
    ./stub/test.c \
    ./shared/Makefile.tmpl \
    ./shared/test.c \
    ./static/Makefile.tmpl \
    ./static/test.c \
    ./arduino-code-dynamic/Makefile.tmpl \
    ./arduino-code-dynamic/ard_code.c \
    ./shared-main/Makefile.tmpl \
    ./shared-main/test.c \
    ./searduino_loop/Makefile.tmpl \
    ./searduino_loop/test.c \
    ./arduino-code-static/Makefile.tmpl \
    ./arduino-code-static/ard_code.c \
    ./hw/Makefile.tmpl \
    ./hw/test.c \
    ./arduino-lib/Makefile.tmpl \
    ./arduino-lib/functions.c \
    ./arduino-lib/functions.h 

#\
#    ./arduino-lib/include/functions.h 

