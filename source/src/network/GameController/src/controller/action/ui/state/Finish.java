package controller.action.ui.state;

import common.Log;
import controller.action.ActionType;
import controller.action.GCAction;
import data.Rules;
import data.states.AdvancedData;
import data.values.GameStates;
import data.values.SecondaryGameStates;


/**
 * @author Michel Bartsch
 *         <p>
 *         This action means that the state is to be set to finish.
 */
public class Finish extends GCAction {
    /**
     * Creates a new Finish action.
     * Look at the ActionBoard before using this.
     */
    public Finish() {
        super(ActionType.UI);
    }

    /**
     * Performs this action to manipulate the data (model).
     *
     * @param data The current data to work on.
     */
    @Override
    public void perform(AdvancedData data) {
        if (data.gameState == GameStates.FINISHED) {
            return;
        }
        if (Rules.league.returnRobotsInGameStoppages) {
            data.resetPenaltyTimes();
        }
        data.addTimeInCurrentState();
        data.whenCurrentGameStateBegan = data.getTime();
        data.gameState = GameStates.FINISHED;
        Log.state(data, "Finished");
    }

    /**
     * Checks if this action is legal with the given data (model).
     * Illegal actions are not performed by the EventHandler.
     *
     * @param data The current data to check with.
     */
    @Override
    public boolean isLegal(AdvancedData data) {
        // Can always click it when in test mode
        if (data.testmode) {
            return true;
        }

        // Cannot move to finish when we are in a penalty or free kick
        if (data.secGameState == SecondaryGameStates.PENALTYKICK ||
                data.secGameState == SecondaryGameStates.DIRECT_FREEKICK ||
                data.secGameState == SecondaryGameStates.INDIRECT_FREEKICK ||
                data.secGameState == SecondaryGameStates.CORNER_KICK ||
                data.secGameState == SecondaryGameStates.GOAL_KICK ||
                data.secGameState == SecondaryGameStates.THROW_IN) {
            return false;
        }

        // Otherwise we just make sure that we are not in initial
        return (data.gameState == GameStates.READY)
                || (data.gameState == GameStates.SET)
                || (data.gameState == GameStates.PLAYING)
                || (data.gameState == GameStates.FINISHED);
    }
}