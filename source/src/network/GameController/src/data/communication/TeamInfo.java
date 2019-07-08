package data.communication;

import data.PlayerInfo;
import data.spl.SPLCoachMessage;
import data.states.PrepTeam;
import data.values.TeamColors;

import java.io.Serializable;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;


/**
 * This class is part of the data wich are send to the robots.
 * It just represents this data, reads and writes between C-structure and
 * Java, nothing more.
 * 
 * @author Michel Bartsch
 */
public class TeamInfo implements Serializable
{
    private static final long serialVersionUID = 2795660408542807763L;

    /**
     * How many players a team may have.
     * Actually that many players in each team need to be sent, even if
     * playersPerTeam in GameControlData is less.
     */
    public static final byte MAX_NUM_PLAYERS = 11;
    
    /** The size in bytes this class has packed. */
    public static final int SIZE =
            1 + // teamNumber
            1 + // teamColor
            1 + // score
            1 + // penaltyShot
            2 + // singleShots
            1 + // coach's sequence number
            SPLCoachMessage.SPL_COACH_MESSAGE_SIZE + // coach's message
            (MAX_NUM_PLAYERS + 1) * PlayerInfo.SIZE; // +1 for the coach

    //this is streamed
    public byte teamNumber;                                         // unique team number
    public TeamColors teamColor;                                    // colour of the team
    public byte score;                                              // team's score
    public byte penaltyShot = 0;                                    // penalty shot counter
    public short singleShots = 0;                                   // bits represent penalty shot success
    public byte coachSequence;                                      // sequence number of the last coach message
    public byte[] coachMessage = new byte[SPLCoachMessage.SPL_COACH_MESSAGE_SIZE];
    public PlayerInfo coach = new PlayerInfo();
    public PlayerInfo[] player = new PlayerInfo[MAX_NUM_PLAYERS];   // the team's players

    private String teamName; // The teams display name


    /**
     * Creates a new TeamInfo.
     */
    public TeamInfo()
    {
        for (int i=0; i<player.length; i++) {
            player[i] = new PlayerInfo();
        }
        teamName = "";
    }
    
    /**
     * Packing this Java class to the C-structure to be send.
     * @return Byte array representing the C-structure.
     */
    public byte[] toByteArray()
    {
        ByteBuffer buffer = ByteBuffer.allocate(SIZE);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.put(teamNumber);
        buffer.put(teamColor.value());
        buffer.put(score);
        buffer.put(penaltyShot);
        buffer.putShort(singleShots);
        buffer.put(coachSequence);
        buffer.put(coachMessage);
        buffer.put(coach.toByteArray());
        for (int i=0; i<MAX_NUM_PLAYERS; i++) {
            buffer.put(player[i].toByteArray());
        }

        return buffer.array();
    }
    
    /**
     * Unpacking the C-structure to the Java class.
     * 
     * @param buffer    The buffered C-structure.
     */
    public void fromByteArray(ByteBuffer buffer)
    {
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        teamNumber = buffer.get();
        teamColor = TeamColors.fromValue(buffer.get());
        score = buffer.get();
        penaltyShot = buffer.get();
        singleShots = buffer.getShort();
        coachSequence = buffer.get();
        buffer.get(coachMessage);
        coach.fromByteArray(buffer);
        for (int i=0; i<player.length; i++) {
            player[i].fromByteArray(buffer);
        }
    }
    
    @Override
    public String toString()
    {
        String out = "--------------------------------------\n";
        out += "         teamNumber: "+teamNumber+"\n";
        out += "          teamColor: "+teamColor.toString()+"\n";
        out += "              score: "+score+"\n";
        out += "        penaltyShot: "+penaltyShot+"\n";
        out += "        singleShots: "+Integer.toBinaryString(singleShots)+"\n";
        out += "      coachSequence: "+coachSequence+"\n";
        out += "       coachMessage: "+new String(coachMessage)+"\n";
        out += "        coachStatus: "+coach.toString()+"\n";
        return out;
    }

    /**
     * Initializes the team from the Prep Team from the selection window
     * @param team - information about the team
     */
    public void initialize(PrepTeam team) {
        this.teamNumber = (byte) team.getTeamInfo().identifier;
        this.teamColor = team.getTeamColorAsByte();
        this.teamName = team.getTeamInfo().name;
    }

    public String getName(){
        return this.teamName;
    }
}