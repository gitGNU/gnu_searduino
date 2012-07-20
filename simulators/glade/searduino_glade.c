/*
 * Compile me with:
   gcc -o seagla searduino_glade.c $(pkg-config --cflags --libs gtk+-3.0 gmodule-3.0)
 */

#include <gtk/gtk.h>

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
      gtk_list_store_set (store, &iter, 0, (gchararray)"Oldfield", -1);

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter, 0, (gchararray)"Oldfield", -1);
    }
}

int
main( int    argc,
      char **argv )
{
    GtkWidget  *window;
    GtkWidget  *top_label;
    GtkWidget  *status;
    GError     *error = NULL;
    GtkBuilder *builder;



    /* Init GTK+ */
    gtk_init( &argc, &argv );

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    /* Load UI from file. If error occurs, report it and quit application.
     * Replace "tut.glade" with your saved project. */
    if( ! gtk_builder_add_from_file( builder, "searduino.glade", &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }

    printf ("builder  %p\n",  builder);

    /* Get main window pointer from UI */
    window = GTK_WIDGET( gtk_builder_get_object( builder, "main_window" ) );

    top_label = GTK_WIDGET( gtk_builder_get_object( builder, "toplabel" ) );
    gtk_label_set_markup(top_label, "<b>Searduino 0.89</b>");

    status = GTK_STATUSBAR( gtk_builder_get_object( builder, "status" ) );
    gtk_statusbar_push(status, 1, "Warming up");


    /* Connect signals */
    gtk_builder_connect_signals( builder, NULL );

    /* Do searduino stuff here */

    add_boards_to_combo(builder);


    /* Destroy builder, since we don't need it anymore */
    g_object_unref( G_OBJECT( builder ) );

    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show( window );




    /* Start main loop */
    gtk_main();


    return( 0 );
}
