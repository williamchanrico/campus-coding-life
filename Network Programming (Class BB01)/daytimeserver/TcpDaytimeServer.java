import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

/**
 * Title: TcpDaytimeServer
 * Description: TCP daytime server class for Network Programming (LA01) course
 * Author: William Chanrico
 * Date: 7-June-2017
 */
public class TcpDaytimeServer {

  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Starts TCP daytime server on the specified port.");
      System.out.println("Usage: TcpDaytimeServer [<port>]");
      System.exit(0);
    }

    new TcpDaytimeServer(Integer.valueOf(args[0]));
  }

  public TcpDaytimeServer(int port) {

    try (ServerSocket socket = new ServerSocket(port)) {

      System.out.println("TCP daytime server is listening on port " + port);

      while (true) {
        try (Socket conn = socket.accept()) {
          Date date = new Date();

          Writer osw = new OutputStreamWriter(conn.getOutputStream(), "UTF-8");
          osw.write(date.toString() + "\r\n");
          osw.flush();

          System.out.println("Served a client from " + 
            conn.getInetAddress().getHostName() + ":" + conn.getPort());
        }
      }
    } catch (IOException ex) {
      ex.printStackTrace();
    }
  }
}
