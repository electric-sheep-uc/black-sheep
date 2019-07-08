package ui.components;

import controller.action.ActionBoard;
import controller.ui.ui.components.TeamComponent;
import data.values.Side;
import org.junit.BeforeClass;
import org.junit.Test;

import javax.swing.*;

/**
 * Created by rkessler on 2017-04-25.
 */
public class TestTeamComponent {

    @BeforeClass
    public static void setUp(){
        System.setProperty("CONFIG_ROOT", "test_resources/");
    }

    @Test
    public void testTeamComponent(){
        ActionBoard.init(); // TODO - get rid of this stupid static thing

        TeamComponent tc = new TeamComponent(Side.LEFT, new ButtonGroup());
    }
}
