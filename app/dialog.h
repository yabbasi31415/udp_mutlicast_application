#ifndef DIALOG_H
#define DIALOG_H

#include "udp_sender_receiver.h"
#include <QDialog>

namespace Ui {
class dialog;
}

class dialog : public QDialog {
  Q_OBJECT

public:
  explicit dialog(QWidget *parent = 0);
  ~dialog();

private slots:
  void on_pushButton_clicked();

private:
  Ui::dialog *ui;

public:

  std::string udp_rx_msg;
  boost::asio::io_service io_service;
  
  void set_udp_string(std::string message)
  {
      udp_rx_msg = message;
  }
};

#endif // DIALOG_H
