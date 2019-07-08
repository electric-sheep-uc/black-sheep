package controller.action.ui;

import controller.action.ActionType;
import controller.action.GCAction;
import data.states.AdvancedData;
import data.values.GameTypes;
import data.values.Side;

public class DropinPointDelta extends GCAction {

    private final Side side;
    private final int player;
    private final int delta;

    public DropinPointDelta(Side side, int player, int delta) {
        super(ActionType.UI);
        this.player = player;
        this.side = side;
        this.delta = delta;
    }

    @Override
    public void perform(AdvancedData data) {
        data.getTeam(this.side).player[this.player].dropInPoints += this.delta;
    }

    @Override
    public boolean isLegal(AdvancedData data) {
        return data.gameType == GameTypes.DROPIN || data.testmode;
    }
}
