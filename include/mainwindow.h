#ifndef UDPSENDER_MAINWINDOW_H
#define UDPSENDER_MAINWINDOW_H

#include <QDesktopWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QSpinBox>
#include <QString>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <udpclient.h>
#include <generalutilities.h>

#include "qudpsenderstrings.h"
#include "qudpsendericons.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    template <typename T>
    QString toQString(const T &convert) { return QString::fromStdString(std::to_string(convert)); }
    QString toQString(const std::string &str) { return QString::fromStdString(str); }
    QString toQString(const char *str) { return QString::fromStdString(static_cast<std::string>(str)); }
    QString toQString(const QString &qstr) { return qstr; }


    explicit MainWindow(std::shared_ptr<QUDPSenderIcons> udpSenderIcons, QWidget *parent = 0);
    void centerAndFitWindow();
    int xPlacement() const;
    int yPlacement() const;
    void calculateXYPlacement();
    ~MainWindow();

private slots:
    void onIPSendButtonClicked();
    void doChangeDNSHostNameMode();

private:
    int m_xPlacement;
    int m_yPlacement;
    bool m_dnsHostNameEnabled;
    std::vector<QSpinBox *> m_ipAddressOctetSpinBoxes;
    std::shared_ptr<QUDPSenderIcons> m_udpSenderIcons;
    std::unique_ptr<Ui::MainWindow> m_uiPtr;

    void setDNSHostNameLineEditStatus();
};

#endif //UDPSENDER_MAINWINDOW_H
