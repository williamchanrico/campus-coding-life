import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Date;

/**
 * Title: MultithreadedUdpDaytimeServer
 * Description: Multithreaded UDP daytime server class
 * Author: William Chanrico
 * Date: 7-June-2017
 */
public class MultithreadedUdpDaytimeServer {

  private DatagramSocket socket;

  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Starts UDP daytime server on the specified port.");
      System.out.println("Usage: MultithreadedUdpDaytimeServer [<port>]");
      System.exit(0);
    }

    new MultithreadedUdpDaytimeServer(Integer.valueOf(args[0]));
  }

  public MultithreadedUdpDaytimeServer(int port) {
    try {
      socket = new DatagramSocket(port);

      System.out.println("UDP daytime server is listening on port " + port);

      while (true) {
        DatagramPacket request = new DatagramPacket(new byte[1024], 1024);
        socket.receive(request);

        Thread task = new ServerThread(request);
        task.start();
      }
    } catch (SocketException ex) {
      ex.printStackTrace();
    } catch (IOException ex) {
      ex.printStackTrace();
    }
  }

  private class ServerThread extends Thread {
    private final DatagramPacket request;

    ServerThread(DatagramPacket request) {
      this.request = request;
    }

    @Override
    public void run() {
      InetAddress cliAddr = request.getAddress();
      int cliPort = request.getPort();

      try {
        String daytime = new Date().toString() + "\r\n";
        byte[] data = daytime.getBytes("UTF-8");

        DatagramPacket response = new DatagramPacket(data, data.length, cliAddr, cliPort);

        socket.send(response);

        System.out.println("Served a client from " + cliAddr + ":" + cliPort);
      } catch (UnsupportedEncodingException ex) {
        ex.printStackTrace();
      } catch (IOException ex) {
        ex.printStackTrace();
      }
    }
  }
}
