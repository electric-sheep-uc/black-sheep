package controller.action.ui;

import common.Log;
import controller.action.ActionType;
import controller.action.GCAction;
import data.states.AdvancedData;
import data.communication.GameControlData;
import data.Rules;
import data.values.GameStates;
import data.values.SecondaryGameStates;


/**
 * @author Michel Bartsch
 * 
 * This action means that a team get kickoff.
 */
public class KickOff extends GCAction
{
    /** On which side (0:left, 1:right) */
    private int side;
    
    
    /**
     * Creates a new KickOff action.
     * Look at the ActionBoard before using this.
     * 
     * @param side      On which side (0:left, 1:right)
     */
    public KickOff(int side)
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
        if (data.kickOffTeam == data.team[side].teamNumber) {
            return;
        }
        data.kickOffTeam = data.team[side].teamNumber;
        if ((Rules.league.kickoffChoice)
                && (data.secGameState == SecondaryGameStates.NORMAL)
                && (data.firstHalf == GameControlData.C_TRUE)
                && (data.gameState == GameStates.INITIAL)) {
            data.leftSideKickoff = (side == 0);
        }
        Log.state(data, "Kickoff " + data.team[side].teamColor);
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
        return (data.kickOffTeam == data.team[side].teamNumber)
                || ((Rules.league.kickoffChoice)
                    && (data.secGameState == SecondaryGameStates.NORMAL)
                    && (data.firstHalf == GameControlData.C_TRUE)
                    && (data.gameState == GameStates.INITIAL))
                || data.testmode;
    }
}