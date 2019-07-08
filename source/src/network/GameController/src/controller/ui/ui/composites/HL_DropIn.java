package controller.ui.ui.composites;

import common.TotalScaleLayout;
import controller.ui.ui.AbstractUI;
import controller.ui.ui.components.*;
import data.states.AdvancedData;
import data.states.GamePreparationData;
import data.values.Side;

import javax.swing.*;
import java.awt.*;


public class HL_DropIn extends AbstractUI {

    private ButtonGroup kickOffGroup;

    public HL_DropIn(boolean fullscreen, AdvancedData data, GamePreparationData gamePrepData) {
        super(fullscreen, data, gamePrepData);

        kickOffGroup = new ButtonGroup();

        setupUI();

        this.setSize(600, 400);

        getContentPane().setLayout(
                new BoxLayout(getContentPane(), BoxLayout.PAGE_AXIS)
        );

        setVisible(true);
    }

    private void setupUI() {

        // Create a root container that is added to the actual panel
        JPanel rootContainer = new JPanel();

        // Put a total scale layout on the container so we can add elements
        TotalScaleLayout layout = new TotalScaleLayout(rootContainer);
        rootContainer.setLayout(layout);

        // First we add the game states

        // Then we add the left panel (left team)
        JPanel left_team_panel = new JPanel();
        TotalScaleLayout left_panel_layout = new TotalScaleLayout(left_team_panel);
        left_team_panel.setLayout(left_panel_layout);
        setupLeftPanel(left_panel_layout);

        // We add the center panel including Clock, Penalties
        JPanel center_panel = new JPanel();
        TotalScaleLayout center_panel_layout = new TotalScaleLayout(center_panel);
        center_panel.setLayout(center_panel_layout);
        setupCenterPanel(center_panel_layout);

        // We add the right panel (right team)
        JPanel right_team_panel = new JPanel();
        TotalScaleLayout right_panel_layout = new TotalScaleLayout(right_team_panel);
        right_team_panel.setLayout(right_panel_layout);
        setupRightPanel(right_panel_layout);

        // Layouting those three
        layout.add(.01, .11, .28, .75, left_team_panel);
        layout.add(.3, .11, .4, .75, center_panel);
        layout.add(.71, .11, .28, .75, right_team_panel);

        GameMetaInfo meta_info = new GameMetaInfo(initialData, gamePrepData);
        elementsReceivingUpdates.add(meta_info);

        // Adding the meta level top component
        layout.add(.01, .01, .98, .07, meta_info);

        // Adding the History component
        GameStateHistoryLogger gshl = new GameStateHistoryLogger();
        elementsReceivingUpdates.add(gshl);
        layout.add(.01, .88, .98, .10, gshl);

        // Add the root container
        this.add(rootContainer);
    }

    private void setupCenterPanel(TotalScaleLayout center_panel_layout) {

        SequenceGameStates sgs = new SequenceGameStates();
        elementsReceivingUpdates.add(sgs);
        center_panel_layout.add(0.01, 0.01, 0.98, 0.1, sgs);

        // Now we actually fill the center elements
        GameStateComponent gsc = new GameStateComponent();
        //gsc.setBackground(Color.yellow);
        elementsReceivingUpdates.add(gsc);
        center_panel_layout.add(0.01, 0.11, 0.98, 0.1, gsc);
        gsc.setBackground(Color.YELLOW);

        ClockComponent cc = new ClockComponent();
        elementsReceivingUpdates.add(cc);
        center_panel_layout.add(0.01, 0.21, 0.98, 0.25, cc);

        PenaltyComponent pc = new PenaltyComponent();
        elementsReceivingUpdates.add(pc);
        center_panel_layout.add(0.01, 0.46, 0.98, 0.45, pc);

    }

    private void setupLeftPanel(TotalScaleLayout left_panel_layout) {
        DropInTeamComponent rl_left = new DropInTeamComponent(Side.LEFT, kickOffGroup);
        rl_left.setBackground(Color.green);
        TeamActions ta_left = new HLTeamActions (Side.LEFT);
        elementsReceivingUpdates.add(rl_left);
        elementsReceivingUpdates.add(ta_left);

        left_panel_layout.add(0.0, 0.0, 1.0, 0.8, rl_left);
        left_panel_layout.add(0.0, 0.8, 1.0, 0.2, ta_left);
    }

    private void setupRightPanel(TotalScaleLayout right_team_panel) {
        DropInTeamComponent rl_right = new DropInTeamComponent(Side.RIGHT, kickOffGroup);

        TeamActions ta_right = new HLTeamActions (Side.RIGHT);

        elementsReceivingUpdates.add(rl_right);
        elementsReceivingUpdates.add(ta_right);

        right_team_panel.add(0.0, 0.0, 1.0, 0.8, rl_right);
        right_team_panel.add(0.0, 0.8, 1.0, 0.2, ta_right);
    }
}
