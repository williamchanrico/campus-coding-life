import java.io.IOException;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Title: blue-cinema-creator-server
 * Description: Blue Cinema Creator server class
 * Author: William Chanrico
 * Date: 6-June-2017
 */
public class BlueCinemaServer {

  final int SERVER_PORT = 8888;
  final int CLIENT_PORT = 7777;
  final String MCAST_ADDR = "224.0.0.3";

  MulticastSocket multicastSocket;
  InetAddress inetAddrMulticast;

  public BlueCinemaServer() {
    BlueCinemaUtil.printServerHeader();

    try {
      multicastSocket = new MulticastSocket(SERVER_PORT);
      inetAddrMulticast = InetAddress.getByName(MCAST_ADDR);

      multicastSocket.joinGroup(inetAddrMulticast);

      System.out.println("Server Active!\n");

      while (true) {
        System.out.println("Waiting data from client.....\n");

        BlueCinemaData data = BlueCinemaUtil.receiveMulticastData(multicastSocket);

        if (data.titleName.equals("exit")) {
          System.out.println("One client disconnected !!\n");

          BlueCinemaUtil.sendDatagramData(data, inetAddrMulticast, CLIENT_PORT);

          continue;
        }

        BlueCinemaUtil.processData(data);
        BlueCinemaUtil.printProcessedData(data);
        BlueCinemaUtil.sendDatagramData(data, inetAddrMulticast, CLIENT_PORT);
      }
    } catch (IOException ex) {
      Logger.getLogger(BlueCinemaServer.class.getName()).log(Level.SEVERE, null, ex);
    }
  }

  public static void main(String[] args) {
    new BlueCinemaServer();
  }
}
