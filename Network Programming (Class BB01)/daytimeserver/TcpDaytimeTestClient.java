import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.Socket;

/**
 * Title: TcpDaytimeTestClient
 * Description: TCP daytime server testing class for Network Programming (LA01) course
 * Author: William Chanrico
 * Date: 7-June-2017
 */
public class TcpDaytimeTestClient {

  public TcpDaytimeTestClient() {}

  public TcpDaytimeTestClient(String host, int port) {

    try (Socket connSocket = new Socket(host, port)) {
      Reader isr = new InputStreamReader(connSocket.getInputStream(), "UTF-8");

      StringBuilder response = new StringBuilder();

      for (int inp = isr.read(); inp != -1; inp = isr.read()) response.append((char) inp);

      System.out.println(response.toString());
    } catch (IOException ex) {
      ex.printStackTrace();
    }
  }

  public static void main(String[] args) {
    if (args.length != 2) {
      System.out.println("Usage: TcpDaytimeTestClient [<host>] [<port>]");
      System.exit(0);
    }

    new TcpDaytimeTestClient(args[0], Integer.valueOf(args[1]));
  }
}
