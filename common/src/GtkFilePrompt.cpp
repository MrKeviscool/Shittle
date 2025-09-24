#include "FilePrompt.hpp"

#include <functional>

#include <gtk-3.0/gtk/gtk.h>

enum class Action {
    load,
    create,
};

struct UiCtx {
    std::string& outStr;
    Action action;
};

static void createPickerCallback(GtkApplication* app, gpointer _ctx){
    UiCtx& ctx = *static_cast<UiCtx*>(_ctx);
    std::string& outName = ctx.outStr;
    GtkWindow* window = reinterpret_cast<GtkWindow*>(gtk_application_window_new(app));

    const GtkFileChooserAction fcAction =
        ctx.action == Action::load ?
        GTK_FILE_CHOOSER_ACTION_OPEN :
        GTK_FILE_CHOOSER_ACTION_SAVE;

    GtkFileChooserNative* native = gtk_file_chooser_native_new("pick file", window, fcAction, NULL, NULL);

    if (ctx.action == Action::create) 
        gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(native), true);

    const auto res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));

    if(res == GTK_RESPONSE_ACCEPT){
        char* fileName;
        GtkFileChooser* chooser = GTK_FILE_CHOOSER(native);
        fileName = gtk_file_chooser_get_filename(chooser);
        outName = fileName;
        g_free(fileName);
    }
    g_object_unref(native);
    gtk_widget_destroy(GTK_WIDGET(window));
}

static void runGtkApp(std::reference_wrapper<std::string> fileNameReference, Action action) {
    UiCtx uiCtx{ fileNameReference, action };
    GtkApplication* app = gtk_application_new("com.github.MrKeviscool.Shittle", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(createPickerCallback), &uiCtx);
    g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);
}

static std::future<std::string> deferPrompt(Action action) {
    std::packaged_task<std::string()> task(
        action == Action::load? askForFileBlocking : askForSaveLocationBlocking
    );

    auto future = task.get_future();
    std::thread thread(std::move(task));
    thread.detach();
    return future;
}

std::string askForFileBlocking() {
    std::string fileName;
    runGtkApp(fileName, Action::load);
    return fileName;
}

std::future<std::string> askForFileDeferred() {
    return deferPrompt(Action::load);
}

std::string askForSaveLocationBlocking() {
    std::string saveLoc;
    runGtkApp(saveLoc, Action::create);
    return saveLoc;
}

std::future<std::string> askForSaveLocationDeferred() {
    return deferPrompt(Action::create);
}
