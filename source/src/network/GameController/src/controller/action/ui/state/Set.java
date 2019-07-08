package controller.action.ui.state;

import common.Log;
import controller.action.ActionType;
import controller.action.GCAction;
import controller.action.ui.half.FirstHalf;
import data.states.AdvancedData;
import data.Rules;
import data.values.GameStates;
import data.values.GameTypes;
import data.values.SecondaryGameStates;

/**
 * @author Michel Bartsch
 *
 * This action means that the state is to be set to set.
 */
public class Set extends GCAction {

    /**
     * Creates a new Set action. Look at the ActionBoard before using this.
     */
    public Set() {
        super(ActionType.UI);
    }

    /**
     * Performs this action to manipulate the data (model).
     *
     * @param data The current data to work on.
     */
    @Override
    public void perform(AdvancedData data) {
        if (data.gameState == GameStates.SET) {
            return;
        }
        if (Rules.league.returnRobotsInGameStoppages) {
            data.resetPenaltyTimes();
        }
        if ((data.gameType != GameTypes.PLAYOFF) && data.timeBeforeCurrentGameState != 0) {
            data.addTimeInCurrentState();
        }
        data.whenCurrentGameStateBegan = data.getTime();

        if (data.secGameState == SecondaryGameStates.PENALTYSHOOT) {
            data.timeBeforeCurrentGameState = 0;
            if (data.gameState != GameStates.INITIAL) {
                data.kickOffTeam = data.team[data.kickOffTeam == data.team[0].teamNumber ? 1 : 0].teamNumber;
                data.changeSide();
            }
            if (data.gameState != GameStates.PLAYING) {
                data.team[data.team[0].teamNumber == data.kickOffTeam ? 0 : 1].penaltyShot++;
            }
        }
        data.gameState = GameStates.SET;
        Log.state(data, "Set");
    }

    /**
     * Checks if this action is legal with the given data (model). Illegal
     * actions are not performed by the EventHandler.
     *
     * @param data The current data to check with.
     */
    @Override
    public boolean isLegal(AdvancedData data) {
        return (data.gameState == GameStates.READY)
                || (data.gameState == GameStates.SET)
                || ((data.secGameState == SecondaryGameStates.PENALTYSHOOT)
                && ((data.gameState != GameStates.PLAYING)
                || (Rules.league.penaltyShotRetries))
                && !data.timeOutActive[0]
                && !data.timeOutActive[1]
                && !data.refereeTimeout)
                || data.testmode;
    }
}
