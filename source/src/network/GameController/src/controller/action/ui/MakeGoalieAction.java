package controller.action.ui;

import controller.action.ActionType;
import controller.action.GCAction;
import data.PlayerInfo;
import data.states.AdvancedData;
import data.values.Side;


public class MakeGoalieAction extends GCAction {

    private final Side side;
    private final int player;

    public MakeGoalieAction(Side side, int player) {
        super(ActionType.UI);
        this.player = player;
        this.side = side;
    }

    @Override
    public void perform(AdvancedData data) {
        // Set all players goalie prop to zero
        for (PlayerInfo pi : data.getTeam(this.side).player){
            pi.isGoalie = 0;
        }

        // Set the one being goalie
        data.getTeam(this.side).player[this.player].isGoalie = 1;
    }

    @Override
    public boolean isLegal(AdvancedData data) {
        return true;
    }
}
