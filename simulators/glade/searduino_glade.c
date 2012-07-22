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

pthread_t   searduino_thread_impl;
pthread_t  *searduino_thread = &searduino_thread_impl;
#define NR_OF_PINS 100
#define PINS_TO_USE 10

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
#define SEMLOCK()     gdk_threads_enter ()
#define SEMREL()      gdk_threads_leave ()
#endif

#ifdef PTHREAD_SEM
#define SEMLOCK()     sem_wait(&sem);
#define SEMREL()      sem_post(&sem);
#endif

#define SERIAL_OUTPUT_VIEW 0
#define LOG_OUTPUT_VIEW    1

#define searduino_log(str)        searduino_log_general(str, LOG_OUTPUT_VIEW)
#define searduino_serial_out(str) searduino_log_general(str, SERIAL_OUTPUT_VIEW)

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
  SEMLOCK();
  gtk_text_buffer_get_end_iter(text_buffer, &iter);
  gtk_text_view_scroll_to_iter(text_view, &iter, 0.0, TRUE, 1.0, 1.0);
  gtk_text_buffer_insert(text_buffer, &iter, str, strlen(str));
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


  printf("Setting value: %d   on: %d   out:%p\n",
  	 value, pin, pins[pin].out);


  if (type==DIGITAL)
    {
      SEMLOCK();
      gtk_label_set_text(pins[pin].out, buf);
      //gtk_label_set_text(pins[pin].type, "Digital");
      SEMREL();
      
    }
  else if (type==ANALOG)
    {
      SEMLOCK();
      gtk_label_set_text(pins[pin].out, buf);
      //gtk_label_set_text(pins[pin].type, "Analog");
      SEMREL();
    }
}

void destroy (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();
}


int play_clicked_cb(void)
{
  GtkLabel *label;
  GtkEntry *entry;
  GtkButton *button;
  printf ("play\n");
  int i ; 

  label = GTK_LABEL(gtk_builder_get_object(builder, "label7" ) );
  button = GTK_BUTTON(gtk_builder_get_object(builder, "button1" ) );
  entry = GTK_ENTRY(gtk_builder_get_object(builder, "entry1" ) );
  
  gdk_threads_enter ();
  gtk_entry_set_text(entry, "annananananan");
  gtk_label_set_label(label, "Ny text");
  gdk_threads_leave ();
  
}

int pause_clicked_cb(void)
{
  GtkLabel *label;
  GtkEntry *entry;
  GtkButton *button;
  printf ("pause\n");
  int i ; 

  label = GTK_LABEL(gtk_builder_get_object(builder, "label7" ) );
  button = GTK_BUTTON(gtk_builder_get_object(builder, "button1" ) );
  entry = GTK_ENTRY(gtk_builder_get_object(builder, "entry1" ) );

  /* get GTK thread lock */
  gdk_threads_enter ();
  gtk_entry_set_text(entry, "einar");
  gtk_label_set_label(label, "Nystroem");
  gdk_threads_leave ();
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

  usleep(1000*2000);
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
  while(1)
    {
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

	printf ("buf: %s\n", buf);

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

	printf ("pin_box: %p\n", pin_box);
	printf ("pin_con: %p\n", pin_container);

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
    GtkStatusbar  *status;
    GError        *error = NULL;
    int i ; 
    int j ; 


    g_thread_init (NULL);
    gdk_threads_init ();
    gdk_threads_enter ();

    sem_init(&sem, 0, 1);
    pthread_create(searduino_thread, NULL, c_arduino_code, NULL);

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

    top_label = GTK_LABEL( gtk_builder_get_object( builder, "toplabel" ) );
    gtk_label_set_markup(top_label, "<b>Searduino 0.89</b>");

    status = GTK_STATUSBAR( gtk_builder_get_object( builder, "status" ) );
    gtk_statusbar_push(status, 1, "Warming up");

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
