package data.communication;

import data.states.AdvancedData;
import data.Rules;
import data.states.SecondaryStateInfo;
import data.values.GameStates;
import data.values.GameTypes;
import data.values.SecondaryGameStates;
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
public class GameControlData implements Serializable
{
    private static final long serialVersionUID = 5061539348771652049L;

    /** Some constants from the C-structure. */
    public static final int GAMECONTROLLER_RETURNDATA_PORT = 3939; // port to receive return-packets on
    public static final int GAMECONTROLLER_GAMEDATA_PORT= 3838; // port to send game state packets to

    public static final String GAMECONTROLLER_STRUCT_HEADER = "RGme";
    public static final byte GAMECONTROLLER_STRUCT_VERSION = 12;
    public static final byte DROPBALL = -128;


    public static final byte C_FALSE = 0;
    public static final byte C_TRUE = 1;
    
    
    /** The size in bytes this class has packed. */
    public static final int SIZE =
            4 + // header
            2 + // version
            1 + // packet number
            1 + // numPlayers
            1 + // gameType
            1 + // gameState
            1 + // firstHalf
            1 + // kickOffTeam
            1 + // secGameState
            4 + // secGameStateInfo
            1 + // dropInTeam
            2 + // dropInTime
            2 + // secsRemaining
            2 + // secondaryTime
            2 * TeamInfo.SIZE;

    //this is streamed
    // GAMECONTROLLER_STRUCT_HEADER                             // header to identify the structure
    // GAMECONTROLLER_STRUCT_VERSION                            // version of the data structure
    public byte packetNumber = 0;
    public byte playersPerTeam = (byte) Rules.league.teamSize;  // The number of players on a team
    public GameTypes gameType = GameTypes.ROUNDROBIN;           // type of the game (GAME_ROUNDROBIN, GAME_PLAYOFF, GAME_DROPIN)
    public GameStates gameState = GameStates.INITIAL;     // state of the game (READY, PLAYING, etc)
    public byte firstHalf = C_TRUE;                             // 1 = game in first half, 0 otherwise
    public byte kickOffTeam;                                    // the next team to kick off

    public SecondaryGameStates secGameState = SecondaryGameStates.NORMAL;
    // Extra state information - (NORMAL, PENALTYSHOOT, etc)
    public SecondaryStateInfo secGameStateInfo = new SecondaryStateInfo();
    // Extra information on the specific state

    public byte dropInTeam;                                     // team that caused last drop in
    protected short dropInTime = -1;                            // number of seconds passed since the last drop in. -1 before first dropin
    public short secsRemaining = (short) Rules.league.halfTime; // estimate of number of seconds remaining in the half
    public short secondaryTime = 0;                             // sub-time (remaining in ready state etc.) in seconds
    public TeamInfo[] team = new TeamInfo[2];
    
    /**
     * Creates a new GameControlData.
     */
    public GameControlData()
    {
        for (int i=0; i<team.length; i++) {
            team[i] = new TeamInfo();
        }
        team[0].teamColor = TeamColors.BLUE;
        team[1].teamColor = TeamColors.RED;
    }
    
    /**
     * Returns the corresponding byte-stream of the state of this object.
     *
     * @return  the corresponding byte-stream of the state of this object
     */
    public ByteBuffer toByteArray()
    {
    	AdvancedData data = (AdvancedData) this;
        ByteBuffer buffer = ByteBuffer.allocate(SIZE);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.put(GAMECONTROLLER_STRUCT_HEADER.getBytes(), 0, 4);
        buffer.putShort(GAMECONTROLLER_STRUCT_VERSION);
        buffer.put(packetNumber);
        buffer.put(playersPerTeam);
        buffer.put(gameType.value());
    	if (secGameState == SecondaryGameStates.NORMAL && gameState == GameStates.PLAYING
                && data.getSecondsSince(data.whenCurrentGameStateBegan) < Rules.league.delayedSwitchToPlaying) {
            buffer.put(GameStates.SET.value());
    	} else {
            buffer.put(gameState.value());
    	}
        buffer.put(firstHalf);
        buffer.put(kickOffTeam);
        buffer.put(secGameState.value());
        buffer.put(secGameStateInfo.toByteArray());
        buffer.put(dropInTeam);
        buffer.putShort(dropInTime);
        buffer.putShort(secsRemaining);
        buffer.putShort(secondaryTime);
        for (TeamInfo aTeam : team) {
            buffer.put(aTeam.toByteArray());
        }

        return buffer;
    }
    
    /**
     * Unpacking the C-structure to the Java class.
     * 
     * @param buffer    The buffered C-structure.
     * @return Whether the structure was well formed. That is, it must have the proper 
     *          {@link #GAMECONTROLLER_STRUCT_VERSION} set.
     */
    public boolean fromByteArray(ByteBuffer buffer)
    {
        // Move to position zero to have a fresh start
        buffer.position(0);

        buffer.order(ByteOrder.LITTLE_ENDIAN);
        byte[] header = new byte[4];
        buffer.get(header, 0, 4);
        if (buffer.getShort() != GAMECONTROLLER_STRUCT_VERSION) {
            return false;
        }
        packetNumber = buffer.get(); 
        playersPerTeam = buffer.get();
        gameType = GameTypes.fromValue(buffer.get());
        gameState = GameStates.fromValue(buffer.get());
        firstHalf = buffer.get();
        kickOffTeam = buffer.get();
        secGameState = SecondaryGameStates.fromValue(buffer.get());

        // Read the additional ste information for the sub state
        byte[] additional_game_state_info = new byte[4];
        buffer.get(additional_game_state_info, 0, 4);
        secGameStateInfo.fromByteArray(additional_game_state_info);

        dropInTeam = buffer.get();
        dropInTime = buffer.getShort();
        secsRemaining = buffer.getShort();
        secondaryTime = buffer.getShort();
        for (int i=0; i<team.length; i++) {
            team[i].fromByteArray(buffer);
        }
        
        return true;
    }
    
    @Override
    public String toString()
    {
        String out = "";
        String temp;
        
        out += "             Header: "+GAMECONTROLLER_STRUCT_HEADER+"\n";
        out += "            Version: "+GAMECONTROLLER_STRUCT_VERSION+"\n";
        out += "      Packet Number: "+(packetNumber & 0xFF)+"\n";
        out += "   Players per Team: "+playersPerTeam+"\n";
        out += "           gameType: "+ gameType +"\n";
        out += "          gameState: "+gameState.toString()+"\n";
        switch (firstHalf) {
            case C_TRUE:  temp = "true";  break;
            case C_FALSE: temp = "false"; break;
            default: temp = "undefinied("+firstHalf+")";
        }
        out += "          firstHalf: "+temp+"\n";
        out += "        kickOffTeam: "+kickOffTeam+"\n";
        out += "       secGameState: "+secGameState+"\n";
        out += "         dropInTeam: "+dropInTeam+"\n";
        out += "         dropInTime: "+dropInTime+"\n";
        out += "      secsRemaining: "+secsRemaining+"\n";
        out += "      secondaryTime: "+secondaryTime+"\n";
        return out;
    }
}