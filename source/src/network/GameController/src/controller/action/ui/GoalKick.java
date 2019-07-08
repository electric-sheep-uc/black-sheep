package controller.action.ui;

import data.values.SecondaryGameStates;

/**
 * @author Ludovic Hofer
 */
public class GoalKick extends GameInterruption
{
    public GoalKick(int side)
    {
        super(side, SecondaryGameStates.GOAL_KICK);
    }

}
