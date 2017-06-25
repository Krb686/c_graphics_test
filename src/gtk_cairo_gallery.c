#include <cairo.h>
#include <gtk/gtk.h>


static void update_drawing(cairo_t *);

static gboolean draw_handler(GtkWidget *widget, cairo_t *cr, gpointer user_data){
    update_drawing(cr);
    return FALSE;
}

static void update_drawing(cairo_t *cr){

}

static gint handle_opts(GtkApplication *app, GVariantDict *opts, gpointer user_data){
    printf("Handling local options\n");
    return -1;
}

static void setup_app(GtkApplication *app, gpointer user_data){
    printf("Setting up the application\n");
    GtkApplicationWindow *window;
    GtkBuilder *builder;

    // Create the GTK builder
    builder = gtk_builder_new_from_file("builder.ui");

    // Create and configure window
    window = gtk_builder_get_object(builder, "window1");
    gtk_window_set_title(GTK_WINDOW(window), "Cairo Gallery");
    gtk_window_set_default_size(GTK_WINDOW(window), 1440, 900);

    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(app));
    gtk_widget_show_all(window); 
}


int main(int argc, char* argv[]){
    GtkApplication *app;
    int status;

    // Create the application object
    app = gtk_application_new("GTK3.a", G_APPLICATION_FLAGS_NONE);

    // Connect the setup_app function on 'activate'
    g_signal_connect(app, "activate", G_CALLBACK(setup_app), NULL);
    g_signal_connect(app, "handle-local-options", G_CALLBACK(handle_opts), NULL);

    // Add cmdline options
    g_application_add_main_option(app, "version", 'v', G_OPTION_FLAG_NONE, G_OPTION_ARG_NONE, "Display gtk_cairo_gallery version", ""); 

    // Run the application
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
