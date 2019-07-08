package actions;

import common.Log;
import controller.action.ActionBoard;
import controller.action.ui.TimeOut;
import data.Rules;
import data.communication.TeamInfo;
import data.hl.HL;
import data.states.AdvancedData;
import data.values.GameStates;
import org.junit.BeforeClass;
import org.junit.Test;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertFalse;
import static junit.framework.TestCase.assertTrue;

/**
 * Created by rkessler on 2017-03-25.
 */
public class TestTimeOut {

    @BeforeClass
    public static void setUp(){
        System.setProperty("CONFIG_ROOT", "test_resources/");
        try {
            Log.init("dummy.log");
        } catch (Exception e){
            // TODO - make sure the logger is a proper singleton
        }
    }

    @Test
    public void testTimeoutIsPossibleOnlyInNotPlayingStates() {
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        TimeOut to = new TimeOut(0);
        AdvancedData data = new AdvancedData();

        data.gameState = GameStates.PLAYING;
        assertFalse(to.isLegal(data));
    }

    @Test
    public void testTimeoutPossibleInReadyState() {
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        TimeOut to = new TimeOut(0);
        AdvancedData data = new AdvancedData();

        data.gameState = GameStates.READY;
        assertTrue(to.isLegal(data));
    }

    @Test
    public void testTimeoutDoesNotSwitchKickOff() {
        ActionBoard.init();
        Rules.league = new HL();

        TimeOut to = new TimeOut(0);
        AdvancedData data = new AdvancedData();
        data.gameState = GameStates.READY;
        data.team = new TeamInfo[2];

        data.team[0] = new TeamInfo();
        data.team[0].teamNumber = 0;

        data.team[1] = new TeamInfo();
        data.team[1].teamNumber = 1;

        // Perform it the first time to activate the timeout
        to.perform(data);

        // Perform it the second time to remove the timeout
        to.perform(data);

        assertEquals(data.kickOffTeam, data.team[0].teamNumber);

    }

}
