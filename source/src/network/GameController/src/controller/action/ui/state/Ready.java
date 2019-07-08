package controller.action.ui.state;

import common.Log;
import controller.action.ActionType;
import controller.action.GCAction;
import data.states.AdvancedData;
import data.Rules;
import data.values.GameStates;
import data.values.SecondaryGameStates;


/**
 * @author Michel Bartsch
 * 
 * This action means that the state is to be set to ready.
 */
public class Ready extends GCAction
{
    /**
     * Creates a new Ready action.
     * Look at the ActionBoard before using this.
     */
    public Ready()
    {
        super(ActionType.UI);
    }

    /**
     * Performs this action to manipulate the data (model).
     * 
     * @param data      The current data to work on.
     */
    @Override
    public void perform(AdvancedData data)
    {
        if (data.gameState == GameStates.READY) {
            return;
        }
        if (Rules.league.returnRobotsInGameStoppages) {
            data.resetPenaltyTimes();
        }
        if (data.gameState == GameStates.PLAYING) {
            data.addTimeInCurrentState();
        }
        data.whenCurrentGameStateBegan = data.getTime();
        data.gameState = GameStates.READY;
        Log.state(data, "Ready");
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
        return ((data.gameState == GameStates.INITIAL)
              && !data.timeOutActive[0] 
              && !data.timeOutActive[1]
              && !data.refereeTimeout
              && (data.secGameState != SecondaryGameStates.PENALTYSHOOT))
            || (data.gameState == GameStates.READY)
            || data.testmode;
    }
}