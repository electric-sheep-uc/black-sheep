package data.values;

/**
 * Created by rkessler on 2017-03-25.
 */
public enum PlayerResponses implements DocumentingMarkdown {

    /** What a player may say. */
    MAN_PENALISE(0, "Manual Penalized"),
    MAN_UNPENALISE(1, "Manual Unpenalized"),
    ALIVE(2, "Alive"),

    UNKNOWN(255, "Unknown");

    private byte byte_value;
    private String humanReadable;

    PlayerResponses(int byte_value, String humanReadable) {
        this.byte_value = (byte) byte_value;
        this.humanReadable = humanReadable;
    }

    public byte value() {
        return byte_value;
    }

    public static PlayerResponses fromValue(byte b) {
        for(PlayerResponses playerResponse : PlayerResponses.values()){
            if (playerResponse.value() == b){
                return playerResponse;
            }
        }
        System.out.println("Warning: Could not resolve PlayerResponse byte.");
        return UNKNOWN;
    }

    public String toString(){
        return this.humanReadable;
    }
}
