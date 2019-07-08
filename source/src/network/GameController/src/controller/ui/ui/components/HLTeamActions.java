package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.action.ActionBoard;
import controller.action.ui.*;
import controller.ui.localization.LocalizationManager;
import controller.ui.ui.customized.Button;
import controller.ui.ui.customized.GameInterruptionButton;
import controller.ui.ui.customized.JMultiStepIndicatorButton;
import data.states.AdvancedData;
import data.values.SecondaryGameStates;
import data.values.Side;

import javax.swing.*;
import java.awt.*;

/**
 * Created by rkessler on 2017-04-29.
 */
public class HLTeamActions extends TeamActions {

    private GameInterruptionButton indirectFreeKick;
    private GameInterruptionButton directFreeKick;
    private GameInterruptionButton penaltyKick;
    private GameInterruptionButton cornerKick;
    private GameInterruptionButton goalKick;
    private GameInterruptionButton throwIn;

    public HLTeamActions(Side side) {
        super(side);

        defineLayout();
    }

    public void defineLayout() {
        container = new JPanel();
        container.setVisible(true);

        TotalScaleLayout layout = new TotalScaleLayout(container);
        container.setLayout(layout);

        timeOut = new JButton(LocalizationManager.getLocalization().TAKE_TIMEOUT);

        directFreeKick = new GameInterruptionButton(LocalizationManager.getLocalization().DIRECT_FREE_KICK);
        indirectFreeKick = new GameInterruptionButton(LocalizationManager.getLocalization().INDIRECT_FREE_KICK);
        penaltyKick = new GameInterruptionButton(LocalizationManager.getLocalization().PENALTY_KICK);
        cornerKick = new GameInterruptionButton(LocalizationManager.getLocalization().CORNER_KICK);
        goalKick = new GameInterruptionButton(LocalizationManager.getLocalization().GOAL_KICK);
        throwIn = new GameInterruptionButton(LocalizationManager.getLocalization().THROW_IN);

        System.out.println("Adding action listeners");

        directFreeKick.addActionListener(new DirectFreeKick(side.value()));
        indirectFreeKick.addActionListener(new IndirectFreeKick(side.value()));
        penaltyKick.addActionListener(new PenaltyKick(side.value()));
        cornerKick.addActionListener(new CornerKick(side.value()));
        goalKick.addActionListener(new GoalKick(side.value()));
        throwIn.addActionListener(new ThrowIn(side.value()));

        System.out.println("Adding action listeners");

        int nb_rows = 7;
        int row = 0;
        double row_height = 1.0 / nb_rows;
        layout.add(0, 0, 1, row_height, timeOut); row++;
        layout.add(0, row * row_height, 1, row_height, penaltyKick);row++;
        layout.add(0, row * row_height, 1, row_height, directFreeKick);row++;
        layout.add(0, row * row_height, 1, row_height, indirectFreeKick);row++;
        layout.add(0, row * row_height, 1, row_height, cornerKick);row++;
        layout.add(0, row * row_height, 1, row_height, goalKick);row++;
        layout.add(0, row * row_height, 1, row_height, throwIn);row++;

        timeOut.setVisible(true);

        timeOut.addActionListener(ActionBoard.timeOut[side.value()]);

        this.setLayout(new TotalScaleLayout(this));
        ((TotalScaleLayout) this.getLayout()).add(0, 0, 1, 1, container);

        this.setVisible(true);
    }

    @Override
    public void update(AdvancedData data) {
        super.update(data);
        update(data, directFreeKick, ActionBoard.directFreeKick[side.value()]);
        update(data, indirectFreeKick, new IndirectFreeKick(side.value()));
        update(data, penaltyKick, new PenaltyKick(side.value()));
        update(data, cornerKick, new CornerKick(side.value()));
        update(data, goalKick, new GoalKick(side.value()));
        update(data, throwIn, new ThrowIn(side.value()));
    }

    private void update(AdvancedData data, GameInterruptionButton button, GameInterruption action) {
        button.setEnabled(action.isLegal(data));
        if (data.secGameState == action.getSecGameState()) {
            byte[] bytes = data.secGameStateInfo.toByteArray();
            byte team = bytes[0];
            byte subMode = bytes[1];

            boolean isUs = team == data.team[side.value()].teamNumber;

            if (isUs) {
                button.setSubMode(subMode);
            }
        } else {
            button.setInitialMode();
        }
    }
}
