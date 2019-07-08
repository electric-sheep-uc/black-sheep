package controller.action.ui;

import data.values.SecondaryGameStates;

/**
 * @author Michel Bartsch
 * 
 * This action means that a timeOut is to be taken or ending.
 */
public class PenaltyKick extends GameInterruption
{

    /**
     * Creates a new TimeOut action.
     * Look at the ActionBoard before using this.
     *
     * @param side      On which side (0:left, 1:right)
     */
    public PenaltyKick(int side)
    {
        super(side, SecondaryGameStates.PENALTYKICK);
    }
}