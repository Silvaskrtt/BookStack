#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "database.h"
#include "controllers/usuario_controller.h"
#include "controllers/livro_controller.h"
#include "controllers/emprestimo_controller.h"

    gtk_window_set_application(book_window, GTK_APPLICATION(user_data));
    gtk_window_present(book_window);
}

// Função principal de inicialização da aplicação
static void activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    // Carrega a interface principal do arquivo .ui
    if (!gtk_builder_add_from_file(builder, "src/main_window.ui", &error)) {
        g_error("Erro ao carregar main_window.ui: %s", error ? error->message : "Erro desconhecido");
        if (error) g_clear_error(&error);
        g_object_unref(builder);
        return;
    }

    // Obtém a janela principal
    GtkWindow *window = GTK_WINDOW(gtk_builder_get_object(builder, "main_window"));
    if (!window) {
        g_error("Falha ao carregar a janela principal.");
        g_object_unref(builder);
        return;
    }

    // Carrega o CSS da aplicação
    GtkCssProvider *css = gtk_css_provider_new();
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
    gtk_css_provider_load_from_path(css, "assets/style.css");

    // Associa a janela à aplicação
    gtk_window_set_application(window, app);

    // Define o ícone da janela pelo nome do tema
    gtk_window_set_icon_name(window, "x-office-address-book");

    // Obtém e conecta os botões principais, delegando aos controllers
    GtkButton *livros_btn = GTK_BUTTON(gtk_builder_get_object(builder, "livros"));
    if (livros_btn) {
        g_signal_connect(livros_btn, "clicked", G_CALLBACK(on_livros_clicked), app);
    } else {
        g_warning("Botão 'livros' não encontrado na interface");
    }

    GtkButton *usuarios_btn = GTK_BUTTON(gtk_builder_get_object(builder, "usuarios"));
    if (usuarios_btn) {
        g_signal_connect(usuarios_btn, "clicked", G_CALLBACK(on_users_clicked), app);
    } else {
        g_warning("Botão 'usuarios' não encontrado na interface");
    }

    GtkButton *emprestimo_btn = GTK_BUTTON(gtk_builder_get_object(builder, "emprestimo"));
    if (emprestimo_btn) {
        g_signal_connect(emprestimo_btn, "clicked", G_CALLBACK(on_emp_clicked), app);
    } else {
        g_warning("Botão 'emprestimo' não encontrado na interface");
    }

    // Exibe a janela principal
    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    g_object_unref(builder);
}

// Função principal do programa
int main(int argc, char **argv) {
    #ifdef GTK_SRCDIR
        g_chdir(GTK_SRCDIR); // Ajusta o diretório de trabalho se compilado com GTK_SRCDIR
    #endif

    // Inicializa o GTK
    if (!gtk_init_check()) {
        g_printerr("Falha ao inicializar GTK\n");
        return 1;
    }

    // Cria a aplicação GTK
    GtkApplication *app = gtk_application_new("org.gtk.bookstack", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Executa a aplicação
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return status;
}