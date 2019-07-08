package data.values;

/**
 * The sides indices for both teams as convenient typed Enum
 */
public enum Side {

    LEFT(0),
    RIGHT(1);

    private int side;

    Side(int side){
        this.side = side;
    }

    public int value(){
        return this.side;
    }

    public Side getOther(){
        if (this == LEFT){
            return RIGHT;
        } else {
            return LEFT;
        }
    }

    public static Side getFromInt(int side){
        if (side == 0){
            return LEFT;
        } else {
            return RIGHT;
        }
    }
}
