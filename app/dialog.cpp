#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);
}

dialog::~dialog()
{
    delete ui;
}

void dialog::on_pushButton_clicked()
{
    io_service.poll();
    
    QString qstr = QString::fromStdString(udp_rx_msg);
    ui->label->setText(qstr);
}
