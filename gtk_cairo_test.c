#include <gtk/gtk.h>

static void print_hello (GtkWidget *widget,
                         gpointer  data) {

    g_print("Hello!\n");
}


static void quit_activate(GtkWidget *Widget, gpointer user_data){
    g_application_quit(user_data);
}

static void activate (GtkApplication *app,
                     gpointer        user_data) {

    GtkWidget *window;
    GtkWidget *grid, *box, *box_main;
    GtkWidget *button, *button2, *button3;
    GtkWidget *menubar;
    GtkWidget *file_menu, *file_menu_open, *file;
    GtkWidget *menuitem_file, *menuitem_open, *menuitem_quit;
    GtkWidget *toolbar;
    GtkWidget *icon_open;
    GtkWidget *text1;
    GtkToolItem *toolbar_item_open;


    // Configure window
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 1440, 900);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);


    // Menu bar
    menubar = gtk_menu_bar_new();

    // File menu
    file_menu = gtk_menu_new();
    menuitem_file = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem_file), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menuitem_file);


    menuitem_open = gtk_menu_item_new_with_label("Open");
    menuitem_quit = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(G_OBJECT(menuitem_quit), "activate", G_CALLBACK(quit_activate), app);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menuitem_open);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menuitem_quit);
    
    
    // Tool bar
    toolbar = gtk_toolbar_new();
    icon_open = gtk_image_new_from_icon_name("folder-open", GTK_ICON_SIZE_SMALL_TOOLBAR);
    toolbar_item_open = gtk_tool_button_new(icon_open, "Open tool");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), toolbar_item_open, 0);


    GtkStyleContext *toolbar_style;
    // style the toolbar
    toolbar_style = gtk_widget_get_style_context(GTK_WIDGET(toolbar));

    // Main box
    box_main = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    text1 = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(box_main), text1, TRUE, TRUE, 2);

    // Box layout
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 3);
    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 3);
    gtk_box_pack_start(GTK_BOX(box), box_main, TRUE, TRUE, 3);
    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
}

int main (int  argc,
          char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("GTK3.a", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
