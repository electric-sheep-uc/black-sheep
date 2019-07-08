package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.action.ActionBoard;
import controller.ui.localization.LocalizationManager;
import data.Rules;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.Side;

import javax.swing.*;

/**
 * Created by rkessler on 2017-03-29.
 */
public class TeamActions extends AbstractComponent {

    private static final int TIMEOUT_HIGHLIGHT_SECONDS = 10;

    protected static final String OUT = "Out";
    protected static final String STUCK = "Global <br/> Game <br/> Stuck";

    protected Side side;

    protected JButton timeOut;
    protected JButton stuck;
    protected JButton out;

    protected JPanel container;

    public TeamActions(Side side) {
        this.side = side;

        defineLayout();
    }


    public void defineLayout() {
        container = new JPanel();
        container.setVisible(true);

        TotalScaleLayout layout = new TotalScaleLayout(container);
        container.setLayout(layout);

        timeOut = new JButton(LocalizationManager.getLocalization().TAKE_TIMEOUT);
        out = new JButton(OUT);
        stuck = new JButton(STUCK);

        layout.add(0, 0, 0.33, 1, timeOut);
        layout.add(0.33, 0, 0.33, 1, out);
        layout.add(0.66, 0, 0.34, 1, stuck);

        out.setVisible(false);
        stuck.setVisible(false);
        timeOut.setVisible(false);



        timeOut.setVisible(true);
        out.setVisible(true);

        timeOut.addActionListener(ActionBoard.timeOut[side.value()]);
        out.addActionListener(ActionBoard.out[side.value()]);

        this.setLayout(new TotalScaleLayout(this));
        ((TotalScaleLayout) this.getLayout()).add(0, 0, 1, 1, container);

        this.setVisible(true);
    }

    @Override
    public void update(AdvancedData data) {
        updateTimeOut(data);
        if (out != null) {
            updateOut(data);
        }
    }

    /**
     * Updates the time-out.
     *
     * @param data The current data (model) the GUI should view.
     */
    protected void updateTimeOut(AdvancedData data) {

        if (data.timeOutActive[side.value()]) {
            timeOut.setText(LocalizationManager.getLocalization().END_TIMEOUT);
        } else {
            timeOut.setText(LocalizationManager.getLocalization().TAKE_TIMEOUT);
        }

        if (!data.timeOutActive[side.value()]) {
            timeOut.setSelected(false);
            resetHighlighting(timeOut);
        } else {
            if (data.isSecondaryClockLowerThan(TIMEOUT_HIGHLIGHT_SECONDS)) {
                highlight(timeOut);
            }
        }

        timeOut.setEnabled(ActionBoard.timeOut[side.value()].isLegal(data));
    }

    /**
     * Updates the global game stuck.
     *
     * @param data The current data (model) the GUI should view.
     */
    protected void updateGlobalStuck(AdvancedData data) {
        if (data.gameState == GameStates.PLAYING
                && data.getRemainingSeconds(data.whenCurrentGameStateBegan, Rules.league.kickoffTime + Rules.league.minDurationBeforeStuck) > 0) {
            stuck.setEnabled(false);
            stuck.setText("<font color=#808080>" + STUCK);
        } else {
            stuck.setEnabled(ActionBoard.stuck[side.value()].isLegal(data));
            stuck.setText((ActionBoard.stuck[side.value()].isLegal(data) ? "<font color=#000000>" : "<font color=#808080>") + STUCK);
        }

    }


    /**
     * Updates the out.
     *
     * @param data The current data (model) the GUI should view.
     */
    protected void updateOut(AdvancedData data) {
        out.setEnabled(ActionBoard.out[side.value()].isLegal(data));
    }
}
