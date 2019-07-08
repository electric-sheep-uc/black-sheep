package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.action.ActionBoard;
import controller.ui.localization.LocalizationManager;
import controller.ui.ui.customized.Button;
import controller.ui.ui.customized.ToggleButton;
import data.Rules;
import data.communication.GameControlData;
import data.hl.HL;
import data.states.AdvancedData;
import data.values.SecondaryGameStates;

import javax.swing.*;

/**
 * Created by rkessler on 2017-03-31.
 */
public class SequenceGameStates extends AbstractComponent {

    protected static final String FIRST_HALF = "First Half";
    protected static final String SECOND_HALF = "Second Half";
    protected static final String FIRST_HALF_SHORT = "1st Half";
    protected static final String SECOND_HALF_SHORT = "2nd Half";
    protected static final String FIRST_HALF_OVERTIME = "1st Extra";
    protected static final String SECOND_HALF_OVERTIME = "2nd Extra";
    protected static final String PENALTY_SHOOT = "Penalty Shots";
    protected static final String PENALTY_SHOOT_SHORT = "Penalty";
    protected static final String DROP_BALL = "Drop Ball";

    protected JToggleButton firstHalf;
    protected JToggleButton secondHalf;
    protected JToggleButton firstHalfOvertime;
    protected JToggleButton secondHalfOvertime;
    protected JToggleButton penaltyShoot;
    protected JToggleButton refereeTimeout;

    // TODO - This needs to be moved to inheritence
    protected JButton dropBall;


    protected ButtonGroup halfGroup;

    public SequenceGameStates() {
        defineLayout();
    }


    public void defineLayout() {

        if (!Rules.league.overtime) {
            firstHalf = new ToggleButton(FIRST_HALF);
            firstHalf.setSelected(true);
            secondHalf = new ToggleButton(SECOND_HALF);
            penaltyShoot = new ToggleButton(PENALTY_SHOOT);
            refereeTimeout = new ToggleButton(LocalizationManager.getLocalization().TAKE_REFEREE_TIMEOUT);

            halfGroup = new ButtonGroup();
            halfGroup.add(firstHalf);
            halfGroup.add(secondHalf);
            halfGroup.add(penaltyShoot);
            halfGroup.add(refereeTimeout);

        } else {
            firstHalf = new ToggleButton(FIRST_HALF_SHORT);
            firstHalf.setSelected(true);
            secondHalf = new ToggleButton(SECOND_HALF_SHORT);
            firstHalfOvertime = new ToggleButton(FIRST_HALF_OVERTIME);
            secondHalfOvertime = new ToggleButton(SECOND_HALF_OVERTIME);
            penaltyShoot = new ToggleButton(PENALTY_SHOOT_SHORT);
            refereeTimeout = new ToggleButton(LocalizationManager.getLocalization().TAKE_REFEREE_TIMEOUT);

            halfGroup = new ButtonGroup();
            halfGroup.add(firstHalf);
            halfGroup.add(secondHalf);
            halfGroup.add(firstHalfOvertime);
            halfGroup.add(secondHalfOvertime);
            halfGroup.add(penaltyShoot);
            halfGroup.add(refereeTimeout);
        }

        firstHalf.addActionListener(ActionBoard.firstHalf);
        secondHalf.addActionListener(ActionBoard.secondHalf);
        if (Rules.league.overtime) {
            firstHalfOvertime.addActionListener(ActionBoard.firstHalfOvertime);
            secondHalfOvertime.addActionListener(ActionBoard.secondHalfOvertime);
        }
        penaltyShoot.addActionListener(ActionBoard.penaltyShoot);

        refereeTimeout.addActionListener(ActionBoard.refereeTimeout);

        if (Rules.league instanceof HL) {
            dropBall = new Button(DROP_BALL);
            dropBall.addActionListener(ActionBoard.dropBall);
        }

        TotalScaleLayout layout = new TotalScaleLayout(this);

        layout.add(0.00, 0, 0.24, 0.5, firstHalf);
        layout.add(0.00, 0.5, 0.24, 0.5, secondHalf);
        layout.add(0.24, 0, 0.24, 0.5, firstHalfOvertime);
        layout.add(0.24, 0.5, 0.24, 0.5, secondHalfOvertime);
        layout.add(0.48, 0, 0.17, 1, penaltyShoot);
        layout.add(0.65, 0, 0.17, 1, refereeTimeout);
        layout.add(0.82, 0, 0.18, 1, dropBall);

        this.setLayout(layout);

    }

    protected void updateDropBall(AdvancedData data) {
        dropBall.setEnabled(ActionBoard.dropBall.isLegal(data));
    }


    @Override
    @SuppressWarnings("Duplicates")
    public void update(AdvancedData data) {

        if (Rules.league instanceof HL) {
            updateDropBall(data);
        }
        firstHalf.setEnabled(ActionBoard.firstHalf.isLegal(data));
        secondHalf.setEnabled(ActionBoard.secondHalf.isLegal(data));
        if (Rules.league.overtime) {
            firstHalfOvertime.setEnabled(ActionBoard.firstHalfOvertime.isLegal(data));
            secondHalfOvertime.setEnabled(ActionBoard.secondHalfOvertime.isLegal(data));
        }
        penaltyShoot.setEnabled(ActionBoard.penaltyShoot.isLegal(data));
        firstHalf.setSelected((data.secGameState == SecondaryGameStates.NORMAL)
                && (data.firstHalf == GameControlData.C_TRUE));
        secondHalf.setSelected((data.secGameState == SecondaryGameStates.NORMAL)
                && (data.firstHalf != GameControlData.C_TRUE));
        if (Rules.league.overtime) {
            firstHalfOvertime.setSelected((data.secGameState == SecondaryGameStates.OVERTIME)
                    && (data.firstHalf == GameControlData.C_TRUE));
            secondHalfOvertime.setSelected((data.secGameState == SecondaryGameStates.OVERTIME)
                    && (data.firstHalf != GameControlData.C_TRUE));
        }
        penaltyShoot.setSelected(data.secGameState == SecondaryGameStates.PENALTYSHOOT || data.previousSecGameState == SecondaryGameStates.PENALTYSHOOT);

        if (data.refereeTimeout) {
            refereeTimeout.setText(LocalizationManager.getLocalization().END_REFEREE_TIMEOUT);
        } else {
            refereeTimeout.setText(LocalizationManager.getLocalization().TAKE_REFEREE_TIMEOUT);
        }

        refereeTimeout.setSelected(data.refereeTimeout);
        refereeTimeout.setEnabled(ActionBoard.refereeTimeout.isLegal(data));
    }
}
