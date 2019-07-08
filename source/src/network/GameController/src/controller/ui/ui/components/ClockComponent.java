package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.action.ActionBoard;
import controller.ui.helper.FontHelper;
import data.Helper;
import data.states.AdvancedData;
import data.states.ExtraClock;
import data.values.GameStates;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;


/**
 * Created by rkessler on 2017-03-28.
 */
public class ClockComponent extends AbstractComponent {

    private JLabel clock;
    private JLabel clockSub;

    private List<JLabel> extraClockLabels = new ArrayList<JLabel>();

    private JButton clockPause;
    private JButton clockReset;

    private static final int KICKOFF_BLOCKED_HIGHLIGHT_SECONDS = 3;

    private static final Color COLOR_HIGHLIGHT = Color.YELLOW;
    private static final Color SUB_CLOCK_COLOUR = new Color(35, 35, 35);
    private static final Color CLOCK_COLOUR = new Color(0, 0, 0);


    public ClockComponent() {
        defineLayout();
    }

    public void defineLayout() {
        this.setBackground(new Color(210, 210, 210));
        clock = new JLabel("10:00");
        clock.setForeground(CLOCK_COLOUR);
        clock.setHorizontalAlignment(JLabel.CENTER);

        clockPause = new JButton("Pause clock");
        clockPause.setOpaque(false);
        clockPause.setBorder(null);

        clockSub = new JLabel("0:00");
        clockSub.setHorizontalAlignment(JLabel.CENTER);
        clockSub.setForeground(SUB_CLOCK_COLOUR);

        // Define extra clocks that can be shown dynamically for specific events
        for (int i = 0; i < 3; i++) {
            JLabel extraClock = new JLabel("0:00");
            extraClock.setHorizontalAlignment(JLabel.LEFT);
            extraClock.setForeground(SUB_CLOCK_COLOUR);
            extraClockLabels.add(extraClock);
        }

        clockReset = new JButton("Reset clock");
        clockReset.setOpaque(false);
        clockReset.setBorder(null);

        clock.setVisible(true);
        clockPause.setVisible(true);
        clockSub.setVisible(true);

        TotalScaleLayout tsl = new TotalScaleLayout(this);

        tsl.add(0, 0, 1, 0.4, clock);
        tsl.add(0, 0.4, 1, 0.2, clockSub);

        tsl.add(0.02, 0.7, 0.74, 0.1, extraClockLabels.get(0));
        tsl.add(0.02, 0.8, 0.74, 0.1, extraClockLabels.get(1));
        tsl.add(0.02, 0.9, 0.74, 0.1, extraClockLabels.get(2));

        tsl.add(0.75, 0.5, 0.25, 0.25, clockPause);
        tsl.add(0.75, 0.75, 0.25, 0.25, clockReset);

        clockReset.addActionListener(ActionBoard.clockReset);
        clockPause.addActionListener(ActionBoard.clockPause);

        this.setLayout(tsl);
        this.setVisible(true);
    }

    @SuppressWarnings("Duplicates")
    @Override
    public void update(AdvancedData data) {
        // Set the font
        clock.setFont(FontHelper.timeFont);
        clockSub.setFont(FontHelper.timeSubFont);

        clock.setText(Helper.formatTime(data.getRemainingGameTime(true)));

        Integer secondaryTime = data.getSecondaryTime(KICKOFF_BLOCKED_HIGHLIGHT_SECONDS - 1);
        if (secondaryTime != null) {
            if (data.gameState == GameStates.PLAYING) {
                clockSub.setText(Helper.formatTime(Math.max(0, secondaryTime)));
                clockSub.setForeground(secondaryTime <= 0
                        && clockSub.getForeground() != COLOR_HIGHLIGHT ? COLOR_HIGHLIGHT : SUB_CLOCK_COLOUR);
            } else {
                clockSub.setText(Helper.formatTime(secondaryTime));
                clockSub.setForeground(SUB_CLOCK_COLOUR);
            }
        } else {
            clockSub.setText("");
            clockSub.setForeground(SUB_CLOCK_COLOUR);
        }

        updateExtraClocks(data);

        clockReset.setVisible(ActionBoard.clockReset.isLegal(data));
        clockPause.setVisible(ActionBoard.clockPause.isLegal(data));
    }


    public void updateExtraClocks(AdvancedData data) {
        List<ExtraClock> extraClocks = data.gameClock.getExtraClocks();

        for (JLabel label : extraClockLabels) {
            label.setVisible(false);
        }

        for (int i = 0; i < Math.min(3, extraClocks.size()); i++) {
            ExtraClock extraClock = extraClocks.get(i);
            JLabel extraClockLabel = extraClockLabels.get(i);
            extraClockLabel.setFont(FontHelper.extraClockFont);

            extraClockLabel.setVisible(true);
            extraClockLabel.setText(extraClock.getLabel() + " " + Helper.formatTime(extraClock.getRemainingSeconds()));
        }
    }
}
