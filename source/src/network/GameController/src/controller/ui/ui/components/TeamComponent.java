package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.action.ActionBoard;
import controller.ui.ui.customized.Button;
import data.Rules;
import data.communication.GameControlData;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.SecondaryGameStates;
import data.values.Side;

import javax.swing.*;
import java.awt.*;

/**
 * Created by rkessler on 2017-03-29.
 */
public class TeamComponent extends AbstractComponent {

    private Side side;

    protected JLabel name;
    protected JButton goalDec;
    protected JButton goalInc;
    protected JLabel goals;

    protected JRadioButton kickOff;

    protected JLabel pushes;

    protected JPanel robots;
    protected JButton[] robot;
    protected JLabel[] robotLabel;
    protected ImageIcon[] lanIcon;
    protected JProgressBar[] robotTime;

    protected ImageIcon lanOnline;
    protected ImageIcon lanHighLatency;
    protected ImageIcon lanOffline;
    protected ImageIcon lanUnknown;

    protected static final String KICKOFF_PENALTY_SHOOTOUT = "P.-taker";

    protected static final String ICONS_PATH = "config/icons/";
    protected static final String ONLINE = "wlan_status_green.png";
    protected static final String OFFLINE = "wlan_status_red.png";
    protected static final String HIGH_LATENCY = "wlan_status_yellow.png";
    protected static final String UNKNOWN_ONLINE_STATUS = "wlan_status_grey.png";

    public static final String KICKOFF = "Kickoff";
    private int teamSize;

    public TeamComponent(Side side, ButtonGroup kickOffGroup) {
        this.side = side;

        goalInc = new Button("+");
        goalDec = new Button("-");
        kickOff = new JRadioButton(KICKOFF);
        kickOff.setOpaque(false);
        kickOff.setHorizontalAlignment(JLabel.CENTER);

        // TODO - needs to be a button group across both sides ( i guess)
        kickOffGroup.add(kickOff);

        goals = new JLabel("0");
        goals.setHorizontalAlignment(JLabel.CENTER);

        goalDec.addActionListener(ActionBoard.goalDec[side.value()]);
        goalInc.addActionListener(ActionBoard.goalInc[side.value()]);
        kickOff.addActionListener(ActionBoard.kickOff[side.value()]);

        pushes = new JLabel("0");
        pushes.setHorizontalAlignment(JLabel.CENTER);


        lanOnline = new ImageIcon(ICONS_PATH + ONLINE);
        lanHighLatency = new ImageIcon(ICONS_PATH + HIGH_LATENCY);
        lanOffline = new ImageIcon(ICONS_PATH + OFFLINE);
        lanUnknown = new ImageIcon(ICONS_PATH + UNKNOWN_ONLINE_STATUS);

        teamSize = Rules.league.teamSize;

        if (Rules.league.isCoachAvailable) {
            teamSize += 1;
        }

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

        // First row
        tsc.add(0, 0, 0.33, 0.1, goals);
        tsc.add(0.33, 0, 0.33, 0.1, pushes);
        tsc.add(0.66, 0, 0.33, 0.1, kickOff);

        //
        tsc.add(0, 0.1, 0.5, 0.1, goalDec);
        tsc.add(0.5, 0.1, 0.5, 0.1, goalInc);

        robot = new JButton[teamSize];
        robotLabel = new JLabel[teamSize];
        lanIcon = new ImageIcon[teamSize];
        robotTime = new JProgressBar[teamSize];

        for (int j = 0; j < teamSize; j++) {
            robot[j] = new Button();
            robotLabel[j] = new JLabel();
            robotLabel[j].setHorizontalAlignment(JLabel.CENTER);
            lanIcon[j] = lanUnknown;
            robotLabel[j].setIcon(lanIcon[j]);
            robotTime[j] = new JProgressBar();
            robotTime[j].setMaximum(1000);
            robotTime[j].setVisible(false);
            robot[j].setLayout(new BoxLayout(robot[j], BoxLayout.Y_AXIS));
            robot[j].add(robotLabel[j]);
            robot[j].add(robotTime[j]);
            tsc.add(0, 0.2 + 0.1 * j, 1, 0.1, robot[j]);

            robot[j].addActionListener(ActionBoard.robot[side.value()][j]);
        }

        robots.setVisible(true);

        this.setLayout(new TotalScaleLayout(this));
        ((TotalScaleLayout) this.getLayout()).add(0, 0, 1, 1, robots);

        this.setVisible(true);
    }

    protected static final String PUSHES = "Pushes";
    protected static final String SHOT = "Shot";
    protected static final String SHOTS = "Shots";


    protected static final String STANDARD_FONT = "Helvetica";

    protected void updatePushes(AdvancedData data) {
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

    public void updateKickOff(AdvancedData data) {
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

        goals.setText("Goals: " + data.team[side.value()].score);
        goalInc.setEnabled(ActionBoard.goalInc[side.value()].isLegal(data));
        goalDec.setVisible(ActionBoard.goalDec[side.value()].isLegal(data));

        Font titleFont = new Font(STANDARD_FONT, Font.PLAIN, (int) (20));

        for (int j = 0; j < teamSize; j++) {
            robotLabel[j].setFont(titleFont);
        }
    }
}
