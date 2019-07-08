package data;

import data.values.Penalties;

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
public class PlayerInfo implements Serializable
{
    private static final long serialVersionUID = -8480462279073509072L;

    /** The size in bytes this class has packed. */
    public static final int SIZE =
            1 + // penalty
            1 +  // secsToUnpen
            1 + // Numbers of yellow cards
            1; // Numbers of red cards

    //this is streamed
    public Penalties penalty = Penalties.NONE; // penalty state of the player
    public byte secsTillUnpenalised;    // estimate of time till unpenalised
    public byte yellowCardCount = 0;    // estimate of time till unpenalised
    public byte redCardCount = 0;    // estimate of time till unpenalised
    public byte isGoalie = 0;    // Save the information whether they are the goalie here to make it easier for the ux

    public byte dropInPoints = 0; // Number of drop in points

    /**
     * Packing this Java class to the C-structure to be send.
     * @return Byte array representing the C-structure.
     */
    public byte[] toByteArray()
    {
        ByteBuffer buffer = ByteBuffer.allocate(SIZE);
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.put(penalty.value());
        buffer.put(secsTillUnpenalised);
        buffer.put(yellowCardCount);
        buffer.put(redCardCount);
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
        penalty = Penalties.fromValue(buffer.get());
        secsTillUnpenalised = buffer.get();
        yellowCardCount = buffer.get();
        redCardCount = buffer.get();
    }

    @Override
    public String toString()
    {
        String out = "----------------------------------------\n";
        out += "            penalty: "+penalty.toString()+"\n";
        out += "secsTillUnpenalised: "+secsTillUnpenalised+"\n";
        out += "yellowCardCount: "+yellowCardCount+"\n";
        out += "redCardCount: "+redCardCount+"\n";
        return out;
    }
}