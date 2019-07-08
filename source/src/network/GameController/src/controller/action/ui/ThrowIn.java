package controller.action.ui;

import data.values.SecondaryGameStates;

/**
 * @author Ludovic Hofer
 */
public class ThrowIn extends GameInterruption
{
    public ThrowIn(int side)
    {
        super(side, SecondaryGameStates.THROW_IN);
    }

}
