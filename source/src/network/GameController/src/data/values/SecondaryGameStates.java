package data.values;

/**
 * Created by rkessler on 2017-03-25.
 */
public enum SecondaryGameStates implements DocumentingMarkdown {

    UNKNOWN(255, "Unknown"),

    NORMAL(0, "Normal"),
    PENALTYSHOOT(1, "Penalty Shoot"),
    OVERTIME(2, "Overtime"),
    TIMEOUT(3, "Timeout"),
    DIRECT_FREEKICK(4, "Direct Free Kick"),
    INDIRECT_FREEKICK(5, "Indirect Free Kick"),

    PENALTYKICK(6, "Penalty Kick"),
    CORNER_KICK(7, "Corner Kick"),
    GOAL_KICK(8, "Goal Kick"),
    THROW_IN(9, "Throw-In"),;

    private byte byte_value;
    private String humanReadable;

    SecondaryGameStates(int byte_value, String humanReadable) {

        this.byte_value = (byte) byte_value;
        this.humanReadable = humanReadable;
    }

    public byte value() {
        return byte_value;
    }

    public static SecondaryGameStates fromValue(byte b) {
        for(SecondaryGameStates secGameState : SecondaryGameStates.values()){
            if (secGameState.value() == b){
                return secGameState;
            }
        }
        System.out.println("Warning: Could not resolve SecondaryGameState byte.");
        return UNKNOWN;
    }

    /**
     * @see controller.action.ui.GameInterruption
     * @return true if secondary game state is on of the 6 game interruptions
     */
    public boolean isGameInterruption(){
        switch (this) {
            case PENALTYKICK:
            case DIRECT_FREEKICK:
            case INDIRECT_FREEKICK:
            case CORNER_KICK:
            case GOAL_KICK:
            case THROW_IN:
                return true;
        }
        return false;
    }

    public String toString(){
        return this.humanReadable;
    }
}
