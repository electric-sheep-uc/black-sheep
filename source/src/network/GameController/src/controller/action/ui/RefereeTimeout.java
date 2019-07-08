package controller.action.ui;

import common.Log;

import controller.action.ActionBoard;
import controller.action.ActionType;
import controller.action.GCAction;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.SecondaryGameStates;

public class RefereeTimeout extends GCAction
{
    public RefereeTimeout()
    {
        super(ActionType.UI);
    }

    @Override
    public void perform(AdvancedData data)
    {
        if (!data.refereeTimeout) {
            data.previousSecGameState = data.secGameState;
            data.secGameState = SecondaryGameStates.TIMEOUT;
            data.refereeTimeout = true;
            Log.setNextMessage("Referee Timeout");
            if (data.gameState == GameStates.PLAYING) {
                data.addTimeInCurrentState();
            }
            if (data.previousSecGameState == SecondaryGameStates.PENALTYSHOOT
                    && (data.gameState == GameStates.SET || data.gameState == GameStates.PLAYING)) {
                data.team[data.kickOffTeam == data.team[0].teamNumber ? 0 : 1].penaltyShot--;
            }
            
            data.gameState = GameStates.IMPOSSIBLE; //something impossible to force execution of next call
            ActionBoard.initial.perform(data);
        } else {
            data.secGameState = data.previousSecGameState;
            data.previousSecGameState = SecondaryGameStates.TIMEOUT;
            data.refereeTimeout = false;
            data.kickOffReason = AdvancedData.KICKOFF_TIMEOUT;
            Log.setNextMessage("End of Referee Timeout");
            if (data.secGameState != SecondaryGameStates.PENALTYSHOOT) {
                ActionBoard.ready.perform(data);
            }
        }
    }

    @Override
    public boolean isLegal(AdvancedData data)
    {
        return data.gameState != GameStates.FINISHED
                && !data.timeOutActive[0] && !data.timeOutActive[1];
    }

}
