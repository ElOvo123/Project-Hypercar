#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create a main widget
    QWidget window;
    window.setWindowTitle("Interface");
    window.resize(1200, 800); // Set size to 1200x800

    // Create a vertical layout for the main window
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    
    // Create a rectangle as a visual element
    QWidget *rectangle = new QWidget();
    rectangle->setStyleSheet("background-color: white"); // Rectangle style
    rectangle->setFixedHeight(125); // Set a fixed height for the rectangle
    rectangle->setFixedWidth(1205); // Set a fixed width for the rectangle

    // Add the rectangle to the main layout
    mainLayout->addWidget(rectangle); // Add rectangle to main layout

    // Create individual buttons with images
    QPushButton *button1 = new QPushButton();
    button1->setIcon(QIcon(QPixmap("image1.png")));
    button1->setIconSize(QSize(70, 70));
    button1->setFixedSize(90, 90);
    QObject::connect(button1, &QPushButton::pressed, [button1]() {
        button1->setStyleSheet("background-color: grey;");
    });
    QObject::connect(button1, &QPushButton::released, [button1]() {
        button1->setStyleSheet(""); // Reset style on release
    });
    button1->setParent(rectangle);
    button1->move(10, 20); // Position manually

    QPushButton *button2 = new QPushButton();
    button2->setIcon(QIcon(QPixmap("image2.png")));
    button2->setIconSize(QSize(70, 70));
    button2->setFixedSize(90, 90);
    QObject::connect(button2, &QPushButton::pressed, [button2]() {
        button2->setStyleSheet("background-color: grey;");
    });
    QObject::connect(button2, &QPushButton::released, [button2]() {
        button2->setStyleSheet(""); // Reset style on release
    });
    button2->setParent(rectangle);
    button2->move(110, 20); // Position manually

    QPushButton *button3 = new QPushButton();
    button3->setIcon(QIcon(QPixmap("image3.png")));
    button3->setIconSize(QSize(70, 70));
    button3->setFixedSize(90, 90);
    QObject::connect(button3, &QPushButton::pressed, [button3]() {
        button3->setStyleSheet("background-color: grey;");
    });
    QObject::connect(button3, &QPushButton::released, [button3]() {
        button3->setStyleSheet(""); // Reset style on release
    });
    button3->setParent(rectangle);
    button3->move(210, 20); // Position manually

    QPushButton *button4 = new QPushButton();
    button4->setIcon(QIcon(QPixmap("image4.png")));
    button4->setIconSize(QSize(70, 70));
    button4->setFixedSize(90, 90);
    QObject::connect(button4, &QPushButton::pressed, [button4]() {
        button4->setStyleSheet("background-color: grey;");
    });
    QObject::connect(button4, &QPushButton::released, [button4]() {
        button4->setStyleSheet(""); // Reset style on release
    });
    button4->setParent(rectangle);
    button4->move(310, 20); // Position manually

    QPushButton *button5 = new QPushButton();
    button5->setIcon(QIcon(QPixmap("image5.png")));
    button5->setIconSize(QSize(70, 70));
    button5->setFixedSize(90, 90);
    QObject::connect(button5, &QPushButton::pressed, [button5]() {
        button5->setStyleSheet("background-color: grey;");
    });
    QObject::connect(button5, &QPushButton::released, [button5]() {
        button5->setStyleSheet(""); // Reset style on release
    });
    button5->setParent(rectangle);
    button5->move(410, 20); // Position manually

    // Create a label to display messages
    QLabel *label = new QLabel("Press a button!", &window);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label, 0, Qt::AlignCenter);

    // Set margins for the main layout
    mainLayout->setContentsMargins(10, 10, 10, 10); // Add some space around the content

    // Set the layout for the main window
    window.setLayout(mainLayout);
    
    // Show the window
    window.show();

    return app.exec();
}
