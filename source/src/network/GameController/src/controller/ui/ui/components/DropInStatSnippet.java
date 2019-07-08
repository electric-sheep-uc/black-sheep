package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.action.ui.CardIncrease;
import controller.action.ui.DropinPointDelta;
import controller.ui.ui.customized.Button;
import data.states.AdvancedData;
import data.values.Side;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * A small component counting drop in points
 * Can be added to the robot label if necessary
 * Created by rkessler on 2017-03-29.
 */
public class DropInStatSnippet  extends AbstractComponent {

    private Side side;
    private int robotId;

    private JButton robotPointsInc;
    private JButton robotPointsDec;
    private JLabel robotPointsLabel;

    public DropInStatSnippet(Side side, int robotId) {
        this.side = side;
        this.robotId = robotId;

        robotPointsInc = new Button("+");
        robotPointsDec = new Button("-");
        robotPointsLabel = new JLabel("0 Points");

        robotPointsInc.addActionListener(new DropinPointDelta(side, this.robotId, 1));
        robotPointsDec.addActionListener(new DropinPointDelta(side, this.robotId, -1));

        defineLayout();
    }

    public void defineLayout() {
        TotalScaleLayout layout = new TotalScaleLayout(this);
        this.setLayout(layout);

        layout.add(0, 0, 1, 0.35, robotPointsInc);
        layout.add(0, 0.35, 1, 0.35, robotPointsDec);
        layout.add(0, 0.70, 1, 0.3, robotPointsLabel);
    }

    @Override
    public void update(AdvancedData data)
    {
        int points = data.getTeam(this.side).player[robotId].dropInPoints;
        robotPointsLabel.setText(points + " Points");
    }
}
