package controller.action.ui.half;

import common.Log;
import controller.action.ActionType;
import controller.action.GCAction;
import data.states.AdvancedData;
import data.communication.GameControlData;
import data.Rules;
import data.values.GameStates;
import data.values.GameTypes;
import data.values.SecondaryGameStates;


/**
 * @author Michel Bartsch
 * 
 * This action means that a penalty shoot is to be starting.
 */
public class PenaltyShoot extends GCAction
{
    /**
     * Creates a new PenaltyShoot action.
     * Look at the ActionBoard before using this.
     */
    public PenaltyShoot()
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
        if (data.secGameState != SecondaryGameStates.PENALTYSHOOT) {
            data.secGameState = SecondaryGameStates.PENALTYSHOOT;
            // Don't set data.whenCurrentGameStateBegan, because it's used to count the pause
            data.gameState = GameStates.INITIAL;
            data.timeBeforeCurrentGameState = 0;
            data.kickOffReason = AdvancedData.KICKOFF_PENALTYSHOOT;
            data.resetPenalties();
            if (Rules.league.timeOutPerHalf) {
                data.timeOutTaken = new boolean[] {false, false};
            }
            Log.state(data, "Penalty Shoot-out");
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
        // Penalty shootout is not possible in round robin
        if (data.gameType == GameTypes.ROUNDROBIN){
            return false;
        }

        return (data.secGameState == SecondaryGameStates.PENALTYSHOOT)
          || (data.previousSecGameState == SecondaryGameStates.PENALTYSHOOT)
          || ((data.firstHalf != GameControlData.C_TRUE)
            && (data.gameState == GameStates.FINISHED))
          || (data.testmode);
    }
}