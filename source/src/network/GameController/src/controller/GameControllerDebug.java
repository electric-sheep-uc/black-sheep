package controller;

public class GameControllerDebug {

    public static void main(String[] args) {
        // Setting the config path right
        System.out.println(System.setProperty("CONFIG_ROOT", "resources/"));

        // Executing the actual game controller
        GameController.main(args);
    }
}
