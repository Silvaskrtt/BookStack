/* 
 * BookStack - Launcher da aplicação GTK
 * Ponto de entrada que inicializa e executa a interface gráfica
 */

#include <gtk/gtk.h>
#include "view/gui.h"

int main(int argc, char **argv) {
    // Inicializa o GTK
    if (!gtk_init_check()) {
        g_printerr("Falha ao inicializar GTK\n");
        return 1;
    }

    // Cria a aplicação GTK
    GtkApplication *app = gtk_application_new("org.gtk.bookstack", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Executa a aplicação (loop principal)
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return status;
}