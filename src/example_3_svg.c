#include <cairo.h>
#include <cairo-svg.h> 
 
int main(void) {

  // Variables  
  cairo_surface_t *surface;
  cairo_t *cr;

  // Create cairo surface
  surface = cairo_svg_surface_create("svgfile.svg", 390, 60);

  // Create context
  cr = cairo_create(surface);

  // Set font style
  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

  // Set font size
  cairo_set_font_size(cr, 40.0);

  // Set source color
  cairo_set_source_rgb(cr, 0, 0, 0);
  
  // Move to 10, 50
  cairo_move_to(cr, 10.0, 50.0);

  // Draw text
  cairo_show_text(cr, "Hello, world.");

  // Cleanup
  cairo_surface_destroy(surface);
  cairo_destroy(cr);

  return 0;
}
