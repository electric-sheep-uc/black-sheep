package controller.action.ui;

import data.values.SecondaryGameStates;

/**
 * @author Ludovic Hofer
 */
public class CornerKick extends GameInterruption
{
    public CornerKick(int side)
    {
        super(side, SecondaryGameStates.CORNER_KICK);
    }

}
