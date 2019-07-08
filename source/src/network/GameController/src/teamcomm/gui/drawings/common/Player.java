package teamcomm.gui.drawings.common;

import com.jogamp.opengl.GL2;
import data.Helper;
import data.spl.SPLStandardMessage;
import data.values.Penalties;
import data.values.TeamColors;
import teamcomm.data.GameState;
import teamcomm.data.RobotState;
import teamcomm.gui.Camera;
import teamcomm.gui.drawings.PerPlayer;
import teamcomm.gui.drawings.RoSi2Loader;

/**
 * Drawing for a robot.
 *
 * @author Felix Thielke
 */
public class Player extends PerPlayer {

    private static String getModelName(final int color) {

        TeamColors teamcolor = TeamColors.fromValue((byte) color);

        if (teamcolor != null){
            return "robot" + Helper.capitalize(teamcolor.toString());
        }
        return "robotWhite";
    }

    @Override
    protected void init(GL2 gl) {
        RoSi2Loader.getInstance().cacheModels(gl, new String[]{"robotBlue", "robotRed", "robotBlack", "robotYellow", "robotWhite", "robotGreen", "robotOrange", "robotPurple", "robotBrown", "robotGray"});
    }

    @Override
    public void draw(final GL2 gl, final RobotState player, final Camera camera) {
        final SPLStandardMessage msg = player.getLastMessage();
        if (msg != null && msg.poseValid) {
            gl.glPushMatrix();

            if (player.getPenalty() != Penalties.NONE) {
                gl.glTranslatef(-msg.playerNum, -3.5f, 0);
                gl.glRotatef(-90, 0, 0, 1);
            } else {
                gl.glTranslatef(msg.pose[0] / 1000.f, msg.pose[1] / 1000.f, 0);
                gl.glRotatef((float) Math.toDegrees(msg.pose[2]), 0, 0, 1);

                if (msg.fallenValid && msg.fallen) {
                    gl.glTranslatef(0, 0, 0.05f);
                    gl.glRotatef(90, 0, 1, 0);
                }
            }

            gl.glCallList(RoSi2Loader.getInstance().loadModel(gl, getModelName(GameState.getInstance().getTeamColor(player.getTeamNumber()))));

            gl.glPopMatrix();
        }
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
