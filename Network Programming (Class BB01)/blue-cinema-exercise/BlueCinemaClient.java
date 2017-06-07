import java.io.IOException;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Title: blue-cinema-creator-client
 * Description: Blue Cinema Creator client class
 * Author: William Chanrico
 * Date: 6-June-2017
 */
public class BlueCinemaClient {

  final int SERVER_PORT = 8888;
  final int CLIENT_PORT = 7777;
  final String MCAST_ADDR = "224.0.0.3";

  MulticastSocket multicastSocket;
  InetAddress inetAddrMulticast;

  boolean clientFinished = false;

  Thread mcastThread =
      new Thread(
          new Runnable() {
            @Override
            public void run() {
              try {
                multicastSocket = new MulticastSocket(CLIENT_PORT);
                multicastSocket.joinGroup(inetAddrMulticast);

                while (true) {
                  BlueCinemaData data = BlueCinemaUtil.receiveMulticastData(multicastSocket);

                  if (data.titleName.equals("exit")) {
                    if (clientFinished) {
                      multicastSocket.leaveGroup(inetAddrMulticast);
                      multicastSocket.close();

                      break;
                    } else {
                      continue;
                    }
                  }

                  BlueCinemaUtil.printBroadcastedData(data);

                  System.out.println("Press Enter to continue...");
                }
              } catch (IOException ex) {
                Logger.getLogger(BlueCinemaClient.class.getName()).log(Level.SEVERE, null, ex);
              }
            }
          });

  public BlueCinemaClient() {
    BlueCinemaUtil.printClientHeader();

    try {
      inetAddrMulticast = InetAddress.getByName(MCAST_ADDR);
    } catch (IOException ex) {
      Logger.getLogger(BlueCinemaServer.class.getName()).log(Level.SEVERE, null, ex);
    }

    mcastThread.start();

    while (true) {
      BlueCinemaData data;

      data = BlueCinemaUtil.inputData();

      if (data.titleName.equals("exit")) {
        clientFinished = true;

        BlueCinemaUtil.sendDatagramData(data, inetAddrMulticast, SERVER_PORT);

        System.out.println("\nThanks for using this apps !!");

        break;
      }

      BlueCinemaUtil.sendDatagramData(data, inetAddrMulticast, SERVER_PORT);

      BlueCinemaUtil.scanner.nextLine();
    }
  }

  public static void main(String[] args) {
    new BlueCinemaClient();
  }
}
