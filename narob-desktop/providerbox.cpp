#include "providerbox.h"

ProviderBox::ProviderBox(QWidget *parent):
    QComboBox(parent)
{
    addItem("Alltel");
    addItem("AT&T");
    addItem("Boost Mobile");
    addItem("Cricket Wireless");
    addItem("Sprint");
    addItem("T-Mobile");
    addItem("U.S. Cellular");
    addItem("Verizon");
    addItem("Virgin Mobile");
    addItem("Republic Wireless");
}
