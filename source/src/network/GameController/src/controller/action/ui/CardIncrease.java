package controller.action.ui;

import common.Log;
import controller.action.ActionType;
import controller.action.GCAction;
import data.states.AdvancedData;
import data.values.Side;

import java.awt.*;

/**
 * Created by rkessler on 2017-06-11.
 */
public class CardIncrease extends GCAction {

    private final Side side;
    private final int player;
    private final Color color;

    public CardIncrease(Side side, int player, Color color) {
        super(ActionType.UI);
        this.player = player;
        this.side = side;
        this.color = color;
    }

    private void giveRedCard(AdvancedData data){
        int currentCount = data.team[side.value()].player[player].redCardCount;

        if (currentCount == 0){
            data.team[side.value()].player[player].redCardCount = 1;
            Log.state(data, "Added red card");
        }
    }

    private void giveYellowCard(AdvancedData data){
        int currentCount = data.team[side.value()].player[player].yellowCardCount;

        if (currentCount < 2){
            currentCount += 1;
            data.team[side.value()].player[player].yellowCardCount = (byte) currentCount;
            Log.state(data, "Added yellow card");
        }

        if (currentCount == 2){
            giveRedCard(data);
        }
    }

    @Override
    public void perform(AdvancedData data) {
        if (this.color == Color.YELLOW) {
            giveYellowCard(data);
        }
        if (this.color == Color.RED) {
            giveRedCard(data);
        }
    }

    @Override
    public boolean isLegal(AdvancedData data) {
        return true;
    }

}
