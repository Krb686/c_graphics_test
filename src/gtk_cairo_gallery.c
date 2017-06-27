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


typedef struct {
    int x1, y1, x2, y2;
    int sa1, sa2, ea1, ea2;
    int endtype;
} ConnectorStraight;

typedef struct {
    int x1, y1, x2, y2;
    int c1x1, c1y1, c1x2, c1y2;
    int c2x1, c2y1, c2x2, c2y2;
} ConnectorCurve;


static void update_drawing(cairo_t *);

void connector_straight_new(cairo_t *cr, ConnectorStraight *ac, int x1, int y1, int x2, int y2, int endtype){
    ac = malloc(sizeof(ConnectorStraight));
    ac->x1=x1;
    ac->x2=x2;
    ac->y1=y1;
    ac->y2=y2;

    ac->endtype=endtype;

    
    cairo_move_to(cr, x1, y1);
    cairo_line_to(cr, x2, y2);
    cairo_stroke(cr);
}

void connector_curve_new(cairo_t *cr, ConnectorCurve *cc, int x1, int y1, int x2, int y2, int parallel_ends){
    cc = malloc(sizeof(ConnectorCurve));
    cc->x1 = x1;
    cc->x2 = x2;
    cc->y1 = y1;
    cc->y2 = y2;

    if(parallel_ends){
        cc->c1x1 = x1;
        cc->c1y1 = y1 + (y2-y1)/2;
        cc->c1x2 = x1 + (x2-x1)/4;
        cc->c1y2 = y1 + (y2-y1)/2;

        cairo_move_to(cr, x1, y1);
        cairo_curve_to(cr, cc->c1x1, cc->c1y1, cc->c1x2, cc->c1y2, x1+(x2-x1)/2, y1+(y2-y1)/2);
        cairo_stroke(cr);

        cc->c2x1 = x2;
        cc->c2y1 = y1 + (y2 - y1) / 2;
        cc->c2x2 = x2;
        cc->c2y2 = y1 + (y2 - y1) / (4/3);

        cairo_move_to(cr, x1+(x2-x1)/2, y1+(y2-y1)/2);
        cairo_curve_to(cr, cc->c2x1, cc->c2y1, cc->c2x2, cc->c2y2, x2, y2);
        cairo_stroke(cr);

    } else {
        cc->c1x1 = x1;
        cc->c1y1 = y2;
        cc->c1x2 = x1 + (x2 - x1) / 2;
        cc->c1y2 = y2;

        cc->c2x1=0;
        cc->c2y1=0;
        cc->c2x2=0;
        cc->c2y2=0;

        cairo_move_to(cr, x1, y1);
        cairo_curve_to(cr, cc->c1x1, cc->c1y1, cc->c1x2, cc->c1y2, x2, y2);
        cairo_stroke(cr);
    }
}

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


    ConnectorCurve *cc1, *cc2;
    connector_curve_new(cr, cc1, 550, 300, 785, 600, 0);
    connector_curve_new(cr, cc2, 550, 300, 800, 585, 1);

    ConnectorStraight *ac;
    connector_straight_new(cr, ac, 50, 50, 350, 350, 1);
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
