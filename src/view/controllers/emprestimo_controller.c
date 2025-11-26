#include "emprestimo_controller.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include "../../db/db_manager.h"

void on_cadastrar_emprestimo(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);

    GtkEntry *dtEmp_entry = GTK_ENTRY(gtk_builder_get_object(builder, "dtEmp_entry"));
    GtkEntry *dtDevPre_entry = GTK_ENTRY(gtk_builder_get_object(builder, "dtDevPre_entry"));
    GtkEntry *idlivro_entry = GTK_ENTRY(gtk_builder_get_object(builder, "idlivro_entry"));
    GtkEntry *iduser_entry = GTK_ENTRY(gtk_builder_get_object(builder, "iduser_entry"));

    if (!dtEmp_entry || !dtDevPre_entry || !idlivro_entry || !iduser_entry) {
        g_warning("Não foi possível obter todos os campos de entrada");
        return;
    }

    const char *dtEmp = gtk_editable_get_text(GTK_EDITABLE(dtEmp_entry));
    const char *dtDevPre = gtk_editable_get_text(GTK_EDITABLE(dtDevPre_entry));
    const char *idlivro = gtk_editable_get_text(GTK_EDITABLE(idlivro_entry));
    const char *iduser = gtk_editable_get_text(GTK_EDITABLE(iduser_entry));

    if (!dtEmp || !dtDevPre || !idlivro || !iduser) {
        g_warning("Todos os campos devem ser preenchidos");
        return;
    }

    Database db = db_init(get_db_path());
    if (db.status != 1) {
        g_warning("Falha ao conectar ao banco de dados");
        return;
    }

    char *idEmp = db_loan_create(db, dtEmp, dtDevPre, idlivro, iduser);
    if (idEmp) {
        g_print("Empréstimo cadastrado com ID: %s\n", idEmp);
        free(idEmp);

        gtk_editable_set_text(GTK_EDITABLE(dtEmp_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(dtDevPre_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(idlivro_entry), "");
        gtk_editable_set_text(GTK_EDITABLE(iduser_entry), "");
    } else {
        g_warning("Falha ao cadastrar usuário");
    }

    db_close(&db);
}

void on_emp_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    if (!gtk_builder_add_from_file(builder, "src/forms/emp_window.ui", &error)) {
        g_warning("Erro ao carregar emp_window.ui: %s", error ? error->message : "Erro desconhecido");
        if (error) g_clear_error(&error);
        g_object_unref(builder);
        return;
    }

    GtkWindow *emp_window = GTK_WINDOW(gtk_builder_get_object(builder, "emp_window"));
    if (!emp_window) {
        g_warning("Falha ao obter a janela de empréstimo do builder");
        g_object_unref(builder);
        return;
    }

    g_object_set_data_full(G_OBJECT(emp_window), "builder", builder, (GDestroyNotify)g_object_unref);

    GtkButton *cad_btn = GTK_BUTTON(gtk_builder_get_object(builder, "cadastrar_emprestimo_btn"));
    if (cad_btn) {
        g_signal_connect(cad_btn, "clicked", G_CALLBACK(on_cadastrar_emprestimo), builder);
    }

    GtkButton *back_btn = GTK_BUTTON(gtk_builder_get_object(builder, "back_button"));
    if (back_btn) {
        g_signal_connect(back_btn, "clicked", G_CALLBACK(gtk_window_destroy), emp_window);
    }

    gtk_window_set_application(emp_window, GTK_APPLICATION(user_data));
    gtk_window_present(emp_window);
}
