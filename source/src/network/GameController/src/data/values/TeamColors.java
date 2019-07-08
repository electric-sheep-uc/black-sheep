package data.values;

import java.awt.*;

/**
 * Created by rkessler on 2017-03-25.
 */
public enum TeamColors  implements DocumentingMarkdown {

    BLUE(0, Color.BLUE),
    RED(1, Color.RED),
    YELLOW(2, new Color(224, 200, 0)),
    BLACK(3, Color.BLACK),
    WHITE(4, Color.WHITE),
    GREEN(5, new Color(0, 128, 0)),
    ORANGE(6, new Color(255, 165, 0)),
    PURPLE(7, new Color(128, 0, 128)),
    BROWN(8, new Color(165, 42, 42)),
    GRAY(9, new Color(128, 128, 128)),

    UNKNOWN(255, new Color(0, 255, 255));

    private byte byte_value;
    private Color color;

    TeamColors(int byte_value, Color color) {
        this.byte_value = (byte) byte_value;
        this.color = color;
    }

    public byte value() {
        return byte_value;
    }

    public static TeamColors fromValue(byte b) {
        for(TeamColors teamColor : TeamColors.values()){
            if (teamColor.value() == b){
                return teamColor;
            }
        }
        System.out.println("Warning: Could not resolve Team Color byte.");
        return UNKNOWN;
    }

    public String toString(){
        switch (this) {
            case BLUE:
                return "blue";
            case RED:
                return"red";
            case YELLOW:
                return "yellow";
            case BLACK:
                return "black";
            case WHITE:
                return "white";
            case GREEN:
                return "green";
            case ORANGE:
                return "orange";
            case PURPLE:
                return "purple";
            case BROWN:
                return "brown";
            case GRAY:
                return "gray";
            default:
                return "undefined";
        }
    }

    public static TeamColors fromColorName(final String colorName) {
        switch (colorName) {
            case "blue":
                return BLUE;
            case "red":
                return RED;
            case "yellow":
                return YELLOW;
            case "black":
                return BLACK;
            case "green":
                return GREEN;
            case "orange":
                return ORANGE;
            case "purple":
                return PURPLE;
            case "brown":
                return BROWN;
            case "gray":
                return GRAY;
            default:
                return WHITE;
        }
    }

    public Color colorValue() {
        return this.color;
    }
}
