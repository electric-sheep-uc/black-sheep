package data;

import data.hl.HL;
import data.hl.HLAdult;
import data.hl.HLTeen;

import java.awt.*;

/**
 * Created by rkessler on 2017-02-11.
 */
public class Helper {

    public static boolean isValidRule(Rules rules){
        boolean result = rules instanceof HL;
        result |= rules instanceof HLTeen;
        result |= rules instanceof HLAdult;
        return result;
    }

    public static String capitalize(final String line) {
        return Character.toUpperCase(line.charAt(0)) + line.substring(1);
    }


    public static Color getColorByString(Rules activeRules, String colorName){
        assert activeRules.teamColor.length == activeRules.teamColorName.length;
        for (int idx=0; idx < activeRules.teamColorName.length; idx++){

            if (activeRules.teamColorName[idx].equals(capitalize(colorName))){
                return activeRules.teamColor[idx];
            }
        }
        return null;
    }

    public static String formatTime(int seconds) {
        int displaySeconds = Math.abs(seconds) % 60;
        int displayMinutes = Math.abs(seconds) / 60;
        return (seconds < 0 ? "-" : "") + String.format("%02d:%02d", displayMinutes, displaySeconds);
    }
}
