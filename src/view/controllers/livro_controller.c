#include "livro_controller.h"
#include <gtk/gtk.h>
#include "../../include/database.h"
#include <stdlib.h>

void on_cadastrar_livros(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);

    GtkEntry *titulo_entry = GTK_ENTRY(gtk_builder_get_object(builder, "titulo_entry"));
    GtkEntry *autor_entry = GTK_ENTRY(gtk_builder_get_object(builder, "autor_entry"));
    GtkEntry *ano_entry = GTK_ENTRY(gtk_builder_get_object(builder, "ano_entry"));
    GtkEntry *disponibilidade_entry = GTK_ENTRY(gtk_builder_get_object(builder, "disponibilidade_entry"));

    if (!titulo_entry || !autor_entry || !ano_entry || !disponibilidade_entry) {
        g_warning("Não foi possível obter todos os campos de entrada");
        return;
    }

    const char *titulo = gtk_editable_get_text(GTK_EDITABLE(titulo_entry));
    const char *autor = gtk_editable_get_text(GTK_EDITABLE(autor_entry));
    const char *ano = gtk_editable_get_text(GTK_EDITABLE(ano_entry));
    const char *disp_text = gtk_editable_get_text(GTK_EDITABLE(disponibilidade_entry));

    if (!titulo || !autor || !ano || !disp_text) {
        g_warning("Todos os campos devem ser preenchidos");
        return;
    }

    Database db = conectaDB("database/BOOKSTACK.db");
    if (db.status != 1) {
        g_warning("Falha ao conectar ao banco de dados");
        return;
    }

    int disp_int = atoi(disp_text);

    char *idLivro = addLivro(db.db, titulo, autor, ano, disp_int);

    if (idLivro) {
        g_print("Livro cadastrado com ID: %s\n", idLivro);
        free(idLivro);

        gtk_editable_set_text(GTK_EDITABLE(titulo_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(autor_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(ano_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(disponibilidade_entry), "");
    } else {
        g_warning("Falha ao cadastrar livro");
    }

    discDB(&db);
}

void on_livros_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "src/book_window.ui", &error)) {
        g_warning("Erro ao carregar book_window.ui: %s", error ? error->message : "Erro desconhecido");
        if (error) g_clear_error(&error);
        g_object_unref(builder);
        return;
    }

    GtkWindow *book_window = GTK_WINDOW(gtk_builder_get_object(builder, "book_window"));
    if (!book_window) {
        g_warning("Falha ao obter a janela de livros do builder");
        g_object_unref(builder);
        return;
    }

    g_object_set_data_full(G_OBJECT(book_window), "builder", builder, (GDestroyNotify)g_object_unref);

    GtkButton *cad_btn = GTK_BUTTON(gtk_builder_get_object(builder, "cadastrar_livro_btn"));
    if (cad_btn) {
        g_signal_connect(cad_btn, "clicked", G_CALLBACK(on_cadastrar_livros), builder);
    }

    GtkButton *back_btn = GTK_BUTTON(gtk_builder_get_object(builder, "back_button"));
    if (back_btn) {
        g_signal_connect(back_btn, "clicked", G_CALLBACK(gtk_widget_destroy), book_window);
    }

    gtk_window_set_application(book_window, GTK_APPLICATION(user_data));
    gtk_window_present(book_window);
}
