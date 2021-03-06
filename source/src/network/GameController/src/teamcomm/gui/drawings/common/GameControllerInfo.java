package teamcomm.gui.drawings.common;

import com.jogamp.opengl.GL2;
import data.communication.GameControlData;
import data.Rules;
import data.communication.TeamInfo;
import data.values.SecondaryGameStates;
import teamcomm.data.GameState;
import teamcomm.gui.Camera;
import teamcomm.gui.drawings.Static;
import teamcomm.gui.drawings.Text;

/**
 * Drawing for the current GameController info.
 *
 * @author Felix Thielke
 */
public class GameControllerInfo extends Static {

    @Override
    protected void init(GL2 gl) {
        setActive(false);
    }

    @Override
    public void draw(final GL2 gl, final Camera camera) {
        final GameControlData data = GameState.getInstance().getLastGameControlData();
        if (data != null) {
            gl.glPushMatrix();
            gl.glTranslatef(0, 4, .5f);
            camera.turnTowardsCamera(gl);

            // Display half
            final String half;
            if (data.team[0].teamNumber == 98 || data.team[0].teamNumber == 99 || data.team[1].teamNumber == 98 || data.team[1].teamNumber == 99) {
                half = "Drop-in Game";
            } else {
                if (data.firstHalf == GameControlData.C_TRUE) {
                    if (data.secGameState == SecondaryGameStates.TIMEOUT) {
                        half = "Timeout";
                    } else {
                        half = "1st half";
                    }
                } else {
                    if (data.secGameState == SecondaryGameStates.NORMAL || data.secGameState == SecondaryGameStates.OVERTIME) {
                        half = "2nd half";
                    } else if (data.secGameState == SecondaryGameStates.TIMEOUT) {
                        half = "Timeout";
                    } else if (data.secGameState == SecondaryGameStates.PENALTYSHOOT) {
                        half = "Penalty Shootout";
                    } else {
                        half = "";
                    }
                }
            }
            Text.drawText(half, 0, 0.9f, 0.3f);

            int minutes = (data.secsRemaining < 0 ? (-data.secsRemaining) : data.secsRemaining) / 60;
            int seconds = (data.secsRemaining < 0 ? (-data.secsRemaining) : data.secsRemaining) % 60;
            Text.drawText((data.secsRemaining < 0 ? "-" : "") + (minutes < 10 ? "0" : "") + minutes + ":" + (seconds < 10 ? "0" : "") + seconds, 0, 0.6f, 0.3f);

            // Display game state
            final String state = data.gameState.toString();
            Text.drawText(state, 0, 0.3f, 0.3f);

            // Display scores
            final TeamInfo teamLeft = data.team[GameState.getInstance().isMirrored() ? 1 : 0];
            final TeamInfo teamRight = data.team[GameState.getInstance().isMirrored() ? 0 : 1];
            Text.drawText("" + teamLeft.score, -0.3f, 0, 0.3f, getColor(teamLeft.teamColor.value()));
            Text.drawText(":", 0, 0, 0.3f);
            Text.drawText("" + teamRight.score, 0.3f, 0, 0.3f, getColor(teamRight.teamColor.value()));
            gl.glPopMatrix();
        }
    }

    private static float[] getColor(final byte color) {
        if (color < 0 || color >= Rules.league.teamColor.length) {
            return new float[]{1, 1, 1, 1};
        }
        return Rules.league.teamColor[color].getComponents(new float[4]);
    }

    @Override
    public boolean hasAlpha() {
        return false;
    }

    @Override
    public int getPriority() {
        return 0;
    }

}
