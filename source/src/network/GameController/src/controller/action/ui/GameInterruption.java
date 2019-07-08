package controller.action.ui;

import common.Log;
import controller.action.ActionBoard;
import controller.action.ActionType;
import controller.action.GCAction;
import data.Rules;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.SecondaryGameStates;

/**
 * @author Ludovic Hofer
 *
 * This class allows to represents the action for all the game interruptions which behaves similarly such as
 * - Penalty Kick
 * - Direct Free Kick
 * - Indirect Free Kick
 *
 * Soon to be introduced
 * - Corner Kick
 * - Goal Kick
 * - Throw-in
 */
public class GameInterruption extends GCAction {

    /**
     * Which side has the advantage with this game interruption
     */
    private int side;

    /**
     * Secondary Game state associated with the action
     */
    private SecondaryGameStates secGameState;

    public GameInterruption(int side, SecondaryGameStates secGameState) {
        super(ActionType.UI);
        this.side = side;
        this.secGameState = secGameState;
    }

    /**
     * @return true if the game_interruption is in progress
     */
    public boolean isActive(AdvancedData data) {
        return data.secGameState == secGameState && data.secGameStateInfo.toByteArray()[0] == data.team[side].teamNumber;

    }

    @Override
    public void perform(AdvancedData data)
    {

        // If action has not been started, change secondary game state and initialize the status
        if (!isActive(data)) {
            data.previousSecGameState = data.secGameState;
            data.secGameState = secGameState;
            data.secGameStateInfo.setFreeKickData(data.team[side].teamNumber, (byte) 0);

            Log.setNextMessage(secGameState.toString() + " " + data.team[side].teamColor.toString());
            ActionBoard.clockPause.perform(data);
        } else {
            // GameInterruption is already happening, increment subMode
            byte team = data.secGameStateInfo.toByteArray()[0];
            byte subMode = data.secGameStateInfo.toByteArray()[1];

            switch(subMode) {
                case 0:
                    data.gameClock.setSecondaryClock(Rules.league.game_interruption_preparation_time);
                    data.secGameStateInfo.setFreeKickData(team, (byte) 1);
                    break;
                case 1:
                    data.gameClock.clearSecondaryClock();
                    data.secGameStateInfo.setFreeKickData(team, (byte) 2);
                    break;
                case 2:
                    data.secGameState = data.previousSecGameState;
                    data.previousSecGameState = secGameState;
                    data.secGameStateInfo.reset();
                    Log.setNextMessage("End " + secGameState.toString() + data.team[side].teamColor.toString());
                    data.gameClock.addExtraClock(secGameState.toString(), 10);
                    ActionBoard.clockPause.perform(data);
                    break;
            }
        }
    }

    @Override
    public boolean isLegal(AdvancedData data)
    {
        if (data.testmode) return true;
        if (isActive(data)) return true;
        boolean validGameState = data.gameState == GameStates.PLAYING;
        boolean validSecGameState = data.secGameState == SecondaryGameStates.NORMAL
                    || data.secGameState == SecondaryGameStates.OVERTIME;

        return validGameState && validSecGameState;
    }

    public SecondaryGameStates getSecGameState() {
        return secGameState;
    }
}
