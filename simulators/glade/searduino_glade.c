/*
 * Compile me with:
   gcc -o seagla searduino_glade.c $(pkg-config --cflags --libs gtk+-3.0 gmodule-3.0)
 */

#include <gtk/gtk.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>

GtkBuilder *builder;
sem_t sem;

int run = 0;

pthread_t   searduino_thread_impl;
pthread_t  *searduino_thread = &searduino_thread_impl;
#define NR_OF_PINS 100
#define PINS_TO_USE 5

void* c_arduino_code(void *in);

struct general_pin
{
  GtkBox        *container;
  GtkLabel      *name;
  GtkLabel      *type;
  GtkLabel      *mode;
  GtkSpinButton *analog_in;
  GtkLabel      *out;
  int           value;
} ;

struct general_pin pins[NR_OF_PINS];

#define uint8_t int 
#define DIGITAL 0
#define ANALOG  1

#define GDK_SEM

#ifdef NO_SEM
#define SEMLOCK()     
#define SEMREL()      
#endif

#ifdef GDK_SEM
#define SEMLOCK()     printf("---->ENTER\n"); fflush(stdout); gdk_threads_enter (); 
#define SEMREL()      gdk_threads_leave (); printf("---->LEAVE\n"); fflush(stdout);
#endif

#ifdef PTHREAD_SEM
#define SEMLOCK()     sem_wait(&sem);
#define SEMREL()      sem_post(&sem);
#endif

#define SERIAL_OUTPUT_VIEW 0
#define LOG_OUTPUT_VIEW    1

#define searduino_log(str)        searduino_log_general(str, LOG_OUTPUT_VIEW)
#define searduino_serial_out(str) searduino_log_general(str, SERIAL_OUTPUT_VIEW)

void searduino_statusbar_push(char *str)
{
  static GtkStatusbar  *statusbar=NULL;

  if (str==NULL)
    {
      return;
    }

  printf ("status: %p\n", statusbar);
  if (statusbar == NULL )
    {
      printf ("??\n");
      statusbar = GTK_STATUSBAR( gtk_builder_get_object( builder, "status_label" ) );
    }
  
  printf ("status getting sem\n");
  //  SEMLOCK();
  printf ("status got sem\n");
  gtk_statusbar_push(statusbar, 1, str);
  printf ("status will rel sem\n");
  //SEMREL();
  printf ("status getting done\n");
}

void searduino_log_general(char *str, int view)
{
  GtkTextIter    iter;
  GtkTextBuffer *text_buffer;
  GtkTextView   *text_view ;

  static GtkTextView   *log_text_view ;
  static GtkTextView   *serial_text_view ;
  static GtkTextBuffer *log_text_buffer    = NULL;
  static GtkTextBuffer *serial_text_buffer = NULL;

  if (str==NULL) 
    {
      return;
    }

  if (view == SERIAL_OUTPUT_VIEW)
    {
      if (serial_text_buffer == NULL)
	{
	  serial_text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "serial_out" ) );      
	  serial_text_buffer =  gtk_text_view_get_buffer(serial_text_view);
	}
      text_buffer = serial_text_buffer;
      text_view   = serial_text_view;
    }
  else if (view == LOG_OUTPUT_VIEW)
    {
      if (log_text_buffer == NULL)
	{
	  log_text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "log" ) );      
	  log_text_buffer =  gtk_text_view_get_buffer(log_text_view);
	}
      text_buffer = log_text_buffer;
      text_view   = log_text_view;
    }
  else
    {
      return ;
    }

  /* all ptrs now point to the correct view and buffer, so let's write */
  printf ("log get sem  %d\n", view);
  SEMLOCK();
  printf ("log get sem a\n");
  gtk_text_buffer_get_end_iter(text_buffer, &iter);
  printf ("log get sem b\n");
  gtk_text_view_scroll_to_iter(text_view, &iter, 0.0, TRUE, 1.0, 1.0);
  printf ("log get sem c\n");
  gtk_text_buffer_insert(text_buffer, &iter, str, strlen(str));
  printf ("log rel sem  %d\n", view);
  SEMREL();
}

void arduino_out(uint8_t pin, uint8_t type, int value)
{
  char buf[5];
  sprintf(buf,"%d", value);

  if (value == pins[pin].value)
    {
      printf ("No need to write same value, ignoring write\n");
      return ;
    }

  pins[pin].value=value;


  printf("<--- Setting value: %d   on: %d   out:%p\n",
  	 value, pin, pins[pin].out);


  if (type==DIGITAL)
    {
      printf ("DIG get sem\n"); fflush(stdout);
      SEMLOCK();
      gtk_label_set_text(pins[pin].out, buf);
      //gtk_label_set_text(pins[pin].type, "Digital");
      SEMREL();
      printf ("DIG rel sem\n"); fflush(stdout);
      
    }
  else if (type==ANALOG)
    {
      printf ("ANA get sem\n"); fflush(stdout);
      SEMLOCK();
      gtk_label_set_text(pins[pin].out, buf);
      //gtk_label_set_text(pins[pin].type, "Analog");
      SEMREL();
      printf ("ANA rel sem\n"); fflush(stdout);
    }
  printf("---> Setting value: %d   on: %d   out:%p\n",
  	 value, pin, pins[pin].out);
}

void destroy (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();
}

#define SET_BUTTON_SENS_GENERIC(button, state) \
  printf("set %s\n", button);gtk_widget_set_sensitive(GTK_WIDGET( gtk_builder_get_object( builder, button)), state); printf("set %s done\n", button);
//  printf("set %s\n", button);SEMLOCK(); gtk_widget_set_sensitive(GTK_BUTTON( gtk_builder_get_object( builder, button)), state); SEMREL();printf("set done\n");
#define SET_BUTTON_SENS(button)			\
  SET_BUTTON_SENS_GENERIC(button, TRUE) 
#define SET_BUTTON_INSENS(button)		\
  SET_BUTTON_SENS_GENERIC(button, FALSE) 


void set_playing(void)
{
  run = 1;
  searduino_statusbar_push("Arduino program running");
  usleep(1000);
  SET_BUTTON_INSENS("play");
  SET_BUTTON_SENS("pause");
  SET_BUTTON_SENS("stop");
}

void set_pause(void)
{
  run = 2 ;
  usleep(1000);
  searduino_statusbar_push("Arduino program paused");
  SET_BUTTON_SENS("play");
  SET_BUTTON_INSENS("pause");
  SET_BUTTON_SENS("stop");
}

void set_stop(void)
{
  searduino_statusbar_push("Arduino program stoped");
  usleep(1000);
  SET_BUTTON_SENS("play");
  SET_BUTTON_INSENS("pause");
  SET_BUTTON_INSENS("stop");
  printf(" done setting stop\n");
}

int play_clicked_cb(void)
{
  if (run==2)
    {
      set_playing();
    }
  else if (run==0)
    {
      set_playing();
      pthread_create(searduino_thread, NULL, c_arduino_code, NULL);
    }
}

int pause_clicked_cb(void)
{
  if (run == 0 )
    {
      return;
    }
  set_pause();
}

int stop_clicked_cb(void)
{
  run = 0 ;
  usleep(1000*1000);
  pthread_cancel(searduino_thread_impl);
  printf ("stop get sem\n");
  printf ("cancel thread\n");
  printf ("stop rem sem\n");
  printf ("stop tweak buttons\n");
  set_stop();
}

int 
add_boards_to_combo(GtkBuilder *in_builder)
{
  GtkListStore  *store;
  GtkTreeIter iter;
  
  store = GTK_LIST_STORE( gtk_builder_get_object( in_builder, "board_list" ) );


  printf ("builder  %p\n",  in_builder);

  printf ("append?  (%p)\n", store);
  if (store!=NULL)
    {
      printf ("append\n");
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"Apa", -1);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"DlslApa", -1);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"Oldfield", -1);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"Oldfield", -1);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"Oldfield", -1);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"Will", -1);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"Oldham", -1);
    }
}

void* c_arduino_code(void *in)
{
  int i;
  int ctr=0;
  int idx = 0;
  char buf[50];
#define DELAY 10

  printf ("starting thread\n");

  /*
  while(1)
    {
      arduino_out(2, 1, 1);
      usleep(1000*10);
      arduino_out(2, 1, 0);
      usleep(1000*10);
      arduino_out(2, 1, 0);
      usleep(1000*10);
    }
  */
  while(run!=0)
    {
      if (run == 2)
	{
	  usleep (1000*100);
	  printf ("z");fflush(stdout);
	  continue;
	}
      for (i=1;i<=PINS_TO_USE;i++)
	{
	  ctr++;
	  if (ctr>200) ctr=2;
	  if (i%2)
	    {
	      /* ANALOG */
	      arduino_out(i, i%2, (i+ctr));
	    }
	  else
	    {
	      arduino_out(i, i%2, (i+ctr)%2);
	    }
	}
      //      usleep(1000*20);
      sprintf(buf,"#:   %d\n", idx++);
      searduino_log("Liverpool FC\n");
      searduino_log("AS Roma\n");
      searduino_log(buf);
      searduino_log("\n");
      searduino_serial_out("To serial.... seria A\n");
      searduino_serial_out(buf);
      usleep(1000*10);
   }
  return NULL;
}


int add_pins(void)
{
  GtkWidget     *pin;
  GtkBuilder    *pin_builder;
  GError        *error = NULL;
  int col=1;
  int nr_pins=0;
  char buf[10];
  int i;
  GtkBox        *pin_container;
  GtkHBox        *pin_box;

  for (i=1;i<=PINS_TO_USE;i++)
    {
	nr_pins++;
	if (nr_pins>20)
	  {
	    col++;
	    nr_pins=1;
	  }
	sprintf(buf,"%s%d", "pin_box", col);
	pin_container = GTK_BOX( gtk_builder_get_object( builder, buf ) );

	//	printf ("buf: %s\n", buf);

	/* Create pin-widget */
	pin_builder = gtk_builder_new();
	if( ! gtk_builder_add_from_file( pin_builder, "pin.glade", &error ) )
	  {
	    g_warning( "%s", error->message );
	    g_free( error );
	    return( 1 );
	  }
	pin_box = GTK_HBOX( gtk_builder_get_object( pin_builder, "pin_box" ) );
	pins[i].container = pin_box;
	pins[i].name = GTK_LABEL( gtk_builder_get_object( pin_builder, "name" ) );
	sprintf(buf,"%d", i);
	gtk_label_set_text(pins[i].name, buf);
	pins[i].type = GTK_LABEL( gtk_builder_get_object( pin_builder, "type" ) );
	pins[i].mode = GTK_LABEL( gtk_builder_get_object( pin_builder, "mode" ) );
	pins[i].analog_in = GTK_SPIN_BUTTON( gtk_builder_get_object( pin_builder, "analog_in" ));
	pins[i].out  = GTK_LABEL( gtk_builder_get_object( pin_builder, "out" ) );


	//	printf ("pin_box: %p\n", pin_box);
	//printf ("pin_con: %p\n", pin_container);

	gtk_widget_show_all(pin_box);
	gtk_box_pack_start(pin_container, GTK_WIDGET(pin_box), FALSE, TRUE, 0);
    }
}


int
main( int    argc,
      char **argv )
{
    GtkWidget     *window;
    GtkLabel      *top_label;
    GError        *error = NULL;
    int i ; 
    int j ; 


    g_thread_init (NULL);
    gdk_threads_init ();
    gdk_threads_enter ();

    sem_init(&sem, 0, 1);

    /* Init GTK+ */
    gtk_init( &argc, &argv );

    /* Create main window */
    builder = gtk_builder_new();
    if( ! gtk_builder_add_from_file( builder, "searduino.glade", &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }

    /* Get main window pointer from UI */
    window = GTK_WIDGET( gtk_builder_get_object( builder, "main_window" ) );

    //    searduino_statusbar_push("Warming up");

    top_label = GTK_LABEL( gtk_builder_get_object( builder, "toplabel" ) );
    gtk_label_set_markup(top_label, "<b>Searduino 0.89</b>");

    /* Connect signals */
    gtk_builder_connect_signals( builder, NULL );

    /* Do searduino stuff here */
    add_boards_to_combo(builder);
    add_pins();


    /* Destroy builder, since we don't need it anymore */
    //    g_object_unref( G_OBJECT( builder ) );

    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show( window );


    printf ("entering main\n");
    /* Start main loop */
    gtk_main();

    gdk_threads_leave ();

    return( 0 );
}
