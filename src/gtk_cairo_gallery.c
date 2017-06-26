#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

// TODO - custom objects
//  - codebox
//  - arrow
// TODO - dashed lines
// TODO - line caps

// ---- Paths ----
// cairo_arc
// cairo_arc_negative
// cairo_rectangle
//
//cairo_stroke
//cairo_stroke_preserve
//



static void update_drawing(cairo_t *);

static gboolean draw_handler(GtkWidget *widget, cairo_t *cr, gpointer user_data){
    update_drawing(cr);
    return FALSE;
}

static void update_drawing(cairo_t *cr){
    double TWOPI = 2*M_PI;

    cairo_set_source_rgb(cr, 0, 0, 0);
    

    // Example 1 - text
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 20.0);
    cairo_move_to(cr, 10.0, 20.0);
    cairo_show_text(cr, "Hello!");

    // Example 2 - lines
    cairo_set_line_width(cr, 1.0);
    cairo_move_to(cr, 20, 40);
    cairo_line_to(cr, 40, 40);
    cairo_stroke(cr);

    // Example 3 - arc
    cairo_arc(cr, 20, 80, 5, 0, (180*(M_PI / 180)));
    cairo_stroke(cr);

    // Example 4 - arc_negative
    cairo_arc_negative(cr, 40, 80, 5, 0, (180*(M_PI/180)));
    cairo_stroke(cr);

    // Example 5 - Bezier spline
    cairo_move_to(cr, 20, 100);
    cairo_curve_to(cr, 40, 130, 60, 110, 60, 100);
    cairo_stroke(cr);

    // Example 6 - Rectangle
    cairo_rectangle(cr, 20, 160, 60, 20);
    cairo_stroke(cr);

    // Example 7 - Fill
    cairo_arc(cr, 20, 200, 10, 0, TWOPI);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 0.6, 0.6, 0.2);
    cairo_fill(cr);

    // Codebox
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_rectangle(cr, 400, 200, 300, 100);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
    cairo_fill(cr);


    cairo_arc(cr, 800, 600, 15, 0, TWOPI);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);

    cairo_move_to(cr, 550, 300);
    cairo_curve_to(cr, 550, 600, 750, 600, 785, 600);
    cairo_stroke(cr);
}

static gint handle_opts(GtkApplication *app, GVariantDict *opts, gpointer user_data){
    printf("Handling local options\n");
    return -1;
}

static void setup_app(GtkApplication *app, gpointer user_data){
    printf("Setting up the application\n");
    GtkApplicationWindow *window;
    GtkBuilder *builder;
    GtkDrawingArea *drawbox;

    // Create the GTK builder
    builder = gtk_builder_new_from_file("builder.ui");

    // Create and configure window
    window = gtk_builder_get_object(builder, "window1");
    gtk_window_set_title(GTK_WINDOW(window), "Cairo Gallery");
    gtk_window_set_default_size(GTK_WINDOW(window), 1440, 900);

    // Grab reference to the drawbox
    drawbox = gtk_builder_get_object(builder, "drawingarea1");
    g_signal_connect(G_OBJECT(drawbox), "draw", G_CALLBACK(draw_handler), NULL);

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
