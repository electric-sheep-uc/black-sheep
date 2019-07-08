package actions.states;

import common.Log;
import controller.action.ActionBoard;
import controller.action.ui.state.Finish;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.SecondaryGameStates;
import org.junit.BeforeClass;
import org.junit.Test;

import static junit.framework.TestCase.*;

/**
 * Created by rkessler on 2017-03-26.
 */
public class TestFinishAction {

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
    public void testFinishActionNotPossibleDuringFreeKick(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        Finish finish = new Finish();

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
        data.secGameState = SecondaryGameStates.DIRECT_FREEKICK;

        // Assert that game cannot be finish in FreeKick
        assertFalse(finish.isLegal(data));
    }

    @Test
    public void testFinishActionNotPossibleDuringPenaltyKick(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        Finish finish = new Finish();

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
        data.secGameState = SecondaryGameStates.PENALTYKICK;

        // Assert that game cannot be finish in FreeKick
        assertFalse(finish.isLegal(data));
    }

    @Test
    public void testFinishActionPossibleNormally(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        /// Create a free kick action
        Finish finish = new Finish();

        // Create an advanced data object to perform it on
        AdvancedData data = new AdvancedData();
        data.gameState = GameStates.PLAYING;
        data.secGameState = SecondaryGameStates.NORMAL;

        // Assert that game cannot be finish in FreeKick
        assertTrue(finish.isLegal(data));
    }
}
