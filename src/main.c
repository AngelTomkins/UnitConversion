#include <gtk/gtk.h>
#include <string.h>

typedef struct{
    GtkWidget *w_txt_f;
    GtkWidget *w_txt_c;
    GtkWidget *w_txt_k;
} app_widgets;


int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    app_widgets *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    widgets->w_txt_c = GTK_WIDGET(gtk_builder_get_object(builder, "txt_c"));
    widgets->w_txt_f = GTK_WIDGET(gtk_builder_get_object(builder, "txt_f"));
    widgets->w_txt_k = GTK_WIDGET(gtk_builder_get_object(builder, "txt_k"));

    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    g_slice_free(app_widgets, widgets);

    return 0;
}

void on_txt_c_activate(GtkEntry *entry, app_widgets *app_wdgts) {

    char tmp[16];
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(app_wdgts->w_txt_c)));

    float num = 0;
    sscanf(tmp, "%f", &num);

    float numk = num + 273.15;
    float numf = (num * 1.8) + 32;

    char outk[16];
    char outf[16];

    sprintf(outk, "%.2f", numk); 
    sprintf(outf, "%.2f", numf); 


    gtk_entry_set_text(GTK_ENTRY(app_wdgts->w_txt_k), outk);
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->w_txt_f), outf);

}

void on_txt_f_activate(GtkEntry *entry, app_widgets *app_wdgts) {


    char tmp[16];
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(app_wdgts->w_txt_f)));

    float num = 0;
    sscanf(tmp, "%f", &num);

    float numk = (num + 459.67) / 1.8;
    float numc = (num - 32) / 1.8;

    char outk[16];
    char outc[16];

    sprintf(outk, "%.2f", numk); 
    sprintf(outc, "%.2f", numc); 


    gtk_entry_set_text(GTK_ENTRY(app_wdgts->w_txt_k), outk);
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->w_txt_c), outc);
}

void on_txt_k_activate(GtkEntry *entry, app_widgets *app_wdgts) {

    char tmp[16];
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(app_wdgts->w_txt_k)));

    float num = 0;
    sscanf(tmp, "%f", &num);

    float numc = num - 273.15;  
    float numf = num * 1.8 - 459.67;

    char outc[16];
    char outf[16];

    sprintf(outc, "%.2f", numc); 
    sprintf(outf, "%.2f", numf); 


    gtk_entry_set_text(GTK_ENTRY(app_wdgts->w_txt_c), outc);
    gtk_entry_set_text(GTK_ENTRY(app_wdgts->w_txt_f), outf);
}



// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
