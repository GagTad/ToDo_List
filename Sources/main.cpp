#include "mainwindow.h" // Ներառում ենք մեր գլխավոր պատուհանի header-ը

#include <QApplication>

int main(int argc, char *argv[])
{
    // 1. Ստեղծում ենք գրաֆիկական հավելվածի օբյեկտը
    QApplication a(argc, argv);

    // 2. Ստեղծում ենք մեր գլխավոր պատուհանի օրինակը
    MainWindow w;

    // 3. Ցուցադրում ենք պատուհանը էկրանին
    w.show();

    // 4. Գործարկում ենք հավելվածը և սպասում, մինչև օգտատերը կփակի այն
    return a.exec();
}
