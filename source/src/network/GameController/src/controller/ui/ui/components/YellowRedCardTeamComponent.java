package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.action.ActionBoard;
import controller.ui.helper.FontHelper;
import controller.ui.ui.customized.Button;
import data.Rules;
import data.communication.GameControlData;
import data.communication.TeamInfo;
import data.states.AdvancedData;
import data.teams.TeamsLoader;
import data.values.GameStates;
import data.values.SecondaryGameStates;
import data.values.Side;

import javax.swing.*;
import java.awt.*;

/**
 * Created by rkessler on 2017-03-29.
 */
public class YellowRedCardTeamComponent extends AbstractComponent {

    private Side side;

    private JButton goalDec;
    private JButton goalInc;
    private JRadioButton kickOff;
    private JLabel pushes;
    private JPanel robots;

    private Robot[] robot;

    private int defaultGoalieIndex = 0;

    private static final String KICKOFF_PENALTY_SHOOTOUT = "P.-taker";

    private static final String KICKOFF = "Kickoff";
    private int teamSize;


    public YellowRedCardTeamComponent(Side side, ButtonGroup kickOffGroup, AdvancedData initialData) {
        this.side = side;

        goalInc = new Button("+");
        goalInc.setHorizontalTextPosition(SwingConstants.CENTER);
        goalInc.setVerticalTextPosition(SwingConstants.CENTER);

        goalDec = new Button("-");
        goalDec.setHorizontalTextPosition(SwingConstants.CENTER);
        goalDec.setVerticalTextPosition(SwingConstants.CENTER);


        kickOff = new JRadioButton(KICKOFF);
        kickOff.setOpaque(false);
        kickOff.setHorizontalAlignment(JLabel.CENTER);
        kickOff.setVerticalAlignment(SwingConstants.CENTER);

        // Add the kickOff button to the passed in button group
        kickOffGroup.add(kickOff);

        goalDec.addActionListener(ActionBoard.goalDec[side.value()]);
        goalInc.addActionListener(ActionBoard.goalInc[side.value()]);
        kickOff.addActionListener(ActionBoard.kickOff[side.value()]);

        pushes = new JLabel("0");
        pushes.setHorizontalAlignment(JLabel.CENTER);

        // Calculate the teamSize based on rule parameters - add one player if coach is available
        teamSize = Rules.league.teamSize;

        if (Rules.league.isCoachAvailable) {
            teamSize += 1;
        }

        // Define the layout
        defineLayout();
    }


    public void defineLayout() {
        int teamSize = Rules.league.teamSize;

        if (Rules.league.isCoachAvailable) {
            teamSize += 1;
        }

        robots = new JPanel();
        TotalScaleLayout tsc = new TotalScaleLayout(robots);
        robots.setLayout(tsc);

        // Second row
        tsc.add(0, 0, 0.25, 0.05, pushes);
        tsc.add(0.25, 0, 0.25, 0.05, kickOff);
        tsc.add(0.8, 0, 0.1, 0.05, goalDec);
        tsc.add(0.9, 0, 0.1, 0.05, goalInc);

        robot = new Robot[teamSize];
        double robot_height = 0.12;

        for (int j = 0; j < teamSize; j++) {
            robot[j] = new Robot(side, j);
            robot[j].setup();

            tsc.add(0, 0.1 + robot_height * j + 0.01 * j, 1, robot_height , robot[j]);

        }
        robots.setVisible(true);

        this.setLayout(new TotalScaleLayout(this));
        ((TotalScaleLayout) this.getLayout()).add(0, 0, 1, 1, robots);

        this.setVisible(true);
    }

    private static final String PUSHES = "Pushes";
    private static final String SHOT = "Shot";
    private static final String SHOTS = "Shots";


    @SuppressWarnings("Duplicates")
    private void updatePushes(AdvancedData data) {
        if (data.secGameState != SecondaryGameStates.PENALTYSHOOT && data.previousSecGameState != SecondaryGameStates.PENALTYSHOOT) {
            if (Rules.league.pushesToEjection == null || Rules.league.pushesToEjection.length == 0) {
                pushes.setText("");
            } else {
                pushes.setText(PUSHES + ": " + data.pushes[side.value()]);
            }
        } else {
            pushes.setText((side.value() == 0 && (data.gameState == GameStates.SET
                    || data.gameState == GameStates.PLAYING) ? SHOT : SHOTS) + ": " + data.team[side.value()].penaltyShot);
        }

    }

    @SuppressWarnings("Duplicates")
    private void updateKickOff(AdvancedData data) {
        if (data.kickOffTeam == GameControlData.DROPBALL) {
            kickOff.setSelected(true);
        } else if (data.team[side.value()].teamNumber == data.kickOffTeam) {
            kickOff.setSelected(true);
        } else {
            kickOff.setSelected(false);
        }

        kickOff.setEnabled(ActionBoard.kickOff[side.value()].isLegal(data));
        if (data.secGameState != SecondaryGameStates.PENALTYSHOOT
                && data.previousSecGameState != SecondaryGameStates.PENALTYSHOOT) {
            kickOff.setText(KICKOFF);
        } else {
            kickOff.setText(KICKOFF_PENALTY_SHOOTOUT);
        }

    }

    @SuppressWarnings("Duplicates")
    @Override
    public void update(AdvancedData data) {
        updateKickOff(data);
        updatePushes(data);

        goalInc.setEnabled(ActionBoard.goalInc[side.value()].isLegal(data));
        goalDec.setVisible(ActionBoard.goalDec[side.value()].isLegal(data));

        for (int j = 0; j < teamSize; j++) {
            robot[j].update(data);
        }
    }
}
