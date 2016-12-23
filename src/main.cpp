#include <QApplication>
#include <memory>

#include "qudpsendericons.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<QApplication> qApplication{std::make_unique<QApplication>(argc, argv)};
    std::shared_ptr<QUDPSenderIcons> udpSenderIcons{std::make_shared<QUDPSenderIcons>()};
    std::unique_ptr<MainWindow> mainWindow{std::make_unique<MainWindow>(udpSenderIcons)};
    mainWindow->setWindowIcon(udpSenderIcons->MAIN_WINDOW_ICON);
    mainWindow->showMaximized();
    mainWindow->centerAndFitWindow();

    return qApplication->exec();
}
