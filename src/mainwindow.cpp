#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<QUDPSenderIcons> udpSenderIcons, QWidget *parent) :
    QMainWindow{parent},
    m_xPlacement{0},
    m_yPlacement{0},
    m_dnsHostNameEnabled{false},
    m_udpSenderIcons{udpSenderIcons},
    m_uiPtr{std::make_unique<Ui::MainWindow>()}
{

    using namespace QUDPSenderStrings;
    this->m_uiPtr->setupUi(this);
    this->m_ipAddressOctetSpinBoxes.push_back(this->m_uiPtr->firstOctetSpinBox);
    this->m_ipAddressOctetSpinBoxes.push_back(this->m_uiPtr->secondOctetSpinBox);
    this->m_ipAddressOctetSpinBoxes.push_back(this->m_uiPtr->thirdOctetSpinBox);
    this->m_ipAddressOctetSpinBoxes.push_back(this->m_uiPtr->fourthOctetSpinBox);
    this->setDNSHostNameLineEditStatus();

    this->m_uiPtr->sendPushButton->setText(TAP_TO_SEND_STRING);
    this->m_uiPtr->sendPushButton->setToolTip(TAP_TO_SEND_TOOL_TIP);

    this->m_uiPtr->dnsHostNameSwitchPushButton->setText(CHANGE_TO_DNS_HOSTNAME_STRING);
    this->m_uiPtr->dnsHostNameSwitchPushButton->setToolTip(CHANGE_TO_DNS_HOSTNAME_TOOL_TIP);

    connect(this->m_uiPtr->sendPushButton, SIGNAL(clicked(bool)), this, SLOT(onIPSendButtonClicked()));
    connect(this->m_uiPtr->dnsHostNameSwitchPushButton, SIGNAL(clicked(bool)), this, SLOT(doChangeDNSHostNameMode()));
}

void MainWindow::doChangeDNSHostNameMode()
{
    this->m_dnsHostNameEnabled ^= 0x1;
    this->setDNSHostNameLineEditStatus();
}

void MainWindow::setDNSHostNameLineEditStatus()
{
    using namespace QUDPSenderStrings;
    if (this->m_dnsHostNameEnabled) {
        this->m_uiPtr->dnsHostNameLineEdit->show();
        for (auto &it : this->m_ipAddressOctetSpinBoxes) {
            it->hide();
        }
        this->m_uiPtr->dnsHostNameSwitchPushButton->setText(CHANGE_TO_IP_ADDRESS_STRING);
        this->m_uiPtr->dnsHostNameSwitchPushButton->setToolTip(CHANGE_TO_IP_ADDRESS_TOOL_TIP);
    } else {
        this->m_uiPtr->dnsHostNameLineEdit->hide();
        for (auto &it : this->m_ipAddressOctetSpinBoxes) {
            it->show();
        }
        this->m_uiPtr->dnsHostNameSwitchPushButton->setText(CHANGE_TO_DNS_HOSTNAME_STRING);
        this->m_uiPtr->dnsHostNameSwitchPushButton->setToolTip(CHANGE_TO_DNS_HOSTNAME_TOOL_TIP);
    }
}

void MainWindow::onIPSendButtonClicked()
{
    using namespace GeneralUtilities;
    using namespace QUDPSenderStrings;
    std::string hostName{""};
    if (this->m_dnsHostNameEnabled) {
        hostName = this->m_uiPtr->dnsHostNameLineEdit->text().toStdString();
    } else {
        hostName = (toString(this->m_uiPtr->firstOctetSpinBox->value())
                  + "."
                  + toString(this->m_uiPtr->secondOctetSpinBox->value())
                  + "."
                  + toString(this->m_uiPtr->thirdOctetSpinBox->value())
                  + "."
                  + toString(this->m_uiPtr->fourthOctetSpinBox->value()));
    }
    if (hostName.empty()) {
        std::unique_ptr<QMessageBox> warningBox{std::make_unique<QMessageBox>()};
        warningBox->setText(toQString(INVALID_SOMETHING_MESSAGE) + NO_HOST_NAME_MESSAGE);
        warningBox->setWindowTitle(INVALID_SOMETHING_WINDOW_TITLE);
        warningBox->setWindowIcon(this->m_udpSenderIcons->MAIN_WINDOW_ICON);
        warningBox->exec();
        return;
    }
    try {
        uint16_t portNumber{static_cast<uint16_t>(this->m_uiPtr->portNumberSpinBox->value())};
        std::unique_ptr<UDPClient> udpClient{std::make_unique<UDPClient>(hostName, portNumber)};
        udpClient->writeString(this->m_uiPtr->textToSendLineEdit->text().toStdString());
    } catch (std::exception &e) {
        std::unique_ptr<QMessageBox> warningBox{std::make_unique<QMessageBox>()};
        warningBox->setText(INVALID_SOMETHING_MESSAGE + toQString(e.what()));
        warningBox->setWindowTitle(INVALID_SOMETHING_WINDOW_TITLE);
        warningBox->setWindowIcon(this->m_udpSenderIcons->MAIN_WINDOW_ICON);
        warningBox->exec();
    }
}

void MainWindow::centerAndFitWindow()
{
    std::unique_ptr<QDesktopWidget> desktopWidget{std::make_unique<QDesktopWidget>()};
    this->setGeometry(desktopWidget->availableGeometry());
    calculateXYPlacement();
    this->move(this->m_xPlacement, this->m_yPlacement);
}

int MainWindow::xPlacement() const
{
    return this->m_xPlacement;
}

int MainWindow::yPlacement() const
{
    return this->m_yPlacement;
}

void MainWindow::calculateXYPlacement()
{
    std::unique_ptr<QDesktopWidget> desktopWidget{std::make_unique<QDesktopWidget>()};
    std::unique_ptr<QRect> avail{std::make_unique<QRect>(desktopWidget->availableGeometry())};
    this->m_xPlacement = (avail->width()/2)-(this->width()/2);
    this->m_yPlacement = (avail->height()/2)-(this->height()/2);
}

MainWindow::~MainWindow()
{

}
