#ifndef USUARIO_CONTROLLER_H
#define USUARIO_CONTROLLER_H

#include <gtk/gtk.h>

// Exported callbacks used by gui.c (connected to main window buttons)
void on_users_clicked(GtkButton *button, gpointer user_data);
void on_cadastrar_usuario(GtkButton *button, gpointer user_data);

#endif // USUARIO_CONTROLLER_H
