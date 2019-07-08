package controller.ui.ui.components;

import common.TotalScaleLayout;
import data.states.AdvancedData;
import data.values.Side;

/**
 * Created by rkessler on 2017-06-11.
 */
public class RobotWithDropInCounter extends Robot {

    private DropInStatSnippet diss;

    public RobotWithDropInCounter(Side side, int id) {
        super(side, id);
        diss = new DropInStatSnippet(side, id);
    }


    public void setup() {
        super.setup();
    }

    public void updateLayout(double aspectRatio) {
        TotalScaleLayout robotLayout = new TotalScaleLayout(robot);
        robot.setLayout(robotLayout);
        robot.removeAll();

        // Figure out a way to make this easier
        double rightOffset = 0.21;

        double cardWidth = 0.4 / aspectRatio;

        robotLayout.add(1 - rightOffset + 0.02, 0.1, 0.18, 0.75, diss);

        robotLayout.add(1 - cardWidth - rightOffset, 0.1, cardWidth, 0.75, yellowCard);
        robotLayout.add(1 - 2 * cardWidth - rightOffset, 0.1, cardWidth, 0.75, redCard);

        double restWidth = 1 - 2 * cardWidth - rightOffset;

        robotLayout.add(0, 0, restWidth, 0.9, robotLabel);

        robotLayout.add(0, 0.9, 1, 0.1, progressBar);
    }


    @Override
    public void update(AdvancedData data) {
        super.update(data);
        diss.update(data);
    }
}
