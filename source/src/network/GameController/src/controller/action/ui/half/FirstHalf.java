package controller.action.ui.half;

import common.Log;
import controller.action.ActionType;
import controller.action.GCAction;
import data.states.AdvancedData;
import data.communication.GameControlData;
import data.Rules;
import data.communication.TeamInfo;
import data.values.GameStates;
import data.values.SecondaryGameStates;
import data.values.TeamColors;

/**
 * @author Michel Bartsch
 * 
 * This action means that the half is to be set to the first half.
 */
public class FirstHalf extends GCAction
{
    /**
     * Creates a new FirstHalf action.
     * Look at the ActionBoard before using this.
     */
    public FirstHalf()
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
        if (data.firstHalf != GameControlData.C_TRUE || data.secGameState == SecondaryGameStates.PENALTYSHOOT) {
            data.firstHalf = GameControlData.C_TRUE;
            data.secGameState = SecondaryGameStates.NORMAL;
            data.changeSide();
            data.kickOffTeam = (data.leftSideKickoff ? data.team[0].teamNumber : data.team[1].teamNumber);
            data.kickOffReason = AdvancedData.KICKOFF_HALF;
            data.gameState = GameStates.INITIAL;
            // Don't set data.whenCurrentGameStateBegan, because it's used to count the pause
            Log.state(data, "1st Half");
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
        return ((data.firstHalf == GameControlData.C_TRUE)
                && (data.secGameState == SecondaryGameStates.NORMAL))
                || (data.testmode);
    }
    
    /**
     * Switches sides for the teams, both for first to second and also
     * second to first half if needed.
     * 
     * @param data      The current data to work on.
     */

}