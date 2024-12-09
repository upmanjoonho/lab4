#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

void onButtonClicked() {
    std::cout << "Hellot!" << std::endl;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Qt Button Example");

    QVBoxLayout *layout = new QVBoxLayout(&window);
    QPushButton *button = new QPushButton("Click!");
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, &onButtonClicked);

    window.show();
    return app.exec();
}
