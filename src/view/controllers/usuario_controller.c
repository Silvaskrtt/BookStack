#include "usuario_controller.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include "../../db/db_manager.h"

// Callback chamado ao clicar no botão de cadastrar usuário
void on_cadastrar_usuario(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);

    GtkEntry *nome_entry = GTK_ENTRY(gtk_builder_get_object(builder, "nome_entry"));
    GtkEntry *sobrenome_entry = GTK_ENTRY(gtk_builder_get_object(builder, "sobrenome_entry"));
    GtkEntry *cpf_entry = GTK_ENTRY(gtk_builder_get_object(builder, "cpf_entry"));
    GtkEntry *numtelefone_entry = GTK_ENTRY(gtk_builder_get_object(builder, "numtelefone_entry"));

    if (!nome_entry || !sobrenome_entry || !cpf_entry || !numtelefone_entry) {
        g_warning("Não foi possível obter todos os campos de entrada");
        return;
    }

    const char *nome = gtk_editable_get_text(GTK_EDITABLE(nome_entry));
    const char *sobrenome = gtk_editable_get_text(GTK_EDITABLE(sobrenome_entry));
    const char *cpf = gtk_editable_get_text(GTK_EDITABLE(cpf_entry));
    const char *numtelefone = gtk_editable_get_text(GTK_EDITABLE(numtelefone_entry));

    if (!nome || !sobrenome || !cpf || !numtelefone) {
        g_warning("Todos os campos devem ser preenchidos");
        return;
    }

    Database db = db_init(get_db_path());
    if (db.status != 1) {
        g_warning("Falha ao conectar ao banco de dados");
        return;
    }

    char *idUsuario = db_user_create(db, nome, sobrenome, cpf, numtelefone);
    if (idUsuario) {
        g_print("Usuário cadastrado com ID: %s\n", idUsuario);
        free(idUsuario);

        gtk_editable_set_text(GTK_EDITABLE(nome_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(sobrenome_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(cpf_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(numtelefone_entry), "");
    } else {
        g_warning("Falha ao cadastrar usuário");
    }

    db_close(&db);
}

// Abre a janela de gerenciamento de usuários
void on_users_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "src/forms/users_window.ui", &error)) {
        g_warning("Erro ao carregar users_window.ui: %s", error ? error->message : "Erro desconhecido");
        if (error) g_clear_error(&error);
        g_object_unref(builder);
        return;
    }

    GtkWindow *users_window = GTK_WINDOW(gtk_builder_get_object(builder, "users_window"));
    if (!users_window) {
        g_warning("Falha ao obter a janela de usuários do builder");
        g_object_unref(builder);
        return;
    }

    g_object_set_data_full(G_OBJECT(users_window), "builder", builder, (GDestroyNotify)g_object_unref);

    GtkButton *cad_btn = GTK_BUTTON(gtk_builder_get_object(builder, "cadastrar_usuario_btn"));
    if (cad_btn) {
        g_signal_connect(cad_btn, "clicked", G_CALLBACK(on_cadastrar_usuario), builder);
    }

    // Conecta botão de voltar
    GtkButton *back_btn = GTK_BUTTON(gtk_builder_get_object(builder, "back_button"));
    if (back_btn) {
        g_signal_connect(back_btn, "clicked", G_CALLBACK(gtk_window_destroy), users_window);
    }

    gtk_window_set_application(users_window, GTK_APPLICATION(user_data));
    gtk_window_present(users_window);
}
