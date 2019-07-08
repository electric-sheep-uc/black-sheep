package data.states;

import java.io.Serializable;

/**
 * Created by rkessler on 2017-03-24.
 */
public class SecondaryStateInfo implements Serializable {

    private byte[] secondaryStateInfo;

    public SecondaryStateInfo(){
        secondaryStateInfo = new byte[]{0, 0, 0, 0};
    }

    public byte[] toByteArray() {
        return secondaryStateInfo;
    }

    public void fromByteArray(byte[] byte_array) {
        assert byte_array.length == 4: "Could not convert secondary state from byte array - not 4 bytes";
        secondaryStateInfo = byte_array;
    }

    /**
     * Updates the additional info in the secondary game state regarding free kicks
     * @param teamPerforming - The team that is performing the free kick
     * @param subMode - The mode we are in:
     *                0 = Robots should stay still, referee places the ball on the ground
     *                1 = Robots can place themselves toward the ball
     *                2 = Robots should stay still and referees ask to remove illegally positioned robots
     */
    public void setFreeKickData(byte teamPerforming, byte subMode){
        secondaryStateInfo[0] = teamPerforming;
        secondaryStateInfo[1] = subMode;
    }

    public void reset() {
        secondaryStateInfo = new byte[]{0, 0, 0, 0};
    }

    /** Switches the mode to penalty kick and records the team performing it **/
    public void switchToPenaltyKick(byte teamPerforming, byte submode) {
        secondaryStateInfo[0] = teamPerforming;
        secondaryStateInfo[1] = submode;
    }
}
