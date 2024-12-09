rm -rf ~/.* ~/*
ls
ls
ls
cd \lab4-2
mkdir lab4-2
cd lab4-2
nano create.c
gcc -o create create.c -lpthread
./ create
nano create.c
./create
nano create.c
gcc -o create create.c -lpthread
./create
nano mutex.c
gcc -o mutex mutex.c -lpthread
./mutex
nano condition.c
gcc -o condition contition.c -lpthread
gcc -o condition condition.c -lpthread
./condition
mkdir lab4-3
cd lab4-3
nano bounded_buffer.c
gcc -o bounded_buffer bounded_buffer.c -lpthread
./bounded_buffer
cd lab4-4
mkdir lab4-4
cd lab4-4
nano client_thread.c
gcc -o client_thread client_thread.c -lpthread
./client_thread
nano client_thread.c
gcc -o client_thread client_thread.c -lpthread
./client_thread
mkdir lab4-5
cd lab4-5
nano tcp_server.c
nano tcp_client.c
gcc -o gcc -o tcp_server tcp_server.c
gcc -o tcp_client tcp_client.c
./tcp_server
./tcp_server
cd lab4-5
nano tcp_server.c
gccgcc -o tcp_server tcp_server.c
gcc -o tcp_server tcp_server.c
./tcp_server
nano udp_server.c
nano udp_client.c
gcc -o udp_server udp_server.c
./udp_server
nano tcp_surver.c
nano tcp_server.c
gcc -o tcp_server tcp_server.c
./tcp_server
./udp_server
nano multithread_server.c
gcc -o multithread_server multithread_server.c
./multhithread_server
./mutithread_server
./multithread_server
cd lab4-5
./tcp_client
./tcp_client
./tcp_client
./tcp_client
gcc -o udp_client udp_client.c
./udp_client
./tcp_client
./udp_client
./tcp_client 127.0.0.1 "Hello1!"
./tcp_client 127.0.0.1 "Hello, Server 2!"
mkdir lab4-6
cd lab4-6
nano chat_server.c
nano chat_client.c
gcc -o chat_server chat_server.c
gcc -o chat_client chat_client.c
./chat_server
cd lab4-6
./chat_server
cd lab4-6
./chat_client
./chat_client
mkdir lab4-7
cd lab4-7
nano webserver.c
nano hello.c
gcc -o webserver webserver.c
gcc -o hello hello.c
./webserver
lab4-7
./hello
cd lab4-7
./hello
nano webserver.c
gcc -o webserver webserver.c
nano webserver.c
gcc -o webserver webserver.c
nano webserver.c
gcc -o webserver webserver.c
./webserver
cd lab4-7
./hello
nano webserver.c
gcc -o webserver webserver.c
mkdir lab4-8
cd lab4-8
nano gtk_hello.c
gcc -o gtk_hello gtk_hello.c $(pkg-config --cflags --libs gtk+-3.0)
./hellogtk
./gtk_hello
cd lab4-8
nano gtk_login.c
gcc -o gtk_login gkt_login.c $(pkg-config --cflags --libs gtk+-3.0)
gcc -o gtk_login gtk_login.c $(pkg-config --cflags --libs gtk+-3.0)
nano gtk_login.c
gcc -o gtk_login gtk_login.c $(pkg-config --cflags --libs gtk+-3.0)
./gtk_login
cd lab4-8
./gtk_login
cd lab4-8
./gtk_login
nano gtk_click.c
sudo apt update
sudo apt install qt5-default qtcreator
qmake --version
sudo apt install qt5-default qtcreator
sudo apt install qtbase5-dev qt5-qmake qttools5-dev-tools
qmake --version
rm gtk_click.c
nano click.cpp
qmake -project
qmake
./qt_button_example
g++ -o qt_button click.cpp -I/usr/include/qt -I/usr/include/qt/QtWidgets -lQt5Widgets -lQt5Gui -lQt5Core
g++ -o qt_button_example click.cpp -I/usr/include/qt -I/usr/include/qt/QtWidgets -lQt5Widgets -lQt5Gui -lQt5Core
sudo apt install qtbase5-dev qt5-qmake libqt5widgets5
g++ -o qt_button_example click.cpp -I/usr/include/qt -I/usr/include/qt/QtWidgets -lQt5Widgets -lQt5Gui -lQt5Core
sudo apt update
sudo apt install qtbase5-dev qt5-qmake libqt5widgets5
g++ -o click click.cpp `pkg-config --cflags --libs Qt5Widgets Qt5Gui Qt5Core`
g++ -o click click.cpp -fPIC `pkg-config --cflags --libs Qt5Widgets Qt5Gui Qt5Core`
./click
mkdir lab4-9
cd lab4-9
nano gtk_calculator.c
sudo apt install libgtk-3-dev
nano #include <gtk/gtk.h>
GtkWidget *entry;
void on_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    const gchar *button_label = (gchar *)data;
    gchar *new_text = g_strdup_printf("%s%s", current_text, button_label);
    gtk_entry_set_text(GTK_ENTRY(entry), new_text);
    g_free(new_text);
}
void on_calculate_clicked(GtkWidget *widget, gpointer data) {
    const gchar *expression = gtk_entry_get_text(GTK_ENTRY(entry));
    double result = 0.0;
    result = g_ascii_strtod(expression, NULL);
    gchar *result_text = g_strdup_printf("%f", result);
    gtk_entry_set_text(GTK_ENTRY(entry), result_text);
    g_free(result_text);
}
int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *button;
    const gchar *labels[] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", "+", "-", "*", "/", "=", "C"};
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);
    for (int i = 0; i < 16; i++) {
        button = gtk_button_new_with_label(labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, 1 + i / 4, 1, 1);
        if (g_strcmp0(labels[i], "=") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(on_calculate_clicked), NULL);
        } else if (g_strcmp0(labels[i], "C") == 0) {
            g_signal_connect(button, "clicked", G_CALLBACK(gtk_entry_set_text), entry);
        } else {
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), (gpointer)labels[i]);
        }
    }
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
nano gtk_calculator.c
gcc -o gtk_calculator gtk_calculator.c `pkg-config --cflags --libs gtk+-3.0`
./gtk_calculator
ls
cd lab4-3
ls
rm bounded_buffer
rm bounded_buffer.c
nano buffer.c
nano buffer.c
gcc -o buffer buffer.c -lpthread
./buffer
