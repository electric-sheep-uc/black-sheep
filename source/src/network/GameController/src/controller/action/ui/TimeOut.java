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
 * @author Michel Bartsch
 * 
 * This action means that a timeOut is to be taken or ending.
 */
public class TimeOut extends GCAction
{
    /** On which side (0:left, 1:right) */
    private int side;

    /**
     * Creates a new TimeOut action.
     * Look at the ActionBoard before using this.
     * 
     * @param side      On which side (0:left, 1:right)
     */
    public TimeOut(int side)
    {
        super(ActionType.UI);
        this.side = side;
    }

    /**
     * Performs this action to manipulate the data (model).
     * 
     * @param data      The current data to work on.
     */
    @Override
    public void perform(AdvancedData data)
    {
        if (!data.timeOutActive[side]) {
            data.previousSecGameState = data.secGameState;
            data.secGameState = SecondaryGameStates.TIMEOUT;
            data.timeOutActive[side] = true;
            data.timeOutTaken[side] = true;

            Log.setNextMessage("Timeout " + data.team[side].teamColor);
            Log.state(data, "End of Timeout " + data.team[side].teamColor);
            data.gameClock.setSecondaryClock(Rules.league.timeOutTime);
            data.gameState = GameStates.IMPOSSIBLE; // something impossible to force execution of next call
            ActionBoard.initial.perform(data);
        } else {
            data.gameClock.clearSecondaryClock();
            data.secGameState = data.previousSecGameState;
            data.previousSecGameState = SecondaryGameStates.TIMEOUT;
            data.timeOutActive[side] = false;
            data.kickOffReason = AdvancedData.KICKOFF_TIMEOUT;
            Log.setNextMessage("End of Timeout " + data.team[side].teamColor);
            if (data.secGameState != SecondaryGameStates.PENALTYSHOOT) {
                ActionBoard.ready.perform(data);
            }
        }
    }
    
    /**
     * Checks if this action is legal with the given data (model).
     * Illegal actions are not performed by the EventHandler.
     * 
     * @param data      The current data to check with.
     */
    @Override
    public boolean isLegal(AdvancedData data)
    {
      return data.timeOutActive[side]
            || ((data.gameState == GameStates.INITIAL ||
                  data.gameState == GameStates.READY ||
                  data.gameState == GameStates.SET)
                && !data.timeOutTaken[side]
                && !data.timeOutActive[side == 0 ? 1 : 0]
                && !(data.secGameState == SecondaryGameStates.TIMEOUT))
            || data.testmode;
    }
}