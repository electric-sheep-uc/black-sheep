package controller.ui.ui.components;

import common.TotalScaleLayout;
import controller.EventHandler;
import controller.action.ActionBoard;
import controller.action.GCAction;
import controller.action.ui.penalty.HLPushing;
import controller.action.ui.penalty.Penalty;

import controller.ui.ui.customized.ToggleButton;
import data.Rules;
import data.hl.HL;
import data.states.AdvancedData;
import data.values.Penalties;

import javax.swing.*;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by rkessler on 2017-03-29.
 */
public class PenaltyComponent extends AbstractComponent {

    private static final String PEN_INACTIVE = "Fallen / Inactive / Local Game Stuck";


    private Map<Penalties, JToggleButton> penaltyButtons;
    private ButtonGroup penaltyGroup;
    private JPanel penaltyButtonContainer;
    private TotalScaleLayout layout;

    public PenaltyComponent() {
        penaltyButtons = new HashMap<>();
        penaltyGroup = new ButtonGroup();
        penaltyButtonContainer = new JPanel();

        layout = new TotalScaleLayout(penaltyButtonContainer);
        penaltyButtonContainer.setLayout(layout);

        defineLayout();
    }

    private void addButtonByPenalty(Penalties pen, Penalty ballManipulation) {
        ToggleButton butt = new ToggleButton(pen.toString());
        butt.addActionListener(ballManipulation);
        penaltyButtons.put(pen, butt);
        penaltyGroup.add(butt);
    }

    public void defineLayout() {
        // TODO Customizable with inheritance
        if (Rules.league instanceof HL) {
            addButtonByPenalty(Penalties.HL_BALL_MANIPULATION, ActionBoard.ballManipulation);
            addButtonByPenalty(Penalties.HL_PHYSICAL_CONTACT, new HLPushing());
            addButtonByPenalty(Penalties.HL_PICKUP_OR_INCAPABLE, ActionBoard.pickUpHL);
            addButtonByPenalty(Penalties.SUBSTITUTE, ActionBoard.substitute);
        }
        penaltyButtonContainer.setVisible(true);

        // Add all penalty buttons to layout
        float height = (float) (1.0 / penaltyButtons.size());
        for (int i = 0; i < penaltyButtons.size(); i++) {
            ToggleButton tb = (ToggleButton) penaltyButtons.values().toArray()[i];
            layout.add(0, i * height, 1, height, tb);
        }

        this.add(penaltyButtonContainer);
        this.setVisible(true);
        this.setLayout(
                new BoxLayout(this, BoxLayout.Y_AXIS)
        );
    }

    @Override
    public void update(AdvancedData data) {
        // Clear current selection
        if (penaltyGroup != null) {
            penaltyGroup.clearSelection();
        }

        updatePenaltiesHL(data);
    }

    private void updatePenaltiesHL(AdvancedData data) {
        penaltyButtons.get(Penalties.HL_BALL_MANIPULATION).setEnabled(ActionBoard.ballManipulation.isLegal(data));
        penaltyButtons.get(Penalties.HL_PICKUP_OR_INCAPABLE).setEnabled(ActionBoard.pickUpHL.isLegal(data));
        penaltyButtons.get(Penalties.SUBSTITUTE).setEnabled(ActionBoard.substitute.isLegal(data));

        GCAction hightlightEvent = EventHandler.getInstance().lastUIEvent;

        penaltyButtons.get(Penalties.HL_BALL_MANIPULATION).setSelected(hightlightEvent == ActionBoard.ballManipulation);
        penaltyButtons.get(Penalties.HL_PHYSICAL_CONTACT).setSelected(new HLPushing().equals(hightlightEvent));
        penaltyButtons.get(Penalties.HL_PICKUP_OR_INCAPABLE).setSelected(hightlightEvent == ActionBoard.pickUpHL);
        penaltyButtons.get(Penalties.SUBSTITUTE).setSelected(hightlightEvent == ActionBoard.substitute);
    }
}
