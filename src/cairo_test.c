#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>

int
main (int argc, char *argv[])
{

        // Variables
        cairo_surface_t *surface;
        cairo_t *cr;

        // Create cairo surface
        surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 240, 80);

        // Create context
        cr = cairo_create(surface);

        // Set font style
        cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

        // Set font size
        cairo_set_font_size(cr, 32.0);

        // Set source color
        cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);

        // Move to 10, 50
        cairo_move_to(cr, 10.0, 50.0);

        // Draw text
        cairo_show_text(cr, "Hello, world");

        // Draw surface to png
        cairo_surface_write_to_png(surface, "hello.png");

        // Cleanup
        cairo_destroy(cr);
        cairo_surface_destroy(surface);

        return 0;
}
