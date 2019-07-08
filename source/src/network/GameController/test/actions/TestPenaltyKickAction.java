package actions;

import common.Log;
import controller.action.ActionBoard;
import controller.action.GCAction;
import controller.action.ui.DirectFreeKick;
import controller.action.ui.PenaltyKick;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.SecondaryGameStates;
import org.junit.BeforeClass;
import org.junit.Test;

import static junit.framework.TestCase.*;

/**
 * Created by rkessler on 2017-03-24.
 */
public class TestPenaltyKickAction {

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
    public void testPenaltyKickAction(){
        AdvancedData data = new AdvancedData();
        data.team[0].teamNumber = 14;
        data.gameState = GameStates.PLAYING;
        data.secGameState = SecondaryGameStates.NORMAL;

        PenaltyKick fk = new PenaltyKick(0);
        SecondaryGameStates secondaryGameState = SecondaryGameStates.PENALTYKICK;

        // Assert that we can execute the action
        assertTrue(fk.isLegal(data));

        // Perform the action and expect the state change
        fk.perform(data);

        assertEquals(secondaryGameState, data.secGameState);
        assertEquals(14, data.secGameStateInfo.toByteArray()[0]);
        assertEquals(1, data.secGameStateInfo.toByteArray()[1]);

        // Perform it again and expect the substate to move forward by one
        fk.perform(data);

        assertEquals(secondaryGameState, data.secGameState);
        assertEquals(14, data.secGameStateInfo.toByteArray()[0]);
        assertEquals(0, data.secGameStateInfo.toByteArray()[1]);

        // Perform it again and expect it being the previous state again
        fk.perform(data);

        assertNotSame(secondaryGameState, SecondaryGameStates.NORMAL);
        assertEquals(0, data.secGameStateInfo.toByteArray()[0]);
        assertEquals(0, data.secGameStateInfo.toByteArray()[1]);
    }


    @Test
    public void testPenaltyKickNotPossibleWhileFreeKickSecondaryGameState(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        PenaltyKick fk = new PenaltyKick(0);

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
//        data.secGameState = SecondaryGameStates.FREEKICK;

        // Assert that it is not possible to execute a FreeKickAction during a PenaltyKick
        assertFalse(fk.isLegal(data));
    }
}
