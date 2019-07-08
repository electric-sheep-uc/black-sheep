package controller.action.ui;

import java.util.ArrayList;

import common.Log;
import controller.EventHandler;
import controller.action.ActionType;
import controller.action.GCAction;
import controller.action.ui.penalty.Penalty;
import controller.action.ui.penalty.PickUpHL;
import controller.action.ui.penalty.Substitute;
import data.hl.HL;
import data.states.AdvancedData;
import data.states.AdvancedData.PenaltyQueueData;
import data.PlayerInfo;
import data.Rules;
import data.values.Penalties;

/**
 * @author Michel Bartsch
 * 
 * This action means that a player has been selected.
 */
public class Robot extends GCAction
{
    /** On which side (0:left, 1:right) */
    private int side;
    /** The players`s number, beginning with 0! */
    private int number;
    
    /**
     * Creates a new Robot action.
     * Look at the ActionBoard before using this.
     * 
     * @param side      On which side (0:left, 1:right)
     * @param number    The players`s number, beginning with 0!
     */
    public Robot(int side, int number)
    {
        super(ActionType.UI);
        this.side = side;
        this.number = number;
    }

    /**
     * Performs this action to manipulate the data (model).
     * 
     * @param data      The current data to work on.
     */
    @Override
    public void perform(AdvancedData data)
    {
        System.out.println("Penalizing");
        PlayerInfo player = data.team[side].player[number];
        if (player.penalty == Penalties.SUBSTITUTE && !isCoach(data)) {
            ArrayList<PenaltyQueueData> playerInfoList = data.penaltyQueueForSubPlayers.get(side);
            if (playerInfoList.isEmpty()) {
                player.penalty = Rules.league.substitutePenalty;
                data.whenPenalized[side][number] = data.getTime();
            } else {
                PenaltyQueueData playerInfo = playerInfoList.get(0);
                player.penalty = playerInfo.penalty;
                data.robotPenaltyCount[side][number] = playerInfo.penaltyCount;
                data.whenPenalized[side][number] = playerInfo.whenPenalized;
                playerInfoList.remove(0);
            }
            Log.state(data, "Entering Player " + data.team[side].teamColor + " " + (number+1));
        }
        else if (player.penalty == Penalties.NONE
                || (EventHandler.getInstance().lastUIEvent instanceof Penalty)
                || EventHandler.getInstance().lastUIEvent instanceof TeammatePushing) {
            EventHandler.getInstance().lastUIEvent.performOn(data, player, side, number);
        }
        else if (data.isServingPenalty[side][number]) {// If robot is currently serving penalty, reset penalty time
            data.whenPenalized[side][number] = data.getTime();
            Log.state(data, "Resetting penalty for " + data.team[side].teamColor + " " + (number+1));
        }
        else if (player.penalty != Penalties.NONE) {// Robot will now starts serving its penalty time
            data.whenPenalized[side][number] = data.getTime();
            data.isServingPenalty[side][number] = true;
            Log.state(data, "Start serving penalty for " + data.team[side].teamColor + " " + (number+1));
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
        return !data.ejected[side][number]
                && ((!(EventHandler.getInstance().lastUIEvent instanceof Penalty))
                && data.team[side].player[number].penalty != Penalties.NONE
                && (Rules.league.allowEarlyPenaltyRemoval || data.getRemainingPenaltyTime(side, number) == 0)
                && (data.team[side].player[number].penalty != Penalties.SUBSTITUTE || data.getNumberOfRobotsInPlay(side) < Rules.league.robotsPlaying)
                && !isCoach(data)
                || EventHandler.getInstance().lastUIEvent instanceof PickUpHL
                && data.team[side].player[number].penalty != Penalties.SUBSTITUTE
                || EventHandler.getInstance().lastUIEvent instanceof Substitute
                && data.team[side].player[number].penalty != Penalties.SUBSTITUTE
                && (!isCoach(data) && (Rules.league instanceof HL) || number != 0))
                || data.team[side].player[number].penalty == Penalties.NONE
                    && (EventHandler.getInstance().lastUIEvent instanceof Penalty)
                    && !(EventHandler.getInstance().lastUIEvent instanceof Substitute)
                    && (!isCoach(data))
                || (data.team[side].player[number].penalty == Penalties.NONE)
                    && (EventHandler.getInstance().lastUIEvent instanceof TeammatePushing)
                || data.testmode;
    }
    
    public boolean isCoach(AdvancedData data)
    {
        return Rules.league.isCoachAvailable && number == Rules.league.teamSize;
    }
}
