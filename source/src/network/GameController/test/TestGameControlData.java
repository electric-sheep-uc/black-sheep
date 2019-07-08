import data.states.AdvancedData;
import data.values.SecondaryGameStates;
import data.values.TeamColors;
import org.junit.BeforeClass;
import org.junit.Test;

import java.nio.ByteBuffer;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertTrue;

/**
 * Created by rkessler on 2017-03-24.
 */
public class TestGameControlData {

    @BeforeClass
    public static void setUp(){
        System.setProperty("CONFIG_ROOT", "test_resources/");
    }

    @Test
    public void test_secondary_game_state_send_correctly() {
        AdvancedData data = new AdvancedData();

        data.secGameState = SecondaryGameStates.DIRECT_FREEKICK;
        data.dropInTeam = TeamColors.BLACK.value();

        ByteBuffer byteBuffer = data.toByteArray();
        byteBuffer.position(0);

        AdvancedData new_data = new AdvancedData();

        boolean done = new_data.fromByteArray(byteBuffer);

        assertTrue("could not parse stuff", done);
        assertEquals(data.secGameState, new_data.secGameState);
        assertEquals(data.dropInTeam, new_data.dropInTeam);
    }


}
