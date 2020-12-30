#include "dialog.h"
#include <QApplication>
#include "udp_sender_receiver.h"

dialog* w_temp;

void on_udp_reception(std::string message)
{
  (*w_temp).set_udp_string(message);
}

int main(int argc, char *argv[]) {
  
  QApplication a(argc, argv);
  dialog w;
  w.show();

  w_temp = &w;

  sender s(w.io_service, boost::asio::ip::address::from_string("239.0.0.0"));
  receiver r(w.io_service, boost::asio::ip::address::from_string("0.0.0.0"),
             boost::asio::ip::address::from_string("239.0.0.0"));

  r.bind_reception_callback(std::bind(on_udp_reception, std::placeholders::_1));
  return a.exec();
}
