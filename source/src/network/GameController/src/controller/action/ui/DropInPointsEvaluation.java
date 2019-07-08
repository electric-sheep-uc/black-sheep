package controller.action.ui;

import controller.action.ActionType;
import controller.action.GCAction;
import data.PlayerInfo;
import data.states.AdvancedData;
import data.values.GameTypes;
import data.values.Penalties;
import data.values.Side;

public class DropInPointsEvaluation extends GCAction {

    private final Side scoring_side;

    public DropInPointsEvaluation(Side scoring_side) {
        super(ActionType.UI);
        this.scoring_side = scoring_side;
    }

    @Override
    public void perform(AdvancedData data) {
        for(PlayerInfo pi : data.getTeam(this.scoring_side).player){
            if (pi.penalty == Penalties.NONE) {
                pi.dropInPoints += 1;
            }
        }

        for(PlayerInfo pi : data.getTeam(this.scoring_side.getOther()).player){
            pi.dropInPoints -= 1;
        }

        data.gameClock.addExtraClock("Add point for scoring robot!", 10);
    }

    @Override
    public boolean isLegal(AdvancedData data) {
        return true;
    }
}
