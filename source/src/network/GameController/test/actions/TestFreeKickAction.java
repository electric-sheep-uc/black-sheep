package actions;

import common.Log;
import controller.action.ActionBoard;
import controller.action.GCAction;
import controller.action.ui.DirectFreeKick;
import controller.action.ui.IndirectFreeKick;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.SecondaryGameStates;
import org.junit.BeforeClass;
import org.junit.Test;
import teamcomm.data.GameState;

import static junit.framework.TestCase.*;

/**
 * Created by rkessler on 2017-03-24.
 */
public class TestFreeKickAction {

    @BeforeClass
    public static void setUp(){
        System.setProperty("CONFIG_ROOT", "test_resources/");
        try {
            Log.init("dummy.log");
        } catch (Exception e){
            // TODO - make sure the logger is a proper singleton
        }
        ActionBoard.init(); // TODO - get rid of this stupid static thing
    }

    AdvancedData data = new AdvancedData();

    @Test
    public void testIndirectFreeKickAction(){
        AdvancedData data = new AdvancedData();
        data.team[0].teamNumber = 14;
        data.gameState = GameStates.PLAYING;
        data.secGameState = SecondaryGameStates.NORMAL;

        IndirectFreeKick fk = new IndirectFreeKick(0);
        verifyFreeKickActionWorks(data, fk, SecondaryGameStates.INDIRECT_FREEKICK);
    }

    @Test
    public void testDirectFreeKickAction(){
        AdvancedData data = new AdvancedData();
        data.team[0].teamNumber = 14;
        data.gameState = GameStates.PLAYING;
        data.secGameState = SecondaryGameStates.NORMAL;

        DirectFreeKick fk = new DirectFreeKick(0);
        verifyFreeKickActionWorks(data, fk, SecondaryGameStates.DIRECT_FREEKICK);
    }

    private void verifyFreeKickActionWorks(AdvancedData data, GCAction fk, SecondaryGameStates secondaryGameState){
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
    public void testDirectFreeKickNotPossibleWhilePenaltyKickSecondaryGameState(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        DirectFreeKick fk = new DirectFreeKick(0);

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
        data.secGameState = SecondaryGameStates.PENALTYKICK;

        // Assert that it is not possible to execute a FreeKickAction during a PenaltyKick
        assertFalse(fk.isLegal(data));
    }

    @Test
    public void testDirectFreeKickNotPossibleWhileIndirectFreeKickSecondaryGameState(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        DirectFreeKick fk = new DirectFreeKick(0);

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
        data.secGameState = SecondaryGameStates.INDIRECT_FREEKICK;

        // Assert that it is not possible to execute a FreeKickAction during a PenaltyKick
        assertFalse(fk.isLegal(data));
    }

    @Test
    public void testIndirectFreeKickNotPossibleWhilePenaltyKickSecondaryGameState(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        IndirectFreeKick fk = new IndirectFreeKick(0);

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
        data.secGameState = SecondaryGameStates.PENALTYKICK;

        // Assert that it is not possible to execute a FreeKickAction during a PenaltyKick
        assertFalse(fk.isLegal(data));
    }

    @Test
    public void testIndirectFreeKickNotPossibleWhileDirectFreeKickSecondaryGameState(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        IndirectFreeKick fk = new IndirectFreeKick(0);

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
        data.secGameState = SecondaryGameStates.DIRECT_FREEKICK;

        // Assert that it is not possible to execute a FreeKickAction during a PenaltyKick
        assertFalse(fk.isLegal(data));
    }
}
