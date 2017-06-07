import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.Random;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Title: blue-cinema-creator-util
 * Description: Blue Cinema Creator utility class
 * Author: William Chanrico
 * Date: 6-June-2017
 */
public class BlueCinemaUtil {

  public static Scanner scanner = new Scanner(System.in);

  private static BlueCinemaUtil instance = null;
  private static int BUFFER_SIZE = 8192;
  private static int dataCount = 0;

  private BlueCinemaUtil() {}

  public static BlueCinemaUtil getInstance() {
    if (instance == null) {
      instance = new BlueCinemaUtil();
    }
    return instance;
  }

  public static void printClientHeader() {
    System.out.println("============================");
    System.out.println("| Welcome to               |");
    System.out.println("|      Blue Cinema Creator |");
    System.out.println("|      ~CLIENT~            |");
    System.out.println("============================\n");
  }

  public static void printServerHeader() {
    System.out.println("============================");
    System.out.println("| Welcome to               |");
    System.out.println("|      Blue Cinema Creator |");
    System.out.println("|      ~SERVER~            |");
    System.out.println("============================\n");
  }

  public static BlueCinemaData receiveMulticastData(MulticastSocket multicastSocket) {
    BlueCinemaData data = null;

    try {
      byte[] buf = new byte[BUFFER_SIZE];

      DatagramPacket datagramPacket = new DatagramPacket(buf, buf.length);
      multicastSocket.receive(datagramPacket);

      ByteArrayInputStream bais = new ByteArrayInputStream(buf);
      ObjectInputStream ois = new ObjectInputStream(bais);
      data = (BlueCinemaData) ois.readObject();
    } catch (IOException | ClassNotFoundException ex) {
      Logger.getLogger(BlueCinemaUtil.class.getName()).log(Level.SEVERE, null, ex);
    }

    return data;
  }

  public static void sendDatagramData(BlueCinemaData data, InetAddress addr, int port) {
    DatagramSocket datagramSocket;
    byte[] buf = new byte[BUFFER_SIZE];

    try {
      datagramSocket = new DatagramSocket();
      ByteArrayOutputStream baos = new ByteArrayOutputStream();
      ObjectOutputStream oos = new ObjectOutputStream(baos);
      oos.writeObject(data);
      buf = baos.toByteArray();

      DatagramPacket datagramPacket = new DatagramPacket(buf, buf.length, addr, port);

      datagramSocket.send(datagramPacket);
    } catch (IOException ex) {
      Logger.getLogger(BlueCinemaUtil.class.getName()).log(Level.SEVERE, null, ex);
    }
  }

  public static BlueCinemaData inputData() {
    int len;
    BlueCinemaData data = new BlueCinemaData();

    do {
      System.out.print("Input title [5...20 | exit]: ");
      data.titleName = scanner.nextLine();

      len = data.titleName.length();
    } while (!data.titleName.equals("exit") && (len < 5 || len > 20));

    if (data.titleName.equals("exit")) {
      return data;
    }

    do {
      System.out.print("Input type ['Action' | 'Drama' | 'Comedy']: ");
      data.genre = scanner.nextLine();
    } while (!data.genre.equalsIgnoreCase("Action")
        && !data.genre.equalsIgnoreCase("Drama")
        && !data.genre.equalsIgnoreCase("Comedy"));

    do {
      System.out.print("Input director [minimum 2 words]: ");
      data.director = scanner.nextLine();
    } while (!data.director.contains(" "));

    do {
      System.out.print("Input duration (minutes) [30...250]: ");
      data.duration = scanner.nextInt();
    } while (data.duration < 30 || data.duration > 250);

    do {
      System.out.print("Input year [min 2016]: ");
      data.year = scanner.nextInt();
    } while (data.year < 2016);

    scanner.nextLine();

    return data;
  }

  public static void printProcessedData(BlueCinemaData data) {
    System.out.println("\nReceived data from client !!!!\n");

    System.out.println("==============================\n");

    System.out.println("Data No\t\t: " + ++dataCount);
    System.out.println("Movie Code\t: " + data.code);
    System.out.println("Movie Title\t: " + data.titleName);
    System.out.println("Release Year\t: " + data.year);
    System.out.println("Movie Genre\t: " + data.genre);
    System.out.println("Movie Duration\t: " + data.duration + " minutes");
    System.out.println("Director\t: " + data.director);
    System.out.println("Rating Category\t: " + data.ratingCategory);
    System.out.println("Total Studio\t: " + data.totalStudio);
    System.out.println("Total Price\t: Rp. " + data.totalPrice);

    System.out.println("\n==============================\n");
  }

  public static void printBroadcastedData(BlueCinemaData data) {
    System.out.println("\nReceived data from server !!!!\n");

    System.out.println("=======Broadcast Message======\n");

    System.out.println("Movie Code\t: " + data.code);
    System.out.println("Movie Title\t: " + data.titleName);
    System.out.println("Release Year\t: " + data.year);
    System.out.println("Movie Genre\t: " + data.genre);
    System.out.println("Movie Duration\t: " + data.duration + " minutes");
    System.out.println("Director\t: " + data.director);
    System.out.println("Rating Category\t: " + data.ratingCategory);
    System.out.println("Total Studio\t: " + data.totalStudio);
    System.out.println("Total Price\t: Rp. " + data.totalPrice);

    System.out.println("\n==============================\n");
  }

  public static void processData(BlueCinemaData data) {
    data.code = generateCode();
    data.ratingCategory = getRatingCategory(data.genre);
    data.totalStudio = getTotalStudio(data.duration);
    data.basePrice = getBasePrice(data.totalStudio);
    data.genrePrice = getGenrePrice(data.genre);
    data.totalPrice = getTotalPrice(data.basePrice, data.genrePrice);
  }

  public static String generateCode() {
    Random rand = new Random();

    return String.format("AC%d%d%d", rand.nextInt(10), rand.nextInt(10), rand.nextInt(10));
  }

  public static String getRatingCategory(String genre) {
    if (genre.equalsIgnoreCase("Action")) {
      return "Parental Guidance (PG)";
    } else if (genre.equalsIgnoreCase("Drama")) {
      return "Teen (T)";
    } else if (genre.equalsIgnoreCase("Comedy")) {
      return "Everyone (E)";
    } else {
      return "Unknown Category";
    }
  }

  public static int getTotalStudio(int duration) {
    if (duration < 120) {
      return 1;
    } else {
      return 2;
    }
  }

  public static int getBasePrice(int totalStudio) {
    switch (totalStudio) {
      case 1:
        return 80000;
      case 2:
        return 100000;
      default:
        return -1;
    }
  }

  public static int getGenrePrice(String genre) {
    if (genre.equalsIgnoreCase("Action")) {
      return 35000;
    } else if (genre.equalsIgnoreCase("Drama")) {
      return 30000;
    } else if (genre.equalsIgnoreCase("Comedy")) {
      return 25000;
    } else {
      return -1;
    }
  }

  public static int getTotalPrice(int basePrice, int genrePrice) {
    return basePrice + genrePrice;
  }
}
