#include <FilePrompt.hpp>

//TODO (whole file)

#if defined(USE_GTK) && !defined(USE_QT)
#include <gtk/gtk.h>
std::string askForFile(){
    GtkWidget* parentWindow = gtk_window_new(); //crashes here
    
    const GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    
    /*GtkWidget* picker =*/ gtk_file_chooser_dialog_new("Open File", reinterpret_cast<GtkWindow*>(parentWindow), action, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    return "";
}

#elif defined(USE_QT) && !defined(USE_GTK)
#include <QtWidgets/qfiledialog.h>
std::string askForFile(){
//    QWidget widget;
//    Qt::WindowFlags windowFlags;
//    QFileDialog fileDialog(&widget, windowFlags);

    return "";
}

#else 
#error ERROR, MUST DEFINE 'USE_GTK' *OR* 'USE_QT'
#endif