#include "FilePrompt.hpp"

#include <functional>

#include <gtk-3.0/gtk/gtk.h>

static void createPickerCallback(GtkApplication* app, gpointer data){
    auto outName = *reinterpret_cast<std::reference_wrapper<std::string>*>(data);

    GtkWindow* window = reinterpret_cast<GtkWindow*>(gtk_application_window_new(app));

    const GtkFileChooserAction fcAction = GTK_FILE_CHOOSER_ACTION_OPEN;

    GtkFileChooserNative* native = gtk_file_chooser_native_new("pick file", window, fcAction, NULL, NULL);
    const auto res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
    if(res == GTK_RESPONSE_ACCEPT){
        char* fileName;
        GtkFileChooser* chooser = GTK_FILE_CHOOSER(native);
        fileName = gtk_file_chooser_get_filename(chooser);
        outName.get() = fileName;
        g_free(fileName);
    }
    g_object_unref(native);
    gtk_widget_destroy(GTK_WIDGET(window));
}

static void runGtkApp(std::reference_wrapper<std::string> fileNameReference){
    GtkApplication* app = gtk_application_new("com.github.MrKeviscool.Shittle", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(createPickerCallback), &fileNameReference);
    g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);
}

std::string askForFileBlocking(){
    std::string fileName;
    runGtkApp(fileName);
    return fileName;
}

std::future<std::string> askForFileDefered(){
    std::packaged_task<std::string()> task(askForFileBlocking);
    auto future = task.get_future();
    std::thread thread(std::move(task));
    thread.detach();
    return future;
}
