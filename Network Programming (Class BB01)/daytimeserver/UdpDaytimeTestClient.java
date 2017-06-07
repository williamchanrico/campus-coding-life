import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 * Title: UdpDaytimeTestClient
 * Description: UDP daytime server testing class
 * Author: William Chanrico
 * Date: 7-June-2017
 */
public class UdpDaytimeTestClient {

  public static void main(String[] args) {
    if (args.length != 2) {
      System.out.println("Connect to UDP daytime server at the specified address.");
      System.out.println("Usage: UdpDaytimeTestClient [<hostname>] [<port>]");
      System.exit(0);
    }

    new UdpDaytimeTestClient(args[0], Integer.valueOf(args[1]));
  }

  public UdpDaytimeTestClient(String hostname, int port) {
    try (DatagramSocket socket = new DatagramSocket(0)) {
      socket.setSoTimeout(15000);

      InetAddress host = InetAddress.getByName(hostname);

      DatagramPacket request = new DatagramPacket(new byte[1], 1, host, port);
      DatagramPacket response = new DatagramPacket(new byte[1024], 1024);

      socket.send(request);
      socket.receive(response);

      String daytime = new String(response.getData(), 0, response.getLength(), "UTF-8");

      System.out.println(daytime);
    } catch (IOException ex) {
      ex.printStackTrace();
    }
  }
}
